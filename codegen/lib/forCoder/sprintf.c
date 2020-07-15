/*
 * File: sprintf.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 12:14:31
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "sprintf.h"
#include "forCoder_emxutil.h"
#include <stdio.h>

/* Function Definitions */

/*
 * Arguments    : int varargin_1
 *                emxArray_char_T *str
 * Return Type  : void
 */
void b_sprintf(int varargin_1, emxArray_char_T *str)
{
  int nbytes;
  int i4;
  nbytes = (int)snprintf(NULL, 0, "%d", varargin_1);
  i4 = str->size[0] * str->size[1];
  str->size[0] = 1;
  str->size[1] = nbytes + 1;
  emxEnsureCapacity_char_T(str, i4);
  snprintf(&str->data[0], (size_t)(nbytes + 1), "%d", varargin_1);
  if (1 > nbytes) {
    str->size[1] = 0;
  } else {
    i4 = str->size[0] * str->size[1];
    str->size[1] = nbytes;
    emxEnsureCapacity_char_T(str, i4);
  }
}

/*
 * File trailer for sprintf.c
 *
 * [EOF]
 */
