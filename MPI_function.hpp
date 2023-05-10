#pragma once

#define SUB_MATRIX_TAG 101
#define SUB_MATRIX_SIZE_TAG 109
#define SUB_VECTOR_TAG 201
#define SUB_VECTOR_SIZE_TAG 209
#define SWAP_VECTOR 301

// Distributed sub-matrix to the other cores
double *deliver_sub_matrix(double *data_matrix, unsigned int matrix_size, int nb_proc);

// All other cores receive their data
double *receives_sub_matrix(unsigned int *matrix_size, int nb_proc);

double *deliver_sub_vector(double *data_vector, unsigned int vector_size, int nb_proc);

double *receives_sub_vector(int nb_proc);

double *pmv_2(double *matrix, double *vector, unsigned int matrix_size, unsigned int nb_proc);

double *gather_result(double *sub_result, unsigned int matrix_size);



