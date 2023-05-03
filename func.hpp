#pragma once

class C_matrix
{
private:
    unsigned int row;
    unsigned int column;

public:
    double *data;
    C_matrix(unsigned int n, unsigned int m);
    void dump(std::string f_name = "Matrix_");
    ~C_matrix();
};

double *init_matrix(unsigned int n, unsigned int m);

void dump_result(double *tab, unsigned n, unsigned int m, std::string f_name = "Result_");