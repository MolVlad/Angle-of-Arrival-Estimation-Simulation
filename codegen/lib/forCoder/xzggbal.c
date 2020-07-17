/*
 * File: xzggbal.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 17-Jul-2020 17:26:12
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "xzggbal.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_creal_T *A
 *                int *ilo
 *                int *ihi
 *                int rscale_data[]
 *                int rscale_size[1]
 * Return Type  : void
 */
void xzggbal(emxArray_creal_T *A, int *ilo, int *ihi, int rscale_data[], int
             rscale_size[1])
{
  int ii;
  int nzcount;
  int exitg2;
  int i;
  int j;
  boolean_T found;
  boolean_T exitg3;
  int jj;
  boolean_T exitg4;
  double atmp_re;
  double atmp_im;
  int exitg1;
  boolean_T b_A;
  rscale_size[0] = A->size[0];
  ii = A->size[0];
  for (nzcount = 0; nzcount < ii; nzcount++) {
    rscale_data[nzcount] = 1;
  }

  *ilo = 1;
  *ihi = A->size[0];
  if (A->size[0] <= 1) {
    *ihi = 1;
  } else {
    do {
      exitg2 = 0;
      i = 0;
      j = -1;
      found = false;
      ii = *ihi;
      exitg3 = false;
      while ((!exitg3) && (ii > 0)) {
        nzcount = 0;
        i = ii;
        j = *ihi - 1;
        jj = 0;
        exitg4 = false;
        while ((!exitg4) && (jj <= *ihi - 1)) {
          b_A = ((A->data[(ii + A->size[0] * jj) - 1].re != 0.0) || (A->data[(ii
                   + A->size[0] * jj) - 1].im != 0.0));
          if (b_A || (ii == jj + 1)) {
            if (nzcount == 0) {
              j = jj;
              nzcount = 1;
              jj++;
            } else {
              nzcount = 2;
              exitg4 = true;
            }
          } else {
            jj++;
          }
        }

        if (nzcount < 2) {
          found = true;
          exitg3 = true;
        } else {
          ii--;
        }
      }

      if (!found) {
        exitg2 = 2;
      } else {
        ii = A->size[0];
        if (i != *ihi) {
          for (nzcount = 1; nzcount <= ii; nzcount++) {
            atmp_re = A->data[(i + A->size[0] * (nzcount - 1)) - 1].re;
            atmp_im = A->data[(i + A->size[0] * (nzcount - 1)) - 1].im;
            A->data[(i + A->size[0] * (nzcount - 1)) - 1] = A->data[(*ihi +
              A->size[0] * (nzcount - 1)) - 1];
            A->data[(*ihi + A->size[0] * (nzcount - 1)) - 1].re = atmp_re;
            A->data[(*ihi + A->size[0] * (nzcount - 1)) - 1].im = atmp_im;
          }
        }

        if (j + 1 != *ihi) {
          for (nzcount = 0; nzcount < *ihi; nzcount++) {
            atmp_re = A->data[nzcount + A->size[0] * j].re;
            atmp_im = A->data[nzcount + A->size[0] * j].im;
            A->data[nzcount + A->size[0] * j] = A->data[nzcount + A->size[0] * (*
              ihi - 1)];
            A->data[nzcount + A->size[0] * (*ihi - 1)].re = atmp_re;
            A->data[nzcount + A->size[0] * (*ihi - 1)].im = atmp_im;
          }
        }

        rscale_data[*ihi - 1] = j + 1;
        (*ihi)--;
        if (*ihi == 1) {
          rscale_data[0] = 1;
          exitg2 = 1;
        }
      }
    } while (exitg2 == 0);

    if (exitg2 == 1) {
    } else {
      do {
        exitg1 = 0;
        i = 0;
        j = 0;
        found = false;
        jj = *ilo;
        exitg3 = false;
        while ((!exitg3) && (jj <= *ihi)) {
          nzcount = 0;
          i = *ihi;
          j = jj;
          ii = *ilo;
          exitg4 = false;
          while ((!exitg4) && (ii <= *ihi)) {
            b_A = ((A->data[(ii + A->size[0] * (jj - 1)) - 1].re != 0.0) ||
                   (A->data[(ii + A->size[0] * (jj - 1)) - 1].im != 0.0));
            if (b_A || (ii == jj)) {
              if (nzcount == 0) {
                i = ii;
                nzcount = 1;
                ii++;
              } else {
                nzcount = 2;
                exitg4 = true;
              }
            } else {
              ii++;
            }
          }

          if (nzcount < 2) {
            found = true;
            exitg3 = true;
          } else {
            jj++;
          }
        }

        if (!found) {
          exitg1 = 1;
        } else {
          ii = A->size[0];
          if (i != *ilo) {
            for (nzcount = *ilo; nzcount <= ii; nzcount++) {
              atmp_re = A->data[(i + A->size[0] * (nzcount - 1)) - 1].re;
              atmp_im = A->data[(i + A->size[0] * (nzcount - 1)) - 1].im;
              A->data[(i + A->size[0] * (nzcount - 1)) - 1] = A->data[(*ilo +
                A->size[0] * (nzcount - 1)) - 1];
              A->data[(*ilo + A->size[0] * (nzcount - 1)) - 1].re = atmp_re;
              A->data[(*ilo + A->size[0] * (nzcount - 1)) - 1].im = atmp_im;
            }
          }

          if (j != *ilo) {
            for (nzcount = 0; nzcount < *ihi; nzcount++) {
              atmp_re = A->data[nzcount + A->size[0] * (j - 1)].re;
              atmp_im = A->data[nzcount + A->size[0] * (j - 1)].im;
              A->data[nzcount + A->size[0] * (j - 1)] = A->data[nzcount +
                A->size[0] * (*ilo - 1)];
              A->data[nzcount + A->size[0] * (*ilo - 1)].re = atmp_re;
              A->data[nzcount + A->size[0] * (*ilo - 1)].im = atmp_im;
            }
          }

          rscale_data[*ilo - 1] = j;
          (*ilo)++;
          if (*ilo == *ihi) {
            rscale_data[*ilo - 1] = *ilo;
            exitg1 = 1;
          }
        }
      } while (exitg1 == 0);
    }
  }
}

/*
 * File trailer for xzggbal.c
 *
 * [EOF]
 */
