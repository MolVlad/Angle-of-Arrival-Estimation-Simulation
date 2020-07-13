/*
 * File: xzhseqr.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 13-Jul-2020 18:10:32
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "xzhseqr.h"
#include "abs.h"
#include "recip.h"
#include "xdlapy3.h"
#include "sqrt.h"
#include "xscal.h"
#include "forCoder_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_creal_T *h
 *                emxArray_creal_T *z
 * Return Type  : int
 */
int eml_zlahqr(emxArray_creal_T *h, emxArray_creal_T *z)
{
  int info;
  int n;
  int itmax;
  int ldh;
  int ldz;
  int knt;
  int j;
  int i;
  double SMLNUM;
  double aa;
  boolean_T exitg1;
  double tst;
  double br;
  int L;
  creal_T sc;
  boolean_T goto140;
  int its;
  boolean_T exitg2;
  int k;
  boolean_T exitg3;
  int ix0_tmp;
  double htmp1;
  int ix0;
  double t_re;
  double t_im;
  creal_T v;
  boolean_T goto70;
  double ba;
  int m;
  double u_re;
  double x_im;
  double u_im;
  double s;
  int b_k;
  creal_T b_v[2];
  int c_k;
  n = h->size[0];
  itmax = 30 * (int)fmax(10.0, h->size[0]);
  ldh = h->size[0];
  ldz = z->size[0];
  info = 0;
  if ((h->size[0] != 0) && (1 != h->size[0])) {
    knt = h->size[0];
    for (j = 0; j <= knt - 4; j++) {
      h->data[(j + h->size[0] * j) + 2].re = 0.0;
      h->data[(j + h->size[0] * j) + 2].im = 0.0;
      h->data[(j + h->size[0] * j) + 3].re = 0.0;
      h->data[(j + h->size[0] * j) + 3].im = 0.0;
    }

    if (1 <= n - 2) {
      h->data[(n + h->size[0] * (n - 3)) - 1].re = 0.0;
      h->data[(n + h->size[0] * (n - 3)) - 1].im = 0.0;
    }

    for (i = 2; i <= n; i++) {
      if (h->data[(i + h->size[0] * (i - 2)) - 1].im != 0.0) {
        aa = h->data[(i + h->size[0] * (i - 2)) - 1].re;
        tst = h->data[(i + h->size[0] * (i - 2)) - 1].im;
        br = fabs(h->data[(i + h->size[0] * (i - 2)) - 1].re) + fabs(h->data[(i
          + h->size[0] * (i - 2)) - 1].im);
        if (tst == 0.0) {
          sc.re = aa / br;
          sc.im = 0.0;
        } else if (aa == 0.0) {
          sc.re = 0.0;
          sc.im = tst / br;
        } else {
          sc.re = aa / br;
          sc.im = tst / br;
        }

        br = rt_hypotd_snf(sc.re, sc.im);
        if (-sc.im == 0.0) {
          sc.re /= br;
          sc.im = 0.0;
        } else if (sc.re == 0.0) {
          sc.re = 0.0;
          sc.im = -sc.im / br;
        } else {
          sc.re /= br;
          sc.im = -sc.im / br;
        }

        tst = h->data[(i + h->size[0] * (i - 2)) - 1].re;
        aa = h->data[(i + h->size[0] * (i - 2)) - 1].im;
        h->data[(i + h->size[0] * (i - 2)) - 1].re = rt_hypotd_snf(tst, aa);
        h->data[(i + h->size[0] * (i - 2)) - 1].im = 0.0;
        xscal((n - i) + 1, sc, h, i + (i - 1) * ldh, ldh);
        ix0_tmp = (i - 1) * ldh;
        ix0 = ix0_tmp + 1;
        t_re = sc.re;
        t_im = -sc.im;
        knt = i + 1;
        if (n < knt) {
          knt = n;
        }

        knt += ix0_tmp;
        for (k = ix0; k <= knt; k++) {
          tst = h->data[k - 1].re;
          aa = h->data[k - 1].im;
          h->data[k - 1].re = t_re * tst - t_im * aa;
          h->data[k - 1].im = t_re * aa + t_im * tst;
        }

        ix0_tmp = (i - 1) * ldz;
        ix0 = ix0_tmp + 1;
        t_re = sc.re;
        t_im = -sc.im;
        knt = ix0_tmp + n;
        for (k = ix0; k <= knt; k++) {
          tst = z->data[k - 1].re;
          aa = z->data[k - 1].im;
          z->data[k - 1].re = t_re * tst - t_im * aa;
          z->data[k - 1].im = t_re * aa + t_im * tst;
        }
      }
    }

    SMLNUM = 2.2250738585072014E-308 * ((double)n / 2.2204460492503131E-16);
    i = n - 1;
    exitg1 = false;
    while ((!exitg1) && (i + 1 >= 1)) {
      L = -1;
      goto140 = false;
      its = 0;
      exitg2 = false;
      while ((!exitg2) && (its <= itmax)) {
        k = i;
        exitg3 = false;
        while ((!exitg3) && ((k + 1 > L + 2) && (!(fabs(h->data[k + h->size[0] *
                   (k - 1)].re) + fabs(h->data[k + h->size[0] * (k - 1)].im) <=
                  SMLNUM)))) {
          tst = (fabs(h->data[(k + h->size[0] * (k - 1)) - 1].re) + fabs(h->
                  data[(k + h->size[0] * (k - 1)) - 1].im)) + (fabs(h->data[k +
            h->size[0] * k].re) + fabs(h->data[k + h->size[0] * k].im));
          if (tst == 0.0) {
            if (k - 1 >= 1) {
              tst = fabs(h->data[(k + h->size[0] * (k - 2)) - 1].re);
            }

            if (k + 2 <= n) {
              tst += fabs(h->data[(k + h->size[0] * k) + 1].re);
            }
          }

          if (fabs(h->data[k + h->size[0] * (k - 1)].re) <=
              2.2204460492503131E-16 * tst) {
            htmp1 = fabs(h->data[k + h->size[0] * (k - 1)].re) + fabs(h->data[k
              + h->size[0] * (k - 1)].im);
            tst = fabs(h->data[(k + h->size[0] * k) - 1].re) + fabs(h->data[(k +
              h->size[0] * k) - 1].im);
            if (htmp1 > tst) {
              t_im = htmp1;
              ba = tst;
            } else {
              t_im = tst;
              ba = htmp1;
            }

            htmp1 = fabs(h->data[k + h->size[0] * k].re) + fabs(h->data[k +
              h->size[0] * k].im);
            br = h->data[(k + h->size[0] * (k - 1)) - 1].re - h->data[k +
              h->size[0] * k].re;
            x_im = h->data[(k + h->size[0] * (k - 1)) - 1].im - h->data[k +
              h->size[0] * k].im;
            tst = fabs(br) + fabs(x_im);
            if (htmp1 > tst) {
              aa = htmp1;
              htmp1 = tst;
            } else {
              aa = tst;
            }

            s = aa + t_im;
            if (ba * (t_im / s) <= fmax(SMLNUM, 2.2204460492503131E-16 * (htmp1 *
                  (aa / s)))) {
              exitg3 = true;
            } else {
              k--;
            }
          } else {
            k--;
          }
        }

        L = k - 1;
        if (k + 1 > 1) {
          h->data[k + h->size[0] * (k - 1)].re = 0.0;
          h->data[k + h->size[0] * (k - 1)].im = 0.0;
        }

        if (k + 1 >= i + 1) {
          goto140 = true;
          exitg2 = true;
        } else {
          if (its == 10) {
            t_re = 0.75 * fabs(h->data[(k + h->size[0] * k) + 1].re) + h->data[k
              + h->size[0] * k].re;
            t_im = h->data[k + h->size[0] * k].im;
          } else if (its == 20) {
            t_re = 0.75 * fabs(h->data[i + h->size[0] * (i - 1)].re) + h->data[i
              + h->size[0] * i].re;
            t_im = h->data[i + h->size[0] * i].im;
          } else {
            t_re = h->data[i + h->size[0] * i].re;
            t_im = h->data[i + h->size[0] * i].im;
            v = h->data[(i + h->size[0] * i) - 1];
            b_sqrt(&v);
            sc = h->data[i + h->size[0] * (i - 1)];
            b_sqrt(&sc);
            u_re = v.re * sc.re - v.im * sc.im;
            u_im = v.re * sc.im + v.im * sc.re;
            s = fabs(u_re) + fabs(u_im);
            if (s != 0.0) {
              tst = h->data[(i + h->size[0] * (i - 1)) - 1].re - h->data[i +
                h->size[0] * i].re;
              aa = h->data[(i + h->size[0] * (i - 1)) - 1].im - h->data[i +
                h->size[0] * i].im;
              br = 0.5 * tst;
              x_im = 0.5 * aa;
              tst = fabs(br) + fabs(x_im);
              s = fmax(s, tst);
              if (x_im == 0.0) {
                t_re = br / s;
                t_im = 0.0;
              } else if (br == 0.0) {
                t_re = 0.0;
                t_im = x_im / s;
              } else {
                t_re = br / s;
                t_im = x_im / s;
              }

              htmp1 = t_re;
              t_re = t_re * t_re - t_im * t_im;
              t_im = htmp1 * t_im + t_im * htmp1;
              if (u_im == 0.0) {
                sc.re = u_re / s;
                sc.im = 0.0;
              } else if (u_re == 0.0) {
                sc.re = 0.0;
                sc.im = u_im / s;
              } else {
                sc.re = u_re / s;
                sc.im = u_im / s;
              }

              v.re = t_re + (sc.re * sc.re - sc.im * sc.im);
              v.im = t_im + (sc.re * sc.im + sc.im * sc.re);
              b_sqrt(&v);
              sc.re = s * v.re;
              sc.im = s * v.im;
              if (tst > 0.0) {
                if (x_im == 0.0) {
                  t_re = br / tst;
                  t_im = 0.0;
                } else if (br == 0.0) {
                  t_re = 0.0;
                  t_im = x_im / tst;
                } else {
                  t_re = br / tst;
                  t_im = x_im / tst;
                }

                if (t_re * sc.re + t_im * sc.im < 0.0) {
                  sc.re = -sc.re;
                  sc.im = -sc.im;
                }
              }

              br += sc.re;
              htmp1 = x_im + sc.im;
              if (htmp1 == 0.0) {
                if (u_im == 0.0) {
                  ba = u_re / br;
                  tst = 0.0;
                } else if (u_re == 0.0) {
                  ba = 0.0;
                  tst = u_im / br;
                } else {
                  ba = u_re / br;
                  tst = u_im / br;
                }
              } else if (br == 0.0) {
                if (u_re == 0.0) {
                  ba = u_im / htmp1;
                  tst = 0.0;
                } else if (u_im == 0.0) {
                  ba = 0.0;
                  tst = -(u_re / htmp1);
                } else {
                  ba = u_im / htmp1;
                  tst = -(u_re / htmp1);
                }
              } else {
                t_im = fabs(br);
                tst = fabs(htmp1);
                if (t_im > tst) {
                  s = htmp1 / br;
                  tst = br + s * htmp1;
                  ba = (u_re + s * u_im) / tst;
                  tst = (u_im - s * u_re) / tst;
                } else if (tst == t_im) {
                  if (br > 0.0) {
                    aa = 0.5;
                  } else {
                    aa = -0.5;
                  }

                  if (htmp1 > 0.0) {
                    tst = 0.5;
                  } else {
                    tst = -0.5;
                  }

                  ba = (u_re * aa + u_im * tst) / t_im;
                  tst = (u_im * aa - u_re * tst) / t_im;
                } else {
                  s = br / htmp1;
                  tst = htmp1 + s * br;
                  ba = (s * u_re + u_im) / tst;
                  tst = (s * u_im - u_re) / tst;
                }
              }

              t_re = h->data[i + h->size[0] * i].re - (u_re * ba - u_im * tst);
              t_im = h->data[i + h->size[0] * i].im - (u_re * tst + u_im * ba);
            }
          }

          goto70 = false;
          m = i;
          exitg3 = false;
          while ((!exitg3) && (m > k + 1)) {
            sc.re = h->data[(m + h->size[0] * (m - 1)) - 1].re - t_re;
            sc.im = h->data[(m + h->size[0] * (m - 1)) - 1].im - t_im;
            tst = h->data[m + h->size[0] * (m - 1)].re;
            s = (fabs(sc.re) + fabs(sc.im)) + fabs(tst);
            if (sc.im == 0.0) {
              sc.re /= s;
              sc.im = 0.0;
            } else if (sc.re == 0.0) {
              sc.re = 0.0;
              sc.im /= s;
            } else {
              sc.re /= s;
              sc.im /= s;
            }

            tst /= s;
            b_v[0] = sc;
            b_v[1].re = tst;
            b_v[1].im = 0.0;
            if (fabs(h->data[(m + h->size[0] * (m - 2)) - 1].re) * fabs(tst) <=
                2.2204460492503131E-16 * ((fabs(sc.re) + fabs(sc.im)) * ((fabs
                   (h->data[(m + h->size[0] * (m - 1)) - 1].re) + fabs(h->data
                    [(m + h->size[0] * (m - 1)) - 1].im)) + (fabs(h->data[m +
                    h->size[0] * m].re) + fabs(h->data[m + h->size[0] * m].im)))))
            {
              goto70 = true;
              exitg3 = true;
            } else {
              m--;
            }
          }

          if (!goto70) {
            sc.re = h->data[k + h->size[0] * k].re - t_re;
            sc.im = h->data[k + h->size[0] * k].im - t_im;
            tst = h->data[(k + h->size[0] * k) + 1].re;
            s = (fabs(sc.re) + fabs(sc.im)) + fabs(tst);
            if (sc.im == 0.0) {
              b_v[0].re = sc.re / s;
              b_v[0].im = 0.0;
            } else if (sc.re == 0.0) {
              b_v[0].re = 0.0;
              b_v[0].im = sc.im / s;
            } else {
              b_v[0].re = sc.re / s;
              b_v[0].im = sc.im / s;
            }

            tst /= s;
            b_v[1].re = tst;
            b_v[1].im = 0.0;
          }

          for (b_k = m; b_k <= i; b_k++) {
            if (b_k > m) {
              b_v[0] = h->data[(b_k + h->size[0] * (b_k - 2)) - 1];
              b_v[1] = h->data[b_k + h->size[0] * (b_k - 2)];
            }

            sc = b_v[0];
            br = b_v[1].re;
            x_im = b_v[1].im;
            t_re = 0.0;
            t_im = 0.0;
            tst = rt_hypotd_snf(b_v[1].re, b_v[1].im);
            if ((tst != 0.0) || (b_v[0].im != 0.0)) {
              htmp1 = xdlapy3(b_v[0].re, b_v[0].im, tst);
              if (b_v[0].re >= 0.0) {
                htmp1 = -htmp1;
              }

              if (fabs(htmp1) < 1.0020841800044864E-292) {
                knt = -1;
                do {
                  knt++;
                  br *= 9.9792015476736E+291;
                  x_im *= 9.9792015476736E+291;
                  htmp1 *= 9.9792015476736E+291;
                  sc.re *= 9.9792015476736E+291;
                  sc.im *= 9.9792015476736E+291;
                } while (!(fabs(htmp1) >= 1.0020841800044864E-292));

                htmp1 = xdlapy3(sc.re, sc.im, rt_hypotd_snf(br, x_im));
                if (sc.re >= 0.0) {
                  htmp1 = -htmp1;
                }

                aa = htmp1 - sc.re;
                if (0.0 - sc.im == 0.0) {
                  t_re = aa / htmp1;
                  t_im = 0.0;
                } else if (aa == 0.0) {
                  t_re = 0.0;
                  t_im = (0.0 - sc.im) / htmp1;
                } else {
                  t_re = aa / htmp1;
                  t_im = (0.0 - sc.im) / htmp1;
                }

                v.re = sc.re - htmp1;
                v.im = sc.im;
                sc = recip(v);
                tst = br;
                br = sc.re * br - sc.im * x_im;
                x_im = sc.re * x_im + sc.im * tst;
                for (c_k = 0; c_k <= knt; c_k++) {
                  htmp1 *= 1.0020841800044864E-292;
                }

                sc.re = htmp1;
                sc.im = 0.0;
              } else {
                aa = htmp1 - b_v[0].re;
                if (0.0 - b_v[0].im == 0.0) {
                  t_re = aa / htmp1;
                  t_im = 0.0;
                } else if (aa == 0.0) {
                  t_re = 0.0;
                  t_im = (0.0 - b_v[0].im) / htmp1;
                } else {
                  t_re = aa / htmp1;
                  t_im = (0.0 - b_v[0].im) / htmp1;
                }

                v.re = b_v[0].re - htmp1;
                v.im = b_v[0].im;
                v = recip(v);
                br = v.re * b_v[1].re - v.im * b_v[1].im;
                x_im = v.re * b_v[1].im + v.im * b_v[1].re;
                sc.re = htmp1;
                sc.im = 0.0;
              }
            }

            b_v[0] = sc;
            b_v[1].re = br;
            b_v[1].im = x_im;
            if (b_k > m) {
              h->data[(b_k + h->size[0] * (b_k - 2)) - 1] = sc;
              h->data[b_k + h->size[0] * (b_k - 2)].re = 0.0;
              h->data[b_k + h->size[0] * (b_k - 2)].im = 0.0;
            }

            htmp1 = t_re * br - t_im * x_im;
            for (j = b_k; j <= n; j++) {
              tst = t_re * h->data[(b_k + h->size[0] * (j - 1)) - 1].re - -t_im *
                h->data[(b_k + h->size[0] * (j - 1)) - 1].im;
              aa = t_re * h->data[(b_k + h->size[0] * (j - 1)) - 1].im + -t_im *
                h->data[(b_k + h->size[0] * (j - 1)) - 1].re;
              sc.re = tst + htmp1 * h->data[b_k + h->size[0] * (j - 1)].re;
              sc.im = aa + htmp1 * h->data[b_k + h->size[0] * (j - 1)].im;
              h->data[(b_k + h->size[0] * (j - 1)) - 1].re -= sc.re;
              h->data[(b_k + h->size[0] * (j - 1)) - 1].im -= sc.im;
              h->data[b_k + h->size[0] * (j - 1)].re -= sc.re * br - sc.im *
                x_im;
              h->data[b_k + h->size[0] * (j - 1)].im -= sc.re * x_im + sc.im *
                br;
            }

            if (b_k + 2 < i + 1) {
              knt = b_k + 1;
            } else {
              knt = i;
            }

            for (j = 0; j <= knt; j++) {
              tst = t_re * h->data[j + h->size[0] * (b_k - 1)].re - t_im *
                h->data[j + h->size[0] * (b_k - 1)].im;
              aa = t_re * h->data[j + h->size[0] * (b_k - 1)].im + t_im *
                h->data[j + h->size[0] * (b_k - 1)].re;
              sc.re = tst + htmp1 * h->data[j + h->size[0] * b_k].re;
              sc.im = aa + htmp1 * h->data[j + h->size[0] * b_k].im;
              h->data[j + h->size[0] * (b_k - 1)].re -= sc.re;
              h->data[j + h->size[0] * (b_k - 1)].im -= sc.im;
              h->data[j + h->size[0] * b_k].re -= sc.re * br - sc.im * -x_im;
              h->data[j + h->size[0] * b_k].im -= sc.re * -x_im + sc.im * br;
            }

            for (j = 0; j < n; j++) {
              tst = t_re * z->data[j + z->size[0] * (b_k - 1)].re - t_im *
                z->data[j + z->size[0] * (b_k - 1)].im;
              aa = t_re * z->data[j + z->size[0] * (b_k - 1)].im + t_im *
                z->data[j + z->size[0] * (b_k - 1)].re;
              sc.re = tst + htmp1 * z->data[j + z->size[0] * b_k].re;
              sc.im = aa + htmp1 * z->data[j + z->size[0] * b_k].im;
              z->data[j + z->size[0] * (b_k - 1)].re -= sc.re;
              z->data[j + z->size[0] * (b_k - 1)].im -= sc.im;
              z->data[j + z->size[0] * b_k].re -= sc.re * br - sc.im * -x_im;
              z->data[j + z->size[0] * b_k].im -= sc.re * -x_im + sc.im * br;
            }

            if ((b_k == m) && (m > k + 1)) {
              br = rt_hypotd_snf(1.0 - t_re, 0.0 - t_im);
              if (0.0 - t_im == 0.0) {
                sc.re = (1.0 - t_re) / br;
                sc.im = 0.0;
              } else if (1.0 - t_re == 0.0) {
                sc.re = 0.0;
                sc.im = (0.0 - t_im) / br;
              } else {
                sc.re = (1.0 - t_re) / br;
                sc.im = (0.0 - t_im) / br;
              }

              tst = h->data[m + h->size[0] * (m - 1)].re;
              aa = h->data[m + h->size[0] * (m - 1)].im;
              h->data[m + h->size[0] * (m - 1)].re = tst * sc.re - aa * -sc.im;
              h->data[m + h->size[0] * (m - 1)].im = tst * -sc.im + aa * sc.re;
              if (m + 2 <= i + 1) {
                tst = h->data[(m + h->size[0] * m) + 1].re;
                aa = h->data[(m + h->size[0] * m) + 1].im;
                h->data[(m + h->size[0] * m) + 1].re = tst * sc.re - aa * sc.im;
                h->data[(m + h->size[0] * m) + 1].im = tst * sc.im + aa * sc.re;
              }

              for (j = m; j <= i + 1; j++) {
                if (j != m + 1) {
                  if (n > j) {
                    ix0 = j + j * ldh;
                    if (ldh >= 1) {
                      knt = ix0 + ldh * ((n - j) - 1);
                      for (c_k = ix0; ldh < 0 ? c_k >= knt : c_k <= knt; c_k +=
                           ldh) {
                        tst = h->data[c_k - 1].re;
                        aa = h->data[c_k - 1].im;
                        h->data[c_k - 1].re = sc.re * tst - sc.im * aa;
                        h->data[c_k - 1].im = sc.re * aa + sc.im * tst;
                      }
                    }
                  }

                  ix0_tmp = (j - 1) * ldh;
                  ldz = ix0_tmp + 1;
                  t_re = sc.re;
                  t_im = -sc.im;
                  knt = (ix0_tmp + j) - 1;
                  for (c_k = ldz; c_k <= knt; c_k++) {
                    tst = h->data[c_k - 1].re;
                    aa = h->data[c_k - 1].im;
                    h->data[c_k - 1].re = t_re * tst - t_im * aa;
                    h->data[c_k - 1].im = t_re * aa + t_im * tst;
                  }

                  t_re = sc.re;
                  t_im = -sc.im;
                  knt = ix0_tmp + n;
                  for (c_k = ldz; c_k <= knt; c_k++) {
                    tst = z->data[c_k - 1].re;
                    aa = z->data[c_k - 1].im;
                    z->data[c_k - 1].re = t_re * tst - t_im * aa;
                    z->data[c_k - 1].im = t_re * aa + t_im * tst;
                  }
                }
              }
            }
          }

          sc = h->data[i + h->size[0] * (i - 1)];
          if (h->data[i + h->size[0] * (i - 1)].im != 0.0) {
            tst = rt_hypotd_snf(h->data[i + h->size[0] * (i - 1)].re, h->data[i
                                + h->size[0] * (i - 1)].im);
            h->data[i + h->size[0] * (i - 1)].re = tst;
            h->data[i + h->size[0] * (i - 1)].im = 0.0;
            if (sc.im == 0.0) {
              sc.re /= tst;
              sc.im = 0.0;
            } else if (sc.re == 0.0) {
              sc.re = 0.0;
              sc.im /= tst;
            } else {
              sc.re /= tst;
              sc.im /= tst;
            }

            if (n > i + 1) {
              ix0 = (i + (i + 1) * ldh) + 1;
              t_re = sc.re;
              t_im = -sc.im;
              if (ldh >= 1) {
                knt = ix0 + ldh * ((n - i) - 2);
                for (k = ix0; ldh < 0 ? k >= knt : k <= knt; k += ldh) {
                  tst = h->data[k - 1].re;
                  aa = h->data[k - 1].im;
                  h->data[k - 1].re = t_re * tst - t_im * aa;
                  h->data[k - 1].im = t_re * aa + t_im * tst;
                }
              }
            }

            ix0_tmp = i * ldh;
            ldz = ix0_tmp + 1;
            knt = ix0_tmp + i;
            for (k = ldz; k <= knt; k++) {
              tst = h->data[k - 1].re;
              aa = h->data[k - 1].im;
              h->data[k - 1].re = sc.re * tst - sc.im * aa;
              h->data[k - 1].im = sc.re * aa + sc.im * tst;
            }

            knt = ix0_tmp + n;
            for (k = ldz; k <= knt; k++) {
              tst = z->data[k - 1].re;
              aa = z->data[k - 1].im;
              z->data[k - 1].re = sc.re * tst - sc.im * aa;
              z->data[k - 1].im = sc.re * aa + sc.im * tst;
            }
          }

          its++;
        }
      }

      if (!goto140) {
        info = i + 1;
        exitg1 = true;
      } else {
        i = L;
      }
    }
  }

  return info;
}

/*
 * File trailer for xzhseqr.c
 *
 * [EOF]
 */
