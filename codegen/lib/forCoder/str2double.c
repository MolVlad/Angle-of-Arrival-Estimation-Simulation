/*
 * File: str2double.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Jul-2020 16:54:31
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "str2double.h"
#include "forCoder_emxutil.h"
#include <stdio.h>

/* Variable Definitions */
static const boolean_T bv0[128] = { true, false, false, false, false, false,
  false, false, false, true, true, true, true, true, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false, true,
  true, true, true, true, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false };

/* Function Declarations */
static boolean_T b_copysign(emxArray_char_T *s1, int *idx, const emxArray_char_T
  *s, int *k, int n);
static boolean_T copydigits(emxArray_char_T *s1, int *idx, const emxArray_char_T
  *s, int *k, int n, boolean_T allowpoint);
static boolean_T copyexponent(emxArray_char_T *s1, int *idx, const
  emxArray_char_T *s, int *k, int n);
static void readNonFinite(const emxArray_char_T *s, int *k, int n, boolean_T
  *b_finite, double *fv);
static void readfloat(emxArray_char_T *s1, int *idx, const emxArray_char_T *s,
                      int *k, int n, boolean_T *isimag, boolean_T *b_finite,
                      double *nfv, boolean_T *success);

/* Function Definitions */

/*
 * Arguments    : emxArray_char_T *s1
 *                int *idx
 *                const emxArray_char_T *s
 *                int *k
 *                int n
 * Return Type  : boolean_T
 */
static boolean_T b_copysign(emxArray_char_T *s1, int *idx, const emxArray_char_T
  *s, int *k, int n)
{
  boolean_T success;
  boolean_T isneg;
  isneg = false;
  while ((*k <= n) && ((s->data[*k - 1] == '+') || (s->data[*k - 1] == '-') ||
                       bv0[(unsigned char)s->data[*k - 1] & 127])) {
    if (s->data[*k - 1] == '-') {
      isneg = !isneg;
    }

    (*k)++;
  }

  success = (*k <= n);
  if (success && isneg) {
    if ((*idx >= 2) && (s1->data[*idx - 2] == '-')) {
      s1->data[*idx - 2] = ' ';
    } else {
      s1->data[*idx - 1] = '-';
      (*idx)++;
    }
  }

  return success;
}

/*
 * Arguments    : emxArray_char_T *s1
 *                int *idx
 *                const emxArray_char_T *s
 *                int *k
 *                int n
 *                boolean_T allowpoint
 * Return Type  : boolean_T
 */
static boolean_T copydigits(emxArray_char_T *s1, int *idx, const emxArray_char_T
  *s, int *k, int n, boolean_T allowpoint)
{
  boolean_T success;
  boolean_T haspoint;
  boolean_T exitg1;
  success = (*k <= n);
  haspoint = !allowpoint;
  exitg1 = false;
  while ((!exitg1) && (*k <= n)) {
    if ((s->data[*k - 1] >= '0') && (s->data[*k - 1] <= '9')) {
      s1->data[*idx - 1] = s->data[*k - 1];
      (*idx)++;
      (*k)++;
    } else if (s->data[*k - 1] == '.') {
      if (haspoint) {
        success = false;
        exitg1 = true;
      } else {
        s1->data[*idx - 1] = '.';
        (*idx)++;
        haspoint = true;
        (*k)++;
      }
    } else if (s->data[*k - 1] != ',') {
      exitg1 = true;
    } else {
      (*k)++;
    }
  }

  return success;
}

/*
 * Arguments    : emxArray_char_T *s1
 *                int *idx
 *                const emxArray_char_T *s
 *                int *k
 *                int n
 * Return Type  : boolean_T
 */
