/*
 * File: diag.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 12:14:31
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "diag.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *v
 *                double d_data[]
 *                int d_size[1]
 * Return Type  : void
 */
void diag(const emxArray_real_T *v, double d_data[], int d_size[1])
{
  int u0;
  int u1;
  if ((v->size[0] == 1) && (v->size[1] == 1)) {
    d_size[0] = 1;
    d_data[0] = v->data[0];
  } else {
    u0 = v->size[0];
    u1 = v->size[1];
    if (u0 < u1) {
      u1 = u0;
    }

    if (0 < v->size[1]) {
      u0 = u1;
    } else {
      u0 = 0;
    }

    d_size[0] = (unsigned char)u0;
    u0--;
    for (u1 = 0; u1 <= u0; u1++) {
      d_data[u1] = v->data[u1 + v->size[0] * u1];
    }
  }
}

/*
 * File trailer for diag.c
 *
 * [EOF]
 */
