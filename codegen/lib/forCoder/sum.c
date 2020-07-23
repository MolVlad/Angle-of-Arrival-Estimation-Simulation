/*
 * File: sum.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 23-Jul-2020 18:38:00
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "sum.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *x
 *                creal_T y[108781]
 * Return Type  : void
 */
void sum(const emxArray_creal_T *x, creal_T y[108781])
{
  int vlen;
  int j;
  int k;
  int xoffset;
  int i12;
  vlen = x->size[1];
  if (x->size[1] == 0) {
    for (vlen = 0; vlen < 108781; vlen++) {
      y[vlen].re = 0.0;
      y[vlen].im = 0.0;
    }
  } else {
    for (j = 0; j < 108781; j++) {
      y[j] = x->data[j];
    }

    for (k = 2; k <= vlen; k++) {
      xoffset = (k - 1) * 108781;
      for (j = 0; j < 108781; j++) {
        i12 = xoffset + j;
        y[j].re += x->data[i12].re;
        y[j].im += x->data[i12].im;
      }
    }
  }
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */
