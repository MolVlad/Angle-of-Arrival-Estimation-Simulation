/*
 * File: forCoder_initialize.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Jul-2020 11:32:44
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "forCoder_initialize.h"
#include "fileManager.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void forCoder_initialize(void)
{
  rt_InitInfAndNaN(8U);
  filedata_init();
}

/*
 * File trailer for forCoder_initialize.c
 *
 * [EOF]
 */
