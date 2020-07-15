/*
 * File: xungorghr.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 12:14:31
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "xungorghr.h"
#include "xzungqr.h"

/* Function Definitions */

/*
 * Arguments    : int n
 *                int ihi
 *                emxArray_creal_T *A
 *                int lda
 *                const creal_T tau_data[]
 * Return Type  : void
 */
void xungorghr(int n, int ihi, emxArray_creal_T *A, int lda, const creal_T
               tau_data[])
{
  int j;
  int i;
  int ia;
  int iajm1;
  int i33;
  if (n != 0) {
    for (j = ihi; j >= 2; j--) {
      ia = (j - 1) * lda;
      for (i = 0; i <= j - 2; i++) {
        i33 = ia + i;
        A->data[i33].re = 0.0;
        A->data[i33].im = 0.0;
      }

      iajm1 = ia - lda;
      i33 = j + 1;
      for (i = i33; i <= ihi; i++) {
        A->data[(ia + i) - 1] = A->data[(iajm1 + i) - 1];
      }

      i33 = ihi + 1;
      for (i = i33; i <= n; i++) {
        iajm1 = (ia + i) - 1;
        A->data[iajm1].re = 0.0;
        A->data[iajm1].im = 0.0;
      }
    }

    for (i = 0; i < n; i++) {
      A->data[i].re = 0.0;
      A->data[i].im = 0.0;
    }

    A->data[0].re = 1.0;
    A->data[0].im = 0.0;
    i33 = ihi + 1;
    for (j = i33; j <= n; j++) {
      ia = (j - 1) * lda;
      for (i = 0; i < n; i++) {
        iajm1 = ia + i;
        A->data[iajm1].re = 0.0;
        A->data[iajm1].im = 0.0;
      }

      iajm1 = (ia + j) - 1;
      A->data[iajm1].re = 1.0;
      A->data[iajm1].im = 0.0;
    }

    xzungqr(ihi - 1, ihi - 1, ihi - 1, A, 2 + lda, lda, tau_data);
  }
}

/*
 * File trailer for xungorghr.c
 *
 * [EOF]
 */
