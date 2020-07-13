/*
 * File: kron.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 13-Jul-2020 18:10:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "kron.h"
#include "forCoder_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *A
 *                const emxArray_creal_T *B
 *                emxArray_creal_T *K
 * Return Type  : void
 */
void kron(const emxArray_creal_T *A, const emxArray_creal_T *B, emxArray_creal_T
          *K)
{
  int ma;
  int mb;
  int kidx;
  int b_j1;
  int j2;
  int i1;
  int i2;
  double A_re;
  double A_im;
  double B_re;
  double B_im;
  ma = A->size[0];
  mb = B->size[0];
  kidx = A->size[0] * B->size[0];
  b_j1 = K->size[0] * K->size[1];
  K->size[0] = kidx;
  K->size[1] = 1082401;
  emxEnsureCapacity_creal_T(K, b_j1);
  kidx = -1;
  for (b_j1 = 0; b_j1 < 1801; b_j1++) {
    for (j2 = 0; j2 < 601; j2++) {
      for (i1 = 0; i1 < ma; i1++) {
        for (i2 = 0; i2 < mb; i2++) {
          kidx++;
          A_re = A->data[i1 + A->size[0] * b_j1].re;
          A_im = A->data[i1 + A->size[0] * b_j1].im;
          B_re = B->data[i2 + B->size[0] * j2].re;
          B_im = B->data[i2 + B->size[0] * j2].im;
          K->data[kidx].re = A_re * B_re - A_im * B_im;
          K->data[kidx].im = A_re * B_im + A_im * B_re;
        }
      }
    }
  }
}

/*
 * File trailer for kron.c
 *
 * [EOF]
 */
