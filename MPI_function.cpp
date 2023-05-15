#include <mpi.h>
#include <iostream>
#include "matrix.hpp"
#include "MPI_function.hpp"

// Distributed sub-matrix to the other cores
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
            int shift_value = nb_row * i * matrix_size + last_nb_row * matrix_size;
            MPI_Send(&matrix_size, 1, MPI_UNSIGNED, i, SUB_MATRIX_SIZE_TAG, MPI_COMM_WORLD);
            MPI_Send((data_matrix + shift_value), nb_row * matrix_size, MPI_DOUBLE, i, SUB_MATRIX_TAG, MPI_COMM_WORLD);
        }
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

// Distributed sub-vector to the other cores
double *deliver_sub_vector(double *data_vector, unsigned int vector_size, int nb_proc)
{
    int world_rank(-1);
    double *sub_vector;
    int nb_row = vector_size / nb_proc;
    int last_nb_row = vector_size % nb_proc;

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == 0)
    {
        for (int i = 1; i < nb_proc; i++)
        {
            int shift_value = nb_row * i + last_nb_row;
            MPI_Send(&vector_size, 1, MPI_UNSIGNED, i, SUB_VECTOR_SIZE_TAG, MPI_COMM_WORLD);
            MPI_Send((data_vector + shift_value), nb_row, MPI_DOUBLE, i, SUB_VECTOR_TAG, MPI_COMM_WORLD);
        }
        sub_vector = new double[nb_row + last_nb_row];
        std::copy(data_vector, data_vector + (nb_row + last_nb_row), sub_vector);
    }

    return sub_vector;
}

// All other cores receive their data
double *receives_sub_vector(int nb_proc)
{
    int world_rank(-1);
    unsigned int vector_size;
    int nb_row;
    double *sub_vector;

    MPI_Status status;

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank != 0)
    {
        MPI_Recv(&vector_size, 1, MPI_UNSIGNED, 0, SUB_VECTOR_SIZE_TAG, MPI_COMM_WORLD, &status);
        nb_row = vector_size / nb_proc;
        sub_vector = new double[nb_row];

        MPI_Recv(sub_vector, nb_row, MPI_DOUBLE, 0, SUB_VECTOR_TAG, MPI_COMM_WORLD, &status);
    }
    return sub_vector;
}

