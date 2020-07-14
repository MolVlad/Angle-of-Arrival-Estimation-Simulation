/*
 * File: sort1.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Jul-2020 11:32:44
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "sort1.h"
#include "sortIdx.h"
#include "nonSingletonDim.h"

/* Function Definitions */

/*
 * Arguments    : double x_data[]
 *                int x_size[1]
 *                int idx_data[]
 *                int idx_size[1]
 * Return Type  : void
 */
void sort(double x_data[], int x_size[1], int idx_data[], int idx_size[1])
{
  int dim;
  int i44;
  int vlen;
  int vwork_size[1];
  int vstride;
  int k;
  double vwork_data[464];
  int iidx_data[464];
  int iidx_size[1];
  dim = nonSingletonDim(x_size);
  if (dim <= 1) {
    i44 = x_size[0];
  } else {
    i44 = 1;
  }

  vlen = i44 - 1;
  vwork_size[0] = (short)i44;
  idx_size[0] = (short)x_size[0];
  vstride = 1;
  for (k = 0; k <= dim - 2; k++) {
    vstride *= x_size[0];
  }

  for (dim = 0; dim < vstride; dim++) {
    for (k = 0; k <= vlen; k++) {
      vwork_data[k] = x_data[dim + k * vstride];
    }

    sortIdx(vwork_data, vwork_size, iidx_data, iidx_size);
    for (k = 0; k <= vlen; k++) {
      i44 = dim + k * vstride;
      x_data[i44] = vwork_data[k];
      idx_data[i44] = iidx_data[k];
    }
  }
}

/*
 * File trailer for sort1.c
 *
 * [EOF]
 */
