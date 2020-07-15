/*
 * File: _coder_forCoder_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 16:54:31
 */

#ifndef _CODER_FORCODER_API_H
#define _CODER_FORCODER_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_forCoder_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void forCoder(real_T seed);
extern void forCoder_api(const mxArray * const prhs[1], int32_T nlhs);
extern void forCoder_atexit(void);
extern void forCoder_initialize(void);
extern void forCoder_terminate(void);
extern void forCoder_xil_terminate(void);

#endif

/*
 * File trailer for _coder_forCoder_api.h
 *
 * [EOF]
 */
