/*
 * File: hankel.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 23-Jul-2020 18:38:00
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
  int i8;
  int istop;
  int u1;
  int j;
  int i;
  nrows = c_size[0];
  ncols = r_size[0];
  i8 = H->size[0] * H->size[1];
  H->size[0] = c_size[0];
  H->size[1] = r_size[0];
  emxEnsureCapacity_creal_T(H, i8);
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

    i8 = istop + 1;
    for (i = i8; i <= nrows; i++) {
      H->data[(i + H->size[0] * j) - 1] = r_data[i - istop];
    }
  }

  i8 = c_size[0] + 1;
  for (j = i8; j <= ncols; j++) {
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
