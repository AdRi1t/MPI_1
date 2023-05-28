#pragma once

/* Performs the matrix-vector product */
double* PMV(double* matrix, double* vector, unsigned int n, unsigned int m);

/* Create and initialize a matrix of dimension n*m */
double* init_matrix(unsigned int n, unsigned int m);

double* init_sparse_matrix(unsigned int n, unsigned int m, float p);

/* Print the matrix to a file */
void dump_result(double* tab, unsigned n, unsigned int m, std::string f_name = "Result_");

double* read_from_file(std::string file_name, unsigned int* n, unsigned int* m);

/* Loads a matrix in MM format */
double* read_from_file_mm(std::string file_name, unsigned int* n, unsigned int* m);

/* Displays program help */
void print_help();

