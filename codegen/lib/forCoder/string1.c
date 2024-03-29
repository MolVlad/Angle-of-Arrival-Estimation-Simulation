/*
 * File: string1.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 23-Jul-2020 18:38:00
 */

/* Include Files */
#include <string.h>
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "string1.h"
#include <stdio.h>

/* Function Definitions */

/*
 * Arguments    : const char obj1_Value_data[]
 *                const int obj1_Value_size[2]
 *                char obj_Value_data[]
 *                int obj_Value_size[2]
 * Return Type  : void
 */
void b_string_plus(const char obj1_Value_data[], const int obj1_Value_size[2],
                   char obj_Value_data[], int obj_Value_size[2])
{
  obj_Value_size[0] = 1;
  obj_Value_size[1] = obj1_Value_size[1] + 4;
  if (0 <= obj1_Value_size[1] - 1) {
    memcpy(&obj_Value_data[0], &obj1_Value_data[0], (unsigned int)
           (obj1_Value_size[1] * (int)sizeof(char)));
  }

  obj_Value_data[obj1_Value_size[1]] = '_';
  obj_Value_data[1 + obj1_Value_size[1]] = 's';
  obj_Value_data[2 + obj1_Value_size[1]] = 'm';
  obj_Value_data[3 + obj1_Value_size[1]] = '_';
}

/*
 * Arguments    : const char obj1_Value_data[]
 *                const int obj1_Value_size[2]
 *                char obj_Value_data[]
 *                int obj_Value_size[2]
 * Return Type  : void
 */
void c_string_plus(const char obj1_Value_data[], const int obj1_Value_size[2],
                   char obj_Value_data[], int obj_Value_size[2])
{
  int i15;
  static const char obj2Value[7] = { '_', 'b', 'a', 'c', 'k', 'w', '_' };

  obj_Value_size[0] = 1;
  obj_Value_size[1] = obj1_Value_size[1] + 7;
  if (0 <= obj1_Value_size[1] - 1) {
    memcpy(&obj_Value_data[0], &obj1_Value_data[0], (unsigned int)
           (obj1_Value_size[1] * (int)sizeof(char)));
  }

  for (i15 = 0; i15 < 7; i15++) {
    obj_Value_data[i15 + obj1_Value_size[1]] = obj2Value[i15];
  }
}

/*
 * Arguments    : const char obj1_Value_data[]
 *                const int obj1_Value_size[2]
 *                char obj_Value_data[]
 *                int obj_Value_size[2]
 * Return Type  : void
 */
void d_string_plus(const char obj1_Value_data[], const int obj1_Value_size[2],
                   char obj_Value_data[], int obj_Value_size[2])
{
  int i16;
  static const char obj2Value[6] = { '_', 'p', 'a', 'c', 'k', '_' };

  obj_Value_size[0] = 1;
  obj_Value_size[1] = obj1_Value_size[1] + 6;
  if (0 <= obj1_Value_size[1] - 1) {
    memcpy(&obj_Value_data[0], &obj1_Value_data[0], (unsigned int)
           (obj1_Value_size[1] * (int)sizeof(char)));
  }

  for (i16 = 0; i16 < 6; i16++) {
    obj_Value_data[i16 + obj1_Value_size[1]] = obj2Value[i16];
  }
}

/*
 * Arguments    : const char obj1_Value_data[]
 *                const int obj1_Value_size[2]
 *                char obj_Value_data[]
 *                int obj_Value_size[2]
 * Return Type  : void
 */
void e_string_plus(const char obj1_Value_data[], const int obj1_Value_size[2],
                   char obj_Value_data[], int obj_Value_size[2])
{
  obj_Value_size[0] = 1;
  obj_Value_size[1] = obj1_Value_size[1] + 2;
  if (0 <= obj1_Value_size[1] - 1) {
    memcpy(&obj_Value_data[0], &obj1_Value_data[0], (unsigned int)
           (obj1_Value_size[1] * (int)sizeof(char)));
  }

  obj_Value_data[obj1_Value_size[1]] = '1';
  obj_Value_data[1 + obj1_Value_size[1]] = '0';
}

/*
 * Arguments    : const char obj1_Value_data[]
 *                const int obj1_Value_size[2]
 *                char obj_Value_data[]
 *                int obj_Value_size[2]
 * Return Type  : void
 */
