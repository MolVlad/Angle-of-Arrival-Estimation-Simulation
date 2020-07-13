/*
 * File: fseek.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 13-Jul-2020 18:10:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "fseek.h"
#include "fileManager.h"
#include <stdio.h>

/* Type Definitions */

/* Function Definitions */

/*
 * Arguments    : double fileID
 * Return Type  : void
 */
void b_fseek(double fileID)
{
  int wherefrom;
  FILE * filestar;
  boolean_T a;
  wherefrom = SEEK_END;
  getfilestar(fileID, &filestar, &a);
  if ((fileID != 0.0) && (fileID != 1.0) && (fileID != 2.0)) {
  } else {
    filestar = NULL;
  }

  if (!(filestar == NULL)) {
    fseek(filestar, (long int)0.0, wherefrom);
  }
}

/*
 * Arguments    : double fileID
 * Return Type  : void
 */
void c_fseek(double fileID)
{
  int wherefrom;
  FILE * filestar;
  boolean_T a;
  wherefrom = SEEK_SET;
  getfilestar(fileID, &filestar, &a);
  if ((fileID != 0.0) && (fileID != 1.0) && (fileID != 2.0)) {
  } else {
    filestar = NULL;
  }

  if (!(filestar == NULL)) {
    fseek(filestar, (long int)0.0, wherefrom);
  }
}

/*
 * File trailer for fseek.c
 *
 * [EOF]
 */
