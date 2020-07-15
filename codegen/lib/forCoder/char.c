/*
 * File: char.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 12:14:31
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
  int i6;
  int loop_ub;
  i6 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = varargin_1->size[1];
  emxEnsureCapacity_char_T(y, i6);
  loop_ub = varargin_1->size[1];
  for (i6 = 0; i6 < loop_ub; i6++) {
    y->data[i6] = (signed char)varargin_1->data[i6];
  }
}

/*
 * File trailer for char.c
 *
 * [EOF]
 */
