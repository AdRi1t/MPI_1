#include <mpi.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include "func.hpp"

int main(int argc, char *argv[])
{
    int matrix_size = 0;
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <size matrix> [dump] \n", argv[0]);
        return 1;
    }
    else
    {
        matrix_size = atoi(argv[1]);
    }
    MPI_Init(&argc, &argv);

    double *sub_matrix;
    double *sub_result;
    double *vector;
    int nb_proc(-1);
    int world_rank(-1);

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    std::cout << "World rank " << world_rank << std::endl;

    MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);

    int nb_row = matrix_size / nb_proc;
    int last_nb_row = matrix_size % nb_proc;

    // Generates a test matrix and distributes it to the other core
    if (world_rank == 0)
    {
        double *data_matrix = init_matrix(matrix_size, matrix_size);
        dump_result(data_matrix, matrix_size, matrix_size, "Data");
        vector = init_matrix(matrix_size, 1);
        for (int i = 1; i < nb_proc; i++)
        {
            std::cout << "row number for sub matrix " << i << ": " << nb_row << std::endl;
            int shift_value = nb_row * i * matrix_size + last_nb_row * matrix_size;
            MPI_Send((data_matrix + shift_value), nb_row * matrix_size, MPI_DOUBLE, i, 101, MPI_COMM_WORLD);
        }
        std::cout << "row number for sub matrix 0"
                  << ": " << (nb_row + last_nb_row) << std::endl;
        sub_matrix = (double *)malloc(matrix_size * (nb_row + last_nb_row) * sizeof(double));
        std::copy(data_matrix, data_matrix + ((nb_row + last_nb_row) * matrix_size), sub_matrix);
    }
    else
    {
        vector = (double *)malloc(matrix_size * sizeof(double));
    }

    // All other cores receive their data
    if (world_rank != 0)
    {
        sub_matrix = (double *)malloc(matrix_size * nb_row * sizeof(double));
        MPI_Recv(sub_matrix, nb_row * matrix_size, MPI_DOUBLE, 0, 101, MPI_COMM_WORLD, nullptr);
    }

    // Send the vector to everyone
    MPI_Bcast(vector, matrix_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (world_rank == 0)
    {
        sub_result = PMV(sub_matrix, vector, nb_row+last_nb_row, matrix_size);
    }else{
        sub_result = PMV(sub_matrix, vector, nb_row, matrix_size);
    }
    if (argc >= 3)
    {
        if ("dump" == std::string(argv[2]))
        {
            if (world_rank != 0)
            {
                dump_result(sub_matrix, nb_row, matrix_size, "sub_matrix_");
                dump_result(sub_result, nb_row, 1, "sub_result_");
            }
            else
            {
                dump_result(vector, matrix_size, 1, "vector");
                dump_result(sub_matrix, nb_row + last_nb_row, matrix_size, "sub_matrix_");
                dump_result(sub_result, nb_row + last_nb_row, 1, "sub_result_");
            }
        }
    }
    MPI_Finalize();
    return 0;
}
