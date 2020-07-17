/*
 * File: xgerc.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 17-Jul-2020 17:26:12
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "xgerc.h"

/* Function Definitions */

/*
 * Arguments    : int m
 *                int n
 *                const creal_T alpha1
 *                int ix0
 *                const creal_T y_data[]
 *                emxArray_creal_T *A
 *                int ia0
 *                int lda
 * Return Type  : void
 */
void b_xgerc(int m, int n, const creal_T alpha1, int ix0, const creal_T y_data[],
             emxArray_creal_T *A, int ia0, int lda)
{
  int jA;
  int jy;
  int j;
  double temp_re;
  double temp_im;
  int ix;
  int i33;
  int i34;
  int ijA;
  double A_re;
  double A_im;
  if ((!(alpha1.re == 0.0)) || (!(alpha1.im == 0.0))) {
    jA = ia0 - 1;
    jy = 0;
    for (j = 0; j < n; j++) {
      if ((y_data[jy].re != 0.0) || (y_data[jy].im != 0.0)) {
        temp_re = y_data[jy].re * alpha1.re + y_data[jy].im * alpha1.im;
        temp_im = y_data[jy].re * alpha1.im - y_data[jy].im * alpha1.re;
        ix = ix0;
        i33 = jA + 1;
        i34 = m + jA;
        for (ijA = i33; ijA <= i34; ijA++) {
          A_re = A->data[ix - 1].re * temp_re - A->data[ix - 1].im * temp_im;
          A_im = A->data[ix - 1].re * temp_im + A->data[ix - 1].im * temp_re;
          A->data[ijA - 1].re += A_re;
          A->data[ijA - 1].im += A_im;
          ix++;
        }
      }

      jy++;
      jA += lda;
    }
  }
}

/*
 * Arguments    : int m
 *                int n
 *                const creal_T alpha1
 *                const creal_T x_data[]
 *                int iy0
 *                emxArray_creal_T *A
 *                int ia0
 *                int lda
 * Return Type  : void
 */
void xgerc(int m, int n, const creal_T alpha1, const creal_T x_data[], int iy0,
           emxArray_creal_T *A, int ia0, int lda)
{
  int jA;
  int jy;
  int j;
  boolean_T b_A;
  double temp_re;
  double temp_im;
  int ix;
  int i29;
  int i30;
  int ijA;
  if ((!(alpha1.re == 0.0)) || (!(alpha1.im == 0.0))) {
    jA = ia0 - 1;
    jy = iy0 - 1;
    for (j = 0; j < n; j++) {
      b_A = ((A->data[jy].re != 0.0) || (A->data[jy].im != 0.0));
      if (b_A) {
        temp_re = A->data[jy].re * alpha1.re + A->data[jy].im * alpha1.im;
        temp_im = A->data[jy].re * alpha1.im - A->data[jy].im * alpha1.re;
        ix = 0;
        i29 = jA + 1;
        i30 = m + jA;
        for (ijA = i29; ijA <= i30; ijA++) {
          A->data[ijA - 1].re += x_data[ix].re * temp_re - x_data[ix].im *
            temp_im;
          A->data[ijA - 1].im += x_data[ix].re * temp_im + x_data[ix].im *
            temp_re;
          ix++;
        }
      }

      jy++;
      jA += lda;
    }
  }
}

/*
 * File trailer for xgerc.c
 *
 * [EOF]
 */
