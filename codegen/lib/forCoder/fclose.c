/*
 * File: fclose.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 17-Jul-2020 17:26:12
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "fclose.h"
#include "forCoder_rtwutil.h"
#include "forCoder_data.h"

/* Function Definitions */

/*
 * Arguments    : double fileID
 * Return Type  : void
 */
void b_fclose(double fileID)
{
  signed char fileid;
  signed char b_fileid;
  FILE * filestar;
  int cst;
  fileid = (signed char)rt_roundd_snf(fileID);
  if ((fileid < 0) || (fileID != fileid)) {
    fileid = -1;
  }

  b_fileid = fileid;
  if (fileid < 0) {
    b_fileid = -1;
  }

  if (b_fileid >= 3) {
    filestar = eml_openfiles[b_fileid - 3];
  } else if (b_fileid == 0) {
    filestar = stdin;
  } else if (b_fileid == 1) {
    filestar = stdout;
  } else if (b_fileid == 2) {
    filestar = stderr;
  } else {
    filestar = NULL;
  }

  if ((filestar != NULL) && (fileid >= 3)) {
    cst = fclose(filestar);
    if (cst == 0) {
      cst = fileid - 3;
      eml_openfiles[cst] = NULL;
      eml_autoflush[cst] = true;
    }
  }
}

/*
 * File trailer for fclose.c
 *
 * [EOF]
 */