void f_string_plus(const char obj1_Value_data[], const int obj1_Value_size[2],
                   char obj_Value_data[], int obj_Value_size[2])
{
  int i17;
  static const char obj2Value[7] = { '_', 'p', 'e', 'r', 'S', 'p', '_' };

  obj_Value_size[0] = 1;
  obj_Value_size[1] = obj1_Value_size[1] + 7;
  if (0 <= obj1_Value_size[1] - 1) {
    memcpy(&obj_Value_data[0], &obj1_Value_data[0], (unsigned int)
           (obj1_Value_size[1] * (int)sizeof(char)));
  }

  for (i17 = 0; i17 < 7; i17++) {
    obj_Value_data[i17 + obj1_Value_size[1]] = obj2Value[i17];
  }
}

/*
 * Arguments    : const char obj1_Value_data[]
 *                const int obj1_Value_size[2]
 *                const char obj2_Value_data[]
 *                const int obj2_Value_size[2]
 *                char obj_Value_data[]
 *                int obj_Value_size[2]
 * Return Type  : void
 */
void g_string_plus(const char obj1_Value_data[], const int obj1_Value_size[2],
                   const char obj2_Value_data[], const int obj2_Value_size[2],
                   char obj_Value_data[], int obj_Value_size[2])
{
  int loop_ub;
  int i18;
  obj_Value_size[0] = 1;
  obj_Value_size[1] = obj1_Value_size[1] + obj2_Value_size[1];
  if (0 <= obj1_Value_size[1] - 1) {
    memcpy(&obj_Value_data[0], &obj1_Value_data[0], (unsigned int)
           (obj1_Value_size[1] * (int)sizeof(char)));
  }

  loop_ub = obj2_Value_size[1];
  for (i18 = 0; i18 < loop_ub; i18++) {
    obj_Value_data[i18 + obj1_Value_size[1]] = obj2_Value_data[i18];
  }
}

/*
 * Arguments    : const char obj1_Value_data[]
 *                const int obj1_Value_size[2]
 *                char obj_Value_data[]
 *                int obj_Value_size[2]
 * Return Type  : void
 */
void h_string_plus(const char obj1_Value_data[], const int obj1_Value_size[2],
                   char obj_Value_data[], int obj_Value_size[2])
{
  obj_Value_size[0] = 1;
  obj_Value_size[1] = obj1_Value_size[1] + 4;
  if (0 <= obj1_Value_size[1] - 1) {
    memcpy(&obj_Value_data[0], &obj1_Value_data[0], (unsigned int)
           (obj1_Value_size[1] * (int)sizeof(char)));
  }

  obj_Value_data[obj1_Value_size[1]] = '_';
  obj_Value_data[1 + obj1_Value_size[1]] = 'b';
  obj_Value_data[2 + obj1_Value_size[1]] = 'w';
  obj_Value_data[3 + obj1_Value_size[1]] = '_';
}

/*
 * Arguments    : const char obj1_Value_data[]
 *                const int obj1_Value_size[2]
 *                char obj_Value_data[]
 *                int obj_Value_size[2]
 * Return Type  : void
 */
void i_string_plus(const char obj1_Value_data[], const int obj1_Value_size[2],
                   char obj_Value_data[], int obj_Value_size[2])
{
  obj_Value_size[0] = 1;
  obj_Value_size[1] = obj1_Value_size[1] + 2;
  if (0 <= obj1_Value_size[1] - 1) {
    memcpy(&obj_Value_data[0], &obj1_Value_data[0], (unsigned int)
           (obj1_Value_size[1] * (int)sizeof(char)));
  }

  obj_Value_data[obj1_Value_size[1]] = '4';
  obj_Value_data[1 + obj1_Value_size[1]] = '0';
}

/*
 * Arguments    : const char obj1_Value_data[]
 *                const int obj1_Value_size[2]
 *                char obj_Value_data[]
 *                int obj_Value_size[2]
 * Return Type  : void
 */
void j_string_plus(const char obj1_Value_data[], const int obj1_Value_size[2],
                   char obj_Value_data[], int obj_Value_size[2])
{
  int i19;
  static const char obj2Value[5] = { '_', 'd', 'e', 'c', '_' };

  obj_Value_size[0] = 1;
  obj_Value_size[1] = obj1_Value_size[1] + 5;
  if (0 <= obj1_Value_size[1] - 1) {
    memcpy(&obj_Value_data[0], &obj1_Value_data[0], (unsigned int)
           (obj1_Value_size[1] * (int)sizeof(char)));
  }

  for (i19 = 0; i19 < 5; i19++) {
    obj_Value_data[i19 + obj1_Value_size[1]] = obj2Value[i19];
  }
}

