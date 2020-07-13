/*
 * File: eig.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 13-Jul-2020 18:10:32
 */

/* Include Files */
#include <math.h>
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "eig.h"
#include "forCoder_emxutil.h"
#include "schur.h"
#include "xzgeev.h"
#include "ishermitian.h"
#include "anyNonFinite.h"

/* Function Declarations */
static void diagDiagUpperHessNoImag(emxArray_creal_T *D);
static void makeD(const creal_T alpha1_data[], const int alpha1_size[1], const
                  creal_T beta1_data[], emxArray_creal_T *D);
static void setDiag(emxArray_creal_T *D, const creal_T val);

/* Function Definitions */

/*
 * Arguments    : emxArray_creal_T *D
 * Return Type  : void
 */
static void diagDiagUpperHessNoImag(emxArray_creal_T *D)
{
  int n;
  double D_re;
  int j;
  int i;
  n = D->size[0];
  D_re = D->data[0].re;
  D->data[0].re = D_re;
  D->data[0].im = 0.0;
  for (j = 2; j <= n; j++) {
    D_re = D->data[(j + D->size[0] * (j - 1)) - 1].re;
    D->data[(j + D->size[0] * (j - 1)) - 1].re = D_re;
    D->data[(j + D->size[0] * (j - 1)) - 1].im = 0.0;
    D->data[(j + D->size[0] * (j - 2)) - 1].re = 0.0;
    D->data[(j + D->size[0] * (j - 2)) - 1].im = 0.0;
    for (i = 0; i <= j - 2; i++) {
      D->data[i + D->size[0] * (j - 1)].re = 0.0;
      D->data[i + D->size[0] * (j - 1)].im = 0.0;
    }
  }
}

/*
 * Arguments    : const creal_T alpha1_data[]
 *                const int alpha1_size[1]
 *                const creal_T beta1_data[]
 *                emxArray_creal_T *D
 * Return Type  : void
 */
static void makeD(const creal_T alpha1_data[], const int alpha1_size[1], const
                  creal_T beta1_data[], emxArray_creal_T *D)
{
  int i12;
  int loop_ub;
  double brm;
  double bim;
  double d;
  i12 = D->size[0] * D->size[1];
  D->size[0] = alpha1_size[0];
  D->size[1] = alpha1_size[0];
  emxEnsureCapacity_creal_T(D, i12);
  loop_ub = alpha1_size[0] * alpha1_size[0];
  for (i12 = 0; i12 < loop_ub; i12++) {
    D->data[i12].re = 0.0;
    D->data[i12].im = 0.0;
  }

  i12 = alpha1_size[0];
  for (loop_ub = 0; loop_ub < i12; loop_ub++) {
    if (beta1_data[loop_ub].im == 0.0) {
      if (alpha1_data[loop_ub].im == 0.0) {
        D->data[loop_ub + D->size[0] * loop_ub].re = alpha1_data[loop_ub].re /
          beta1_data[loop_ub].re;
        D->data[loop_ub + D->size[0] * loop_ub].im = 0.0;
      } else if (alpha1_data[loop_ub].re == 0.0) {
        D->data[loop_ub + D->size[0] * loop_ub].re = 0.0;
        D->data[loop_ub + D->size[0] * loop_ub].im = alpha1_data[loop_ub].im /
          beta1_data[loop_ub].re;
      } else {
        D->data[loop_ub + D->size[0] * loop_ub].re = alpha1_data[loop_ub].re /
          beta1_data[loop_ub].re;
        D->data[loop_ub + D->size[0] * loop_ub].im = alpha1_data[loop_ub].im /
          beta1_data[loop_ub].re;
      }
    } else if (beta1_data[loop_ub].re == 0.0) {
      if (alpha1_data[loop_ub].re == 0.0) {
        D->data[loop_ub + D->size[0] * loop_ub].re = alpha1_data[loop_ub].im /
          beta1_data[loop_ub].im;
        D->data[loop_ub + D->size[0] * loop_ub].im = 0.0;
      } else if (alpha1_data[loop_ub].im == 0.0) {
        D->data[loop_ub + D->size[0] * loop_ub].re = 0.0;
        D->data[loop_ub + D->size[0] * loop_ub].im = -(alpha1_data[loop_ub].re /
          beta1_data[loop_ub].im);
      } else {
        D->data[loop_ub + D->size[0] * loop_ub].re = alpha1_data[loop_ub].im /
          beta1_data[loop_ub].im;
        D->data[loop_ub + D->size[0] * loop_ub].im = -(alpha1_data[loop_ub].re /
          beta1_data[loop_ub].im);
      }
    } else {
      brm = fabs(beta1_data[loop_ub].re);
      bim = fabs(beta1_data[loop_ub].im);
      if (brm > bim) {
        bim = beta1_data[loop_ub].im / beta1_data[loop_ub].re;
        d = beta1_data[loop_ub].re + bim * beta1_data[loop_ub].im;
        D->data[loop_ub + D->size[0] * loop_ub].re = (alpha1_data[loop_ub].re +
          bim * alpha1_data[loop_ub].im) / d;
        D->data[loop_ub + D->size[0] * loop_ub].im = (alpha1_data[loop_ub].im -
          bim * alpha1_data[loop_ub].re) / d;
      } else if (bim == brm) {
        if (beta1_data[loop_ub].re > 0.0) {
          bim = 0.5;
        } else {
          bim = -0.5;
        }

        if (beta1_data[loop_ub].im > 0.0) {
          d = 0.5;
        } else {
          d = -0.5;
        }

        D->data[loop_ub + D->size[0] * loop_ub].re = (alpha1_data[loop_ub].re *
          bim + alpha1_data[loop_ub].im * d) / brm;
        D->data[loop_ub + D->size[0] * loop_ub].im = (alpha1_data[loop_ub].im *
          bim - alpha1_data[loop_ub].re * d) / brm;
      } else {
        bim = beta1_data[loop_ub].re / beta1_data[loop_ub].im;
        d = beta1_data[loop_ub].im + bim * beta1_data[loop_ub].re;
        D->data[loop_ub + D->size[0] * loop_ub].re = (bim * alpha1_data[loop_ub]
          .re + alpha1_data[loop_ub].im) / d;
        D->data[loop_ub + D->size[0] * loop_ub].im = (bim * alpha1_data[loop_ub]
          .im - alpha1_data[loop_ub].re) / d;
      }
    }
  }
}

