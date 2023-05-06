#pragma once

#define SUB_MATRIX_TAG 101
#define SUB_MATRIX_SIZE_TAG 109

// Generates a test matrix and distributes it to the other core
double *deliver_sub_matrix(double *data_matrix,unsigned int matrix_size, int nb_proc);

double *receives_sub_matrix(unsigned int *matrix_size, int nb_proc);
