#pragma once

double *PMV(double *matrix, double *vector, unsigned int n, unsigned int m);

double *init_matrix(unsigned int n, unsigned int m);

double *init_sparse_matrix(unsigned int n, unsigned int m, float p);

void dump_result(double *tab, unsigned n, unsigned int m, std::string f_name = "Result_");

double *read_from_file(std::string file_name, unsigned int *n, unsigned int *m);

void print_help();

