/*
 * File: hankel.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Jul-2020 11:32:44
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "hankel.h"
#include "forCoder_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const creal_T c_data[]
 *                const int c_size[1]
 *                const creal_T r_data[]
 *                const int r_size[1]
 *                emxArray_creal_T *H
 * Return Type  : void
 */
void hankel(const creal_T c_data[], const int c_size[1], const creal_T r_data[],
            const int r_size[1], emxArray_creal_T *H)
{
  int nrows;
  int ncols;
  int i9;
  int istop;
  int u1;
  int j;
  int i;
  nrows = c_size[0];
  ncols = r_size[0];
  i9 = H->size[0] * H->size[1];
  H->size[0] = c_size[0];
  H->size[1] = r_size[0];
  emxEnsureCapacity_creal_T(H, i9);
  istop = c_size[0];
  u1 = r_size[0];
  if (istop < u1) {
    u1 = istop;
  }

  for (j = 0; j < u1; j++) {
    istop = nrows - j;
    for (i = 0; i < istop; i++) {
      H->data[i + H->size[0] * j] = c_data[i + j];
    }

    i9 = istop + 1;
    for (i = i9; i <= nrows; i++) {
      H->data[(i + H->size[0] * j) - 1] = r_data[i - istop];
    }
  }

  i9 = c_size[0] + 1;
  for (j = i9; j <= ncols; j++) {
    istop = j - nrows;
    for (i = 0; i < nrows; i++) {
      H->data[i + H->size[0] * (j - 1)] = r_data[i + istop];
    }
  }
}

/*
 * File trailer for hankel.c
 *
 * [EOF]
 */
