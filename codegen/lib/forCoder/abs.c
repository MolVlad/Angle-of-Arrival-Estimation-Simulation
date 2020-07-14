/*
 * File: abs.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Jul-2020 11:32:44
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "abs.h"
#include "forCoder_emxutil.h"
#include "forCoder_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void b_abs(const emxArray_creal_T *x, emxArray_real_T *y)
{
  int nx;
  short unnamed_idx_0;
  short unnamed_idx_1;
  int k;
  nx = x->size[0] * x->size[1];
  unnamed_idx_0 = (short)x->size[0];
  unnamed_idx_1 = (short)x->size[1];
  k = y->size[0] * y->size[1];
  y->size[0] = unnamed_idx_0;
  y->size[1] = unnamed_idx_1;
  emxEnsureCapacity_real_T(y, k);
  for (k = 0; k < nx; k++) {
    y->data[k] = rt_hypotd_snf(x->data[k].re, x->data[k].im);
  }
}

/*
 * Arguments    : const creal_T x[108781]
 *                double y[108781]
 * Return Type  : void
 */
void c_abs(const creal_T x[108781], double y[108781])
{
  int k;
  for (k = 0; k < 108781; k++) {
    y[k] = rt_hypotd_snf(x[k].re, x[k].im);
  }
}

/*
 * File trailer for abs.c
 *
 * [EOF]
 */
