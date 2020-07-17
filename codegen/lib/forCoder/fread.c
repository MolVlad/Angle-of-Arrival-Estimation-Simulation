/*
 * File: fread.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 17-Jul-2020 17:26:12
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "fread.h"
#include "forCoder_emxutil.h"
#include "fileManager.h"

/* Type Definitions */
#include <stddef.h>

/* Function Definitions */

/*
 * Arguments    : double fileID
 *                int sizeA
 *                emxArray_real_T *A
 *                double *count
 * Return Type  : void
 */
void b_fread(double fileID, int sizeA, emxArray_real_T *A, double *count)
{
  size_t nBytes;
  FILE * filestar;
  boolean_T a;
  int numRead;
  int bytesOut;
  int bdims_idx_0;
  int buf_size_idx_0;
  int num2Read;
  int b_numRead;
  size_t numReadSizeT;
  char buf_data[1024];
  nBytes = sizeof(char);
  getfilestar(fileID, &filestar, &a);
  if ((fileID != 0.0) && (fileID != 1.0) && (fileID != 2.0)) {
  } else {
    filestar = NULL;
  }

  if (filestar == NULL) {
    A->size[0] = 0;
    bytesOut = 0;
  } else {
    numRead = A->size[0];
    A->size[0] = sizeA;
    emxEnsureCapacity_real_T(A, numRead);
    if (sizeA > 1024) {
      bdims_idx_0 = 1024;
    } else {
      bdims_idx_0 = sizeA;
    }

    bytesOut = 0;
    numRead = 1;
    buf_size_idx_0 = bdims_idx_0;
    while ((bytesOut < sizeA) && (numRead > 0)) {
      num2Read = buf_size_idx_0;
      numRead = sizeA - bytesOut;
      if (buf_size_idx_0 > numRead) {
        num2Read = numRead;
      }

      buf_size_idx_0 = (short)bdims_idx_0;
      numRead = 0;
      b_numRead = 1;
      while ((numRead < num2Read) && (b_numRead > 0)) {
        numReadSizeT = fread(&buf_data[numRead], nBytes, num2Read - numRead,
                             filestar);
        b_numRead = (int)numReadSizeT;
        numRead += (int)numReadSizeT;
      }

      for (num2Read = 0; num2Read < numRead; num2Read++) {
        A->data[num2Read + bytesOut] = (unsigned char)buf_data[num2Read];
      }

      bytesOut += numRead;
    }

    numRead = bytesOut + 1;
    b_numRead = A->size[0];
    for (num2Read = numRead; num2Read <= b_numRead; num2Read++) {
      A->data[num2Read - 1] = 0.0;
    }

    if (bytesOut < sizeA) {
      if (1 > bytesOut) {
        A->size[0] = 0;
      } else {
        numRead = A->size[0];
        A->size[0] = bytesOut;
        emxEnsureCapacity_real_T(A, numRead);
      }
    }
  }

  *count = bytesOut;
}

/*
 * File trailer for fread.c
 *
 * [EOF]
 */
