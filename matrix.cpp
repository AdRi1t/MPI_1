#include <mpi.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "matrix.hpp"

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
            }else{
                tab[i * m + j] = 0;
            }
        }
    }

    return tab;
}