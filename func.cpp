#include <mpi.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "func.hpp"

C_matrix::C_matrix(unsigned int n, unsigned int m)
{
    this->row = n;
    this->column = m;
    data = (double *)malloc(m * n * sizeof(double));
}

C_matrix::C_matrix()
{
    this->row = 0;
    this->column = 0;
}

void C_matrix::dump(std::string f_name)
{
    std::ofstream resultFile;
    int w_rank(-1);
    MPI_Comm_rank(MPI_COMM_WORLD, &w_rank);
    f_name += std::to_string(w_rank);
    f_name += ".txt";
    resultFile.open(f_name, std::ios::out);
    for (unsigned int i = 0; i < this->row; i++)
    {
        for (unsigned int j = 0; j < this->column; j++)
        {
            resultFile.width(8);
            resultFile << std::to_string(this->data[i * this->column + j]) << "  ";
        }
        resultFile << std::endl;
    }
    resultFile.close();
}

int C_matrix::get_column()
{
    return column;
}

int C_matrix::get_row()
{
    return row;
}

C_matrix::~C_matrix()
{
    free(this->data);
    this->row = 0;
    this->column = 0;
}

double *PMV(double *matrix, double *vector, unsigned int n, unsigned int m)
{
    unsigned int i, j;
    double *result = (double *)malloc(n * sizeof(double));
    for (i = 0; i < n; i++)
    {
        result[i] = 0;
        for (j = 0; j < m; j++)
        {
           result[i] += matrix[i*m + j] * vector[j];
        }
    }
    return result;
}

double *init_matrix(unsigned int n, unsigned int m)
{
    srand(1337);
    double *tab = (double *)malloc(n * m * sizeof(double));

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
