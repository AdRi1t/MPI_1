#pragma once

class sparse_matrix
{
private:
    unsigned int *row_first_index;
    unsigned int *col_index;
    double *data;

public:
    sparse_matrix(double *data, unsigned int dim);
    ~sparse_matrix();
};

