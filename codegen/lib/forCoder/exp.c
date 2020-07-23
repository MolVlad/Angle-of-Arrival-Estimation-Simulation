/*
 * File: exp.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 23-Jul-2020 18:38:00
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "exp.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_creal_T *x
 * Return Type  : void
 */
void b_exp(emxArray_creal_T *x)
{
  int nx;
  int k;
  double r;
  double x_im;
  double b_x_im;
  nx = x->size[0] * 601;
  for (k = 0; k < nx; k++) {
    if (x->data[k].im == 0.0) {
      r = x->data[k].re;
      x->data[k].re = exp(r);
      x->data[k].im = 0.0;
    } else if (rtIsInf(x->data[k].im) && rtIsInf(x->data[k].re) && (x->data[k].
                re < 0.0)) {
      x->data[k].re = 0.0;
      x->data[k].im = 0.0;
    } else {
      r = exp(x->data[k].re / 2.0);
      x_im = x->data[k].im;
      b_x_im = x->data[k].im;
      x->data[k].re = r * (r * cos(x_im));
      x->data[k].im = r * (r * sin(b_x_im));
    }
  }
}

/*
 * Arguments    : creal_T x_data[]
 *                int x_size[2]
 * Return Type  : void
 */
void c_exp(creal_T x_data[], int x_size[2])
{
  int nx;
  int k;
  double r;
  double x_data_im;
  nx = x_size[0] * 181;
  for (k = 0; k < nx; k++) {
    if (x_data[k].im == 0.0) {
      x_data[k].re = exp(x_data[k].re);
      x_data[k].im = 0.0;
    } else if (rtIsInf(x_data[k].im) && rtIsInf(x_data[k].re) && (x_data[k].re <
                0.0)) {
      x_data[k].re = 0.0;
      x_data[k].im = 0.0;
    } else {
      r = exp(x_data[k].re / 2.0);
      x_data_im = x_data[k].im;
      x_data[k].re = r * (r * cos(x_data[k].im));
      x_data[k].im = r * (r * sin(x_data_im));
    }
  }
}

/*
 * File trailer for exp.c
 *
 * [EOF]
 */
