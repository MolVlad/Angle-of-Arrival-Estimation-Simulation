/*
 * File: xzlangeM.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 16:54:31
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "xzlangeM.h"
#include "abs.h"
#include "forCoder_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *x
 * Return Type  : double
 */
double xzlangeM(const emxArray_creal_T *x)
{
  double y;
  boolean_T b0;
  boolean_T b1;
  int k;
  boolean_T exitg1;
  double absxk;
  y = 0.0;
  b0 = (x->size[0] == 0);
  b1 = (x->size[1] == 0);
  if ((!b0) && (!b1)) {
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= x->size[0] * x->size[1] - 1)) {
      absxk = rt_hypotd_snf(x->data[k].re, x->data[k].im);
      if (rtIsNaN(absxk)) {
        y = rtNaN;
        exitg1 = true;
      } else {
        if (absxk > y) {
          y = absxk;
        }

        k++;
      }
    }
  }

  return y;
}

/*
 * File trailer for xzlangeM.c
 *
 * [EOF]
 */
