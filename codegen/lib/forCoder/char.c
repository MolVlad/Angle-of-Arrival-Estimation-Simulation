/*
 * File: char.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 23-Jul-2020 18:38:00
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "char.h"
#include "forCoder_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_uint8_T *varargin_1
 *                emxArray_char_T *y
 * Return Type  : void
 */
void b_char(const emxArray_uint8_T *varargin_1, emxArray_char_T *y)
{
  int i7;
  int loop_ub;
  i7 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = varargin_1->size[1];
  emxEnsureCapacity_char_T(y, i7);
  loop_ub = varargin_1->size[1];
  for (i7 = 0; i7 < loop_ub; i7++) {
    y->data[i7] = (signed char)varargin_1->data[i7];
  }
}

/*
 * File trailer for char.c
 *
 * [EOF]
 */
