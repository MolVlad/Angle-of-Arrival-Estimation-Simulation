/*
 * File: triu.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Jul-2020 11:32:44
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "triu.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_creal_T *x
 * Return Type  : void
 */
void triu(emxArray_creal_T *x)
{
  int m;
  int istart;
  int jend;
  int j;
  int i;
  m = x->size[0];
  if ((x->size[0] == 0) || (x->size[1] == 0) || (1 >= x->size[0])) {
  } else {
    istart = 2;
    if (x->size[0] - 2 < x->size[1] - 1) {
      jend = x->size[0] - 1;
    } else {
      jend = x->size[1];
    }

    for (j = 0; j < jend; j++) {
      for (i = istart; i <= m; i++) {
        x->data[(i + x->size[0] * j) - 1].re = 0.0;
        x->data[(i + x->size[0] * j) - 1].im = 0.0;
      }

      istart++;
    }
  }
}

/*
 * File trailer for triu.c
 *
 * [EOF]
 */
