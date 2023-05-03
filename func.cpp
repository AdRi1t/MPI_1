#include <mpi.h>
#include <iostream>
#include <fstream>
#include "func.hpp"

C_matrix::C_matrix(unsigned int n, unsigned int m)
{
    this->row = n;
    this->column = m;
    data = (double *)malloc(m * n * sizeof(double));
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
            resultFile << this->data[i * this->column + j] << " ";
        }
        resultFile << std::endl;
    }
    resultFile.close();
}

C_matrix::~C_matrix()
{
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
            resultFile << tab[i * m + j] << " ";
        }
        resultFile << std::endl;
    }
    resultFile.close();
}
