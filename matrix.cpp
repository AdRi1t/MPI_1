#include <mpi.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "matrix.hpp"

extern "C"
{
#include "mmio.h"
}

double *PMV(double *matrix, double *vector, unsigned int n, unsigned int m)
{
    unsigned int i, j;
    double *result = new double[n];
    for (i = 0; i < n; i++)
    {
        result[i] = 0;
        for (j = 0; j < m; j++)
        {
            result[i] += matrix[i * m + j] * vector[j];
        }
    }
    return result;
}

double *init_matrix(unsigned int n, unsigned int m)
{
    srand(1337);
    double *tab = new double[n * m];

    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
        {
            tab[i * m + j] = ((double)rand() / (double)RAND_MAX) * 10;
        }
    }

    return tab;
}

void dump_result(double *tab, unsigned n, unsigned int m, std::string f_name)
{
    std::ofstream resultFile;
    int w_rank(-1);
    MPI_Comm_rank(MPI_COMM_WORLD, &w_rank);
    f_name += std::to_string(w_rank);
    f_name += ".txt";
    resultFile.open(f_name, std::ios::out);
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
        {
            resultFile.width(6);
            resultFile.precision(4);
            resultFile << tab[i * m + j] << " ";
        }
        resultFile << std::endl;
    }
    resultFile.close();
}

double *read_from_file(std::string file_name, unsigned int *n, unsigned int *m)
{
    std::ifstream input_file;
    char *line;
    double *data;
    unsigned int i;
    line = new char[4096];
    input_file.open(file_name, std::ios::in);

    input_file >> line;
    *n = strtol(line, nullptr, 10);
    input_file >> line;
    *m = strtol(line, nullptr, 10);
    i = 0;

    if (*n != 0 && *m != 0)
    {
        data = new double[(*n) * (*m)];
    }

    while (input_file.eof() != true && i != (*n) * (*m))
    {
        input_file >> line;
        data[i] = strtod(line, nullptr);
        i++;
    }

    input_file.close();
    return data;
}

double *read_from_file_mm(std::string file_name, unsigned int *n, unsigned int *m)
{
    FILE *mm_file;
    MM_typecode matcode;
    double *sparse_data;
    double *data_matrix;
    unsigned int *row;
    unsigned int *column;
    int nb_row, nb_column, nb_data;
    int ret_code;
    nb_row = 0;
    nb_column = 0;
    nb_data = 0;
    ret_code = 0;

    mm_file = fopen(file_name.c_str(), "r");
    if (mm_file == NULL)
    {
        std::cerr << "Could not open file: " << file_name << std::endl;
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
    *m = nb_column ;
    *n = nb_row ;
    row = new unsigned int[nb_data];
    column = new unsigned int[nb_data];
    sparse_data = new double[nb_data];
    data_matrix = new double[(*n) * (*n)];
    // Read the elements of the file
    for (int i = 0; i < nb_data; i++)
    {
        fscanf(mm_file, "%d %d %lg\n", &row[i], &column[i], &sparse_data[i]);
        row[i]--;
        column[i]--;
    }
    // Create data matrix
    for (int i = 0; i < nb_row; i++)
    {
        for (int j = 0; j < nb_column; j++)
        {
            data_matrix[i * nb_row + j] = 0;
        }
    }
    for (int i = 0; i < nb_data; i++)
    {
        data_matrix[row[i] * nb_row + column[i]] = sparse_data[i];
    }
    fclose(mm_file);
    delete[] row;
    delete[] column;
    delete[] sparse_data;
    
    return data_matrix;
}

void print_help()
{
    std::cout.width(18);
    std::cout << std::left << "pmv_mpi";
    std::cout << std::right << " Size of matrix or source file " << std::endl;
    std::cout.width(18);
    std::cout << std::left << " -n ";
    std::cout << std::right << " Specify the dimension of the square matrix " << std::endl;
    std::cout.width(18);
    std::cout << std::left << " -f ";
    std::cout << std::right << " Specify the name of the input file " << std::endl;
    std::cout.width(18);
    std::cout << std::left << " -d ";
    std::cout << std::right << " Create the matrix files generated during processing in a human-readable format " << std::endl;
    std::cout.width(18);
    std::cout << std::left << " -c ";
    std::cout << std::right << " Use COO format to store matrices in memory " << std::endl;
}

double *init_sparse_matrix(unsigned int n, unsigned int m, float p)
{
    srand(1337);
    double *tab = new double[n * m];

    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++)
        {
            if (rand() % 100 < p * 100)
            {
                tab[i * m + j] = ((double)rand() / (double)RAND_MAX) * 10;
            }
            else
            {
                tab[i * m + j] = 0;
            }
        }
    }

    return tab;
}