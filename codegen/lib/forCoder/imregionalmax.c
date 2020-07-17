/*
 * File: imregionalmax.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 16:31:04
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "imregionalmax.h"
#include "libmwimregionalmax.h"

/* Function Definitions */

/*
 * Arguments    : const double varargin_1[108781]
 *                boolean_T BW[108781]
 * Return Type  : void
 */
void imregionalmax(const double varargin_1[108781], boolean_T BW[108781])
{
  int i13;
  boolean_T conn[9];
  double imSizeT[2];
  double connSizeT[2];
  for (i13 = 0; i13 < 9; i13++) {
    conn[i13] = true;
  }

  imSizeT[0] = 601.0;
  connSizeT[0] = 3.0;
  imSizeT[1] = 181.0;
  connSizeT[1] = 3.0;
  imregionalmax_real64(varargin_1, BW, 2.0, imSizeT, conn, 2.0, connSizeT);
}

/*
 * File trailer for imregionalmax.c
 *
 * [EOF]
 */