static boolean_T copyexponent(emxArray_char_T *s1, int *idx, const
  emxArray_char_T *s, int *k, int n)
{
  boolean_T success;
  success = true;
  if ((*k <= n) && ((s->data[*k - 1] == 'E') || (s->data[*k - 1] == 'e'))) {
    s1->data[*idx - 1] = 'e';
    (*idx)++;
    (*k)++;
    if (*k <= n) {
      if (s->data[*k - 1] == '-') {
        s1->data[*idx - 1] = '-';
        (*idx)++;
        (*k)++;
      } else {
        if (s->data[*k - 1] == '+') {
          (*k)++;
        }
      }
    }

    success = copydigits(s1, idx, s, k, n, false);
  }

  return success;
}

/*
 * Arguments    : const emxArray_char_T *s
 *                int *k
 *                int n
 *                boolean_T *b_finite
 *                double *fv
 * Return Type  : void
 */
static void readNonFinite(const emxArray_char_T *s, int *k, int n, boolean_T
  *b_finite, double *fv)
{
  *b_finite = true;
  *fv = 0.0;
  if (*k + 2 <= n) {
    if (((s->data[*k - 1] == 'I') || (s->data[*k - 1] == 'i')) && ((s->data[*k] ==
          'N') || (s->data[*k] == 'n')) && ((s->data[*k + 1] == 'F') || (s->
          data[*k + 1] == 'f'))) {
      *b_finite = false;
      *fv = rtInf;
      *k += 3;
    } else {
      if (((s->data[*k - 1] == 'N') || (s->data[*k - 1] == 'n')) && ((s->data[*k]
            == 'A') || (s->data[*k] == 'a')) && ((s->data[*k + 1] == 'N') ||
           (s->data[*k + 1] == 'n'))) {
        *b_finite = false;
        *fv = rtNaN;
        *k += 3;
      }
    }
  }
}

/*
 * Arguments    : emxArray_char_T *s1
 *                int *idx
 *                const emxArray_char_T *s
 *                int *k
 *                int n
 *                boolean_T *isimag
 *                boolean_T *b_finite
 *                double *nfv
 *                boolean_T *success
 * Return Type  : void
 */
static void readfloat(emxArray_char_T *s1, int *idx, const emxArray_char_T *s,
                      int *k, int n, boolean_T *isimag, boolean_T *b_finite,
                      double *nfv, boolean_T *success)
{
  int b_idx;
  *isimag = false;
  *b_finite = true;
  *nfv = 0.0;
  b_idx = *idx;
  *success = b_copysign(s1, &b_idx, s, k, n);
  *idx = b_idx;
  if (*success) {
    if ((*k <= n) && ((s->data[*k - 1] == 'j') || ((s->data[*k - 1] == 'i') &&
          ((*k == n) || ((s->data[*k] != 'n') && (s->data[*k] != 'N')))))) {
      *success = false;
    } else {
      readNonFinite(s, k, n, b_finite, nfv);
      if (*b_finite) {
        *success = copydigits(s1, idx, s, k, n, true);
        if (*success) {
          *success = copyexponent(s1, idx, s, k, n);
        }
      } else {
        if ((b_idx >= 2) && (s1->data[b_idx - 2] == '-')) {
          *idx = b_idx - 1;
          s1->data[b_idx - 2] = ' ';
          *nfv = -*nfv;
        }
      }

      while ((*k <= n) && bv0[(unsigned char)s->data[*k - 1] & 127]) {
        (*k)++;
      }

      if ((*k <= n) && (s->data[*k - 1] == '*')) {
        (*k)++;
        while ((*k <= n) && bv0[(unsigned char)s->data[*k - 1] & 127]) {
          (*k)++;
        }
      }

      if ((*k <= n) && ((s->data[*k - 1] == 'i') || (s->data[*k - 1] == 'j'))) {
        (*k)++;
        *isimag = true;
      }
    }

    while ((*k <= n) && bv0[(unsigned char)s->data[*k - 1] & 127]) {
      (*k)++;
    }
  }
}

/*
 * Arguments    : const emxArray_char_T *s
 * Return Type  : creal_T
 */
creal_T str2double(const emxArray_char_T *s)
{
  creal_T x;
  int n;
  emxArray_char_T *s1;
  int ntoread;
  unsigned int unnamed_idx_1;
  int loop_ub;
  boolean_T isimag1;
  boolean_T b_finite;
  double scanned1;
  int idx;
  boolean_T isneg;
  boolean_T success;
  double scanned2;
  boolean_T isimag2;
  boolean_T c_finite;
  int b_idx;
  double b_scanned1;
  x.re = rtNaN;
  x.im = 0.0;
  n = s->size[1];
  if (s->size[1] >= 1) {
    emxInit_char_T(&s1, 2);
    ntoread = s1->size[0] * s1->size[1];
    s1->size[0] = 1;
    emxEnsureCapacity_char_T(s1, ntoread);
    unnamed_idx_1 = (unsigned int)(s->size[1] + 2);
    ntoread = s1->size[0] * s1->size[1];
    s1->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity_char_T(s1, ntoread);
    unnamed_idx_1 = (unsigned int)(s->size[1] + 2);
    loop_ub = (int)unnamed_idx_1;
    for (ntoread = 0; ntoread < loop_ub; ntoread++) {
      s1->data[ntoread] = '\x00';
    }

    ntoread = 0;
    isimag1 = false;
    b_finite = true;
    scanned1 = 0.0;
    loop_ub = 1;
    idx = 1;
    isneg = false;
    while ((loop_ub <= n) && ((s->data[loop_ub - 1] == '+') || (s->data[loop_ub
             - 1] == '-') || bv0[(unsigned char)s->data[loop_ub - 1] & 127])) {
      if (s->data[loop_ub - 1] == '-') {
        isneg = !isneg;
      }

      loop_ub++;
    }

    success = (loop_ub <= s->size[1]);
    if (success && isneg) {
      s1->data[0] = '-';
      idx = 2;
    }

    if (success) {
      if ((loop_ub <= s->size[1]) && ((s->data[loop_ub - 1] == 'j') || ((s->
             data[loop_ub - 1] == 'i') && ((loop_ub == s->size[1]) || ((s->
               data[loop_ub] != 'n') && (s->data[loop_ub] != 'N')))))) {
        isimag1 = true;
        loop_ub++;
        while ((loop_ub <= n) && bv0[(unsigned char)s->data[loop_ub - 1] & 127])
        {
          loop_ub++;
        }

        if ((loop_ub <= s->size[1]) && (s->data[loop_ub - 1] == '*')) {
          loop_ub++;
          readfloat(s1, &idx, s, &loop_ub, s->size[1], &isneg, &b_finite,
                    &scanned1, &success);
        } else {
          s1->data[idx - 1] = '1';
          idx++;
        }
      } else {
        readNonFinite(s, &loop_ub, s->size[1], &b_finite, &scanned1);
        if (b_finite) {
          success = copydigits(s1, &idx, s, &loop_ub, s->size[1], true);
          if (success) {
            success = copyexponent(s1, &idx, s, &loop_ub, s->size[1]);
          }
        } else {
          if ((idx >= 2) && (s1->data[0] == '-')) {
            idx = 1;
            s1->data[0] = ' ';
            scanned1 = -scanned1;
          }
        }

        while ((loop_ub <= n) && bv0[(unsigned char)s->data[loop_ub - 1] & 127])
        {
          loop_ub++;
        }

        if ((loop_ub <= s->size[1]) && (s->data[loop_ub - 1] == '*')) {
          loop_ub++;
          while ((loop_ub <= n) && bv0[(unsigned char)s->data[loop_ub - 1] & 127])
          {
            loop_ub++;
          }
        }

        if ((loop_ub <= s->size[1]) && ((s->data[loop_ub - 1] == 'i') ||
             (s->data[loop_ub - 1] == 'j'))) {
          loop_ub++;
          isimag1 = true;
        }
      }

      while ((loop_ub <= n) && bv0[(unsigned char)s->data[loop_ub - 1] & 127]) {
        loop_ub++;
      }
    }

    if (b_finite) {
      ntoread = 1;
    }

    if (success && (loop_ub <= s->size[1])) {
      s1->data[idx - 1] = ' ';
      isimag2 = false;
      c_finite = true;
      scanned2 = 0.0;
      b_idx = idx + 1;
      success = b_copysign(s1, &b_idx, s, &loop_ub, s->size[1]);
      idx = b_idx;
      if (success) {
        if ((loop_ub <= s->size[1]) && ((s->data[loop_ub - 1] == 'j') ||
             ((s->data[loop_ub - 1] == 'i') && ((loop_ub == s->size[1]) ||
               ((s->data[loop_ub] != 'n') && (s->data[loop_ub] != 'N')))))) {
          isimag2 = true;
          loop_ub++;
          while ((loop_ub <= n) && bv0[(unsigned char)s->data[loop_ub - 1] & 127])
          {
            loop_ub++;
          }

          if ((loop_ub <= s->size[1]) && (s->data[loop_ub - 1] == '*')) {
            loop_ub++;
            readfloat(s1, &idx, s, &loop_ub, s->size[1], &isneg, &c_finite,
                      &scanned2, &success);
          } else {
            s1->data[b_idx - 1] = '1';
            idx = b_idx + 1;
          }
        } else {
          readNonFinite(s, &loop_ub, s->size[1], &c_finite, &scanned2);
          if (c_finite) {
            success = copydigits(s1, &idx, s, &loop_ub, s->size[1], true);
            if (success) {
              success = copyexponent(s1, &idx, s, &loop_ub, s->size[1]);
            }
          } else {
            if ((b_idx >= 2) && (s1->data[b_idx - 2] == '-')) {
              idx = b_idx - 1;
              s1->data[b_idx - 2] = ' ';
              scanned2 = -scanned2;
            }
          }

          while ((loop_ub <= n) && bv0[(unsigned char)s->data[loop_ub - 1] & 127])
          {
            loop_ub++;
          }

          if ((loop_ub <= s->size[1]) && (s->data[loop_ub - 1] == '*')) {
            loop_ub++;
            while ((loop_ub <= n) && bv0[(unsigned char)s->data[loop_ub - 1] &
                   127]) {
              loop_ub++;
            }
          }

          if ((loop_ub <= s->size[1]) && ((s->data[loop_ub - 1] == 'i') ||
               (s->data[loop_ub - 1] == 'j'))) {
            loop_ub++;
            isimag2 = true;
          }
        }

        while ((loop_ub <= n) && bv0[(unsigned char)s->data[loop_ub - 1] & 127])
        {
          loop_ub++;
        }
      }

      if (c_finite) {
        ntoread++;
      }

      if (success && (loop_ub > s->size[1]) && ((isimag1 ^ isimag2) != 0)) {
        success = true;
      } else {
        success = false;
      }
    } else {
      scanned2 = 0.0;
    }

    if (success) {
      s1->data[idx - 1] = '\x00';
      if (ntoread == 2) {
        ntoread = sscanf(&s1->data[0], "%lf %lf", &scanned1, &scanned2);
        if (ntoread != 2) {
          scanned1 = rtNaN;
          scanned2 = rtNaN;
        }
      } else {
        if (ntoread == 1) {
          ntoread = sscanf(&s1->data[0], "%lf", &b_scanned1);
          if (ntoread == 1) {
          } else {
            b_scanned1 = rtNaN;
          }

          if (b_finite) {
            scanned1 = b_scanned1;
          } else {
            scanned2 = b_scanned1;
          }
        }
      }

      if (isimag1) {
        x.re = scanned2;
        x.im = scanned1;
      } else {
        x.re = scanned1;
        x.im = scanned2;
      }
    }

    emxFree_char_T(&s1);
  }

  return x;
}

/*
 * File trailer for str2double.c
 *
 * [EOF]
 */
