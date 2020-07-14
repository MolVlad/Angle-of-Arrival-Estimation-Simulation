/*
 * File: xhseqr.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Jul-2020 11:32:44
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "xhseqr.h"
#include "xzhseqr.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_creal_T *h
 *                emxArray_creal_T *z
 * Return Type  : int
 */
int xhseqr(emxArray_creal_T *h, emxArray_creal_T *z)
{
  int info;
  int m;
  int istart;
  int jend;
  int j;
  int i;
  info = eml_zlahqr(h, z);
  m = h->size[0];
  if ((h->size[0] == 0) || (h->size[1] == 0) || (3 >= h->size[0])) {
  } else {
    istart = 4;
    if (h->size[0] - 4 < h->size[1] - 1) {
      jend = h->size[0] - 3;
    } else {
      jend = h->size[1];
    }

    for (j = 0; j < jend; j++) {
      for (i = istart; i <= m; i++) {
        h->data[(i + h->size[0] * j) - 1].re = 0.0;
        h->data[(i + h->size[0] * j) - 1].im = 0.0;
      }

      istart++;
    }
  }

  return info;
}

/*
 * File trailer for xhseqr.c
 *
 * [EOF]
 */
