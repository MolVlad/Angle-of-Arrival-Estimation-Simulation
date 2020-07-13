/*
 * File: sum.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 13-Jul-2020 18:10:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "sum.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *x
 *                creal_T y[1082401]
 * Return Type  : void
 */
void sum(const emxArray_creal_T *x, creal_T y[1082401])
{
  int vlen;
  int j;
  int k;
  int xoffset;
  int i13;
  vlen = x->size[1];
  if (x->size[1] == 0) {
    for (vlen = 0; vlen < 1082401; vlen++) {
      y[vlen].re = 0.0;
      y[vlen].im = 0.0;
    }
  } else {
    for (j = 0; j < 1082401; j++) {
      y[j] = x->data[j];
    }

    for (k = 2; k <= vlen; k++) {
      xoffset = (k - 1) * 1082401;
      for (j = 0; j < 1082401; j++) {
        i13 = xoffset + j;
        y[j].re += x->data[i13].re;
        y[j].im += x->data[i13].im;
      }
    }
  }
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */
