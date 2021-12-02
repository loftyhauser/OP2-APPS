//
// auto-generated by op2.py
//

//user function
inline void bres_calc(const double *x1, const double *x2, const double *q1,
                      const double *adt1, double *res1, const int *bound) {
  double dx, dy, mu, ri, p1, vol1, p2, vol2, f;

  dx = x1[0] - x2[0];
  dy = x1[1] - x2[1];

  ri = 1.0f / q1[0];
  p1 = gm1 * (q1[3] - 0.5f * ri * (q1[1] * q1[1] + q1[2] * q1[2]));

  if (*bound == 1) {
    res1[1] += +p1 * dy;
    res1[2] += -p1 * dx;
  } else {
    vol1 = ri * (q1[1] * dy - q1[2] * dx);

    ri = 1.0f / qinf[0];
    p2 = gm1 * (qinf[3] - 0.5f * ri * (qinf[1] * qinf[1] + qinf[2] * qinf[2]));
    vol2 = ri * (qinf[1] * dy - qinf[2] * dx);

    mu = (*adt1) * eps;

    f = 0.5f * (vol1 * q1[0] + vol2 * qinf[0]) + mu * (q1[0] - qinf[0]);
    res1[0] += f;
    f = 0.5f * (vol1 * q1[1] + p1 * dy + vol2 * qinf[1] + p2 * dy) +
        mu * (q1[1] - qinf[1]);
    res1[1] += f;
    f = 0.5f * (vol1 * q1[2] - p1 * dx + vol2 * qinf[2] - p2 * dx) +
        mu * (q1[2] - qinf[2]);
    res1[2] += f;
    f = 0.5f * (vol1 * (q1[3] + p1) + vol2 * (qinf[3] + p2)) +
        mu * (q1[3] - qinf[3]);
    res1[3] += f;
  }
}
#ifdef VECTORIZE
//user function -- modified for vectorisation
#if defined __clang__ || defined __GNUC__
__attribute__((always_inline))
#endif
inline void bres_calc_vec( const double x1[][SIMD_VEC], const double x2[][SIMD_VEC], const double q1[][SIMD_VEC], const double adt1[][SIMD_VEC], double res1[][SIMD_VEC], const int bound[][SIMD_VEC], int idx ) {
  double dx, dy, mu, ri, p1, vol1, p2, vol2, f;

  dx = x1[0][idx] - x2[0][idx];
  dy = x1[1][idx] - x2[1][idx];

  ri = 1.0f / q1[0][idx];
  p1 = gm1 * (q1[3][idx] - 0.5f * ri * (q1[1][idx] * q1[1][idx] + q1[2][idx] * q1[2][idx]));

  if (bound[0][idx]== 1) {
    res1[1][idx] = +p1 * dy;
    res1[2][idx] = -p1 * dx;
  } else {
    vol1 = ri * (q1[1][idx] * dy - q1[2][idx] * dx);

    ri = 1.0f / qinf[0];
    p2 = gm1 * (qinf[3] - 0.5f * ri * (qinf[1] * qinf[1] + qinf[2] * qinf[2]));
    vol2 = ri * (qinf[1] * dy - qinf[2] * dx);

    mu = (adt1[0][idx]) * eps;

    f = 0.5f * (vol1 * q1[0][idx] + vol2 * qinf[0]) + mu * (q1[0][idx] - qinf[0]);
    res1[0][idx] = f;
    f = 0.5f * (vol1 * q1[1][idx] + p1 * dy + vol2 * qinf[1] + p2 * dy) +
        mu * (q1[1][idx] - qinf[1]);
    res1[1][idx] = f;
    f = 0.5f * (vol1 * q1[2][idx] - p1 * dx + vol2 * qinf[2] - p2 * dx) +
        mu * (q1[2][idx] - qinf[2]);
    res1[2][idx] = f;
    f = 0.5f * (vol1 * (q1[3][idx] + p1) + vol2 * (qinf[3] + p2)) +
        mu * (q1[3][idx] - qinf[3]);
    res1[3][idx] = f;
  }

}
#endif

// host stub function
void op_par_loop_bres_calc(char const *name, op_set set,
  op_arg arg0,
  op_arg arg1,
  op_arg arg2,
  op_arg arg3,
  op_arg arg4,
  op_arg arg5){

  int nargs = 6;
  op_arg args[6];

  args[0] = arg0;
  args[1] = arg1;
  args[2] = arg2;
  args[3] = arg3;
  args[4] = arg4;
  args[5] = arg5;
  //create aligned pointers for dats
  ALIGNED_double const double * __restrict__ ptr0 = (double *) arg0.data;
  DECLARE_PTR_ALIGNED(ptr0,double_ALIGN);
  ALIGNED_double const double * __restrict__ ptr1 = (double *) arg1.data;
  DECLARE_PTR_ALIGNED(ptr1,double_ALIGN);
  ALIGNED_double const double * __restrict__ ptr2 = (double *) arg2.data;
  DECLARE_PTR_ALIGNED(ptr2,double_ALIGN);
  ALIGNED_double const double * __restrict__ ptr3 = (double *) arg3.data;
  DECLARE_PTR_ALIGNED(ptr3,double_ALIGN);
  ALIGNED_double       double * __restrict__ ptr4 = (double *) arg4.data;
  DECLARE_PTR_ALIGNED(ptr4,double_ALIGN);
  ALIGNED_int const int * __restrict__ ptr5 = (int *) arg5.data;
  DECLARE_PTR_ALIGNED(ptr5,int_ALIGN);

  // initialise timers
  double cpu_t1, cpu_t2, wall_t1, wall_t2;
  op_timing_realloc(3);
  op_timers_core(&cpu_t1, &wall_t1);

  if (OP_diags>2) {
    printf(" kernel routine with indirection: bres_calc\n");
  }

  int exec_size = op_mpi_halo_exchanges(set, nargs, args);

  if (exec_size >0) {

    #ifdef VECTORIZE
    #pragma novector
    for ( int n=0; n<(exec_size/SIMD_VEC)*SIMD_VEC; n+=SIMD_VEC ){
      if (n<set->core_size && n>0 && n % OP_mpi_test_frequency == 0)
        op_mpi_test_all(nargs,args);
      if ((n+SIMD_VEC >= set->core_size) && (n+SIMD_VEC-set->core_size < SIMD_VEC)) {
        op_mpi_wait_all(nargs, args);
      }
      ALIGNED_double double dat0[2][SIMD_VEC];
      ALIGNED_double double dat1[2][SIMD_VEC];
      ALIGNED_double double dat2[4][SIMD_VEC];
      ALIGNED_double double dat3[1][SIMD_VEC];
      ALIGNED_double double dat4[4][SIMD_VEC];
      ALIGNED_int int dat5[1][SIMD_VEC];
      #pragma omp simd simdlen(SIMD_VEC)
      for ( int i=0; i<SIMD_VEC; i++ ){
        int idx0_2 = 2 * arg0.map_data[(n+i) * arg0.map->dim + 0];
        int idx1_2 = 2 * arg0.map_data[(n+i) * arg0.map->dim + 1];
        int idx2_4 = 4 * arg2.map_data[(n+i) * arg2.map->dim + 0];
        int idx3_1 = 1 * arg2.map_data[(n+i) * arg2.map->dim + 0];
        int idx5_1 = 1 * (n+i);

        dat0[0][i] = (ptr0)[idx0_2 + 0];
        dat0[1][i] = (ptr0)[idx0_2 + 1];

        dat1[0][i] = (ptr1)[idx1_2 + 0];
        dat1[1][i] = (ptr1)[idx1_2 + 1];

        dat2[0][i] = (ptr2)[idx2_4 + 0];
        dat2[1][i] = (ptr2)[idx2_4 + 1];
        dat2[2][i] = (ptr2)[idx2_4 + 2];
        dat2[3][i] = (ptr2)[idx2_4 + 3];

        dat3[0][i] = (ptr3)[idx3_1 + 0];

        dat4[0][i] = 0.0;
        dat4[1][i] = 0.0;
        dat4[2][i] = 0.0;
        dat4[3][i] = 0.0;

        dat5[0][i] = (ptr5)[idx5_1 + 0];

      }
      #pragma omp simd simdlen(SIMD_VEC)
      for ( int i=0; i<SIMD_VEC; i++ ){
        bres_calc_vec(
          dat0,
          dat1,
          dat2,
          dat3,
          dat4,
          dat5,
          i);
      }
      for ( int i=0; i<SIMD_VEC; i++ ){
        int idx4_4 = 4 * arg2.map_data[(n+i) * arg2.map->dim + 0];

        (ptr4)[idx4_4 + 0] += dat4[0][i];
        (ptr4)[idx4_4 + 1] += dat4[1][i];
        (ptr4)[idx4_4 + 2] += dat4[2][i];
        (ptr4)[idx4_4 + 3] += dat4[3][i];

      }
    }

    //remainder
    for ( int n=(exec_size/SIMD_VEC)*SIMD_VEC; n<exec_size; n++ ){
    #else
    for ( int n=0; n<exec_size; n++ ){
    #endif
      if (n==set->core_size) {
        op_mpi_wait_all(nargs, args);
      }
      int map0idx;
      int map1idx;
      int map2idx;
      map0idx = arg0.map_data[n * arg0.map->dim + 0];
      map1idx = arg0.map_data[n * arg0.map->dim + 1];
      map2idx = arg2.map_data[n * arg2.map->dim + 0];

      bres_calc(
        &(ptr0)[2 * map0idx],
        &(ptr1)[2 * map1idx],
        &(ptr2)[4 * map2idx],
        &(ptr3)[1 * map2idx],
        &(ptr4)[4 * map2idx],
        &(ptr5)[1 * n]);
    }
  }

  if (exec_size == 0 || exec_size == set->core_size) {
    op_mpi_wait_all(nargs, args);
  }
  // combine reduction data
  op_mpi_set_dirtybit(nargs, args);

  // update kernel record
  op_timers_core(&cpu_t2, &wall_t2);
  OP_kernels[3].name      = name;
  OP_kernels[3].count    += 1;
  OP_kernels[3].time     += wall_t2 - wall_t1;
  OP_kernels[3].transfer += (float)set->size * arg0.size;
  OP_kernels[3].transfer += (float)set->size * arg2.size;
  OP_kernels[3].transfer += (float)set->size * arg3.size;
  OP_kernels[3].transfer += (float)set->size * arg4.size * 2.0f;
  OP_kernels[3].transfer += (float)set->size * arg5.size;
  OP_kernels[3].transfer += (float)set->size * arg0.map->dim * 4.0f;
  OP_kernels[3].transfer += (float)set->size * arg2.map->dim * 4.0f;
}
