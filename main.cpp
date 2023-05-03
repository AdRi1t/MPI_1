#include <mpi.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include "func.hpp"

int main(int argc, char *argv[])
{
    int matrix_size = 0;
    double *sub_matrix;
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

    int nb_proc(-1);
    int world_rank(-1);

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    std::cout << " world rank " << world_rank << std::endl;

    MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);

    int nb_row = matrix_size / nb_proc;
    int last_nb_row = matrix_size % nb_proc;

    // Generates a test matrix and distributes it to the other core
    if (world_rank == 0)
    {
        double *data_matrix = init_matrix(matrix_size, matrix_size);
        dump_result(data_matrix, matrix_size, matrix_size, "Data");
        for (int i = 1; i < nb_proc; i++)
        {
            std::cout << "row number for sub matrix " << i << ": " << nb_row << std::endl;
            int shift_value = nb_row * i * matrix_size + last_nb_row * matrix_size;
            MPI_Send((data_matrix + shift_value), nb_row * matrix_size, MPI_DOUBLE, i, 101, MPI_COMM_WORLD);
        }
        std::cout << "row number for sub matrix 0"
                  << ": " << (nb_row + last_nb_row) << std::endl;
        sub_matrix = (double *)malloc(matrix_size * (nb_row + last_nb_row) * sizeof(double));
        memcpy(sub_matrix, data_matrix, (nb_row + last_nb_row) * matrix_size);
    }

    // Wait everyone
    MPI_Barrier(MPI_COMM_WORLD);

    // All other cores receive their data
    if (world_rank != 0)
    {
        sub_matrix = (double *)malloc(matrix_size * nb_row * sizeof(double));
        MPI_Recv(sub_matrix, nb_row * matrix_size, MPI_DOUBLE, 0, 101, MPI_COMM_WORLD, nullptr);
    }

    if (argc >= 3)
    {
        if ("dump" == std::string(argv[2]))
        {
            if (world_rank != 0)
            {
                dump_result(sub_matrix, nb_row, matrix_size);
            }
            else
            {
                dump_result(sub_matrix, nb_row + last_nb_row, matrix_size);

            }
        }
    }
    MPI_Finalize();
    return 0;
}
