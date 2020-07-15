/*
 * File: xzlarfg.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 16:54:31
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "xzlarfg.h"
#include "recip.h"
#include "xdlapy3.h"
#include "xnrm2.h"

/* Function Definitions */

/*
 * Arguments    : int n
 *                creal_T *alpha1
 *                emxArray_creal_T *x
 *                int ix0
 * Return Type  : creal_T
 */
creal_T xzlarfg(int n, creal_T *alpha1, emxArray_creal_T *x, int ix0)
{
  creal_T tau;
  double xnorm;
  double beta1;
  int knt;
  double ai;
  int i26;
  int k;
  creal_T b_alpha1;
  double x_re;
  double x_im;
  tau.re = 0.0;
  tau.im = 0.0;
  if (n > 0) {
    xnorm = xnrm2(n - 1, x, ix0);
    if ((xnorm != 0.0) || (alpha1->im != 0.0)) {
      beta1 = xdlapy3(alpha1->re, alpha1->im, xnorm);
      if (alpha1->re >= 0.0) {
        beta1 = -beta1;
      }

      if (fabs(beta1) < 1.0020841800044864E-292) {
        knt = -1;
        i26 = (ix0 + n) - 2;
        do {
          knt++;
          for (k = ix0; k <= i26; k++) {
            x_re = x->data[k - 1].re;
            x_im = x->data[k - 1].im;
            x->data[k - 1].re = 9.9792015476736E+291 * x_re - 0.0 * x_im;
            x->data[k - 1].im = 9.9792015476736E+291 * x_im + 0.0 * x_re;
          }

          beta1 *= 9.9792015476736E+291;
          alpha1->re *= 9.9792015476736E+291;
          alpha1->im *= 9.9792015476736E+291;
        } while (!(fabs(beta1) >= 1.0020841800044864E-292));

        beta1 = xdlapy3(alpha1->re, alpha1->im, xnrm2(n - 1, x, ix0));
        if (alpha1->re >= 0.0) {
          beta1 = -beta1;
        }

        xnorm = beta1 - alpha1->re;
        ai = 0.0 - alpha1->im;
        if (ai == 0.0) {
          tau.re = xnorm / beta1;
          tau.im = 0.0;
        } else if (xnorm == 0.0) {
          tau.re = 0.0;
          tau.im = ai / beta1;
        } else {
          tau.re = xnorm / beta1;
          tau.im = ai / beta1;
        }

        b_alpha1.re = alpha1->re - beta1;
        b_alpha1.im = alpha1->im;
        *alpha1 = recip(b_alpha1);
        i26 = (ix0 + n) - 2;
        for (k = ix0; k <= i26; k++) {
          xnorm = alpha1->re;
          ai = alpha1->im;
          x_re = x->data[k - 1].re;
          x_im = x->data[k - 1].im;
          x->data[k - 1].re = xnorm * x_re - ai * x_im;
          x->data[k - 1].im = xnorm * x_im + ai * x_re;
        }

        for (k = 0; k <= knt; k++) {
          beta1 *= 1.0020841800044864E-292;
        }

        alpha1->re = beta1;
        alpha1->im = 0.0;
      } else {
        xnorm = beta1 - alpha1->re;
        ai = 0.0 - alpha1->im;
        if (ai == 0.0) {
          tau.re = xnorm / beta1;
          tau.im = 0.0;
        } else if (xnorm == 0.0) {
          tau.re = 0.0;
          tau.im = ai / beta1;
        } else {
          tau.re = xnorm / beta1;
          tau.im = ai / beta1;
        }

        b_alpha1.re = alpha1->re - beta1;
        b_alpha1.im = alpha1->im;
        *alpha1 = recip(b_alpha1);
        i26 = (ix0 + n) - 2;
        for (k = ix0; k <= i26; k++) {
          xnorm = alpha1->re;
          ai = alpha1->im;
          x_re = x->data[k - 1].re;
          x_im = x->data[k - 1].im;
          x->data[k - 1].re = xnorm * x_re - ai * x_im;
          x->data[k - 1].im = xnorm * x_im + ai * x_re;
        }

        alpha1->re = beta1;
        alpha1->im = 0.0;
      }
    }
  }

  return tau;
}

/*
 * File trailer for xzlarfg.c
 *
 * [EOF]
 */
