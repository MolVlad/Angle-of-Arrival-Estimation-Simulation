/*
 * File: fileManager.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 16-Jul-2020 16:31:04
 */

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "forCoder_types.h"

/* Function Declarations */
extern signed char b_cfopen(const char cfilename[15], const char * cpermission);
extern signed char c_cfopen(const char cfilename_data[], const int
  cfilename_size[2], const char * cpermission);
extern signed char cfopen(const char cfilename[11], const char * cpermission);
extern void filedata_init(void);
extern void getfilestar(double fid, FILE * *filestar, boolean_T *autoflush);

#endif

/*
 * File trailer for fileManager.h
 *
 * [EOF]
 */
