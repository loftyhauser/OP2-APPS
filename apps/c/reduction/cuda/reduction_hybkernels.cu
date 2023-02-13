//
// auto-generated by op2.py
//

//header
#ifdef GPUPASS
#define op_par_loop_res_calc op_par_loop_res_calc_gpu
#define op_par_loop_update op_par_loop_update_gpu
#include "reduction_kernels.cu"
#undef op_par_loop_res_calc
#undef op_par_loop_update
#else
#define SKIP_DECL_CONST
#define op_par_loop_res_calc op_par_loop_res_calc_cpu
#define op_par_loop_update op_par_loop_update_cpu
#include "../openmp/reduction_kernels.cpp"
#undef op_par_loop_res_calc
#undef op_par_loop_update

//user kernel files

void op_par_loop_res_calc_gpu(char const *name, op_set set,
  op_arg arg0,
  op_arg arg1);

//GPU host stub function
#if OP_HYBRID_GPU
void op_par_loop_res_calc(char const *name, op_set set,
  op_arg arg0,
  op_arg arg1){

  if (OP_hybrid_gpu) {
    op_par_loop_res_calc_gpu(name, set,
      arg0,
      arg1);

    }else{
    op_par_loop_res_calc_cpu(name, set,
      arg0,
      arg1);

  }
}
#else
void op_par_loop_res_calc(char const *name, op_set set,
  op_arg arg0,
  op_arg arg1){

  op_par_loop_res_calc_gpu(name, set,
    arg0,
    arg1);

  }
#endif //OP_HYBRID_GPU

void op_par_loop_update_gpu(char const *name, op_set set,
  op_arg arg0,
  op_arg arg1);

//GPU host stub function
#if OP_HYBRID_GPU
void op_par_loop_update(char const *name, op_set set,
  op_arg arg0,
  op_arg arg1){

  if (OP_hybrid_gpu) {
    op_par_loop_update_gpu(name, set,
      arg0,
      arg1);

    }else{
    op_par_loop_update_cpu(name, set,
      arg0,
      arg1);

  }
}
#else
void op_par_loop_update(char const *name, op_set set,
  op_arg arg0,
  op_arg arg1){

  op_par_loop_update_gpu(name, set,
    arg0,
    arg1);

  }
#endif //OP_HYBRID_GPU
#endif
