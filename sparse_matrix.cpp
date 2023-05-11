#include <mpi.h>
#include <string>
#include <iostream>
#include <fstream>
#include "sparse_matrix.hpp"

extern "C"
{
#include "mmio.h"
}

CSR_matrix::CSR_matrix(double *data, unsigned int dim)
{
    row_first_index = new unsigned int[dim];
    double *tmp_non_zero = new double[dim * dim];
    unsigned int nb_no_zero = 0;
    unsigned int i, j;
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            if (data[i * dim + j] != 0)
            {
                tmp_non_zero[nb_no_zero] = data[i * dim + j];
                nb_no_zero += 1;
            }
        }
    }
    data = new double[nb_no_zero];
    for (i = 0; i < nb_no_zero; i++)
    {
        data[i] = tmp_non_zero[i];
    }
    delete[] tmp_non_zero;
}

CSR_matrix::~CSR_matrix()
{
    delete[] row_first_index;
}

COO_matrix::COO_matrix(unsigned int size)
{
    this->size = size;
    this->nb_elements = 0;
}

void COO_matrix::load_from_file(std::string mm_file_name)
{
    FILE *mm_file;
    MM_typecode matcode;
    int nb_row, nb_column, nb_data;
    int ret_code;
    nb_row = 0;
    nb_column = 0;
    nb_data = 0;
    ret_code = 0;

    mm_file = fopen(mm_file_name.c_str(), "r");
    if (mm_file == NULL)
    {
        std::cerr << "Could not open file: " << mm_file_name << std::endl;
    }
    if (mm_read_banner(mm_file, &matcode) != 0)
    {
        std::cerr << "Could not process Matrix Market banner" << std::endl;
    }

    // Obtain number of rows number of columns and number of elements
    if ((ret_code = mm_read_mtx_crd_size(mm_file, &nb_row, &nb_column, &nb_data)) != 0)
    {
        std::cerr << "Could not process Matrix Market dimensions" << std::endl;
    }
    size = nb_row;
    nb_elements = nb_data;
    row = new unsigned int[nb_data];
    column = new unsigned int[nb_data];
    data = new double[nb_data];

    // Read the elements of the file
    for (int i = 0; i < nb_data; i++)
    {
        fscanf(mm_file, "%d %d %lg\n", &row[i], &column[i], &data[i]);
        row[i]--;
        column[i]--;
    }
}

void COO_matrix::init_random_sparse(float p)
{
    unsigned int k = 0;
    nb_elements = int(p * size * size);
    row = new unsigned int[nb_elements];
    column = new unsigned int[nb_elements];
    data = new double[nb_elements];

    for (unsigned int i = 0; k < nb_elements && i < size; i++)
    {
        for (unsigned int j = 0; k < nb_elements && j < size; j++)
        {
            if (rand() % 100 < p * 100)
            {
                row[k] = i;
                column[k] = j;
                data[k] = ((double)rand() / (double)RAND_MAX) * 10;
                k++;
            }
        }
    }
}

void COO_matrix::deliver_sub_matrix(unsigned int rank, unsigned int nb_proc)
{
    unsigned int sub_size;
    if (rank == 0)
    {
        sub_size = int(nb_elements / nb_proc) + nb_elements % nb_proc;
    }
    else
    {
        sub_size = int(nb_elements / nb_proc);
    }
    for (unsigned int i = 1; i < nb_proc; i++)
    {
        int shift_value = sub_size * i + nb_elements % nb_proc;
        MPI_Send(&nb_elements, 1, MPI_UNSIGNED, i, 600, MPI_COMM_WORLD);
        MPI_Send(&size, 1, MPI_UNSIGNED, i, 601, MPI_COMM_WORLD);
        MPI_Send((row + shift_value), sub_size, MPI_UNSIGNED, i, 602, MPI_COMM_WORLD);
        MPI_Send((column + shift_value), sub_size, MPI_UNSIGNED, i, 603, MPI_COMM_WORLD);
        MPI_Send((data + shift_value), sub_size, MPI_DOUBLE, i, 604, MPI_COMM_WORLD);
    }
    unsigned int *tmp_row = new unsigned int[sub_size];
    unsigned int *tmp_column = new unsigned int[sub_size];
    double *tmp_data = new double[sub_size];
    std::copy(row, row + (sub_size), tmp_row);
    std::copy(column, column + (sub_size), tmp_column);
    std::copy(data, data + (sub_size), tmp_data);
    row = tmp_row;
    column = tmp_column;
    data = tmp_data;
}

void COO_matrix::receives_sub_matrix(unsigned int rank, unsigned int nb_proc)
{
    MPI_Status status[5];
    unsigned int sub_size;

    MPI_Recv(&nb_elements, 1, MPI_UNSIGNED, 0, 600, MPI_COMM_WORLD, &(status[0]));
    
    if (rank == 0)
    {
        sub_size = nb_elements / nb_proc + nb_elements % nb_proc;
    }
    else
    {
        sub_size = nb_elements / nb_proc;
    }
    std::cout << "sub size " << sub_size << std::endl;

    if (rank != 0)
    {
        row = new unsigned int[sub_size];
        column = new unsigned int[sub_size];
        data = new double[sub_size];
        nb_elements = sub_size;
        MPI_Recv(&size, 1, MPI_UNSIGNED, 0, 601, MPI_COMM_WORLD, &(status[1]));
        MPI_Recv(row, sub_size, MPI_UNSIGNED, 0, 602, MPI_COMM_WORLD, &(status[2]));
        MPI_Recv(column, sub_size, MPI_UNSIGNED, 0, 603, MPI_COMM_WORLD, &(status[3]));
        MPI_Recv(data, sub_size, MPI_DOUBLE, 0, 604, MPI_COMM_WORLD, &(status[4]));
    }
}

void COO_matrix::dump(std::string file_name)
{
    std::ofstream resultFile;
    int w_rank(-1);
    unsigned int k(0);
    MPI_Comm_rank(MPI_COMM_WORLD, &w_rank);
    file_name += std::to_string(w_rank);
    file_name += ".txt";
    resultFile.open(file_name, std::ios::out);
    for (unsigned int i = 0; i < size; i++)
    {
        for (unsigned int j = 0; j < size; j++)
        {
            for (k = 0; k < nb_elements; k++)
            {
                if (row[k] == i && column[k] == j)
                {
                    resultFile.width(6);
                    resultFile.precision(3);
                    resultFile << data[k] << " ";
                    k++;
                    break;
                }
            }
            if (k == nb_elements)
            {
                resultFile.width(6);
                resultFile << " 0 "
                           << " ";
            }
        }
        resultFile << std::endl;
    }
    resultFile.close();
}

COO_matrix::~COO_matrix()
{
    delete[] row;
    delete[] column;
    delete[] data;
}


