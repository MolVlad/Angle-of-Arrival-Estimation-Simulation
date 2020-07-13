/*
 * File: imregionalmax.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 13-Jul-2020 18:10:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "imregionalmax.h"
#include "libmwimregionalmax.h"

/* Function Definitions */

/*
 * Arguments    : const double varargin_1[1082401]
 *                boolean_T BW[1082401]
 * Return Type  : void
 */
void imregionalmax(const double varargin_1[1082401], boolean_T BW[1082401])
{
  int i14;
  boolean_T conn[9];
  double imSizeT[2];
  double connSizeT[2];
  for (i14 = 0; i14 < 9; i14++) {
    conn[i14] = true;
  }

  imSizeT[0] = 601.0;
  connSizeT[0] = 3.0;
  imSizeT[1] = 1801.0;
  connSizeT[1] = 3.0;
  imregionalmax_real64(varargin_1, BW, 2.0, imSizeT, conn, 2.0, connSizeT);
}

/*
 * File trailer for imregionalmax.c
 *
 * [EOF]
 */
