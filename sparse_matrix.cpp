#include <string>
#include <iostream>
#include "sparse_matrix.hpp"
#include "mmio.h"

CSR_matrix::CSR_matrix(double *data, unsigned int dim)
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

CSR_matrix::~CSR_matrix()
{
    delete[] row_first_index;
}


COO_matrix::COO_matrix(unsigned int size)
{
    row = new unsigned int[size];
    column = new unsigned int[size];
    data = new double [size];
}

COO_matrix::COO_matrix(std::string mm_file_name)
{
    FILE* mm_file;
    MM_typecode matcode;
	int nb_row,nb_column,nb_data;
	int ret_code;
	nb_row = 0;
	nb_column = 0;
	nb_data = 0;
	ret_code = 0;
	
	mm_file = fopen(mm_file_name.c_str(),"r");
	if(mm_file == NULL){
		std::cerr << "Could not open file: " << mm_file_name << std::endl;
	}
	if(mm_read_banner(mm_file, &matcode) != 0 )
    {
        std::cerr << "Could not process Matrix Market banner" << std::endl;
    }
    
    //On obtient nombre de lignes nombre de colonnes et nombre d'éléments
	if((ret_code = mm_read_mtx_crd_size(mm_file, &nb_row, &nb_column, &nb_data)) !=0 ){
        return 1;
	}
	I = (int *) malloc(nb_data * sizeof(int));
    J = (int *) malloc(nb_data * sizeof(int));
    coeff = (double *) malloc(nb_data * sizeof(double));
    
    //On lit les éléments du fichier
	for (i=0; i<nb_data; i++)
    {
        fscanf(fichier_matrice, "%d %d %lg\n", &I[i], &J[i], &coeff[i]);
        I[i]--;
        J[i]--;
    }
	//On reconstitue la matrice
	init_matrice(matrice,nb_row,nb_column);
	for (i=0; i<nb_data; i++)
    {
		(*matrice)->coeffs[I[i]][J[i]] = coeff[i];
		(*matrice)->coeffs[J[i]][I[i]] = coeff[i];
	}
	return 0;
}

COO_matrix::~COO_matrix()
{
    delete[] row;
    delete[] column;
    delete[] data;
}
