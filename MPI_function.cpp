#include <mpi.h>
#include <iostream>
#include "MPI_function.hpp"

// Generates a test matrix and distributes it to the other core
double *deliver_sub_matrix(double *data_matrix, unsigned int matrix_size, int nb_proc)
{
    int world_rank(-1);
    double *sub_matrix;
    int nb_row = matrix_size / nb_proc;
    int last_nb_row = matrix_size % nb_proc;

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == 0)
    {
        for (int i = 1; i < nb_proc; i++)
        {
            std::cout << "row number for sub matrix " << i << ": " << nb_row << std::endl;
            int shift_value = nb_row * i * matrix_size + last_nb_row * matrix_size;
            MPI_Send(&matrix_size, 1, MPI_UNSIGNED, i, SUB_MATRIX_SIZE_TAG, MPI_COMM_WORLD);
            MPI_Send((data_matrix + shift_value), nb_row * matrix_size, MPI_DOUBLE, i, SUB_MATRIX_TAG, MPI_COMM_WORLD);
        }
        std::cout << "row number for sub matrix 0"
                  << ": " << (nb_row + last_nb_row) << std::endl;
        sub_matrix = new double[matrix_size * (nb_row + last_nb_row)];
        std::copy(data_matrix, data_matrix + ((nb_row + last_nb_row) * matrix_size), sub_matrix);
    }

    return sub_matrix;
}

// All other cores receive their data
double *receives_sub_matrix(unsigned int *matrix_size, int nb_proc)
{
    int world_rank(-1);
    int nb_row;
    double *sub_matrix;
    
    MPI_Status status;

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank != 0)
    {
        MPI_Recv(matrix_size, 1, MPI_UNSIGNED, 0, SUB_MATRIX_SIZE_TAG, MPI_COMM_WORLD, &status);
        nb_row = *matrix_size / nb_proc;
        sub_matrix = new double[(*matrix_size) * nb_row];
        
        MPI_Recv(sub_matrix, nb_row * (*matrix_size), MPI_DOUBLE, 0, SUB_MATRIX_TAG, MPI_COMM_WORLD, &status);
    }
    return sub_matrix;
}

