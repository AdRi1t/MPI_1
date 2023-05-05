#include <mpi.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include "matrix.hpp"
#include "MPI_function.hpp"
#include "sparse_matrix.hpp"


int main(int argc, char *argv[])
{
    unsigned int matrix_size = 0;
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <size matrix/file name> [dump] \n", argv[0]);
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
        double *data_matrix;
        if (matrix_size == 0)
        {
            data_matrix = read_from_file(argv[1], &matrix_size, &matrix_size);
        }
        else
        {
            data_matrix = init_sparse_matrix(matrix_size, matrix_size,0.2);
        }
        dump_result(data_matrix, matrix_size, matrix_size, "Data_");
        vector = init_matrix(matrix_size, 1);
        sub_matrix = deliver_sub_matrix(data_matrix, matrix_size, nb_proc);
    }


    // All other cores receive their data
    if (world_rank != 0)
    {
        sub_matrix = receives_sub_matrix(matrix_size, nb_proc);
        vector = new double[matrix_size];
    }

    // Send the vector to everyone
    MPI_Bcast(vector, matrix_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (world_rank == 0)
    {
        sub_result = PMV(sub_matrix, vector, nb_row + last_nb_row, matrix_size);
    }
    else
    {
        sub_result = PMV(sub_matrix, vector, nb_row, matrix_size);
    }

    // Gather all the sub-results in rank order
    double *result = new double[matrix_size];
    int *nb_sent_element = new int[nb_proc];
    int *shift = new int[nb_proc];
    nb_sent_element[0] = nb_row + last_nb_row;
    shift[0] = 0;
    for (int i = 1; i < nb_proc; i++)
    {
        nb_sent_element[i] = nb_row;
        shift[i] = shift[i - 1] + nb_sent_element[i - 1];
    }
    MPI_Gatherv(sub_result, nb_row, MPI_DOUBLE, result, nb_sent_element, shift, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    if (world_rank != 0)
    {
        delete[] result;
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
                dump_result(result, matrix_size, 1);
            }
        }
    }
    delete[] vector;
    delete[] sub_matrix;
    MPI_Finalize();
    return 0;
}

