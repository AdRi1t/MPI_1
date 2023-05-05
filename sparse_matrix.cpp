#include "sparse_matrix.hpp"

sparse_matrix::sparse_matrix(double *data, unsigned int dim)
{
    row_first_index = new unsigned int[dim];
    double *tmp_non_zero = new double[dim * dim];
    unsigned int nb_no_zero = 0;
    unsigned int i, j;
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            if (data[i * dim + j] != 0)
            {
                tmp_non_zero[nb_no_zero] = data[i * dim + j];
                nb_no_zero += 1;
            }
        }
    }
    data = new double[nb_no_zero];
    for(i = 0 ; i< nb_no_zero;i++){
        data[i] = tmp_non_zero[i];
    }
    delete[] tmp_non_zero;

}

sparse_matrix::~sparse_matrix()
{
    delete[] row_first_index;
}
