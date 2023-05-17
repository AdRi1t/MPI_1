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
    // delete[] row_first_index;
}

COO_matrix::COO_matrix(unsigned int size)
{
    this->nb_row = size;
    this->nb_col = size;
    this->nb_elements = 0;
}

COO_matrix::COO_matrix(unsigned int size, float p)
{
    srand(1337);
    unsigned int k = 0;
    this->nb_row = size;
    this->nb_col = size;
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
    nb_elements = k;
}

COO_matrix::COO_matrix(unsigned int n, unsigned int m, float p)
{
    srand(1337);
    unsigned int k = 0;
    this->nb_row = n;
    this->nb_col = m;
    nb_elements = int(p * n * m);
    row = new unsigned int[nb_elements];
    column = new unsigned int[nb_elements];
    data = new double[nb_elements];
    for (unsigned int i = 0; k < nb_elements && i < nb_row; i++)
    {
        for (unsigned int j = 0; k < nb_elements && j < nb_col; j++)
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
    nb_elements = k;
}

void COO_matrix::free()
{
    nb_col = 0;
    nb_row = 0;
    nb_elements = 0;
    delete[] row;
    delete[] column;
    delete[] data;
}

COO_matrix::~COO_matrix()
{
}

unsigned int COO_matrix::getNb_row(void) const
{
    return nb_row;
}

unsigned int COO_matrix::getNb_col(void) const
{
    return nb_col;
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
    this->nb_col = nb_column;
    this->nb_row = nb_row;
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
    fclose(mm_file);
}

COO_matrix COO_matrix::deliver_sub_matrix(unsigned int rank, unsigned int nb_proc)
{
    unsigned int sub_size;
    unsigned int extra_size;
    extra_size = nb_elements % nb_proc;
    sub_size = int(nb_elements / nb_proc);

    // std::cout << "sub size: " << sub_size << std::endl;
    // std::cout << "extra size: " << extra_size << std::endl;

    for (unsigned int i = 1; i < nb_proc; i++)
    {
        int shift_value = sub_size * i + extra_size;
        MPI_Send(&nb_elements, 1, MPI_UNSIGNED, i, COO_NB_ELEMENTS, MPI_COMM_WORLD);
        MPI_Send(&nb_row, 1, MPI_UNSIGNED, i, COO_SIZE, MPI_COMM_WORLD);
        MPI_Send((row + shift_value), sub_size, MPI_UNSIGNED, i, COO_ROW, MPI_COMM_WORLD);
        MPI_Send((column + shift_value), sub_size, MPI_UNSIGNED, i, COO_COLUMN, MPI_COMM_WORLD);
        MPI_Send((data + shift_value), sub_size, MPI_DOUBLE, i, COO_DATA, MPI_COMM_WORLD);
    }
    unsigned int *tmp_row = new unsigned int[sub_size + extra_size];
    unsigned int *tmp_column = new unsigned int[sub_size + extra_size];
    double *tmp_data = new double[sub_size + extra_size];
    std::copy(this->row, this->row + (sub_size + extra_size), tmp_row);
    std::copy(this->column, this->column + (sub_size + extra_size), tmp_column);
    std::copy(this->data, this->data + (sub_size + extra_size), tmp_data);
    delete[] this->row;
    delete[] this->column;
    delete[] this->data;
    
    this->nb_elements = (sub_size + extra_size);
    this->row = tmp_row;
    this->column = tmp_column;
    this->data = tmp_data;
    return *this;
}

void COO_matrix::receives_sub_matrix(unsigned int rank, unsigned int nb_proc)
{
    MPI_Status status[5];
    unsigned int sub_size;
    unsigned int extra_size;

    MPI_Recv(&nb_elements, 1, MPI_UNSIGNED, 0, COO_NB_ELEMENTS, MPI_COMM_WORLD, &(status[0]));

    extra_size = nb_elements % nb_proc;
    sub_size = int(nb_elements / nb_proc);

    if (rank != 0)
    {
        row = new unsigned int[sub_size];
        column = new unsigned int[sub_size];
        data = new double[sub_size];
        nb_elements = sub_size;
        MPI_Recv(&nb_row, 1, MPI_UNSIGNED, 0, COO_SIZE, MPI_COMM_WORLD, &(status[1]));
        nb_col = nb_row;
        MPI_Recv(row, sub_size, MPI_UNSIGNED, 0, COO_ROW, MPI_COMM_WORLD, &(status[2]));
        MPI_Recv(column, sub_size, MPI_UNSIGNED, 0, COO_COLUMN, MPI_COMM_WORLD, &(status[3]));
        MPI_Recv(data, sub_size, MPI_DOUBLE, 0, COO_DATA, MPI_COMM_WORLD, &(status[4]));
    }
}

void COO_matrix::bcast_vector(unsigned int rank)
{
    MPI_Bcast(&nb_row, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    MPI_Bcast(&nb_col, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    MPI_Bcast(&nb_elements, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    if (rank != 0)
    {
        row = new unsigned int[nb_elements];
        column = new unsigned int[nb_elements];
        data = new double[nb_elements];
    }
    MPI_Bcast(row, nb_elements, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    MPI_Bcast(column, nb_elements, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    MPI_Bcast(data, nb_elements, MPI_DOUBLE, 0, MPI_COMM_WORLD);
}

// To do
COO_matrix COO_matrix::pmv2(const COO_matrix &vector)
{
    // Distrib vector
}

COO_matrix COO_matrix::pmv(const COO_matrix &vector)
{
    COO_matrix result(0);
    result.nb_col = 1;
    result.nb_row = vector.nb_row;
    result.nb_elements = vector.nb_elements;
    result.row = new unsigned int[vector.nb_elements];
    result.column = new unsigned int[vector.nb_elements];
    result.data = new double[vector.nb_elements];

    for (unsigned int i = 0; i < vector.nb_row; i++)
    {
        result.data[i] = 0;
        result.row[i] = i;
        result.column[i] = 0;
    }
    // Matrix elements
    for (unsigned int k = 0; k < this->nb_elements; k++)
    {
        result.data[this->row[k]] += this->data[k] * vector.data[column[k]];
    }
    return result;
}

COO_matrix COO_matrix::gather_result(unsigned int rank)
{
    COO_matrix result(0);
    result.nb_row = this->nb_row;
    result.nb_col = this->nb_col;
    result.nb_elements = this->nb_elements;
    result.row = new unsigned int[result.nb_elements];
    result.column = new unsigned int[result.nb_elements];
    result.data = new double[result.nb_elements];
    result.row = this->row;
    result.column = this->column;
    MPI_Reduce(this->data, result.data, this->nb_elements, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    return result;
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
    resultFile << nb_row << " x " << nb_col << " : " << nb_elements << std::endl;
    for (k = 0; k < nb_elements; k++)
    {
        resultFile << row[k] << " " << column[k] << " " << data[k] << std::endl;
    }
    resultFile.close();
}

void COO_matrix::readable_output(std::string file_name)
{
    std::ofstream resultFile;
    int w_rank(-1);
    unsigned int k(0);
    MPI_Comm_rank(MPI_COMM_WORLD, &w_rank);
    file_name += std::to_string(w_rank);
    file_name += ".txt";
    resultFile.open(file_name, std::ios::out);
    for (unsigned int i = 0; i < this->nb_row; i++)
    {
        for (unsigned int j = 0; j < this->nb_col; j++)
        {
            if (this->row[k] == i && this->column[k] == j)
            {
                resultFile.width(6);
                resultFile.precision(4);
                resultFile << this->data[k] << " ";
                k++;
            }
            else
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
