/*
 * File: xgemv.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Jul-2020 11:32:44
 */

#ifndef XGEMV_H
#define XGEMV_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "forCoder_types.h"

/* Function Declarations */
extern void b_xgemv(int m, int n, const emxArray_creal_T *A, int ia0, int lda,
                    const emxArray_creal_T *x, int ix0, creal_T y_data[]);
extern void xgemv(int m, int n, const emxArray_creal_T *A, int ia0, int lda,
                  const emxArray_creal_T *x, int ix0, creal_T y_data[]);

#endif

/*
 * File trailer for xgemv.h
 *
 * [EOF]
 */
