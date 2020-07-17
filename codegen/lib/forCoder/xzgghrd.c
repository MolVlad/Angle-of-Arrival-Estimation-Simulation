/*
 * File: xzgghrd.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 16:31:04
 */

/* Include Files */
#include <string.h>
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
  int n;
  int jcolp1;
  int jrow;
  int loop_ub;
  signed char I_data[50176];
  int jcol;
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
  n = A->size[0];
  jcolp1 = A->size[0];
  jrow = A->size[0];
  loop_ub = A->size[0] * A->size[0];
  if (0 <= loop_ub - 1) {
    memset(&I_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(signed char)));
  }

  if (A->size[0] > 0) {
    for (loop_ub = 0; loop_ub < n; loop_ub++) {
      I_data[loop_ub + jcolp1 * loop_ub] = 1;
    }
  }

  jcol = Z->size[0] * Z->size[1];
  Z->size[0] = jcolp1;
  Z->size[1] = jrow;
  emxEnsureCapacity_creal_T(Z, jcol);
  loop_ub = jcolp1 * jrow;
  for (jcol = 0; jcol < loop_ub; jcol++) {
    Z->data[jcol].re = I_data[jcol];
    Z->data[jcol].im = 0.0;
  }

  if ((A->size[0] > 1) && (ihi >= ilo + 2)) {
    for (jcol = ilo - 1; jcol + 1 < ihi - 1; jcol++) {
      jcolp1 = jcol + 2;
      for (jrow = ihi - 1; jrow + 1 > jcol + 2; jrow--) {
        b_A = A->data[(jrow + A->size[0] * jcol) - 1];
        c_A = A->data[jrow + A->size[0] * jcol];
        xzlartg(b_A, c_A, &c, &s, &A->data[(jrow + A->size[0] * jcol) - 1]);
        A->data[jrow + A->size[0] * jcol].re = 0.0;
        A->data[jrow + A->size[0] * jcol].im = 0.0;
        for (loop_ub = jcolp1; loop_ub <= n; loop_ub++) {
          s_re = s.re * A->data[jrow + A->size[0] * (loop_ub - 1)].re - s.im *
            A->data[jrow + A->size[0] * (loop_ub - 1)].im;
          s_im = s.re * A->data[jrow + A->size[0] * (loop_ub - 1)].im + s.im *
            A->data[jrow + A->size[0] * (loop_ub - 1)].re;
          stemp_re = c * A->data[(jrow + A->size[0] * (loop_ub - 1)) - 1].re +
            s_re;
          stemp_im = c * A->data[(jrow + A->size[0] * (loop_ub - 1)) - 1].im +
            s_im;
          s_re = A->data[(jrow + A->size[0] * (loop_ub - 1)) - 1].re;
          s_im = A->data[(jrow + A->size[0] * (loop_ub - 1)) - 1].im;
          A_im = A->data[(jrow + A->size[0] * (loop_ub - 1)) - 1].im;
          A_re = A->data[(jrow + A->size[0] * (loop_ub - 1)) - 1].re;
          A->data[jrow + A->size[0] * (loop_ub - 1)].re = c * A->data[jrow +
            A->size[0] * (loop_ub - 1)].re - (s.re * s_re + s.im * s_im);
          A->data[jrow + A->size[0] * (loop_ub - 1)].im = c * A->data[jrow +
            A->size[0] * (loop_ub - 1)].im - (s.re * A_im - s.im * A_re);
          A->data[(jrow + A->size[0] * (loop_ub - 1)) - 1].re = stemp_re;
          A->data[(jrow + A->size[0] * (loop_ub - 1)) - 1].im = stemp_im;
        }

        s.re = -s.re;
        s.im = -s.im;
        for (loop_ub = 1; loop_ub <= ihi; loop_ub++) {
          s_re = s.re * A->data[(loop_ub + A->size[0] * (jrow - 1)) - 1].re -
            s.im * A->data[(loop_ub + A->size[0] * (jrow - 1)) - 1].im;
          s_im = s.re * A->data[(loop_ub + A->size[0] * (jrow - 1)) - 1].im +
            s.im * A->data[(loop_ub + A->size[0] * (jrow - 1)) - 1].re;
          stemp_re = c * A->data[(loop_ub + A->size[0] * jrow) - 1].re + s_re;
          stemp_im = c * A->data[(loop_ub + A->size[0] * jrow) - 1].im + s_im;
          s_re = A->data[(loop_ub + A->size[0] * jrow) - 1].re;
          s_im = A->data[(loop_ub + A->size[0] * jrow) - 1].im;
          A_im = A->data[(loop_ub + A->size[0] * jrow) - 1].im;
          A_re = A->data[(loop_ub + A->size[0] * jrow) - 1].re;
          A->data[(loop_ub + A->size[0] * (jrow - 1)) - 1].re = c * A->data
            [(loop_ub + A->size[0] * (jrow - 1)) - 1].re - (s.re * s_re + s.im *
            s_im);
          A->data[(loop_ub + A->size[0] * (jrow - 1)) - 1].im = c * A->data
            [(loop_ub + A->size[0] * (jrow - 1)) - 1].im - (s.re * A_im - s.im *
            A_re);
          A->data[(loop_ub + A->size[0] * jrow) - 1].re = stemp_re;
          A->data[(loop_ub + A->size[0] * jrow) - 1].im = stemp_im;
        }

        for (loop_ub = 1; loop_ub <= n; loop_ub++) {
          s_re = s.re * Z->data[(loop_ub + Z->size[0] * (jrow - 1)) - 1].re -
            s.im * Z->data[(loop_ub + Z->size[0] * (jrow - 1)) - 1].im;
          s_im = s.re * Z->data[(loop_ub + Z->size[0] * (jrow - 1)) - 1].im +
            s.im * Z->data[(loop_ub + Z->size[0] * (jrow - 1)) - 1].re;
          stemp_re = c * Z->data[(loop_ub + Z->size[0] * jrow) - 1].re + s_re;
          stemp_im = c * Z->data[(loop_ub + Z->size[0] * jrow) - 1].im + s_im;
          s_re = Z->data[(loop_ub + Z->size[0] * jrow) - 1].re;
          s_im = Z->data[(loop_ub + Z->size[0] * jrow) - 1].im;
          A_im = Z->data[(loop_ub + Z->size[0] * jrow) - 1].im;
          A_re = Z->data[(loop_ub + Z->size[0] * jrow) - 1].re;
          Z->data[(loop_ub + Z->size[0] * (jrow - 1)) - 1].re = c * Z->data
            [(loop_ub + Z->size[0] * (jrow - 1)) - 1].re - (s.re * s_re + s.im *
            s_im);
          Z->data[(loop_ub + Z->size[0] * (jrow - 1)) - 1].im = c * Z->data
            [(loop_ub + Z->size[0] * (jrow - 1)) - 1].im - (s.re * A_im - s.im *
            A_re);
          Z->data[(loop_ub + Z->size[0] * jrow) - 1].re = stemp_re;
          Z->data[(loop_ub + Z->size[0] * jrow) - 1].im = stemp_im;
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
