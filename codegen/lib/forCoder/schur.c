/*
 * File: schur.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 17-Jul-2020 17:26:12
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "schur.h"
#include "forCoder_emxutil.h"
#include "triu.h"
#include "xhseqr.h"
#include "xungorghr.h"
#include "xgehrd.h"
#include "anyNonFinite.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *A
 *                emxArray_creal_T *V
 *                emxArray_creal_T *T
 * Return Type  : void
 */
void schur(const emxArray_creal_T *A, emxArray_creal_T *V, emxArray_creal_T *T)
{
  int i9;
  unsigned char unnamed_idx_0;
  unsigned char unnamed_idx_1;
  int loop_ub;
  creal_T tau_data[223];
  int tau_size[1];
  if (anyNonFinite(A)) {
    unnamed_idx_0 = (unsigned char)A->size[0];
    unnamed_idx_1 = (unsigned char)A->size[1];
    i9 = V->size[0] * V->size[1];
    V->size[0] = unnamed_idx_0;
    V->size[1] = unnamed_idx_1;
    emxEnsureCapacity_creal_T(V, i9);
    loop_ub = unnamed_idx_0 * unnamed_idx_1;
    for (i9 = 0; i9 < loop_ub; i9++) {
      V->data[i9].re = rtNaN;
      V->data[i9].im = 0.0;
    }

    triu(V);
    unnamed_idx_0 = (unsigned char)A->size[0];
    unnamed_idx_1 = (unsigned char)A->size[1];
    i9 = T->size[0] * T->size[1];
    T->size[0] = unnamed_idx_0;
    T->size[1] = unnamed_idx_1;
    emxEnsureCapacity_creal_T(T, i9);
    loop_ub = unnamed_idx_0 * unnamed_idx_1;
    for (i9 = 0; i9 < loop_ub; i9++) {
      T->data[i9].re = rtNaN;
      T->data[i9].im = 0.0;
    }
  } else {
    i9 = T->size[0] * T->size[1];
    T->size[0] = A->size[0];
    T->size[1] = A->size[1];
    emxEnsureCapacity_creal_T(T, i9);
    loop_ub = A->size[0] * A->size[1];
    for (i9 = 0; i9 < loop_ub; i9++) {
      T->data[i9] = A->data[i9];
    }

    xgehrd(T, tau_data, tau_size);
    i9 = V->size[0] * V->size[1];
    V->size[0] = T->size[0];
    V->size[1] = T->size[1];
    emxEnsureCapacity_creal_T(V, i9);
    loop_ub = T->size[0] * T->size[1];
    for (i9 = 0; i9 < loop_ub; i9++) {
      V->data[i9] = T->data[i9];
    }

    xungorghr(A->size[0], A->size[0], V, A->size[0], tau_data);
    xhseqr(T, V);
  }
}

/*
 * File trailer for schur.c
 *
 * [EOF]
 */
