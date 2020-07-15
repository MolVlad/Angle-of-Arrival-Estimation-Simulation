/*
 * File: ishermitian.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 12:14:31
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "ishermitian.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *A
 * Return Type  : boolean_T
 */
boolean_T ishermitian(const emxArray_creal_T *A)
{
  boolean_T p;
  int j;
  boolean_T exitg2;
  int i;
  int exitg1;
  double A_re;
  double A_im;
  boolean_T b_A;
  p = (A->size[0] == A->size[1]);
  if (p) {
    j = 0;
    exitg2 = false;
    while ((!exitg2) && (j <= A->size[1] - 1)) {
      i = 0;
      do {
        exitg1 = 0;
        if (i <= j) {
          A_re = A->data[j + A->size[0] * i].re;
          A_im = -A->data[j + A->size[0] * i].im;
          b_A = ((A->data[i + A->size[0] * j].re == A_re) && (A->data[i +
                  A->size[0] * j].im == A_im));
          if (!b_A) {
            p = false;
            exitg1 = 1;
          } else {
            i++;
          }
        } else {
          j++;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  }

  return p;
}

/*
 * File trailer for ishermitian.c
 *
 * [EOF]
 */
