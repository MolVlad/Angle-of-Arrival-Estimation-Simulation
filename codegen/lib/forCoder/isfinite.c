/*
 * File: isfinite.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 16:31:04
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "isfinite.h"

/* Function Definitions */

/*
 * Arguments    : double x
 * Return Type  : boolean_T
 */
boolean_T b_isfinite(double x)
{
  return (!rtIsInf(x)) && (!rtIsNaN(x));
}

/*
 * File trailer for isfinite.c
 *
 * [EOF]
 */