/*
 * Arguments    : emxArray_creal_T *D
 *                const creal_T val
 * Return Type  : void
 */
static void setDiag(emxArray_creal_T *D, const creal_T val)
{
  int i25;
  int k;
  i25 = D->size[0];
  for (k = 0; k < i25; k++) {
    D->data[k + D->size[0] * k] = val;
  }
}

/*
 * Arguments    : emxArray_creal_T *A
 *                emxArray_creal_T *V
 * Return Type  : void
 */
void eig(emxArray_creal_T *A, emxArray_creal_T *V)
{
  static creal_T dc0 = { 0.0,          /* re */
    0.0                                /* im */
  };

  int i23;
  short unnamed_idx_0;
  int info;
  creal_T alpha1_data[464];
  int alpha1_size[1];
  creal_T beta1_data[464];
  int beta1_size[1];
  emxArray_creal_T *b_A;
  short unnamed_idx_1;
  int loop_ub;
  int i24;
  dc0.re = rtGetNaN();
  if ((A->size[0] == 0) || (A->size[1] == 0)) {
    i23 = V->size[0] * V->size[1];
    V->size[0] = A->size[0];
    V->size[1] = A->size[1];
    emxEnsureCapacity_creal_T(V, i23);
    info = A->size[0] * A->size[1];
    for (i23 = 0; i23 < info; i23++) {
      V->data[i23] = A->data[i23];
    }
  } else if (anyNonFinite(A)) {
    if ((A->size[0] == 1) && (A->size[1] == 1)) {
      unnamed_idx_0 = (short)A->size[0];
      unnamed_idx_1 = (short)A->size[1];
      i23 = V->size[0] * V->size[1];
      V->size[0] = unnamed_idx_0;
      V->size[1] = unnamed_idx_1;
      emxEnsureCapacity_creal_T(V, i23);
      info = unnamed_idx_0 * unnamed_idx_1;
      for (i23 = 0; i23 < info; i23++) {
        V->data[i23] = dc0;
      }

      i23 = A->size[0] * A->size[1];
      emxEnsureCapacity_creal_T(A, i23);
      info = A->size[1];
      for (i23 = 0; i23 < info; i23++) {
        loop_ub = A->size[0];
        for (i24 = 0; i24 < loop_ub; i24++) {
          A->data[i24 + A->size[0] * i23] = dc0;
        }
      }
    } else {
      unnamed_idx_0 = (short)A->size[0];
      unnamed_idx_1 = (short)A->size[1];
      i23 = V->size[0] * V->size[1];
      V->size[0] = unnamed_idx_0;
      V->size[1] = unnamed_idx_1;
      emxEnsureCapacity_creal_T(V, i23);
      info = unnamed_idx_0 * unnamed_idx_1;
      for (i23 = 0; i23 < info; i23++) {
        V->data[i23].re = rtNaN;
        V->data[i23].im = 0.0;
      }

      unnamed_idx_0 = (short)A->size[0];
      unnamed_idx_1 = (short)A->size[1];
      i23 = A->size[0] * A->size[1];
      A->size[0] = unnamed_idx_0;
      A->size[1] = unnamed_idx_1;
      emxEnsureCapacity_creal_T(A, i23);
      info = unnamed_idx_1;
      for (i23 = 0; i23 < info; i23++) {
        loop_ub = unnamed_idx_0;
        for (i24 = 0; i24 < loop_ub; i24++) {
          A->data[i24 + A->size[0] * i23].re = 0.0;
          A->data[i24 + A->size[0] * i23].im = 0.0;
        }
      }

      setDiag(A, dc0);
    }
  } else if ((A->size[0] == 1) && (A->size[1] == 1)) {
    unnamed_idx_0 = (short)A->size[0];
    unnamed_idx_1 = (short)A->size[1];
    i23 = V->size[0] * V->size[1];
    V->size[0] = unnamed_idx_0;
    V->size[1] = unnamed_idx_1;
    emxEnsureCapacity_creal_T(V, i23);
    info = unnamed_idx_0 * unnamed_idx_1;
    for (i23 = 0; i23 < info; i23++) {
      V->data[i23].re = 1.0;
      V->data[i23].im = 0.0;
    }
  } else if (ishermitian(A)) {
    emxInit_creal_T(&b_A, 2);
    i23 = b_A->size[0] * b_A->size[1];
    b_A->size[0] = A->size[0];
    b_A->size[1] = A->size[1];
    emxEnsureCapacity_creal_T(b_A, i23);
    info = A->size[0] * A->size[1];
    for (i23 = 0; i23 < info; i23++) {
      b_A->data[i23] = A->data[i23];
    }

    schur(b_A, V, A);
    diagDiagUpperHessNoImag(A);
    emxFree_creal_T(&b_A);
  } else {
    xzgeev(A, &info, alpha1_data, alpha1_size, beta1_data, beta1_size, V);
    makeD(alpha1_data, alpha1_size, beta1_data, A);
  }
}

/*
 * File trailer for eig.c
 *
 * [EOF]
 */
