/*
 * File: schur.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 13-Jul-2020 18:10:32
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
  int i10;
  short unnamed_idx_0;
  short unnamed_idx_1;
  int loop_ub;
  creal_T tau_data[463];
  int tau_size[1];
  if (anyNonFinite(A)) {
    unnamed_idx_0 = (short)A->size[0];
    unnamed_idx_1 = (short)A->size[1];
    i10 = V->size[0] * V->size[1];
    V->size[0] = unnamed_idx_0;
    V->size[1] = unnamed_idx_1;
    emxEnsureCapacity_creal_T(V, i10);
    loop_ub = unnamed_idx_0 * unnamed_idx_1;
    for (i10 = 0; i10 < loop_ub; i10++) {
      V->data[i10].re = rtNaN;
      V->data[i10].im = 0.0;
    }

    triu(V);
    unnamed_idx_0 = (short)A->size[0];
    unnamed_idx_1 = (short)A->size[1];
    i10 = T->size[0] * T->size[1];
    T->size[0] = unnamed_idx_0;
    T->size[1] = unnamed_idx_1;
    emxEnsureCapacity_creal_T(T, i10);
    loop_ub = unnamed_idx_0 * unnamed_idx_1;
    for (i10 = 0; i10 < loop_ub; i10++) {
      T->data[i10].re = rtNaN;
      T->data[i10].im = 0.0;
    }
  } else {
    i10 = T->size[0] * T->size[1];
    T->size[0] = A->size[0];
    T->size[1] = A->size[1];
    emxEnsureCapacity_creal_T(T, i10);
    loop_ub = A->size[0] * A->size[1];
    for (i10 = 0; i10 < loop_ub; i10++) {
      T->data[i10] = A->data[i10];
    }

    xgehrd(T, tau_data, tau_size);
    i10 = V->size[0] * V->size[1];
    V->size[0] = T->size[0];
    V->size[1] = T->size[1];
    emxEnsureCapacity_creal_T(V, i10);
    loop_ub = T->size[0] * T->size[1];
    for (i10 = 0; i10 < loop_ub; i10++) {
      V->data[i10] = T->data[i10];
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
