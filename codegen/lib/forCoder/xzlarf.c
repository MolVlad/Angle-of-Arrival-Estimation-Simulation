/*
 * File: xzlarf.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 12:14:31
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "xzlarf.h"
#include "xgerc.h"
#include "xgemv.h"

/* Function Declarations */
static int ilazlc(int m, int n, const emxArray_creal_T *A, int ia0, int lda);
static int ilazlr(int m, int n, const emxArray_creal_T *A, int ia0, int lda);

/* Function Definitions */

/*
 * Arguments    : int m
 *                int n
 *                const emxArray_creal_T *A
 *                int ia0
 *                int lda
 * Return Type  : int
 */
static int ilazlc(int m, int n, const emxArray_creal_T *A, int ia0, int lda)
{
  int j;
  boolean_T exitg2;
  int coltop;
  int ia;
  int exitg1;
  boolean_T b_A;
  j = n;
  exitg2 = false;
  while ((!exitg2) && (j > 0)) {
    coltop = ia0 + (j - 1) * lda;
    ia = coltop;
    do {
      exitg1 = 0;
      if (ia <= (coltop + m) - 1) {
        b_A = ((A->data[ia - 1].re != 0.0) || (A->data[ia - 1].im != 0.0));
        if (b_A) {
          exitg1 = 1;
        } else {
          ia++;
        }
      } else {
        j--;
        exitg1 = 2;
      }
    } while (exitg1 == 0);

    if (exitg1 == 1) {
      exitg2 = true;
    }
  }

  return j;
}

/*
 * Arguments    : int m
 *                int n
 *                const emxArray_creal_T *A
 *                int ia0
 *                int lda
 * Return Type  : int
 */
static int ilazlr(int m, int n, const emxArray_creal_T *A, int ia0, int lda)
{
  int i;
  boolean_T exitg2;
  int rowleft;
  int rowright;
  int exitg1;
  boolean_T b_A;
  i = m;
  exitg2 = false;
  while ((!exitg2) && (i > 0)) {
    rowleft = (ia0 + i) - 1;
    rowright = rowleft + (n - 1) * lda;
    do {
      exitg1 = 0;
      if (((lda > 0) && (rowleft <= rowright)) || ((lda < 0) && (rowleft >=
            rowright))) {
        b_A = ((A->data[rowleft - 1].re != 0.0) || (A->data[rowleft - 1].im !=
                0.0));
        if (b_A) {
          exitg1 = 1;
        } else {
          rowleft += lda;
        }
      } else {
        i--;
        exitg1 = 2;
      }
    } while (exitg1 == 0);

    if (exitg1 == 1) {
      exitg2 = true;
    }
  }

  return i;
}

/*
 * Arguments    : int m
 *                int n
 *                int iv0
 *                const creal_T tau
 *                emxArray_creal_T *C
 *                int ic0
 *                int ldc
 *                creal_T work_data[]
 * Return Type  : void
 */
void b_xzlarf(int m, int n, int iv0, const creal_T tau, emxArray_creal_T *C, int
              ic0, int ldc, creal_T work_data[])
{
  int lastv;
  int lastc;
  boolean_T exitg1;
  creal_T b_tau;
  boolean_T b_C;
  if ((tau.re != 0.0) || (tau.im != 0.0)) {
    lastv = m;
    lastc = iv0 + m;
    exitg1 = false;
    while ((!exitg1) && (lastv > 0)) {
      b_C = ((C->data[lastc - 2].re == 0.0) && (C->data[lastc - 2].im == 0.0));
      if (b_C) {
        lastv--;
        lastc--;
      } else {
        exitg1 = true;
      }
    }

    lastc = ilazlc(lastv, n, C, ic0, ldc);
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    b_xgemv(lastv, lastc, C, ic0, ldc, C, iv0, work_data);
    b_tau.re = -tau.re;
    b_tau.im = -tau.im;
    b_xgerc(lastv, lastc, b_tau, iv0, work_data, C, ic0, ldc);
  }
}

/*
 * Arguments    : int m
 *                int n
 *                int iv0
 *                const creal_T tau
 *                emxArray_creal_T *C
 *                int ic0
 *                int ldc
 *                creal_T work_data[]
 * Return Type  : void
 */
void xzlarf(int m, int n, int iv0, const creal_T tau, emxArray_creal_T *C, int
            ic0, int ldc, creal_T work_data[])
{
  int lastv;
  int lastc;
  boolean_T exitg1;
  creal_T b_tau;
  boolean_T b_C;
  if ((tau.re != 0.0) || (tau.im != 0.0)) {
    lastv = n;
    lastc = iv0 + n;
    exitg1 = false;
    while ((!exitg1) && (lastv > 0)) {
      b_C = ((C->data[lastc - 2].re == 0.0) && (C->data[lastc - 2].im == 0.0));
      if (b_C) {
        lastv--;
        lastc--;
      } else {
        exitg1 = true;
      }
    }

    lastc = ilazlr(m, lastv, C, ic0, ldc);
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    xgemv(lastc, lastv, C, ic0, ldc, C, iv0, work_data);
    b_tau.re = -tau.re;
    b_tau.im = -tau.im;
    xgerc(lastc, lastv, b_tau, work_data, iv0, C, ic0, ldc);
  }
}

/*
 * File trailer for xzlarf.c
 *
 * [EOF]
 */
