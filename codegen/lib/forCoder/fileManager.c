/*
 * File: fileManager.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 12:14:31
 */

/* Include Files */
#include <string.h>
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "fileManager.h"
#include "fclose.h"
#include "forCoder_rtwutil.h"
#include "forCoder_data.h"

/* Function Declarations */
static signed char filedata(void);

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : signed char
 */
static signed char filedata(void)
{
  signed char f;
  int k;
  boolean_T exitg1;
  f = 0;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 20)) {
    if (eml_openfiles[k] == NULL) {
      f = (signed char)(k + 1);
      exitg1 = true;
    } else {
      k++;
    }
  }

  return f;
}

/*
 * Arguments    : const char cfilename_data[]
 *                const int cfilename_size[2]
 *                const char * cpermission
 * Return Type  : signed char
 */
signed char b_cfopen(const char cfilename_data[], const int cfilename_size[2],
                     const char * cpermission)
{
  signed char fileid;
  signed char j;
  char ccfilename_data[1465];
  FILE * filestar;
  int i19;
  fileid = -1;
  j = filedata();
  if (j >= 1) {
    if (0 <= cfilename_size[1] - 1) {
      memcpy(&ccfilename_data[0], &cfilename_data[0], (unsigned int)
             (cfilename_size[1] * (int)sizeof(char)));
    }

    ccfilename_data[cfilename_size[1]] = '\x00';
    filestar = fopen(&ccfilename_data[0], cpermission);
    if (filestar != NULL) {
      eml_openfiles[j - 1] = filestar;
      eml_autoflush[j - 1] = true;
      i19 = j + 2;
      if (i19 > 127) {
        i19 = 127;
      }

      fileid = (signed char)i19;
    }
  }

  return fileid;
}

/*
 * Arguments    : const char cfilename[15]
 *                const char * cpermission
 * Return Type  : signed char
 */
signed char cfopen(const char cfilename[15], const char * cpermission)
{
  signed char fileid;
  signed char j;
  int i5;
  char ccfilename[16];
  FILE * filestar;
  fileid = -1;
  j = filedata();
  if (j >= 1) {
    for (i5 = 0; i5 < 15; i5++) {
      ccfilename[i5] = cfilename[i5];
    }

    ccfilename[15] = '\x00';
    filestar = fopen(&ccfilename[0], cpermission);
    if (filestar != NULL) {
      eml_openfiles[j - 1] = filestar;
      eml_autoflush[j - 1] = true;
      i5 = j + 2;
      if (i5 > 127) {
        i5 = 127;
      }

      fileid = (signed char)i5;
    }
  }

  return fileid;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void filedata_init(void)
{
  FILE * a;
  int i;
  a = NULL;
  for (i = 0; i < 20; i++) {
    eml_autoflush[i] = false;
    eml_openfiles[i] = a;
  }
}

/*
 * Arguments    : double fid
 *                FILE * *filestar
 *                boolean_T *autoflush
 * Return Type  : void
 */
void getfilestar(double fid, FILE * *filestar, boolean_T *autoflush)
{
  signed char fileid;
  fileid = (signed char)rt_roundd_snf(fid);
  if ((fileid < 0) || (fid != fileid)) {
    fileid = -1;
  }

  if (fileid >= 3) {
    *filestar = eml_openfiles[fileid - 3];
    *autoflush = eml_autoflush[fileid - 3];
  } else if (fileid == 0) {
    *filestar = stdin;
    *autoflush = true;
  } else if (fileid == 1) {
    *filestar = stdout;
    *autoflush = true;
  } else if (fileid == 2) {
    *filestar = stderr;
    *autoflush = true;
  } else {
    *filestar = NULL;
    *autoflush = true;
  }
}

/*
 * File trailer for fileManager.c
 *
 * [EOF]
 */