// Gather all the sub-results in rank order
double *gather_result(double *sub_result, unsigned int matrix_size)
{
    int nb_proc(-1);
    int world_rank(-1);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);

    double *result = new double[matrix_size];
    int *nb_sent_element = new int[nb_proc];
    int *shift = new int[nb_proc];
    int nb_row = matrix_size / nb_proc;
    int last_nb_row = matrix_size % nb_proc;
    nb_sent_element[0] = nb_row + last_nb_row;
    shift[0] = 0;
    for (int i = 1; i < nb_proc; i++)
    {
        nb_sent_element[i] = nb_row;
        shift[i] = shift[i - 1] + nb_sent_element[i - 1];
    }
    if (world_rank == 0)
    {
        MPI_Gatherv(sub_result, nb_row + last_nb_row, MPI_DOUBLE, result, nb_sent_element, shift, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Gatherv(sub_result, nb_row, MPI_DOUBLE, result, nb_sent_element, shift, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }

    return result;
}

double *pmv_2(double *matrix, double *vector, unsigned int matrix_size, unsigned int nb_proc)
{
    int world_rank;
    unsigned int i, j, k;
    unsigned int start_index;
    unsigned int stop_index;
    unsigned int local_nb_row;
    MPI_Request *request;
    MPI_Status *status;
    double *result;
    double *next_vector;
    double *vector_tmp;
    int nb_row = matrix_size / nb_proc;
    int last_nb_row = matrix_size % nb_proc;
    unsigned int *dest_rank = new unsigned int[nb_proc - 1];
    unsigned int *source_rank = new unsigned int[nb_proc - 1];

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Creation of the list of neighbors for each core
    k = world_rank;
    for (i = 0; i < nb_proc - 1; i++)
    {
        if (k == (nb_proc - 1) && world_rank != 0)
        {
            source_rank[i] = 0;
            k = 0;
        }
        else if (k + 1 != world_rank)
        {
            source_rank[i] = k + 1;
            k++;
        }
    }
    k = world_rank;
    for (i = 0; i < nb_proc - 1; i++)
    {
        if (k == 0 && world_rank != (nb_proc - 1))
        {
            dest_rank[i] = nb_proc - 1;
            k = nb_proc - 1;
        }
        else if (k - 1 != world_rank)
        {
            dest_rank[i] = k - 1;
            k--;
        }
    }
    if (world_rank == 0)
    {
        result = new double[nb_row + last_nb_row];
        local_nb_row = nb_row + last_nb_row;
    }
    else
    {
        result = new double[nb_row];
        local_nb_row = nb_row;
    }

    if (world_rank == 0)
    {
        for (k = 0; k < nb_proc - 1; k++)
        {
            request = new MPI_Request[2];
            status = new MPI_Status[2];
            next_vector = new double[nb_row];
            MPI_Irecv(next_vector, nb_row, MPI_DOUBLE, source_rank[k], SWAP_VECTOR, MPI_COMM_WORLD, &(request[0]));
            MPI_Isend(vector, nb_row + last_nb_row, MPI_DOUBLE, dest_rank[k], SWAP_VECTOR, MPI_COMM_WORLD, &(request[1]));

            if (k == 0)
            {
                start_index = 0;
                stop_index = nb_row + last_nb_row;
                for (i = 0; i < local_nb_row; i++)
                {
                    result[i] = 0;
                    for (j = start_index; j < stop_index; j++)
                    {
                        result[i] += matrix[i * matrix_size + j] * vector[j - start_index];
                    }
                }
            }
            else
            {
                start_index = source_rank[k - 1] * nb_row + last_nb_row;
                stop_index = (source_rank[k - 1] + 1) * nb_row + last_nb_row;
                for (i = 0; i < local_nb_row; i++)
                {
                    for (j = start_index; j < stop_index; j++)
                    {
                        result[i] += matrix[i * matrix_size + j] * vector_tmp[j - start_index];
                    }
                }
            }
            MPI_Wait(request, status);
            vector_tmp = next_vector;
        }
    }
    else
    {
        for (k = 0; k < nb_proc - 1; k++)
        {
            request = new MPI_Request[2];
            status = new MPI_Status[2];
            if (source_rank[k] == 0)
            {
                next_vector = new double[nb_row + last_nb_row];
                MPI_Irecv(next_vector, nb_row + last_nb_row, MPI_DOUBLE, source_rank[k], SWAP_VECTOR, MPI_COMM_WORLD, &(request[0]));
            }
            else
            {
                next_vector = new double[nb_row];
                MPI_Irecv(next_vector, nb_row, MPI_DOUBLE, source_rank[k], SWAP_VECTOR, MPI_COMM_WORLD, &(request[0]));
            }

            MPI_Isend(vector, nb_row, MPI_DOUBLE, dest_rank[k], SWAP_VECTOR, MPI_COMM_WORLD, &(request[1]));

            if (k == 0)
            {
                start_index = world_rank * nb_row + last_nb_row;
                stop_index = (world_rank + 1) * nb_row + last_nb_row;
                for (i = 0; i < local_nb_row; i++)
                {
                    result[i] = 0;
                    for (j = start_index; j < stop_index; j++)
                    {
                        result[i] += matrix[i * matrix_size + j] * vector[j - start_index];
                    }
                }
            }
            else if (source_rank[k - 1] == 0)
            {
                start_index = 0;
                stop_index = nb_row + last_nb_row;
                for (i = 0; i < local_nb_row; i++)
                {
                    for (j = start_index; j < stop_index; j++)
                    {
                        result[i] += matrix[i * matrix_size + j] * vector_tmp[j - start_index];
                    }
                }
            }
            else
            {
                start_index = source_rank[k - 1] * nb_row + last_nb_row;
                stop_index = (source_rank[k - 1] + 1) * nb_row + last_nb_row;
                for (i = 0; i < local_nb_row; i++)
                {
                    for (j = start_index; j < stop_index; j++)
                    {
                        result[i] += matrix[i * matrix_size + j] * vector_tmp[j - start_index];
                    }
                }
            }
            MPI_Wait(request, status);
            vector_tmp = next_vector;
        }
    }
    if (source_rank[nb_proc - 2] == 0)
    {
        start_index = 0;
        stop_index = nb_row + last_nb_row;
    }
    else
    {
        start_index = source_rank[nb_proc - 2] * nb_row + last_nb_row;
        stop_index = (source_rank[nb_proc - 2] + 1) * nb_row + last_nb_row;
    }
    for (i = 0; i < local_nb_row; i++)
    {
        for (j = start_index; j < stop_index; j++)
        {
            result[i] += matrix[i * matrix_size + j] * vector_tmp[j - start_index];
        }
    }
    delete[] next_vector;
    return result;
}



