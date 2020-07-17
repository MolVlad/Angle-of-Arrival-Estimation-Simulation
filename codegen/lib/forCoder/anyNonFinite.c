/*
 * File: anyNonFinite.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 17-Jul-2020 17:26:12
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "anyNonFinite.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *x
 * Return Type  : boolean_T
 */
boolean_T anyNonFinite(const emxArray_creal_T *x)
{
  boolean_T p;
  int nx;
  int k;
  nx = x->size[0] * x->size[1];
  p = true;
  for (k = 0; k < nx; k++) {
    if (p && ((!rtIsInf(x->data[k].re)) && (!rtIsInf(x->data[k].im)) &&
              ((!rtIsNaN(x->data[k].re)) && (!rtIsNaN(x->data[k].im))))) {
      p = true;
    } else {
      p = false;
    }
  }

  return !p;
}

/*
 * File trailer for anyNonFinite.c
 *
 * [EOF]
 */
