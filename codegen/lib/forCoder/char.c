/*
 * File: char.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 13-Jul-2020 18:10:32
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
  int i8;
  int loop_ub;
  i8 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = varargin_1->size[1];
  emxEnsureCapacity_char_T(y, i8);
  loop_ub = varargin_1->size[1];
  for (i8 = 0; i8 < loop_ub; i8++) {
    y->data[i8] = (signed char)varargin_1->data[i8];
  }
}

/*
 * File trailer for char.c
 *
 * [EOF]
 */
