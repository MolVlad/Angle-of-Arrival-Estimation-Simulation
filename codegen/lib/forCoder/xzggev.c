/*
 * File: xzggev.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Jul-2020 11:32:44
 */

/* Include Files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "xzggev.h"
#include "forCoder_emxutil.h"
#include "xzlascl.h"
#include "xzggbak.h"
#include "xztgevc.h"
#include "xzhgeqz.h"
#include "xzgghrd.h"
#include "xzggbal.h"
#include "isfinite.h"
#include "xzlangeM.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_creal_T *A
 *                int *info
 *                creal_T alpha1_data[]
 *                int alpha1_size[1]
 *                creal_T beta1_data[]
 *                int beta1_size[1]
 *                emxArray_creal_T *V
 * Return Type  : void
 */
void xzggev(emxArray_creal_T *A, int *info, creal_T alpha1_data[], int
            alpha1_size[1], creal_T beta1_data[], int beta1_size[1],
            emxArray_creal_T *V)
{
  int n;
  int loop_ub;
  int ihi;
  double anrm;
  boolean_T ilascl;
  double anrmto;
  int rscale_data[464];
  int rscale_size[1];
  double vtemp;
  double y;
  *info = 0;
  n = A->size[0] - 1;
  alpha1_size[0] = A->size[0];
  loop_ub = A->size[0];
  if (0 <= loop_ub - 1) {
    memset(&alpha1_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(creal_T)));
  }

  beta1_size[0] = A->size[0];
  loop_ub = A->size[0];
  if (0 <= loop_ub - 1) {
    memset(&beta1_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(creal_T)));
  }

  ihi = V->size[0] * V->size[1];
  V->size[0] = A->size[0];
  V->size[1] = A->size[0];
  emxEnsureCapacity_creal_T(V, ihi);
  loop_ub = A->size[0] * A->size[0];
  for (ihi = 0; ihi < loop_ub; ihi++) {
    V->data[ihi].re = 0.0;
    V->data[ihi].im = 0.0;
  }

  if ((A->size[0] != 0) && (A->size[1] != 0)) {
    anrm = xzlangeM(A);
    if (!b_isfinite(anrm)) {
      alpha1_size[0] = A->size[0];
      loop_ub = A->size[0];
      for (ihi = 0; ihi < loop_ub; ihi++) {
        alpha1_data[ihi].re = rtNaN;
        alpha1_data[ihi].im = 0.0;
      }

      beta1_size[0] = A->size[0];
      loop_ub = A->size[0];
      for (ihi = 0; ihi < loop_ub; ihi++) {
        beta1_data[ihi].re = rtNaN;
        beta1_data[ihi].im = 0.0;
      }

      ihi = V->size[0] * V->size[1];
      V->size[0] = A->size[0];
      V->size[1] = A->size[0];
      emxEnsureCapacity_creal_T(V, ihi);
      loop_ub = A->size[0] * A->size[0];
      for (ihi = 0; ihi < loop_ub; ihi++) {
        V->data[ihi].re = rtNaN;
        V->data[ihi].im = 0.0;
      }
    } else {
      ilascl = false;
      anrmto = anrm;
      if ((anrm > 0.0) && (anrm < 6.7178761075670888E-139)) {
        anrmto = 6.7178761075670888E-139;
        ilascl = true;
      } else {
        if (anrm > 1.4885657073574029E+138) {
          anrmto = 1.4885657073574029E+138;
          ilascl = true;
        }
      }

      if (ilascl) {
        xzlascl(anrm, anrmto, A);
      }

      xzggbal(A, &loop_ub, &ihi, rscale_data, rscale_size);
      xzgghrd(loop_ub, ihi, A, V);
      xzhgeqz(A, loop_ub, ihi, V, info, alpha1_data, alpha1_size, beta1_data,
              beta1_size);
      if (*info == 0) {
        xztgevc(A, V);
        xzggbak(V, loop_ub, ihi, rscale_data);
        for (loop_ub = 0; loop_ub <= n; loop_ub++) {
          vtemp = fabs(V->data[V->size[0] * loop_ub].re) + fabs(V->data[V->size
            [0] * loop_ub].im);
          if (n + 1 > 1) {
            for (ihi = 0; ihi < n; ihi++) {
              y = fabs(V->data[(ihi + V->size[0] * loop_ub) + 1].re) + fabs
                (V->data[(ihi + V->size[0] * loop_ub) + 1].im);
              if (y > vtemp) {
                vtemp = y;
              }
            }
          }

          if (vtemp >= 6.7178761075670888E-139) {
            vtemp = 1.0 / vtemp;
            for (ihi = 0; ihi <= n; ihi++) {
              V->data[ihi + V->size[0] * loop_ub].re *= vtemp;
              V->data[ihi + V->size[0] * loop_ub].im *= vtemp;
            }
          }
        }

        if (ilascl) {
          b_xzlascl(anrmto, anrm, alpha1_data, alpha1_size);
        }
      }
    }
  }
}

/*
 * File trailer for xzggev.c
 *
 * [EOF]
 */
