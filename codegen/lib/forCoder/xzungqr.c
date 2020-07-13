/*
 * File: xzungqr.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 13-Jul-2020 18:10:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "xzungqr.h"
#include "xzlarf.h"

/* Function Definitions */

/*
 * Arguments    : int m
 *                int n
 *                int k
 *                emxArray_creal_T *A
 *                int ia0
 *                int lda
 *                const creal_T tau_data[]
 * Return Type  : void
 */
void xzungqr(int m, int n, int k, emxArray_creal_T *A, int ia0, int lda, const
             creal_T tau_data[])
{
  int i37;
  int j;
  int itau;
  int ia;
  short unnamed_idx_0;
  int b_k;
  int i;
  int iaii;
  creal_T work_data[464];
  double a_re;
  double a_im;
  double A_re;
  double A_im;
  if (n >= 1) {
    i37 = n - 1;
    for (j = k; j <= i37; j++) {
      ia = (ia0 + j * lda) - 1;
      b_k = m - 1;
      for (i = 0; i <= b_k; i++) {
        iaii = ia + i;
        A->data[iaii].re = 0.0;
        A->data[iaii].im = 0.0;
      }

      b_k = ia + j;
      A->data[b_k].re = 1.0;
      A->data[b_k].im = 0.0;
    }

    itau = k - 1;
    unnamed_idx_0 = (short)A->size[1];
    ia = unnamed_idx_0;
    for (i37 = 0; i37 < ia; i37++) {
      work_data[i37].re = 0.0;
      work_data[i37].im = 0.0;
    }

    for (i = k; i >= 1; i--) {
      iaii = ((ia0 + i) + (i - 1) * lda) - 1;
      if (i < n) {
        A->data[iaii - 1].re = 1.0;
        A->data[iaii - 1].im = 0.0;
        b_xzlarf((m - i) + 1, n - i, iaii, tau_data[itau], A, iaii + lda, lda,
                 work_data);
      }

      if (i < m) {
        ia = iaii + 1;
        a_re = -tau_data[itau].re;
        a_im = -tau_data[itau].im;
        i37 = (iaii + m) - i;
        for (b_k = ia; b_k <= i37; b_k++) {
          A_re = A->data[b_k - 1].re;
          A_im = A->data[b_k - 1].im;
          A->data[b_k - 1].re = a_re * A_re - a_im * A_im;
          A->data[b_k - 1].im = a_re * A_im + a_im * A_re;
        }
      }

      A->data[iaii - 1].re = 1.0 - tau_data[itau].re;
      A->data[iaii - 1].im = 0.0 - tau_data[itau].im;
      for (j = 0; j <= i - 2; j++) {
        i37 = (iaii - j) - 2;
        A->data[i37].re = 0.0;
        A->data[i37].im = 0.0;
      }

      itau--;
    }
  }
}

/*
 * File trailer for xzungqr.c
 *
 * [EOF]
 */
