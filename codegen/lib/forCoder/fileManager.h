/*
 * File: fileManager.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 13-Jul-2020 18:10:32
 */

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "forCoder_types.h"

/* Function Declarations */
extern signed char b_cfopen(const char cfilename_data[], const int
  cfilename_size[2], const char * cpermission);
extern signed char cfopen(const char cfilename[35], const char * cpermission);
extern void filedata_init(void);
extern void getfilestar(double fid, FILE * *filestar, boolean_T *autoflush);

#endif

/*
 * File trailer for fileManager.h
 *
 * [EOF]
 */
