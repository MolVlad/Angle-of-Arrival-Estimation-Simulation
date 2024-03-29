/*
 * File: xzgeev.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 23-Jul-2020 18:38:00
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "xzgeev.h"
#include "xnrm2.h"
#include "forCoder_emxutil.h"
#include "xzggev.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *A
 *                int *info
 *                creal_T alpha1_data[]
 *                int alpha1_size[1]
 *                creal_T beta1_data[]
 *                int beta1_size[1]
 *                emxArray_creal_T *V
 * Return Type  : void
 */
void xzgeev(const emxArray_creal_T *A, int *info, creal_T alpha1_data[], int
            alpha1_size[1], creal_T beta1_data[], int beta1_size[1],
            emxArray_creal_T *V)
{
  emxArray_creal_T *At;
  int i10;
  int n;
  int lastcol;
  int coltop;
  double colnorm;
  int j;
  double V_re;
  double V_im;
  emxInit_creal_T(&At, 2);
  i10 = At->size[0] * At->size[1];
  At->size[0] = A->size[0];
  At->size[1] = A->size[1];
  emxEnsureCapacity_creal_T(At, i10);
  n = A->size[0] * A->size[1];
  for (i10 = 0; i10 < n; i10++) {
    At->data[i10] = A->data[i10];
  }

  xzggev(At, info, alpha1_data, alpha1_size, beta1_data, beta1_size, V);
  n = A->size[0];
  emxFree_creal_T(&At);
  if (A->size[0] > 0) {
    lastcol = (A->size[0] - 1) * A->size[0] + 1;
    for (coltop = 1; n < 0 ? coltop >= lastcol : coltop <= lastcol; coltop += n)
    {
      colnorm = xnrm2(n, V, coltop);
      i10 = (coltop + n) - 1;
      for (j = coltop; j <= i10; j++) {
        V_re = V->data[j - 1].re;
        V_im = V->data[j - 1].im;
        if (V_im == 0.0) {
          V->data[j - 1].re = V_re / colnorm;
          V->data[j - 1].im = 0.0;
        } else if (V_re == 0.0) {
          V->data[j - 1].re = 0.0;
          V->data[j - 1].im = V_im / colnorm;
        } else {
          V->data[j - 1].re = V_re / colnorm;
          V->data[j - 1].im = V_im / colnorm;
        }
      }
    }
  }
}

/*
 * File trailer for xzgeev.c
 *
 * [EOF]
 */
