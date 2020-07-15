/*
 * File: xgemv.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 16:54:31
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "xgemv.h"

/* Function Definitions */

/*
 * Arguments    : int m
 *                int n
 *                const emxArray_creal_T *A
 *                int ia0
 *                int lda
 *                const emxArray_creal_T *x
 *                int ix0
 *                creal_T y_data[]
 * Return Type  : void
 */
void b_xgemv(int m, int n, const emxArray_creal_T *A, int ia0, int lda, const
             emxArray_creal_T *x, int ix0, creal_T y_data[])
{
  int iy;
  int i31;
  int iac;
  int ix;
  double c_re;
  double c_im;
  int i32;
  int ia;
  if (n != 0) {
    for (iy = 0; iy < n; iy++) {
      y_data[iy].re = 0.0;
      y_data[iy].im = 0.0;
    }

    iy = 0;
    i31 = ia0 + lda * (n - 1);
    for (iac = ia0; lda < 0 ? iac >= i31 : iac <= i31; iac += lda) {
      ix = ix0 - 1;
      c_re = 0.0;
      c_im = 0.0;
      i32 = (iac + m) - 1;
      for (ia = iac; ia <= i32; ia++) {
        c_re += A->data[ia - 1].re * x->data[ix].re + A->data[ia - 1].im *
          x->data[ix].im;
        c_im += A->data[ia - 1].re * x->data[ix].im - A->data[ia - 1].im *
          x->data[ix].re;
        ix++;
      }

      y_data[iy].re += c_re - 0.0 * c_im;
      y_data[iy].im += c_im + 0.0 * c_re;
      iy++;
    }
  }
}

/*
 * Arguments    : int m
 *                int n
 *                const emxArray_creal_T *A
 *                int ia0
 *                int lda
 *                const emxArray_creal_T *x
 *                int ix0
 *                creal_T y_data[]
 * Return Type  : void
 */
void xgemv(int m, int n, const emxArray_creal_T *A, int ia0, int lda, const
           emxArray_creal_T *x, int ix0, creal_T y_data[])
{
  int iy;
  int ix;
  int i27;
  int iac;
  double c_re;
  double c_im;
  int i28;
  int ia;
  double A_re;
  double A_im;
  if (m != 0) {
    for (iy = 0; iy < m; iy++) {
      y_data[iy].re = 0.0;
      y_data[iy].im = 0.0;
    }

    ix = ix0;
    i27 = ia0 + lda * (n - 1);
    for (iac = ia0; lda < 0 ? iac >= i27 : iac <= i27; iac += lda) {
      c_re = x->data[ix - 1].re - 0.0 * x->data[ix - 1].im;
      c_im = x->data[ix - 1].im + 0.0 * x->data[ix - 1].re;
      iy = 0;
      i28 = (iac + m) - 1;
      for (ia = iac; ia <= i28; ia++) {
        A_re = A->data[ia - 1].re * c_re - A->data[ia - 1].im * c_im;
        A_im = A->data[ia - 1].re * c_im + A->data[ia - 1].im * c_re;
        y_data[iy].re += A_re;
        y_data[iy].im += A_im;
        iy++;
      }

      ix++;
    }
  }
}

/*
 * File trailer for xgemv.c
 *
 * [EOF]
 */
