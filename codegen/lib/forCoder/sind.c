/*
 * File: sind.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 13-Jul-2020 18:10:32
 */

/* Include Files */
#include <float.h>
#include <math.h>
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "sind.h"

/* Function Declarations */
static double rt_remd_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_remd_snf(double u0, double u1)
{
  double y;
  double q;
  if (rtIsNaN(u0) || rtIsInf(u0) || (rtIsNaN(u1) || rtIsInf(u1))) {
    y = rtNaN;
  } else if ((u1 != 0.0) && (u1 != trunc(u1))) {
    q = fabs(u0 / u1);
    if (fabs(q - floor(q + 0.5)) <= DBL_EPSILON * q) {
      y = 0.0 * u0;
    } else {
      y = fmod(u0, u1);
    }
  } else {
    y = fmod(u0, u1);
  }

  return y;
}

/*
 * Arguments    : double x[1801]
 * Return Type  : void
 */
void b_sind(double x[1801])
{
  int k;
  double b_x;
  double absx;
  signed char n;
  for (k = 0; k < 1801; k++) {
    b_x = rt_remd_snf(x[k], 360.0);
    absx = fabs(b_x);
    if (absx > 180.0) {
      if (b_x > 0.0) {
        b_x -= 360.0;
      } else {
        b_x += 360.0;
      }

      absx = fabs(b_x);
    }

    if (absx <= 45.0) {
      b_x *= 0.017453292519943295;
      n = 0;
    } else if (absx <= 135.0) {
      if (b_x > 0.0) {
        b_x = 0.017453292519943295 * (b_x - 90.0);
        n = 1;
      } else {
        b_x = 0.017453292519943295 * (b_x + 90.0);
        n = -1;
      }
    } else if (b_x > 0.0) {
      b_x = 0.017453292519943295 * (b_x - 180.0);
      n = 2;
    } else {
      b_x = 0.017453292519943295 * (b_x + 180.0);
      n = -2;
    }

    if (n == 0) {
      x[k] = sin(b_x);
    } else if (n == 1) {
      x[k] = cos(b_x);
    } else if (n == -1) {
      x[k] = -cos(b_x);
    } else {
      x[k] = -sin(b_x);
    }
  }
}

/*
 * File trailer for sind.c
 *
 * [EOF]
 */
