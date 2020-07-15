/*
 * File: ftell.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 12:14:31
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "ftell.h"
#include "fileManager.h"

/* Function Definitions */

/*
 * Arguments    : double fileID
 * Return Type  : double
 */
double b_ftell(double fileID)
{
  double position;
  FILE * filestar;
  boolean_T a;
  long position_t;
  getfilestar(fileID, &filestar, &a);
  if ((fileID != 0.0) && (fileID != 1.0) && (fileID != 2.0)) {
  } else {
    filestar = NULL;
  }

  if (filestar == NULL) {
    position = -1.0;
  } else {
    position_t = ftell(filestar);
    position = (double)position_t;
  }

  return position;
}

/*
 * File trailer for ftell.c
 *
 * [EOF]
 */
