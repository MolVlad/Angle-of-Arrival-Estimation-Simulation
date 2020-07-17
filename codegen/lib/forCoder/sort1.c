/*
 * File: sort1.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 17-Jul-2020 17:26:12
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
  int i43;
  int vlen;
  int vwork_size[1];
  int vstride;
  int k;
  double vwork_data[224];
  int iidx_data[224];
  int iidx_size[1];
  dim = nonSingletonDim(x_size);
  if (dim <= 1) {
    i43 = x_size[0];
  } else {
    i43 = 1;
  }

  vlen = i43 - 1;
  vwork_size[0] = (unsigned char)i43;
  idx_size[0] = (unsigned char)x_size[0];
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
      i43 = dim + k * vstride;
      x_data[i43] = vwork_data[k];
      idx_data[i43] = iidx_data[k];
    }
  }
}

/*
 * File trailer for sort1.c
 *
 * [EOF]
 */