/*
 * Arguments    : const char obj1_Value_data[]
 *                const int obj1_Value_size[2]
 *                char obj_Value_data[]
 *                int obj_Value_size[2]
 * Return Type  : void
 */
void k_string_plus(const char obj1_Value_data[], const int obj1_Value_size[2],
                   char obj_Value_data[], int obj_Value_size[2])
{
  obj_Value_size[0] = 1;
  obj_Value_size[1] = obj1_Value_size[1] + 4;
  if (0 <= obj1_Value_size[1] - 1) {
    memcpy(&obj_Value_data[0], &obj1_Value_data[0], (unsigned int)
           (obj1_Value_size[1] * (int)sizeof(char)));
  }

  obj_Value_data[obj1_Value_size[1]] = '.';
  obj_Value_data[1 + obj1_Value_size[1]] = 't';
  obj_Value_data[2 + obj1_Value_size[1]] = 'x';
  obj_Value_data[3 + obj1_Value_size[1]] = 't';
}

/*
 * Arguments    : const char obj1_Value[14]
 *                const char obj2_Value_data[]
 *                const int obj2_Value_size[2]
 *                char obj_Value_data[]
 *                int obj_Value_size[2]
 * Return Type  : void
 */
void l_string_plus(const char obj1_Value[14], const char obj2_Value_data[],
                   const int obj2_Value_size[2], char obj_Value_data[], int
                   obj_Value_size[2])
{
  int i20;
  obj_Value_size[0] = 1;
  obj_Value_size[1] = 14 + obj2_Value_size[1];
  for (i20 = 0; i20 < 14; i20++) {
    obj_Value_data[i20] = obj1_Value[i20];
  }

  if (0 <= obj2_Value_size[1] - 1) {
    memcpy(&obj_Value_data[14], &obj2_Value_data[0], (unsigned int)
           (obj2_Value_size[1] * (int)sizeof(char)));
  }
}

/*
 * Arguments    : const char obj1_Value[12]
 *                const char obj2_Value_data[]
 *                const int obj2_Value_size[2]
 *                char obj_Value_data[]
 *                int obj_Value_size[2]
 * Return Type  : void
 */
void string_plus(const char obj1_Value[12], const char obj2_Value_data[], const
                 int obj2_Value_size[2], char obj_Value_data[], int
                 obj_Value_size[2])
{
  int i14;
  obj_Value_size[0] = 1;
  obj_Value_size[1] = 12 + obj2_Value_size[1];
  for (i14 = 0; i14 < 12; i14++) {
    obj_Value_data[i14] = obj1_Value[i14];
  }

  if (0 <= obj2_Value_size[1] - 1) {
    memcpy(&obj_Value_data[12], &obj2_Value_data[0], (unsigned int)
           (obj2_Value_size[1] * (int)sizeof(char)));
  }
}

/*
 * Arguments    : double val
 *                char obj_Value_data[]
 *                int obj_Value_size[2]
 * Return Type  : void
 */
void string_string(double val, char obj_Value_data[], int obj_Value_size[2])
{
  int resCount;
  char str_data[23];
  char st[24];
  if (val == 0.0) {
    resCount = 1;
    str_data[0] = '0';
  } else if (rtIsInf(val)) {
    resCount = 3;
    str_data[0] = 'I';
    str_data[1] = 'n';
    str_data[2] = 'f';
  } else if (rtIsNaN(val)) {
    resCount = 3;
    str_data[0] = 'N';
    str_data[1] = 'a';
    str_data[2] = 'N';
  } else {
    resCount = sprintf(&st[0], "%.16g", val);
    if (0 <= resCount - 1) {
      memcpy(&str_data[0], &st[0], (unsigned int)(resCount * (int)sizeof(char)));
    }
  }

  obj_Value_size[0] = 1;
  obj_Value_size[1] = resCount;
  if (0 <= resCount - 1) {
    memcpy(&obj_Value_data[0], &str_data[0], (unsigned int)(resCount * (int)
            sizeof(char)));
  }
}

/*
 * File trailer for string1.c
 *
 * [EOF]
 */
