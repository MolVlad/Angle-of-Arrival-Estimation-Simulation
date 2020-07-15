/*
 * File: xztgevc.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 12:14:31
 */

/* Include Files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "xztgevc.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *A
 *                emxArray_creal_T *V
 * Return Type  : void
 */
void xztgevc(const emxArray_creal_T *A, emxArray_creal_T *V)
{
  int n;
  int loop_ub;
  creal_T work1_data[224];
  creal_T work2_data[224];
  double SMALL;
  double BIG;
  double BIGNUM;
  double rworka_data[224];
  double anorm;
  int i38;
  int j;
  double xmx;
  double y;
  double ascale;
  int je;
  int b_je;
  double temp;
  double temp_re;
  double salpha_re;
  double salpha_im;
  double acoeff;
  boolean_T lscalea;
  boolean_T lscaleb;
  double scale;
  double acoefa;
  int jr;
  double dmin;
  int b_j;
  double d_re;
  double d_im;
  n = A->size[0] - 1;
  loop_ub = A->size[0];
  if (0 <= loop_ub - 1) {
    memset(&work1_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(creal_T)));
  }

  loop_ub = A->size[0];
  if (0 <= loop_ub - 1) {
    memset(&work2_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(creal_T)));
  }

  SMALL = 2.2250738585072014E-308 * (double)A->size[0] / 2.2204460492503131E-16;
  BIG = 1.0 / SMALL;
  BIGNUM = 1.0 / (2.2250738585072014E-308 * (double)A->size[0]);
  loop_ub = A->size[0];
  if (0 <= loop_ub - 1) {
    memset(&rworka_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(double)));
  }

  anorm = fabs(A->data[0].re) + fabs(A->data[0].im);
  i38 = A->size[0];
  for (j = 0; j <= i38 - 2; j++) {
    for (loop_ub = 0; loop_ub <= j; loop_ub++) {
      rworka_data[j + 1] += fabs(A->data[loop_ub + A->size[0] * (j + 1)].re) +
        fabs(A->data[loop_ub + A->size[0] * (j + 1)].im);
    }

    y = rworka_data[j + 1] + (fabs(A->data[(j + A->size[0] * (j + 1)) + 1].re) +
      fabs(A->data[(j + A->size[0] * (j + 1)) + 1].im));
    if (y > anorm) {
      anorm = y;
    }
  }

  xmx = anorm;
  if (2.2250738585072014E-308 > anorm) {
    xmx = 2.2250738585072014E-308;
  }

  ascale = 1.0 / xmx;
  i38 = (int)((1.0 + (-1.0 - (double)A->size[0])) / -1.0);
  for (je = 0; je < i38; je++) {
    b_je = n - je;
    xmx = (fabs(A->data[b_je + A->size[0] * b_je].re) + fabs(A->data[b_je +
            A->size[0] * b_je].im)) * ascale;
    if (1.0 > xmx) {
      xmx = 1.0;
    }

    temp = 1.0 / xmx;
    temp_re = temp * A->data[b_je + A->size[0] * b_je].re;
    xmx = temp * A->data[b_je + A->size[0] * b_je].im;
    salpha_re = ascale * temp_re;
    salpha_im = ascale * xmx;
    acoeff = temp * ascale;
    if ((temp >= 2.2250738585072014E-308) && (fabs(acoeff) < SMALL)) {
      lscalea = true;
    } else {
      lscalea = false;
    }

    temp_re = fabs(salpha_re) + fabs(salpha_im);
    if ((temp_re >= 2.2250738585072014E-308) && (temp_re < SMALL)) {
      lscaleb = true;
    } else {
      lscaleb = false;
    }

    scale = 1.0;
    if (lscalea) {
      xmx = anorm;
      if (BIG < anorm) {
        xmx = BIG;
      }

      scale = SMALL / temp * xmx;
    }

    if (lscaleb) {
      xmx = 1.0;
      if (BIG < 1.0) {
        xmx = BIG;
      }

      y = SMALL / temp_re * xmx;
      if (y > scale) {
        scale = y;
      }
    }

    if (lscalea || lscaleb) {
      xmx = fabs(acoeff);
      if (1.0 > xmx) {
        xmx = 1.0;
      }

      if (temp_re > xmx) {
        xmx = temp_re;
      }

      y = 1.0 / (2.2250738585072014E-308 * xmx);
      if (y < scale) {
        scale = y;
      }

      if (lscalea) {
        acoeff = ascale * (scale * temp);
      } else {
        acoeff *= scale;
      }

      salpha_re *= scale;
      salpha_im *= scale;
    }

    acoefa = fabs(acoeff);
    for (jr = 0; jr <= n; jr++) {
      work1_data[jr].re = 0.0;
      work1_data[jr].im = 0.0;
    }

    work1_data[b_je].re = 1.0;
    work1_data[b_je].im = 0.0;
    dmin = 2.2204460492503131E-16 * acoefa * anorm;
    y = 2.2204460492503131E-16 * (fabs(salpha_re) + fabs(salpha_im));
    if (y > dmin) {
      dmin = y;
    }

    if (2.2250738585072014E-308 > dmin) {
      dmin = 2.2250738585072014E-308;
    }

    for (jr = 0; jr < b_je; jr++) {
      work1_data[jr].re = acoeff * A->data[jr + A->size[0] * b_je].re;
      work1_data[jr].im = acoeff * A->data[jr + A->size[0] * b_je].im;
    }

    work1_data[b_je].re = 1.0;
    work1_data[b_je].im = 0.0;
    loop_ub = (int)((1.0 + (-1.0 - ((double)(b_je + 1) - 1.0))) / -1.0);
    for (j = 0; j < loop_ub; j++) {
      b_j = (b_je - j) - 1;
      d_re = acoeff * A->data[b_j + A->size[0] * b_j].re - salpha_re;
      d_im = acoeff * A->data[b_j + A->size[0] * b_j].im - salpha_im;
      if (fabs(d_re) + fabs(d_im) <= dmin) {
        d_re = dmin;
        d_im = 0.0;
      }

      xmx = fabs(d_re) + fabs(d_im);
      if (xmx < 1.0) {
        temp_re = fabs(work1_data[b_j].re) + fabs(work1_data[b_j].im);
        if (temp_re >= BIGNUM * xmx) {
          temp = 1.0 / temp_re;
          for (jr = 0; jr <= b_je; jr++) {
            work1_data[jr].re *= temp;
            work1_data[jr].im *= temp;
          }
        }
      }

      y = -work1_data[b_j].re;
      if (d_im == 0.0) {
        if (-work1_data[b_j].im == 0.0) {
          work1_data[b_j].re = -work1_data[b_j].re / d_re;
          work1_data[b_j].im = 0.0;
        } else if (-work1_data[b_j].re == 0.0) {
          work1_data[b_j].re = 0.0;
          work1_data[b_j].im = -work1_data[b_j].im / d_re;
        } else {
          work1_data[b_j].re = -work1_data[b_j].re / d_re;
          work1_data[b_j].im = -work1_data[b_j].im / d_re;
        }
      } else if (d_re == 0.0) {
        if (-work1_data[b_j].re == 0.0) {
          work1_data[b_j].re = -work1_data[b_j].im / d_im;
          work1_data[b_j].im = 0.0;
        } else if (-work1_data[b_j].im == 0.0) {
          work1_data[b_j].re = 0.0;
          work1_data[b_j].im = -(y / d_im);
        } else {
          work1_data[b_j].re = -work1_data[b_j].im / d_im;
          work1_data[b_j].im = -(y / d_im);
        }
      } else {
        scale = fabs(d_re);
        xmx = fabs(d_im);
        if (scale > xmx) {
          temp_re = d_im / d_re;
          xmx = d_re + temp_re * d_im;
          work1_data[b_j].re = (-work1_data[b_j].re + temp_re * -work1_data[b_j]
                                .im) / xmx;
          work1_data[b_j].im = (-work1_data[b_j].im - temp_re * y) / xmx;
        } else if (xmx == scale) {
          if (d_re > 0.0) {
            temp_re = 0.5;
          } else {
            temp_re = -0.5;
          }

          if (d_im > 0.0) {
            xmx = 0.5;
          } else {
            xmx = -0.5;
          }

          work1_data[b_j].re = (-work1_data[b_j].re * temp_re + -work1_data[b_j]
                                .im * xmx) / scale;
          work1_data[b_j].im = (-work1_data[b_j].im * temp_re - y * xmx) / scale;
        } else {
          temp_re = d_re / d_im;
          xmx = d_im + temp_re * d_re;
          work1_data[b_j].re = (temp_re * -work1_data[b_j].re + -work1_data[b_j]
                                .im) / xmx;
          work1_data[b_j].im = (temp_re * -work1_data[b_j].im - y) / xmx;
        }
      }

      if (b_j + 1 > 1) {
        xmx = fabs(work1_data[b_j].re) + fabs(work1_data[b_j].im);
        if (xmx > 1.0) {
          temp = 1.0 / xmx;
          if (acoefa * rworka_data[b_j] >= BIGNUM * temp) {
            for (jr = 0; jr <= b_je; jr++) {
              work1_data[jr].re *= temp;
              work1_data[jr].im *= temp;
            }
          }
        }

        d_re = acoeff * work1_data[b_j].re;
        d_im = acoeff * work1_data[b_j].im;
        for (jr = 0; jr < b_j; jr++) {
          xmx = d_re * A->data[jr + A->size[0] * b_j].re - d_im * A->data[jr +
            A->size[0] * b_j].im;
          temp_re = d_re * A->data[jr + A->size[0] * b_j].im + d_im * A->data[jr
            + A->size[0] * b_j].re;
          work1_data[jr].re += xmx;
          work1_data[jr].im += temp_re;
        }
      }
    }

    for (jr = 0; jr <= n; jr++) {
      work2_data[jr].re = 0.0;
      work2_data[jr].im = 0.0;
    }

    for (loop_ub = 0; loop_ub <= b_je; loop_ub++) {
      for (jr = 0; jr <= n; jr++) {
        xmx = V->data[jr + V->size[0] * loop_ub].re * work1_data[loop_ub].re -
          V->data[jr + V->size[0] * loop_ub].im * work1_data[loop_ub].im;
        temp_re = V->data[jr + V->size[0] * loop_ub].re * work1_data[loop_ub].im
          + V->data[jr + V->size[0] * loop_ub].im * work1_data[loop_ub].re;
        work2_data[jr].re += xmx;
        work2_data[jr].im += temp_re;
      }
    }

    xmx = fabs(work2_data[0].re) + fabs(work2_data[0].im);
    if (n + 1 > 1) {
      for (jr = 0; jr < n; jr++) {
        y = fabs(work2_data[jr + 1].re) + fabs(work2_data[jr + 1].im);
        if (y > xmx) {
          xmx = y;
        }
      }
    }

    if (xmx > 2.2250738585072014E-308) {
      temp = 1.0 / xmx;
      for (jr = 0; jr <= n; jr++) {
        V->data[jr + V->size[0] * b_je].re = temp * work2_data[jr].re;
        V->data[jr + V->size[0] * b_je].im = temp * work2_data[jr].im;
      }
    } else {
      for (jr = 0; jr <= n; jr++) {
        V->data[jr + V->size[0] * b_je].re = 0.0;
        V->data[jr + V->size[0] * b_je].im = 0.0;
      }
    }
  }
}

/*
 * File trailer for xztgevc.c
 *
 * [EOF]
 */
