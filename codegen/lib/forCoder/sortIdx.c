/*
 * File: sortIdx.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 12:14:31
 */

/* Include Files */
#include <string.h>
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "sortIdx.h"

/* Function Declarations */
static void merge(int idx_data[], double x_data[], int offset, int np, int nq,
                  int iwork_data[], double xwork_data[]);
static void merge_block(int idx_data[], double x_data[], int n, int iwork_data[],
  double xwork_data[]);

/* Function Definitions */

/*
 * Arguments    : int idx_data[]
 *                double x_data[]
 *                int offset
 *                int np
 *                int nq
 *                int iwork_data[]
 *                double xwork_data[]
 * Return Type  : void
 */
static void merge(int idx_data[], double x_data[], int offset, int np, int nq,
                  int iwork_data[], double xwork_data[])
{
  int n_tmp;
  int iout;
  int p;
  int i42;
  int q;
  int exitg1;
  if (nq != 0) {
    n_tmp = np + nq;
    for (iout = 0; iout < n_tmp; iout++) {
      i42 = offset + iout;
      iwork_data[iout] = idx_data[i42];
      xwork_data[iout] = x_data[i42];
    }

    p = 0;
    q = np;
    iout = offset - 1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork_data[p] <= xwork_data[q]) {
        idx_data[iout] = iwork_data[p];
        x_data[iout] = xwork_data[p];
        if (p + 1 < np) {
          p++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx_data[iout] = iwork_data[q];
        x_data[iout] = xwork_data[q];
        if (q + 1 < n_tmp) {
          q++;
        } else {
          q = iout - p;
          for (iout = p + 1; iout <= np; iout++) {
            i42 = q + iout;
            idx_data[i42] = iwork_data[iout - 1];
            x_data[i42] = xwork_data[iout - 1];
          }

          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

/*
 * Arguments    : int idx_data[]
 *                double x_data[]
 *                int n
 *                int iwork_data[]
 *                double xwork_data[]
 * Return Type  : void
 */
static void merge_block(int idx_data[], double x_data[], int n, int iwork_data[],
  double xwork_data[])
{
  int nPairs;
  int bLen;
  int tailOffset;
  int nTail;
  nPairs = n >> 2;
  bLen = 4;
  while (nPairs > 1) {
    if ((nPairs & 1) != 0) {
      nPairs--;
      tailOffset = bLen * nPairs;
      nTail = n - tailOffset;
      if (nTail > bLen) {
        merge(idx_data, x_data, tailOffset, bLen, nTail - bLen, iwork_data,
              xwork_data);
      }
    }

    tailOffset = bLen << 1;
    nPairs >>= 1;
    for (nTail = 0; nTail < nPairs; nTail++) {
      merge(idx_data, x_data, nTail * tailOffset, bLen, bLen, iwork_data,
            xwork_data);
    }

    bLen = tailOffset;
  }

  if (n > bLen) {
    merge(idx_data, x_data, 0, bLen, n - bLen, iwork_data, xwork_data);
  }
}

/*
 * Arguments    : double x_data[]
 *                int x_size[1]
 *                int idx_data[]
 *                int idx_size[1]
 * Return Type  : void
 */
void sortIdx(double x_data[], int x_size[1], int idx_data[], int idx_size[1])
{
  unsigned char x_idx_0;
  int n;
  double x4[4];
  unsigned char idx4[4];
  int ib;
  double xwork_data[224];
  int nNaNs;
  int k;
  int i4;
  int idx_data_tmp;
  signed char perm[4];
  int quartetOffset;
  int i2;
  int i3;
  int iwork_data[224];
  double d0;
  double d1;
  x_idx_0 = (unsigned char)x_size[0];
  idx_size[0] = x_idx_0;
  if (0 <= x_idx_0 - 1) {
    memset(&idx_data[0], 0, (unsigned int)(x_idx_0 * (int)sizeof(int)));
  }

  if (x_size[0] != 0) {
    n = x_size[0];
    x4[0] = 0.0;
    idx4[0] = 0U;
    x4[1] = 0.0;
    idx4[1] = 0U;
    x4[2] = 0.0;
    idx4[2] = 0U;
    x4[3] = 0.0;
    idx4[3] = 0U;
    ib = (unsigned char)x_size[0];
    if (0 <= ib - 1) {
      memset(&xwork_data[0], 0, (unsigned int)(ib * (int)sizeof(double)));
    }

    nNaNs = 0;
    ib = -1;
    for (k = 0; k < n; k++) {
      if (rtIsNaN(x_data[k])) {
        idx_data_tmp = (n - nNaNs) - 1;
        idx_data[idx_data_tmp] = k + 1;
        xwork_data[idx_data_tmp] = x_data[k];
        nNaNs++;
      } else {
        ib++;
        idx4[ib] = (unsigned char)(k + 1);
        x4[ib] = x_data[k];
        if (ib + 1 == 4) {
          quartetOffset = k - nNaNs;
          if (x4[0] <= x4[1]) {
            ib = 1;
            i2 = 2;
          } else {
            ib = 2;
            i2 = 1;
          }

          if (x4[2] <= x4[3]) {
            i3 = 3;
            i4 = 4;
          } else {
            i3 = 4;
            i4 = 3;
          }

          d0 = x4[ib - 1];
          d1 = x4[i3 - 1];
          if (d0 <= d1) {
            if (x4[i2 - 1] <= d1) {
              perm[0] = (signed char)ib;
              perm[1] = (signed char)i2;
              perm[2] = (signed char)i3;
              perm[3] = (signed char)i4;
            } else if (x4[i2 - 1] <= x4[i4 - 1]) {
              perm[0] = (signed char)ib;
              perm[1] = (signed char)i3;
              perm[2] = (signed char)i2;
              perm[3] = (signed char)i4;
            } else {
              perm[0] = (signed char)ib;
              perm[1] = (signed char)i3;
              perm[2] = (signed char)i4;
              perm[3] = (signed char)i2;
            }
          } else {
            d1 = x4[i4 - 1];
            if (d0 <= d1) {
              if (x4[i2 - 1] <= d1) {
                perm[0] = (signed char)i3;
                perm[1] = (signed char)ib;
                perm[2] = (signed char)i2;
                perm[3] = (signed char)i4;
              } else {
                perm[0] = (signed char)i3;
                perm[1] = (signed char)ib;
                perm[2] = (signed char)i4;
                perm[3] = (signed char)i2;
              }
            } else {
              perm[0] = (signed char)i3;
              perm[1] = (signed char)i4;
              perm[2] = (signed char)ib;
              perm[3] = (signed char)i2;
            }
          }

          idx_data_tmp = perm[0] - 1;
          idx_data[quartetOffset - 3] = idx4[idx_data_tmp];
          i3 = perm[1] - 1;
          idx_data[quartetOffset - 2] = idx4[i3];
          ib = perm[2] - 1;
          idx_data[quartetOffset - 1] = idx4[ib];
          i2 = perm[3] - 1;
          idx_data[quartetOffset] = idx4[i2];
          x_data[quartetOffset - 3] = x4[idx_data_tmp];
          x_data[quartetOffset - 2] = x4[i3];
          x_data[quartetOffset - 1] = x4[ib];
          x_data[quartetOffset] = x4[i2];
          ib = -1;
        }
      }
    }

    i4 = (n - nNaNs) - 1;
    if (ib + 1 > 0) {
      perm[1] = 0;
      perm[2] = 0;
      perm[3] = 0;
      if (ib + 1 == 1) {
        perm[0] = 1;
      } else if (ib + 1 == 2) {
        if (x4[0] <= x4[1]) {
          perm[0] = 1;
          perm[1] = 2;
        } else {
          perm[0] = 2;
          perm[1] = 1;
        }
      } else if (x4[0] <= x4[1]) {
        if (x4[1] <= x4[2]) {
          perm[0] = 1;
          perm[1] = 2;
          perm[2] = 3;
        } else if (x4[0] <= x4[2]) {
          perm[0] = 1;
          perm[1] = 3;
          perm[2] = 2;
        } else {
          perm[0] = 3;
          perm[1] = 1;
          perm[2] = 2;
        }
      } else if (x4[0] <= x4[2]) {
        perm[0] = 2;
        perm[1] = 1;
        perm[2] = 3;
      } else if (x4[1] <= x4[2]) {
        perm[0] = 2;
        perm[1] = 3;
        perm[2] = 1;
      } else {
        perm[0] = 3;
        perm[1] = 2;
        perm[2] = 1;
      }

      for (k = 0; k <= ib; k++) {
        idx_data_tmp = perm[k] - 1;
        i3 = (i4 - ib) + k;
        idx_data[i3] = idx4[idx_data_tmp];
        x_data[i3] = x4[idx_data_tmp];
      }
    }

    ib = (nNaNs >> 1) + 1;
    for (k = 0; k <= ib - 2; k++) {
      i2 = (i4 + k) + 1;
      i3 = idx_data[i2];
      idx_data_tmp = (n - k) - 1;
      idx_data[i2] = idx_data[idx_data_tmp];
      idx_data[idx_data_tmp] = i3;
      x_data[i2] = xwork_data[idx_data_tmp];
      x_data[idx_data_tmp] = xwork_data[i2];
    }

    if ((nNaNs & 1) != 0) {
      i4 += ib;
      x_data[i4] = xwork_data[i4];
    }

    ib = x_size[0] - nNaNs;
    if (ib > 1) {
      if (0 <= x_idx_0 - 1) {
        memset(&iwork_data[0], 0, (unsigned int)(x_idx_0 * (int)sizeof(int)));
      }

      merge_block(idx_data, x_data, ib, iwork_data, xwork_data);
    }
  }
}

/*
 * File trailer for sortIdx.c
 *
 * [EOF]
 */
