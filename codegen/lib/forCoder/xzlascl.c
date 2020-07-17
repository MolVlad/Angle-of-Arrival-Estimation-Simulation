/*
 * File: xzlascl.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 16:31:04
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "xzlascl.h"
#include "forCoder_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : double cfrom
 *                double cto
 *                creal_T A_data[]
 *                int A_size[1]
 * Return Type  : void
 */
void b_xzlascl(double cfrom, double cto, creal_T A_data[], int A_size[1])
{
  double cfromc;
  double ctoc;
  boolean_T notdone;
  double cfrom1;
  double cto1;
  double a;
  int loop_ub;
  int i42;
  cfromc = cfrom;
  ctoc = cto;
  notdone = true;
  while (notdone) {
    cfrom1 = cfromc * 2.0041683600089728E-292;
    cto1 = ctoc / 4.9896007738368E+291;
    if ((fabs(cfrom1) > fabs(ctoc)) && (ctoc != 0.0)) {
      a = 2.0041683600089728E-292;
      cfromc = cfrom1;
    } else if (fabs(cto1) > fabs(cfromc)) {
      a = 4.9896007738368E+291;
      ctoc = cto1;
    } else {
      a = ctoc / cfromc;
      notdone = false;
    }

    loop_ub = A_size[0];
    for (i42 = 0; i42 < loop_ub; i42++) {
      A_data[i42].re *= a;
      A_data[i42].im *= a;
    }
  }
}

/*
 * Arguments    : double cfrom
 *                double cto
 *                emxArray_creal_T *A
 * Return Type  : void
 */
void xzlascl(double cfrom, double cto, emxArray_creal_T *A)
{
  double cfromc;
  double ctoc;
  boolean_T notdone;
  double cfrom1;
  double cto1;
  double a;
  int i38;
  int loop_ub;
  int b_loop_ub;
  int i39;
  cfromc = cfrom;
  ctoc = cto;
  notdone = true;
  while (notdone) {
    cfrom1 = cfromc * 2.0041683600089728E-292;
    cto1 = ctoc / 4.9896007738368E+291;
    if ((fabs(cfrom1) > fabs(ctoc)) && (ctoc != 0.0)) {
      a = 2.0041683600089728E-292;
      cfromc = cfrom1;
    } else if (fabs(cto1) > fabs(cfromc)) {
      a = 4.9896007738368E+291;
      ctoc = cto1;
    } else {
      a = ctoc / cfromc;
      notdone = false;
    }

    i38 = A->size[0] * A->size[1];
    emxEnsureCapacity_creal_T(A, i38);
    loop_ub = A->size[1];
    for (i38 = 0; i38 < loop_ub; i38++) {
      b_loop_ub = A->size[0];
      for (i39 = 0; i39 < b_loop_ub; i39++) {
        A->data[i39 + A->size[0] * i38].re *= a;
        A->data[i39 + A->size[0] * i38].im *= a;
      }
    }
  }
}

/*
 * File trailer for xzlascl.c
 *
 * [EOF]
 */
