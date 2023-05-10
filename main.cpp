#include <mpi.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "mmio.h"
#include "matrix.hpp"
#include "MPI_function.hpp"
#include "sparse_matrix.hpp"

int main(int argc, char *argv[])
{
    bool dump_enable = false;
    unsigned int matrix_size = 0;
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <size matrix/file name> [-d] \n", argv[0]);
        return 1;
    }
    else
    {
        matrix_size = atoi(argv[1]);
    }
    if (getopt(argc, argv, "d") == 'd')
    {
        dump_enable = true;
    }
    MPI_Init(&argc, &argv);

    double *sub_matrix;
    double *sub_result;
    double *sub_vector;
    int nb_proc(-1);
    int world_rank(-1);

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    std::cout << "World rank " << world_rank << std::endl;

    MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);

    // Generates a test matrix and distributes it to the other core
    if (world_rank == 0)
    {
        double *data_matrix;
        double *data_vector;
        if (matrix_size == 0)
        {
            data_matrix = read_from_file(argv[1], &matrix_size, &matrix_size);
        }
        else
        {
            data_matrix = init_sparse_matrix(matrix_size, matrix_size, 0.5);
        }
        data_vector = init_matrix(matrix_size, 1);
        sub_matrix = deliver_sub_matrix(data_matrix, matrix_size, nb_proc);
        sub_vector = deliver_sub_vector(data_vector, matrix_size, nb_proc);
        if (dump_enable)
        {
            dump_result(data_matrix, matrix_size, matrix_size, "data_matrix_");
            dump_result(data_vector, matrix_size, 1, "data_vector_");
        }
        delete[] data_matrix;
        delete[] data_vector;
    }

    // All other cores receive their data
    if (world_rank != 0)
    {
        sub_matrix = receives_sub_matrix(&matrix_size, nb_proc);
        sub_vector = receives_sub_vector(nb_proc);
    }

    int nb_row = matrix_size / nb_proc;
    int last_nb_row = matrix_size % nb_proc;
    
    
    sub_result = pmv_2(sub_matrix, sub_vector, matrix_size, nb_proc);

    double *result;
    result = gather_result(sub_result, matrix_size);
    if (world_rank != 0)
    {
        delete[] result;
    }
    if (dump_enable)
    {
        if (world_rank != 0)
        {
            dump_result(sub_matrix, nb_row, matrix_size, "sub_matrix_");
            dump_result(sub_vector, nb_row, 1, "sub_vector_");
            dump_result(sub_result, nb_row, 1, "sub_result_");
        }
        else
        {
            dump_result(sub_matrix, nb_row + last_nb_row, matrix_size, "sub_matrix_");
            dump_result(sub_vector, nb_row + last_nb_row, 1, "sub_vector_");
            dump_result(sub_result, nb_row + last_nb_row, 1, "sub_result_");
            dump_result(result, matrix_size, 1);
        }
    }

    delete[] sub_vector;
    delete[] sub_matrix;
    MPI_Finalize();
    return 0;
}
