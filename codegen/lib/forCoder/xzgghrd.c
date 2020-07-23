/*
 * File: xzgghrd.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 23-Jul-2020 18:38:00
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "xzgghrd.h"
#include "xzlartg.h"
#include "forCoder_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : int ilo
 *                int ihi
 *                emxArray_creal_T *A
 *                emxArray_creal_T *Z
 * Return Type  : void
 */
void xzgghrd(int ilo, int ihi, emxArray_creal_T *A, emxArray_creal_T *Z)
{
  emxArray_int8_T *b_I;
  int n;
  int k;
  int jcol;
  int jcolp1;
  int jrow;
  creal_T b_A;
  creal_T c_A;
  double c;
  creal_T s;
  double s_re;
  double s_im;
  double stemp_re;
  double stemp_im;
  double A_im;
  double A_re;
  emxInit_int8_T(&b_I, 2);
  n = A->size[0];
  k = b_I->size[0] * b_I->size[1];
  b_I->size[0] = A->size[0];
  b_I->size[1] = A->size[0];
  emxEnsureCapacity_int8_T(b_I, k);
  jcol = A->size[0] * A->size[0];
  for (k = 0; k < jcol; k++) {
    b_I->data[k] = 0;
  }

  if (A->size[0] > 0) {
    for (k = 0; k < n; k++) {
      b_I->data[k + b_I->size[0] * k] = 1;
    }
  }

  k = Z->size[0] * Z->size[1];
  Z->size[0] = b_I->size[0];
  Z->size[1] = b_I->size[1];
  emxEnsureCapacity_creal_T(Z, k);
  jcol = b_I->size[0] * b_I->size[1];
  for (k = 0; k < jcol; k++) {
    Z->data[k].re = b_I->data[k];
    Z->data[k].im = 0.0;
  }

  emxFree_int8_T(&b_I);
  if ((A->size[0] > 1) && (ihi >= ilo + 2)) {
    for (jcol = ilo - 1; jcol + 1 < ihi - 1; jcol++) {
      jcolp1 = jcol + 2;
      for (jrow = ihi - 1; jrow + 1 > jcol + 2; jrow--) {
        b_A = A->data[(jrow + A->size[0] * jcol) - 1];
        c_A = A->data[jrow + A->size[0] * jcol];
        xzlartg(b_A, c_A, &c, &s, &A->data[(jrow + A->size[0] * jcol) - 1]);
        A->data[jrow + A->size[0] * jcol].re = 0.0;
        A->data[jrow + A->size[0] * jcol].im = 0.0;
        for (k = jcolp1; k <= n; k++) {
          s_re = s.re * A->data[jrow + A->size[0] * (k - 1)].re - s.im * A->
            data[jrow + A->size[0] * (k - 1)].im;
          s_im = s.re * A->data[jrow + A->size[0] * (k - 1)].im + s.im * A->
            data[jrow + A->size[0] * (k - 1)].re;
          stemp_re = c * A->data[(jrow + A->size[0] * (k - 1)) - 1].re + s_re;
          stemp_im = c * A->data[(jrow + A->size[0] * (k - 1)) - 1].im + s_im;
          s_re = A->data[(jrow + A->size[0] * (k - 1)) - 1].re;
          s_im = A->data[(jrow + A->size[0] * (k - 1)) - 1].im;
          A_im = A->data[(jrow + A->size[0] * (k - 1)) - 1].im;
          A_re = A->data[(jrow + A->size[0] * (k - 1)) - 1].re;
          A->data[jrow + A->size[0] * (k - 1)].re = c * A->data[jrow + A->size[0]
            * (k - 1)].re - (s.re * s_re + s.im * s_im);
          A->data[jrow + A->size[0] * (k - 1)].im = c * A->data[jrow + A->size[0]
            * (k - 1)].im - (s.re * A_im - s.im * A_re);
          A->data[(jrow + A->size[0] * (k - 1)) - 1].re = stemp_re;
          A->data[(jrow + A->size[0] * (k - 1)) - 1].im = stemp_im;
        }

        s.re = -s.re;
        s.im = -s.im;
        for (k = 1; k <= ihi; k++) {
          s_re = s.re * A->data[(k + A->size[0] * (jrow - 1)) - 1].re - s.im *
            A->data[(k + A->size[0] * (jrow - 1)) - 1].im;
          s_im = s.re * A->data[(k + A->size[0] * (jrow - 1)) - 1].im + s.im *
            A->data[(k + A->size[0] * (jrow - 1)) - 1].re;
          stemp_re = c * A->data[(k + A->size[0] * jrow) - 1].re + s_re;
          stemp_im = c * A->data[(k + A->size[0] * jrow) - 1].im + s_im;
          s_re = A->data[(k + A->size[0] * jrow) - 1].re;
          s_im = A->data[(k + A->size[0] * jrow) - 1].im;
          A_im = A->data[(k + A->size[0] * jrow) - 1].im;
          A_re = A->data[(k + A->size[0] * jrow) - 1].re;
          A->data[(k + A->size[0] * (jrow - 1)) - 1].re = c * A->data[(k +
            A->size[0] * (jrow - 1)) - 1].re - (s.re * s_re + s.im * s_im);
          A->data[(k + A->size[0] * (jrow - 1)) - 1].im = c * A->data[(k +
            A->size[0] * (jrow - 1)) - 1].im - (s.re * A_im - s.im * A_re);
          A->data[(k + A->size[0] * jrow) - 1].re = stemp_re;
          A->data[(k + A->size[0] * jrow) - 1].im = stemp_im;
        }

        for (k = 1; k <= n; k++) {
          s_re = s.re * Z->data[(k + Z->size[0] * (jrow - 1)) - 1].re - s.im *
            Z->data[(k + Z->size[0] * (jrow - 1)) - 1].im;
          s_im = s.re * Z->data[(k + Z->size[0] * (jrow - 1)) - 1].im + s.im *
            Z->data[(k + Z->size[0] * (jrow - 1)) - 1].re;
          stemp_re = c * Z->data[(k + Z->size[0] * jrow) - 1].re + s_re;
          stemp_im = c * Z->data[(k + Z->size[0] * jrow) - 1].im + s_im;
          s_re = Z->data[(k + Z->size[0] * jrow) - 1].re;
          s_im = Z->data[(k + Z->size[0] * jrow) - 1].im;
          A_im = Z->data[(k + Z->size[0] * jrow) - 1].im;
          A_re = Z->data[(k + Z->size[0] * jrow) - 1].re;
          Z->data[(k + Z->size[0] * (jrow - 1)) - 1].re = c * Z->data[(k +
            Z->size[0] * (jrow - 1)) - 1].re - (s.re * s_re + s.im * s_im);
          Z->data[(k + Z->size[0] * (jrow - 1)) - 1].im = c * Z->data[(k +
            Z->size[0] * (jrow - 1)) - 1].im - (s.re * A_im - s.im * A_re);
          Z->data[(k + Z->size[0] * jrow) - 1].re = stemp_re;
          Z->data[(k + Z->size[0] * jrow) - 1].im = stemp_im;
        }
      }
    }
  }
}

/*
 * File trailer for xzgghrd.c
 *
 * [EOF]
 */
