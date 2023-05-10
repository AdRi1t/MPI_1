#pragma once


class CSR_matrix
{
private:
    unsigned int *row_first_index;
    unsigned int *col_index;
    double *data;

public:
    CSR_matrix(double *data, unsigned int dim);
    ~CSR_matrix();
};

class COO_matrix
{
private:
    unsigned int size;
    unsigned int nb_elements;
    unsigned int *row;
    unsigned int *column;
    double *data;

public:
    COO_matrix(unsigned int size);
    COO_matrix(std::string mm_file_name);
    void dump(std::string file_name="COO_matrix");
    ~COO_matrix();
};


