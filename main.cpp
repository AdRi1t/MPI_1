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
    bool coo_enable = false;
    bool file_source = false;
    unsigned int matrix_size = 0;
    char opt;
    extern char *optarg;
    std::string file_name;
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s -n size_matrix -f file source [-d] [-h] [-c] \n", argv[0]);
        return 1;
    }

    MPI_Init(&argc, &argv);

    int nb_proc(-1);
    int world_rank(-1);

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    while ((opt = getopt(argc, argv, "dcf:n:h")) != -1)
    {
        switch (opt)
        {
        case 'd':
            dump_enable = true;
            break;
        case 'c':
            coo_enable = true;
            break;
        case 'f':
            file_source = true;
            file_name.assign(optarg);
            break;
        case 'n':
            matrix_size = atoi(std::string(optarg).c_str());
            break;
        case 'h':
            if (world_rank == 0)
            {
                print_help();
            }
            MPI_Finalize();
            return 0;
            break;
        }
    }

    if (matrix_size == 0 && file_source == false)
    {
        fprintf(stderr, "Usage: %s -n size_matrix -f file source [-d] [-h] [-c] \n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    std::cout << "World rank " << world_rank << std::endl;

    MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);

    if (coo_enable == false)
    {
        double *sub_matrix;
        double *sub_result;
        double *sub_vector;

        // Generates a test matrix and distributes it to the other core
        if (world_rank == 0)
        {
            double *data_matrix;
            double *data_vector;
            if (file_source == true)
            {
                data_matrix = read_from_file(file_name, &matrix_size, &matrix_size);
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
    }
    else
    {
        COO_matrix sub_matrix(0);
        // Generates a test matrix and distributes it to the other core
        if (world_rank == 0)
        {
            COO_matrix *data_matrix = new COO_matrix(matrix_size);
            data_matrix->init_random_sparse(0.4);
            data_matrix->deliver_sub_matrix(world_rank, nb_proc);
            data_matrix->dump();
            delete data_matrix;
        }
        else
        {
            sub_matrix.receives_sub_matrix(world_rank, nb_proc);
            sub_matrix.dump("sub_matrix_");
        }
    }
    MPI_Finalize();
    return 0;
}
