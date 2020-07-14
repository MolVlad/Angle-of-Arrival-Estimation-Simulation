/*
 * File: xscal.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Jul-2020 11:32:44
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "xscal.h"

/* Function Definitions */

/*
 * Arguments    : int n
 *                const creal_T a
 *                emxArray_creal_T *x
 *                int ix0
 *                int incx
 * Return Type  : void
 */
void xscal(int n, const creal_T a, emxArray_creal_T *x, int ix0, int incx)
{
  int i38;
  int k;
  double x_re;
  double x_im;
  if (incx >= 1) {
    i38 = ix0 + incx * (n - 1);
    for (k = ix0; incx < 0 ? k >= i38 : k <= i38; k += incx) {
      x_re = x->data[k - 1].re;
      x_im = x->data[k - 1].im;
      x->data[k - 1].re = a.re * x_re - a.im * x_im;
      x->data[k - 1].im = a.re * x_im + a.im * x_re;
    }
  }
}

/*
 * File trailer for xscal.c
 *
 * [EOF]
 */
