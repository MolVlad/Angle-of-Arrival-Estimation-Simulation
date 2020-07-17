/*
 * File: xgehrd.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 17-Jul-2020 17:26:12
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "xgehrd.h"
#include "xzlarf.h"
#include "xzlarfg.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_creal_T *a
 *                creal_T tau_data[]
 *                int tau_size[1]
 * Return Type  : void
 */
void xgehrd(emxArray_creal_T *a, creal_T tau_data[], int tau_size[1])
{
  int n;
  int ntau;
  unsigned char unnamed_idx_0;
  int i25;
  creal_T work_data[224];
  int im1n;
  int in;
  creal_T alpha1;
  int u0;
  creal_T dc1;
  creal_T dc2;
  n = a->size[0];
  if (a->size[0] < 1) {
    ntau = 0;
  } else {
    ntau = a->size[0] - 1;
  }

  tau_size[0] = (short)ntau;
  unnamed_idx_0 = (unsigned char)a->size[0];
  ntau = unnamed_idx_0;
  for (i25 = 0; i25 < ntau; i25++) {
    work_data[i25].re = 0.0;
    work_data[i25].im = 0.0;
  }

  i25 = a->size[0];
  for (ntau = 0; ntau <= i25 - 2; ntau++) {
    im1n = ntau * n + 2;
    in = (ntau + 1) * n;
    alpha1 = a->data[(ntau + a->size[0] * ntau) + 1];
    u0 = ntau + 3;
    if (u0 >= n) {
      u0 = n;
    }

    dc1 = xzlarfg((n - ntau) - 1, &alpha1, a, u0 + ntau * n);
    tau_data[ntau] = dc1;
    a->data[(ntau + a->size[0] * ntau) + 1].re = 1.0;
    a->data[(ntau + a->size[0] * ntau) + 1].im = 0.0;
    xzlarf(n, (n - ntau) - 1, ntau + im1n, dc1, a, in + 1, n, work_data);
    dc2.re = dc1.re;
    dc2.im = -dc1.im;
    b_xzlarf((n - ntau) - 1, (n - ntau) - 1, ntau + im1n, dc2, a, (ntau + in) +
             2, n, work_data);
    a->data[(ntau + a->size[0] * ntau) + 1] = alpha1;
  }
}

/*
 * File trailer for xgehrd.c
 *
 * [EOF]
 */
