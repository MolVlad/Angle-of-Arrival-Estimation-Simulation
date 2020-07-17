/*
 * File: xzggbak.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 16:31:04
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "xzggbak.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_creal_T *V
 *                int ilo
 *                int ihi
 *                const int rscale_data[]
 * Return Type  : void
 */
void xzggbak(emxArray_creal_T *V, int ilo, int ihi, const int rscale_data[])
{
  int n;
  int m;
  int i;
  int k;
  int i41;
  int j;
  double tmp_re;
  double tmp_im;
  n = V->size[0];
  m = V->size[1] - 1;
  if (ilo > 1) {
    for (i = ilo - 2; i + 1 >= 1; i--) {
      k = rscale_data[i] - 1;
      if (rscale_data[i] != i + 1) {
        for (j = 0; j <= m; j++) {
          tmp_re = V->data[i + V->size[0] * j].re;
          tmp_im = V->data[i + V->size[0] * j].im;
          V->data[i + V->size[0] * j] = V->data[k + V->size[0] * j];
          V->data[k + V->size[0] * j].re = tmp_re;
          V->data[k + V->size[0] * j].im = tmp_im;
        }
      }
    }
  }

  if (ihi < n) {
    k = ihi + 1;
    for (i = k; i <= n; i++) {
      i41 = rscale_data[i - 1];
      if (i41 != i) {
        for (j = 0; j <= m; j++) {
          tmp_re = V->data[(i + V->size[0] * j) - 1].re;
          tmp_im = V->data[(i + V->size[0] * j) - 1].im;
          V->data[(i + V->size[0] * j) - 1] = V->data[(i41 + V->size[0] * j) - 1];
          V->data[(i41 + V->size[0] * j) - 1].re = tmp_re;
          V->data[(i41 + V->size[0] * j) - 1].im = tmp_im;
        }
      }
    }
  }
}

/*
 * File trailer for xzggbak.c
 *
 * [EOF]
 */
