#pragma once

// Generates a test matrix and distributes it to the other core
double *deliver_sub_matrix(double *data_matrix,int matrix_size,int nb_proc);

double *receives_sub_matrix(int matrix_size, int nb_proc);


