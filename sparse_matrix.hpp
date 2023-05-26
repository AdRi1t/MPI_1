#pragma once

#define COO_MATRIX_NB_ELEMENTS 600
#define COO_MATRIX_SIZE 001
#define COO_MATRIX_ROW 602
#define COO_MATRIX_COLUMN 603
#define COO_MATRIX_DATA 604

#define COO_VECTOR_NB_ELEMENTS 700
#define COO_VECTOR_SIZE 701
#define COO_VECTOR_ROW 702
#define COO_VECTOR_COLUMN 703
#define COO_VECTOR_DATA 704

class CSR_matrix
{
private:
  unsigned int* row_first_index;
  unsigned int* col_index;
  double* data;

public:
  CSR_matrix(double* data, unsigned int dim);
  ~CSR_matrix();
};

class COO_matrix
{
private:
  unsigned int nb_row;
  unsigned int nb_col;
  unsigned int nb_elements;
  unsigned int* row;
  unsigned int* column;
  double* data;

public:
  COO_matrix(unsigned int size);
  COO_matrix(unsigned int size, float p);
  COO_matrix(unsigned int n, unsigned int m, float p);
  void init_for_test();
  unsigned int getNb_row(void) const;
  unsigned int getNb_col(void) const;
  void load_from_file(std::string mm_file_name);
  COO_matrix deliver_sub_matrix(unsigned int rank, unsigned int nb_proc);
  COO_matrix deliver_sub_vector(unsigned int rank, unsigned int nb_proc);
  void receives_sub_matrix(unsigned int rank, unsigned int nb_proc);
  void receives_sub_vector(unsigned int rank, unsigned int nb_proc);
  void bcast_vector(unsigned int rank);
  COO_matrix pmv(const COO_matrix& vector);
  COO_matrix pmv2(COO_matrix& vector, unsigned int rank, unsigned int nb_proc);
  COO_matrix gather_result(unsigned int rank);
  void dump(std::string file_name = "COO_matrix");
  void readable_output(std::string file_name = "COO_matrix");
  void free();
  ~COO_matrix();
};
