/*
 * File: nonSingletonDim.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 17-Jul-2020 17:26:12
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "nonSingletonDim.h"

/* Function Definitions */

/*
 * Arguments    : const int x_size[1]
 * Return Type  : int
 */
int nonSingletonDim(const int x_size[1])
{
  int dim;
  dim = 2;
  if (x_size[0] != 1) {
    dim = 1;
  }

  return dim;
}

/*
 * File trailer for nonSingletonDim.c
 *
 * [EOF]
 */
