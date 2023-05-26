#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <mpi.h>
#include <unistd.h>

#include "MPI_function.hpp"
#include "matrix.hpp"
#include "mmio.h"
#include "sparse_matrix.hpp"

#define REPETITION 31

int main(int argc, char* argv[])
{
  bool dump_enable = false;
  bool coo_enable = false;
  bool file_source = false;
  bool dump_matrix_result = false;
  bool distributed_vector = false;
  unsigned int matrix_size = 0;
  char opt;
  extern char* optarg;
  std::chrono::system_clock timer;

  std::string file_name;
  if(argc < 2)
  {
    fprintf(stderr, "Usage: %s -n size_matrix -f file source [-d] [-h] [-c] \n", argv[0]);
    return 1;
  }

  MPI_Init(&argc, &argv);

  int nb_proc(-1);
  int world_rank(-1);

  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  while((opt = getopt(argc, argv, "vrdcf:n:h")) != -1)
  {
    switch(opt)
    {
    case 'd':
      dump_enable = true;
      break;
    case 'r':
      dump_matrix_result = true;
      break;
    case 'c':
      coo_enable = true;
      break;
    case 'v':
      distributed_vector = true;
      break;
    case 'f':
      file_source = true;
      file_name.assign(optarg);
      break;
    case 'n':
      matrix_size = atoi(std::string(optarg).c_str());
      break;
    case 'h':
      if(world_rank == 0)
      {
        print_help();
      }
      MPI_Finalize();
      return 0;
      break;
    }
  }
  if(matrix_size == 0 && file_source == false)
  {
    fprintf(stderr, "Usage: %s -n size_matrix -f file source [-d] [-p] [-h] [-c] \n", argv[0]);
    MPI_Finalize();
    return 1;
  }

  MPI_Comm_size(MPI_COMM_WORLD, &nb_proc);

  if(coo_enable == false)
  {
    std::chrono::system_clock::duration duration(0);
    for(int i = 0; i < REPETITION; i++)
    {
      double* sub_matrix;
      double* sub_result;
      double* sub_vector;
      double* result;
      double* data_matrix;
      double* data_vector;

      // Generates a test matrix and distributes it to the other core
      if(world_rank == 0)
      {
        if(file_source == true)
        {
          data_matrix = read_from_file_mm(file_name, &matrix_size, &matrix_size);
        }
        else
        {
          data_matrix = init_matrix(matrix_size, matrix_size);
        }
        data_vector = init_matrix(matrix_size, 1);
        sub_matrix = deliver_sub_matrix(data_matrix, matrix_size, nb_proc);

        if(distributed_vector == true)
        {
          sub_vector = deliver_sub_vector(data_vector, matrix_size, nb_proc);
        }
        if(dump_enable)
        {
          dump_result(data_matrix, matrix_size, matrix_size, "data_matrix_");
          dump_result(data_vector, matrix_size, 1, "data_vector_");
        }
      }
      // All other cores receive their data
      if(world_rank != 0)
      {
        sub_matrix = receives_sub_matrix(&matrix_size, nb_proc);
        if(distributed_vector == true)
        {
          sub_vector = receives_sub_vector(nb_proc);
        }
        else
        {
          data_vector = new double[matrix_size];
        }
      }
      int nb_row = matrix_size / nb_proc;
      int last_nb_row = matrix_size % nb_proc;

      if(world_rank == 0 && i == 0)
      {
        std::cout << "row number for sub matrix 0"
                  << ": " << nb_row + last_nb_row << std::endl;
        std::cout << "row number for others sub matrix"
                  << ": " << nb_row << std::endl;
      }
      if(distributed_vector == true)
      {
        auto t1 = timer.now();
        sub_result = pmv_2(sub_matrix, sub_vector, matrix_size, nb_proc);
        result = gather_result(sub_result, matrix_size);
        auto t2 = timer.now();
        duration += (t2 - t1);
      }
      else
      {
        auto t1 = timer.now();
        MPI_Bcast(data_vector, matrix_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        if(world_rank == 0)
        {
          sub_result = PMV(sub_matrix, data_vector, nb_row + last_nb_row, matrix_size);
        }
        else
        {
          sub_result = PMV(sub_matrix, data_vector, nb_row, matrix_size);
        }
        result = gather_result(sub_result, matrix_size);
        auto t2 = timer.now();
        duration += (t2 - t1);
      }

      if(dump_matrix_result == true && world_rank == 0)
      {
        dump_result(result, matrix_size, 1);
      }
      if(dump_enable && i == 0)
      {
        if(world_rank != 0)
        {
          dump_result(sub_matrix, nb_row, matrix_size, "sub_matrix_");
          dump_result(sub_vector, nb_row, 1, "sub_vector_");
          dump_result(sub_result, nb_row, 1, "sub_result_");
        }
        else
        {
          dump_result(sub_matrix, nb_row + last_nb_row, matrix_size, "sub_matrix_");
          dump_result(sub_vector, nb_row + last_nb_row, 1, "sub_vector_");
          dump_result(sub_result, nb_row + last_nb_row, 1, "sub_result_");
          dump_result(result, matrix_size, 1);
        }
      }
      if(world_rank == 0)
      {
        delete[] data_matrix;
        delete[] data_vector;
      }
      else
      {
        delete[] sub_matrix;
      }
      if(distributed_vector == true)
      {
        delete[] sub_vector;
      }
    }
    auto time = std::chrono::duration_cast<std::chrono::microseconds>((duration) / REPETITION);
    std::cout << "temps :" << float(time.count()) / 1000 << " ms " << std::endl;
  }
  else
  {
    std::chrono::system_clock::duration duration(0);
    for(int i = 0; i < REPETITION; i++)
    {
      COO_matrix sub_matrix(0);
      COO_matrix sub_vector(0);
      COO_matrix sub_result(0);
      COO_matrix data_matrix(0);
      COO_matrix data_vector(0);
      auto t1 = timer.now();
      // Generates a test matrix in COO format and distributes it to the other core
      if(world_rank == 0)
      {
        if(file_source == true)
        {
          data_matrix.load_from_file(file_name);
        }
        else
        {
          data_matrix = COO_matrix(matrix_size);
          data_matrix.init_for_test();
        }
        data_vector = COO_matrix(data_matrix.getNb_col(), 1, 1);
        data_vector.init_for_test();
        if(dump_enable == true)
        {
          data_matrix.readable_output("data_matrix_");
          data_vector.readable_output("data_vector_");
        }
        sub_matrix = data_matrix.deliver_sub_matrix(world_rank, nb_proc);
        if(distributed_vector == true)
        {
          sub_vector = data_vector.deliver_sub_vector(world_rank, nb_proc);
        }
        else
        {
          data_vector.bcast_vector(world_rank);
          sub_vector = data_vector;
        }
      }
      else
      {
        sub_matrix.receives_sub_matrix(world_rank, nb_proc);
        if(distributed_vector == true)
        {
          sub_vector.receives_sub_vector(world_rank, nb_proc);
        }
        else
        {
          sub_vector.bcast_vector(world_rank);
        }
      }
      COO_matrix result(0);
      if(distributed_vector == true)
      {
        t1 = timer.now();
        sub_result = sub_matrix.pmv2(sub_vector, world_rank, nb_proc);
        result = sub_result.gather_result(world_rank);
        auto t2 = timer.now();
        duration += (t2 - t1);
      }
      else
      {
        t1 = timer.now();
        sub_result = sub_matrix.pmv(sub_vector);
        result = sub_result.gather_result(world_rank);
        auto t2 = timer.now();
        duration += (t2 - t1);
      }
      if(dump_enable == true)
      {
        sub_matrix.dump("sub_matrix_");
        sub_vector.dump("sub_vector_");
        sub_result.dump("sub_result_");
      }
      if((dump_matrix_result || dump_enable) && world_rank == 0)
      {
        result.dump("result_");
      }
      sub_matrix.free();
      sub_vector.free();
      sub_result.free();
    }
    auto time = std::chrono::duration_cast<std::chrono::microseconds>((duration) / REPETITION);
    std::cout << "temps :" << float(time.count()) / 1000 << " ms " << std::endl;
  }

  MPI_Finalize();

  return 0;
}
