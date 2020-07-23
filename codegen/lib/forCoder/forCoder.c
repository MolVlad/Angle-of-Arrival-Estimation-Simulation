/*
 * File: forCoder.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 23-Jul-2020 18:38:00
 */

/* Include Files */
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "forCoder_emxutil.h"
#include "fclose.h"
#include "fileManager.h"
#include "string1.h"
#include "imregionalmax.h"
#include "abs.h"
#include "sum.h"
#include "sort1.h"
#include "diag.h"
#include "eig.h"
#include "kron.h"
#include "exp.h"
#include "hankel.h"
#include "str2double.h"
#include "char.h"
#include "fread.h"
#include "fseek.h"
#include "ftell.h"
#include "sprintf.h"
#include "forCoder_rtwutil.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* Function Definitions */

/*
 * Arguments    : double seed
 * Return Type  : void
 */
void forCoder(double seed)
{
  emxArray_char_T *s;
  double cdiff;
  int i0;
  char seed_str[5];
  int loop_ub;
  int i1;
  char subdir_Value[11];
  static const char cv0[6] = { 'm', 'u', 's', 'i', 'c', '_' };

  signed char fileid;
  FILE * b_NULL;
  FILE * filestar;
  boolean_T autoflush;
  char filename_Value[15];
  static const char cv1[6] = { '.', '/', 'c', 's', 'i', '_' };

  static unsigned char buffer[2097152];
  int remaining;
  int b_index;
  emxArray_real_T *dataRead;
  emxArray_int32_T *r0;
  boolean_T exitg1;
  int nm1d2;
  emxArray_uint8_T *b_buffer;
  double apnd;
  emxArray_char_T *str;
  int i2;
  int k;
  emxArray_char_T *b_str;
  int i;
  int j;
  unsigned char u0;
  emxArray_creal_T *matrixCSI;
  emxArray_creal_T *smoothedMatrixCSI;
  emxArray_creal_T *D;
  emxArray_creal_T *De;
  emxArray_creal_T *tmp;
  static creal_T y[28800];
  emxArray_creal_T *steeringVector;
  emxArray_real_T *nsDelayAngleSpotfiEstimated;
  emxArray_creal_T *mat;
  emxArray_creal_T *Rxx;
  emxArray_creal_T *Qn;
  emxArray_boolean_T *isStrongEnough;
  emxArray_real_T *newEstimation;
  emxArray_creal_T *Utmp;
  emxArray_creal_T *r1;
  emxArray_boolean_T *r2;
  emxArray_boolean_T *r3;
  emxArray_int32_T *r4;
  emxArray_int32_T *r5;
  emxArray_creal_T *b;
  emxArray_creal_T *b_y;
  emxArray_int32_T *ii;
  emxArray_uint8_T *vk;
  emxArray_real_T *varargin_1;
  emxArray_creal_T *r6;
  emxArray_creal_T *r7;
  emxArray_real_T *r8;
  emxArray_creal_T *b_steeringVector;
  emxArray_real_T *b_newEstimation;
  emxArray_real_T *b_nsDelayAngleSpotfiEstimated;
  int ant;
  int b_ant;
  int subarrayNum;
  int numberOfAntennaInSubset;
  double a;
  double b_b;
  int perSpec;
  int numberOfSpectrums;
  int loop_ub_tmp;
  int dec;
  static const signed char iv0[2] = { 0, 1 };

  short subCarrInd_data[117];
  int numberOfSubcarrierSubsets;
  int columnsNum_tmp_tmp;
  int columnsNum_tmp;
  int columnsNum;
  int b_loop_ub_tmp;
  int b_loop_ub;
  int coffset;
  int boffset;
  int t;
  signed char y_data[58];
  int aoffset;
  double b_y_data[7];
  int i3;
  int tmp_size[2];
  creal_T dcv0[181];
  static const double dv0[181] = { -0.5, -0.49992384757819563,
    -0.49969541350954788, -0.49931476737728692, -0.4987820251299121,
    -0.49809734904587277, -0.49726094768413664, -0.496273075820661,
    -0.49513403437078518, -0.49384417029756889, -0.492403876506104,
    -0.490813591723832, -0.48907380036690284, -0.48718503239261762,
    -0.48514786313799824, -0.48296291314453416, -0.48063084796915945,
    -0.47815237798151772, -0.47552825814757677, -0.47275928779965842,
    -0.46984631039295421, -0.46679021324860087, -0.46359192728339371,
    -0.46025242672622019, -0.45677272882130043, -0.45315389351832497,
    -0.44939702314958352, -0.44550326209418395, -0.44147379642946349,
    -0.43730985356969787, -0.43301270189221935, -0.42858365035105617,
    -0.424024048078213, -0.419335283972712, -0.41451878627752081,
    -0.4095760221444959, -0.40450849718747373, -0.39931775502364641,
    -0.39400537680336095, -0.38857298072848545, -0.383022221559489,
    -0.377354790111386, -0.37157241273869712, -0.36567685080958523,
    -0.3596699001693256, -0.35355339059327373, -0.34732918522949863,
    -0.34099918003124924, -0.33456530317942912, -0.32802951449525364,
    -0.32139380484326963, -0.3146601955249187, -0.30783073766282915,
    -0.30090751157602413, -0.29389262614623657, -0.286788218175523,
    -0.27959645173537345, -0.27231951750751354, -0.26495963211660245,
    -0.25751903745502708, -0.24999999999999997, -0.24240481012316853,
    -0.2347357813929454, -0.22699524986977337, -0.2191855733945387,
    -0.21130913087034972, -0.2033683215379001, -0.19536556424463689,
    -0.187303296707956, -0.17918397477265013, -0.17101007166283436,
    -0.16278407722857835, -0.1545084971874737, -0.14618585236136838,
    -0.13781867790849958, -0.12940952255126037, -0.12096094779983387,
    -0.1124755271719325, -0.10395584540887967, -0.0954044976882724,
    -0.086824088833465166, -0.078217232520115434, -0.069586550480032719,
    -0.060934671702573738, -0.052264231633826735, -0.043577871373829083,
    -0.034878236872062651, -0.026167978121471917, -0.017449748351250485,
    -0.0087262032186417558, 0.0, 0.0087262032186417558, 0.017449748351250485,
    0.026167978121471917, 0.034878236872062651, 0.043577871373829083,
    0.052264231633826735, 0.060934671702573738, 0.069586550480032719,
    0.078217232520115434, 0.086824088833465166, 0.0954044976882724,
    0.10395584540887967, 0.1124755271719325, 0.12096094779983387,
    0.12940952255126037, 0.13781867790849958, 0.14618585236136838,
    0.1545084971874737, 0.16278407722857835, 0.17101007166283436,
    0.17918397477265013, 0.187303296707956, 0.19536556424463689,
    0.2033683215379001, 0.21130913087034972, 0.2191855733945387,
    0.22699524986977337, 0.2347357813929454, 0.24240481012316853,
    0.24999999999999997, 0.25751903745502708, 0.26495963211660245,
    0.27231951750751354, 0.27959645173537345, 0.286788218175523,
    0.29389262614623657, 0.30090751157602413, 0.30783073766282915,
    0.3146601955249187, 0.32139380484326963, 0.32802951449525364,
    0.33456530317942912, 0.34099918003124924, 0.34732918522949863,
    0.35355339059327373, 0.3596699001693256, 0.36567685080958523,
    0.37157241273869712, 0.377354790111386, 0.383022221559489,
    0.38857298072848545, 0.39400537680336095, 0.39931775502364641,
    0.40450849718747373, 0.4095760221444959, 0.41451878627752081,
    0.419335283972712, 0.424024048078213, 0.42858365035105617,
    0.43301270189221935, 0.43730985356969787, 0.44147379642946349,
    0.44550326209418395, 0.44939702314958352, 0.45315389351832497,
    0.45677272882130043, 0.46025242672622019, 0.46359192728339371,
    0.46679021324860087, 0.46984631039295421, 0.47275928779965842,
    0.47552825814757677, 0.47815237798151772, 0.48063084796915945,
    0.48296291314453416, 0.48514786313799824, 0.48718503239261762,
    0.48907380036690284, 0.490813591723832, 0.492403876506104,
    0.49384417029756889, 0.49513403437078518, 0.496273075820661,
    0.49726094768413664, 0.49809734904587277, 0.4987820251299121,
    0.49931476737728692, 0.49969541350954788, 0.49992384757819563, 0.5 };

  creal_T csiFromEachPacket_data[936];
  creal_T tmp_data[1267];
  creal_T b_csiFromEachPacket_data[58];
  int csiFromEachPacket_size[1];
  creal_T dcv1[601];
  static const double dv1[601] = { -3.0000000000000004E-7, -2.99E-7,
    -2.9800000000000005E-7, -2.97E-7, -2.9600000000000006E-7,
    -2.9500000000000003E-7, -2.9400000000000007E-7, -2.9300000000000004E-7,
    -2.92E-7, -2.9100000000000005E-7, -2.9000000000000003E-7,
    -2.8900000000000006E-7, -2.8800000000000004E-7, -2.87E-7,
    -2.8600000000000005E-7, -2.85E-7, -2.8400000000000005E-7,
    -2.8300000000000003E-7, -2.82E-7, -2.8100000000000004E-7, -2.8E-7,
    -2.7900000000000005E-7, -2.7800000000000003E-7, -2.7700000000000006E-7,
    -2.7600000000000004E-7, -2.75E-7, -2.7400000000000004E-7, -2.73E-7,
    -2.7200000000000005E-7, -2.7100000000000003E-7, -2.7000000000000006E-7,
    -2.6900000000000004E-7, -2.68E-7, -2.6700000000000005E-7, -2.66E-7,
    -2.6500000000000006E-7, -2.6400000000000003E-7, -2.6300000000000007E-7,
    -2.6200000000000004E-7, -2.61E-7, -2.6000000000000005E-7,
    -2.5900000000000003E-7, -2.58E-7, -2.5700000000000004E-7, -2.56E-7,
    -2.5500000000000005E-7, -2.54E-7, -2.5300000000000006E-7,
    -2.5200000000000003E-7, -2.51E-7, -2.5000000000000004E-7, -2.49E-7,
    -2.4800000000000005E-7, -2.4700000000000003E-7, -2.4600000000000006E-7,
    -2.4500000000000004E-7, -2.44E-7, -2.4300000000000005E-7, -2.42E-7,
    -2.4100000000000005E-7, -2.4000000000000003E-7, -2.3900000000000006E-7,
    -2.3800000000000004E-7, -2.3700000000000002E-7, -2.3600000000000005E-7,
    -2.3500000000000003E-7, -2.3400000000000003E-7, -2.3300000000000003E-7,
    -2.3200000000000004E-7, -2.3100000000000004E-7, -2.3000000000000002E-7,
    -2.2900000000000005E-7, -2.2800000000000003E-7, -2.2700000000000003E-7,
    -2.2600000000000004E-7, -2.2500000000000002E-7, -2.2400000000000005E-7,
    -2.2300000000000002E-7, -2.2200000000000003E-7, -2.2100000000000003E-7,
    -2.2000000000000004E-7, -2.1900000000000004E-7, -2.1800000000000002E-7,
    -2.1700000000000005E-7, -2.1600000000000003E-7, -2.1500000000000003E-7,
    -2.1400000000000004E-7, -2.1300000000000001E-7, -2.1200000000000005E-7,
    -2.1100000000000002E-7, -2.1000000000000003E-7, -2.0900000000000003E-7,
    -2.0800000000000004E-7, -2.0700000000000004E-7, -2.0600000000000002E-7,
    -2.0500000000000005E-7, -2.0400000000000003E-7, -2.0300000000000003E-7,
    -2.0200000000000004E-7, -2.0100000000000004E-7, -2.0000000000000004E-7,
    -1.9900000000000002E-7, -1.9800000000000005E-7, -1.9700000000000003E-7,
    -1.9600000000000003E-7, -1.9500000000000004E-7, -1.9400000000000002E-7,
    -1.9300000000000005E-7, -1.9200000000000003E-7, -1.9100000000000003E-7,
    -1.9000000000000003E-7, -1.8900000000000004E-7, -1.8800000000000004E-7,
    -1.8700000000000002E-7, -1.8600000000000005E-7, -1.8500000000000003E-7,
    -1.8400000000000003E-7, -1.8300000000000004E-7, -1.8200000000000002E-7,
    -1.8100000000000005E-7, -1.8000000000000002E-7, -1.7900000000000003E-7,
    -1.7800000000000003E-7, -1.7700000000000004E-7, -1.7600000000000004E-7,
    -1.7500000000000002E-7, -1.7400000000000002E-7, -1.7300000000000003E-7,
    -1.7200000000000003E-7, -1.7100000000000004E-7, -1.7000000000000004E-7,
    -1.6900000000000004E-7, -1.6800000000000002E-7, -1.6700000000000003E-7,
    -1.6600000000000003E-7, -1.6500000000000003E-7, -1.6400000000000004E-7,
    -1.6300000000000004E-7, -1.6200000000000002E-7, -1.6100000000000003E-7,
    -1.6000000000000003E-7, -1.5900000000000003E-7, -1.5800000000000004E-7,
    -1.5700000000000004E-7, -1.5600000000000002E-7, -1.5500000000000002E-7,
    -1.5400000000000003E-7, -1.5300000000000003E-7, -1.5200000000000004E-7,
    -1.5100000000000004E-7, -1.5000000000000002E-7, -1.4900000000000002E-7,
    -1.4800000000000003E-7, -1.4700000000000003E-7, -1.4600000000000004E-7,
    -1.4500000000000004E-7, -1.4400000000000002E-7, -1.4300000000000002E-7,
    -1.4200000000000003E-7, -1.4100000000000003E-7, -1.4000000000000004E-7,
    -1.3900000000000004E-7, -1.3800000000000002E-7, -1.3700000000000002E-7,
    -1.3600000000000003E-7, -1.3500000000000003E-7, -1.3400000000000004E-7,
    -1.3300000000000004E-7, -1.3200000000000002E-7, -1.3100000000000002E-7,
    -1.3000000000000003E-7, -1.2900000000000003E-7, -1.2800000000000003E-7,
    -1.2700000000000004E-7, -1.2600000000000002E-7, -1.2500000000000002E-7,
    -1.2400000000000003E-7, -1.2300000000000003E-7, -1.2200000000000003E-7,
    -1.2100000000000004E-7, -1.2000000000000002E-7, -1.1900000000000002E-7,
    -1.1800000000000002E-7, -1.1700000000000003E-7, -1.1600000000000003E-7,
    -1.1500000000000004E-7, -1.1400000000000001E-7, -1.1300000000000002E-7,
    -1.1200000000000002E-7, -1.1100000000000003E-7, -1.1000000000000003E-7,
    -1.0900000000000004E-7, -1.0800000000000001E-7, -1.0700000000000002E-7,
    -1.0600000000000002E-7, -1.0500000000000003E-7, -1.0400000000000003E-7,
    -1.0300000000000004E-7, -1.0200000000000004E-7, -1.0100000000000002E-7,
    -1.0000000000000002E-7, -9.9000000000000026E-8, -9.8000000000000031E-8,
    -9.7000000000000035E-8, -9.6000000000000039E-8, -9.5000000000000017E-8,
    -9.4000000000000021E-8, -9.3000000000000025E-8, -9.200000000000003E-8,
    -9.1000000000000034E-8, -9.0000000000000038E-8, -8.9000000000000016E-8,
    -8.800000000000002E-8, -8.7000000000000025E-8, -8.6000000000000029E-8,
    -8.5000000000000033E-8, -8.4000000000000037E-8, -8.3000000000000015E-8,
    -8.200000000000002E-8, -8.1000000000000024E-8, -8.0000000000000028E-8,
    -7.9000000000000032E-8, -7.8000000000000037E-8, -7.7000000000000015E-8,
    -7.6000000000000019E-8, -7.5000000000000023E-8, -7.4000000000000027E-8,
    -7.3000000000000032E-8, -7.2000000000000036E-8, -7.1000000000000014E-8,
    -7.0000000000000018E-8, -6.9000000000000022E-8, -6.8000000000000027E-8,
    -6.7000000000000031E-8, -6.6000000000000035E-8, -6.5000000000000013E-8,
    -6.4000000000000017E-8, -6.3000000000000022E-8, -6.2000000000000026E-8,
    -6.100000000000003E-8, -6.0000000000000008E-8, -5.9000000000000039E-8,
    -5.8000000000000016E-8, -5.7000000000000047E-8, -5.6000000000000025E-8,
    -5.5E-8, -5.4000000000000034E-8, -5.3000000000000011E-8,
    -5.2000000000000042E-8, -5.100000000000002E-8, -5.0E-8,
    -4.9000000000000028E-8, -4.8000000000000006E-8, -4.7000000000000037E-8,
    -4.6000000000000015E-8, -4.5000000000000046E-8, -4.4000000000000023E-8,
    -4.3E-8, -4.2000000000000032E-8, -4.100000000000001E-8,
    -4.0000000000000041E-8, -3.9000000000000018E-8, -3.8000000000000049E-8,
    -3.7000000000000027E-8, -3.6000000000000005E-8, -3.5000000000000035E-8,
    -3.4000000000000013E-8, -3.3000000000000044E-8, -3.2000000000000022E-8,
    -3.1E-8, -3.000000000000003E-8, -2.9000000000000008E-8,
    -2.8000000000000039E-8, -2.7000000000000017E-8, -2.6000000000000048E-8,
    -2.5000000000000025E-8, -2.4000000000000003E-8, -2.3000000000000034E-8,
    -2.2000000000000012E-8, -2.1000000000000042E-8, -2.000000000000002E-8,
    -1.8999999999999998E-8, -1.8000000000000029E-8, -1.7000000000000007E-8,
    -1.6000000000000037E-8, -1.5000000000000015E-8, -1.4000000000000046E-8,
    -1.3000000000000024E-8, -1.2000000000000002E-8, -1.1000000000000032E-8,
    -1.000000000000001E-8, -9.0000000000000409E-9, -8.0000000000000187E-9,
    -6.9999999999999965E-9, -6.0000000000000273E-9, -5.0000000000000051E-9,
    -4.0000000000000358E-9, -3.0000000000000136E-9, -2.0000000000000444E-9,
    -1.0000000000000222E-9, 0.0, 9.9999999999996925E-10, 1.9999999999999914E-9,
    2.9999999999999607E-9, 3.9999999999999829E-9, 5.0000000000000051E-9,
    5.9999999999999743E-9, 6.9999999999999965E-9, 7.9999999999999658E-9,
    8.9999999999999879E-9, 9.9999999999999572E-9, 1.0999999999999979E-8,
    1.2000000000000002E-8, 1.2999999999999971E-8, 1.3999999999999993E-8,
    1.4999999999999962E-8, 1.5999999999999984E-8, 1.7000000000000007E-8,
    1.7999999999999976E-8, 1.8999999999999998E-8, 1.9999999999999967E-8,
    2.099999999999999E-8, 2.1999999999999959E-8, 2.2999999999999981E-8,
    2.4000000000000003E-8, 2.4999999999999972E-8, 2.5999999999999995E-8,
    2.6999999999999964E-8, 2.7999999999999986E-8, 2.8999999999999955E-8,
    2.9999999999999977E-8, 3.1E-8, 3.1999999999999969E-8, 3.2999999999999991E-8,
    3.399999999999996E-8, 3.4999999999999983E-8, 3.6000000000000005E-8,
    3.6999999999999974E-8, 3.7999999999999996E-8, 3.8999999999999965E-8,
    3.9999999999999988E-8, 4.0999999999999957E-8, 4.1999999999999979E-8, 4.3E-8,
    4.399999999999997E-8, 4.4999999999999993E-8, 4.5999999999999962E-8,
    4.6999999999999984E-8, 4.8000000000000006E-8, 4.8999999999999976E-8, 5.0E-8,
    5.0999999999999967E-8, 5.1999999999999989E-8, 5.2999999999999958E-8,
    5.3999999999999981E-8, 5.5E-8, 5.5999999999999972E-8, 5.6999999999999994E-8,
    5.7999999999999963E-8, 5.8999999999999986E-8, 6.0000000000000008E-8,
    6.0999999999999977E-8, 6.2E-8, 6.2999999999999969E-8, 6.3999999999999991E-8,
    6.499999999999996E-8, 6.5999999999999982E-8, 6.7E-8, 6.7999999999999974E-8,
    6.9E-8, 6.9999999999999965E-8, 7.0999999999999987E-8, 7.2000000000000009E-8,
    7.2999999999999979E-8, 7.4E-8, 7.499999999999997E-8, 7.5999999999999992E-8,
    7.6999999999999962E-8, 7.7999999999999984E-8, 7.9E-8, 7.9999999999999975E-8,
    8.1E-8, 8.1999999999999967E-8, 8.2999999999999989E-8, 8.4000000000000011E-8,
    8.499999999999998E-8, 8.6E-8, 8.6999999999999972E-8, 8.8E-8,
    8.8999999999999963E-8, 8.9999999999999985E-8, 9.1000000000000008E-8,
    9.1999999999999977E-8, 9.3E-8, 9.3999999999999968E-8, 9.499999999999999E-8,
    9.599999999999996E-8, 9.6999999999999982E-8, 9.8E-8, 9.8999999999999973E-8,
    1.0E-7, 1.0099999999999996E-7, 1.0199999999999999E-7, 1.0300000000000001E-7,
    1.0399999999999998E-7, 1.05E-7, 1.0599999999999997E-7, 1.0699999999999999E-7,
    1.0799999999999996E-7, 1.0899999999999998E-7, 1.1E-7, 1.1099999999999997E-7,
    1.12E-7, 1.1299999999999997E-7, 1.1399999999999999E-7, 1.1500000000000001E-7,
    1.1599999999999998E-7, 1.17E-7, 1.1799999999999997E-7, 1.19E-7,
    1.1999999999999996E-7, 1.2099999999999998E-7, 1.22E-7, 1.2299999999999998E-7,
    1.24E-7, 1.2499999999999997E-7, 1.26E-7, 1.27E-7, 1.2799999999999998E-7,
    1.29E-7, 1.2999999999999997E-7, 1.31E-7, 1.3199999999999996E-7,
    1.3299999999999999E-7, 1.34E-7, 1.3499999999999998E-7, 1.36E-7,
    1.3699999999999997E-7, 1.38E-7, 1.3900000000000001E-7, 1.3999999999999998E-7,
    1.41E-7, 1.4199999999999997E-7, 1.43E-7, 1.4399999999999997E-7, 1.45E-7,
    1.46E-7, 1.4699999999999998E-7, 1.48E-7, 1.4899999999999997E-7, 1.5E-7,
    1.5099999999999996E-7, 1.5199999999999998E-7, 1.53E-7, 1.5399999999999998E-7,
    1.55E-7, 1.5599999999999997E-7, 1.57E-7, 1.58E-7, 1.5899999999999998E-7,
    1.6E-7, 1.6099999999999997E-7, 1.62E-7, 1.6299999999999996E-7,
    1.6399999999999999E-7, 1.65E-7, 1.6599999999999998E-7, 1.67E-7,
    1.6799999999999997E-7, 1.69E-7, 1.7000000000000001E-7, 1.7099999999999998E-7,
    1.72E-7, 1.7299999999999997E-7, 1.74E-7, 1.7499999999999997E-7, 1.76E-7,
    1.77E-7, 1.7799999999999998E-7, 1.7899999999999995E-7, 1.8000000000000002E-7,
    1.81E-7, 1.8199999999999996E-7, 1.8300000000000004E-7, 1.84E-7,
    1.8499999999999998E-7, 1.8599999999999994E-7, 1.8700000000000002E-7, 1.88E-7,
    1.8899999999999996E-7, 1.9000000000000003E-7, 1.91E-7, 1.9199999999999997E-7,
    1.9299999999999994E-7, 1.9400000000000002E-7, 1.9499999999999999E-7,
    1.9599999999999996E-7, 1.9700000000000003E-7, 1.98E-7, 1.9899999999999997E-7,
    2.0000000000000004E-7, 2.01E-7, 2.0199999999999998E-7, 2.0299999999999995E-7,
    2.0400000000000003E-7, 2.05E-7, 2.0599999999999997E-7, 2.0700000000000004E-7,
    2.08E-7, 2.0899999999999998E-7, 2.0999999999999995E-7, 2.1100000000000002E-7,
    2.12E-7, 2.1299999999999996E-7, 2.1400000000000004E-7, 2.15E-7,
    2.1599999999999998E-7, 2.1699999999999994E-7, 2.1800000000000002E-7, 2.19E-7,
    2.1999999999999996E-7, 2.2100000000000003E-7, 2.22E-7, 2.2299999999999997E-7,
    2.2399999999999994E-7, 2.2500000000000002E-7, 2.2599999999999999E-7,
    2.2699999999999995E-7, 2.2800000000000003E-7, 2.29E-7, 2.2999999999999997E-7,
    2.3100000000000004E-7, 2.32E-7, 2.3299999999999998E-7, 2.3399999999999995E-7,
    2.3500000000000003E-7, 2.36E-7, 2.3699999999999996E-7, 2.3800000000000004E-7,
    2.39E-7, 2.4E-7, 2.4099999999999995E-7, 2.42E-7, 2.43E-7,
    2.4399999999999996E-7, 2.4500000000000004E-7, 2.46E-7, 2.47E-7,
    2.4799999999999994E-7, 2.49E-7, 2.5E-7, 2.5099999999999996E-7,
    2.5200000000000003E-7, 2.53E-7, 2.5399999999999997E-7, 2.5500000000000005E-7,
    2.56E-7, 2.57E-7, 2.5799999999999995E-7, 2.5900000000000003E-7, 2.6E-7,
    2.6099999999999997E-7, 2.6200000000000004E-7, 2.63E-7, 2.64E-7,
    2.6499999999999995E-7, 2.66E-7, 2.67E-7, 2.6799999999999996E-7,
    2.6900000000000004E-7, 2.7E-7, 2.71E-7, 2.7199999999999995E-7, 2.73E-7,
    2.74E-7, 2.7499999999999996E-7, 2.7600000000000004E-7, 2.77E-7, 2.78E-7,
    2.7899999999999994E-7, 2.8E-7, 2.81E-7, 2.8199999999999996E-7,
    2.8300000000000003E-7, 2.84E-7, 2.8499999999999997E-7, 2.8600000000000005E-7,
    2.87E-7, 2.88E-7, 2.8899999999999995E-7, 2.9000000000000003E-7, 2.91E-7,
    2.9199999999999997E-7, 2.9300000000000004E-7, 2.94E-7, 2.95E-7,
    2.9599999999999995E-7, 2.97E-7, 2.98E-7, 2.9899999999999996E-7,
    3.0000000000000004E-7 };

  int b_csiFromEachPacket_size[1];
  creal_T c_csiFromEachPacket_data[117];
  char obj_Value[12];
  short start_idx;
  char obj1_Value_data[292];
  int obj1_Value_size[2];
  char name_Value_data[292];
  int name_Value_size[2];
  static const char cv2[5] = { '_', 'a', 'n', 't', '_' };

  short b_tmp_data[58];
  char t0_Value_data[292];
  int t0_Value_size[2];
  double d_data[406];
  int iidx_data[406];
  char b_obj_Value[14];
  double temp_re;
  double temp_im;
  static creal_T dcv2[108781];
  static double SpotfiSpectrum[108781];
  boolean_T isPeak[108781];
  emxInit_char_T(&s, 2);

  /*  ЗДЕСЬ НУЖНО ЗАМЕНИТЬ 181 на 1801 и 61 на 601 !!!!! */
  cdiff = rt_roundd_snf(seed);
  if (cdiff < 2.147483648E+9) {
    if (cdiff >= -2.147483648E+9) {
      i0 = (int)cdiff;
    } else {
      i0 = MIN_int32_T;
    }
  } else if (cdiff >= 2.147483648E+9) {
    i0 = MAX_int32_T;
  } else {
    i0 = 0;
  }

  b_sprintf(i0, s);
  for (i0 = 0; i0 < 5; i0++) {
    seed_str[i0] = '0';
  }

  if (6 - s->size[1] > 5) {
    i0 = 0;
  } else {
    i0 = 5 - s->size[1];
  }

  loop_ub = s->size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    seed_str[i0 + i1] = s->data[i1];
  }

  emxFree_char_T(&s);
  for (i0 = 0; i0 < 6; i0++) {
    subdir_Value[i0] = cv0[i0];
  }

  for (i0 = 0; i0 < 5; i0++) {
    subdir_Value[i0 + 6] = seed_str[i0];
  }

  mkdir(subdir_Value, 0777);
  for (i0 = 0; i0 < 6; i0++) {
    filename_Value[i0] = cv1[i0];
  }

  for (i0 = 0; i0 < 5; i0++) {
    filename_Value[i0 + 6] = seed_str[i0];
  }

  filename_Value[11] = '.';
  filename_Value[12] = 't';
  filename_Value[13] = 'x';
  filename_Value[14] = 't';
  fileid = b_cfopen(filename_Value, "rb");
  b_fseek(fileid);
  cdiff = rt_roundd_snf(b_ftell(fileid));
  if (cdiff < 2.147483648E+9) {
    if (cdiff >= -2.147483648E+9) {
      i0 = (int)cdiff;
    } else {
      i0 = MIN_int32_T;
    }
  } else if (cdiff >= 2.147483648E+9) {
    i0 = MAX_int32_T;
  } else {
    i0 = 0;
  }

  c_fseek(fileid);
  memset(&buffer[0], 0, sizeof(unsigned char) << 21);
  remaining = i0;
  b_index = 1;
  emxInit_real_T(&dataRead, 1);
  emxInit_int32_T(&r0, 2);
  exitg1 = false;
  while ((!exitg1) && (remaining > 0)) {
    if (b_index > MAX_int32_T - remaining) {
      nm1d2 = MAX_int32_T;
    } else {
      nm1d2 = remaining + b_index;
    }

    if (nm1d2 > 2097152) {
      printf("Attempt to read file which is bigger than internal buffer.\n");
      fflush(stdout);
      printf("Current buffer size is %d bytes and file size is %d bytes.\n",
             2097152, i0);
      fflush(stdout);
      exitg1 = true;
    } else {
      b_fread(fileid, remaining, dataRead, &apnd);
      cdiff = rt_roundd_snf((double)b_index + apnd);
      if (cdiff < 2.147483648E+9) {
        if (cdiff >= -2.147483648E+9) {
          nm1d2 = (int)cdiff;
        } else {
          nm1d2 = MIN_int32_T;
        }
      } else if (cdiff >= 2.147483648E+9) {
        nm1d2 = MAX_int32_T;
      } else {
        nm1d2 = 0;
      }

      if (nm1d2 < -2147483647) {
        nm1d2 = MIN_int32_T;
      } else {
        nm1d2--;
      }

      if (b_index > nm1d2) {
        i1 = 0;
        nm1d2 = 0;
      } else {
        i1 = b_index - 1;
      }

      i2 = r0->size[0] * r0->size[1];
      r0->size[0] = 1;
      loop_ub = nm1d2 - i1;
      r0->size[1] = loop_ub;
      emxEnsureCapacity_int32_T(r0, i2);
      for (i2 = 0; i2 < loop_ub; i2++) {
        r0->data[i2] = i1 + i2;
      }

      loop_ub = r0->size[0] * r0->size[1];
      for (i1 = 0; i1 < loop_ub; i1++) {
        cdiff = rt_roundd_snf(dataRead->data[i1]);
        if (cdiff < 256.0) {
          if (cdiff >= 0.0) {
            u0 = (unsigned char)cdiff;
          } else {
            u0 = 0U;
          }
        } else if (cdiff >= 256.0) {
          u0 = MAX_uint8_T;
        } else {
          u0 = 0U;
        }

        buffer[r0->data[i1]] = u0;
      }

      cdiff = rt_roundd_snf(apnd);
      if (cdiff < 2.147483648E+9) {
        if (cdiff >= -2.147483648E+9) {
          nm1d2 = (int)cdiff;
        } else {
          nm1d2 = MIN_int32_T;
        }
      } else if (cdiff >= 2.147483648E+9) {
        nm1d2 = MAX_int32_T;
      } else {
        nm1d2 = 0;
      }

      if (nm1d2 == 0) {
        exitg1 = true;
      } else {
        /*  Did something went wrong when reading? */
        if (nm1d2 < 0) {
          printf("Could not read from file: %d.\n", nm1d2);
          fflush(stdout);
          exitg1 = true;
        } else {
          /*  Update state variables */
          remaining -= nm1d2;
          if ((b_index < 0) && (nm1d2 < MIN_int32_T - b_index)) {
            b_index = MIN_int32_T;
          } else if ((b_index > 0) && (nm1d2 > MAX_int32_T - b_index)) {
            b_index = MAX_int32_T;
          } else {
            b_index += nm1d2;
          }
        }
      }
    }
  }

  emxFree_int32_T(&r0);
  emxFree_real_T(&dataRead);
  emxInit_uint8_T(&b_buffer, 2);

  /*  Close file */
  b_fclose(fileid);
  i0 = b_buffer->size[0] * b_buffer->size[1];
  b_buffer->size[0] = 1;
  b_buffer->size[1] = b_index;
  emxEnsureCapacity_uint8_T(b_buffer, i0);
  for (i0 = 0; i0 < b_index; i0++) {
    b_buffer->data[i0] = buffer[i0];
  }

  emxInit_char_T(&str, 2);
  b_char(b_buffer, str);
  emxFree_uint8_T(&b_buffer);
  i0 = str->size[0] * str->size[1];
  if (1 > b_index - 1) {
    str->size[1] = 0;
  } else {
    str->size[1] = b_index - 1;
  }

  emxEnsureCapacity_char_T(str, i0);
  k = 1;
  emxInit_char_T(&b_str, 2);
  for (i = 0; i < 28800; i++) {
    for (j = k - 1; str->data[j] != ' '; j++) {
    }

    if (k > j) {
      i0 = 0;
      i1 = 0;
    } else {
      i0 = k - 1;
      i1 = j;
    }

    i2 = b_str->size[0] * b_str->size[1];
    b_str->size[0] = 1;
    loop_ub = i1 - i0;
    b_str->size[1] = loop_ub;
    emxEnsureCapacity_char_T(b_str, i2);
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_str->data[i1] = str->data[i0 + i1];
    }

    y[i] = str2double(b_str);
    k = j + 2;
  }

  emxFree_char_T(&b_str);
  emxFree_char_T(&str);

  /*  reading completed */
  /*  packetNum = [10]; */
  /*  packetPerSpectrum = [1]; */
  /*  antennasNum = [4]; */
  /*  bandwidth = [20]; */
  /*  subcarrierDecimationUsed = [1]; */
  /*  backwardSmoothing = [0]; */
  /*  useSmothing = [0]; */
  emxInit_creal_T(&matrixCSI, 3);
  emxInit_creal_T(&smoothedMatrixCSI, 3);
  emxInit_creal_T(&D, 3);
  emxInit_creal_T(&De, 2);
  emxInit_creal_T(&tmp, 2);
  emxInit_creal_T(&steeringVector, 2);
  emxInit_real_T(&nsDelayAngleSpotfiEstimated, 2);
  emxInit_creal_T(&mat, 2);
  emxInit_creal_T(&Rxx, 2);
  emxInit_creal_T(&Qn, 2);
  emxInit_boolean_T(&isStrongEnough, 1);
  emxInit_real_T(&newEstimation, 2);
  emxInit_creal_T(&Utmp, 2);
  emxInit_creal_T(&r1, 2);
  emxInit_boolean_T(&r2, 2);
  emxInit_boolean_T(&r3, 2);
  emxInit_int32_T(&r4, 1);
  emxInit_int32_T(&r5, 2);
  emxInit_creal_T(&b, 2);
  emxInit_creal_T(&b_y, 2);
  emxInit_int32_T(&ii, 1);
  emxInit_uint8_T(&vk, 1);
  emxInit_real_T(&varargin_1, 1);
  emxInit_creal_T(&r6, 2);
  emxInit_creal_T(&r7, 2);
  emxInit_real_T(&r8, 2);
  emxInit_creal_T(&b_steeringVector, 2);
  emxInit_real_T(&b_newEstimation, 2);
  emxInit_real_T(&b_nsDelayAngleSpotfiEstimated, 2);
  for (ant = 0; ant < 2; ant++) {
    b_ant = 4 + (ant << 2);
    switch (b_ant) {
     case 8:
      subarrayNum = 2;
      break;

     case 4:
      subarrayNum = 1;
      break;
    }

    numberOfAntennaInSubset = b_ant - subarrayNum;
    a = ((double)numberOfAntennaInSubset - 1.0) / 2.0;
    b_b = -((double)numberOfAntennaInSubset - 1.0) / 2.0;
    for (perSpec = 0; perSpec < 2; perSpec++) {
      numberOfSpectrums = (int)floor(10.0 / (1.0 + (double)perSpec));
      loop_ub_tmp = numberOfSpectrums * (1 + perSpec);
      for (dec = 0; dec < 2; dec++) {
        if (iv0[dec] != 0) {
          nm1d2 = 4;
        } else {
          nm1d2 = 1;
        }

        remaining = (int)floor(116.0 / (double)nm1d2) + 1;
        loop_ub = (int)floor(116.0 / (double)nm1d2);
        for (i0 = 0; i0 <= loop_ub; i0++) {
          subCarrInd_data[i0] = (short)(1 + nm1d2 * i0);
        }

        k = remaining + 1;
        numberOfSubcarrierSubsets = (int)floor((double)remaining / 2.0);

        /*  number fo subset of subcarriers chosen for smoothing music */
        i0 = matrixCSI->size[0] * matrixCSI->size[1] * matrixCSI->size[2];
        matrixCSI->size[0] = remaining;
        matrixCSI->size[1] = b_ant;
        matrixCSI->size[2] = loop_ub_tmp;
        emxEnsureCapacity_creal_T(matrixCSI, i0);
        for (i0 = 0; i0 < loop_ub_tmp; i0++) {
          for (i1 = 0; i1 < b_ant; i1++) {
            for (i2 = 0; i2 < remaining; i2++) {
              matrixCSI->data[(i2 + matrixCSI->size[0] * i1) + matrixCSI->size[0]
                * matrixCSI->size[1] * i0] = y[((subCarrInd_data[i2] + 120 * i1)
                + 960 * i0) - 1];
            }
          }
        }

        i0 = smoothedMatrixCSI->size[0] * smoothedMatrixCSI->size[1] *
          smoothedMatrixCSI->size[2];
        smoothedMatrixCSI->size[0] = remaining;
        smoothedMatrixCSI->size[1] = b_ant;
        smoothedMatrixCSI->size[2] = loop_ub_tmp;
        emxEnsureCapacity_creal_T(smoothedMatrixCSI, i0);
        loop_ub = remaining * b_ant * loop_ub_tmp;
        for (i0 = 0; i0 < loop_ub; i0++) {
          smoothedMatrixCSI->data[i0] = matrixCSI->data[i0];
        }

        columnsNum_tmp_tmp = b_ant - numberOfAntennaInSubset;
        columnsNum_tmp = columnsNum_tmp_tmp + 1;
        columnsNum = columnsNum_tmp * ((remaining - numberOfSubcarrierSubsets) +
          1);
        i0 = matrixCSI->size[0] * matrixCSI->size[1] * matrixCSI->size[2];
        matrixCSI->size[0] = numberOfAntennaInSubset * numberOfSubcarrierSubsets;
        matrixCSI->size[1] = columnsNum * (1 + perSpec);
        matrixCSI->size[2] = numberOfSpectrums;
        emxEnsureCapacity_creal_T(matrixCSI, i0);
        loop_ub = numberOfAntennaInSubset * numberOfSubcarrierSubsets *
          (columnsNum * (1 + perSpec)) * numberOfSpectrums;
        for (i0 = 0; i0 < loop_ub; i0++) {
          matrixCSI->data[i0].re = 0.0;
          matrixCSI->data[i0].im = 0.0;
        }

        i0 = 1 + perSpec;
        loop_ub = numberOfSubcarrierSubsets * ((remaining -
          numberOfSubcarrierSubsets) + 1) * b_ant;
        if (numberOfSubcarrierSubsets > remaining) {
          i1 = 0;
          i2 = -1;
        } else {
          i1 = numberOfSubcarrierSubsets - 1;
          i2 = remaining - 1;
        }

        b_loop_ub_tmp = i2 - i1;
        b_loop_ub = numberOfAntennaInSubset * numberOfSubcarrierSubsets *
          columnsNum;
        coffset = numberOfSubcarrierSubsets * (columnsNum_tmp * ((remaining -
          numberOfSubcarrierSubsets) + 1));
        boffset = numberOfSubcarrierSubsets - 1;
        for (i2 = 0; i2 <= boffset; i2++) {
          y_data[i2] = (signed char)(1 + i2);
        }

        for (t = 0; t < numberOfSpectrums; t++) {
          for (aoffset = 0; aoffset < i0; aoffset++) {
            boffset = smoothedMatrixCSI->size[0];
            i = smoothedMatrixCSI->size[1];
            remaining = t * (1 + perSpec) + aoffset;
            for (i2 = 0; i2 < i; i2++) {
              for (i3 = 0; i3 < boffset; i3++) {
                csiFromEachPacket_data[i3 + boffset * i2] =
                  smoothedMatrixCSI->data[(i3 + smoothedMatrixCSI->size[0] * i2)
                  + smoothedMatrixCSI->size[0] * smoothedMatrixCSI->size[1] *
                  remaining];
              }
            }

            i2 = D->size[0] * D->size[1] * D->size[2];
            D->size[0] = numberOfSubcarrierSubsets;
            D->size[1] = k - numberOfSubcarrierSubsets;
            D->size[2] = b_ant;
            emxEnsureCapacity_creal_T(D, i2);
            for (i2 = 0; i2 < loop_ub; i2++) {
              D->data[i2].re = 0.0;
              D->data[i2].im = 0.0;
            }

            for (nm1d2 = 0; nm1d2 < b_ant; nm1d2++) {
              /*  mth antenna */
              csiFromEachPacket_size[0] = numberOfSubcarrierSubsets;
              for (i2 = 0; i2 < numberOfSubcarrierSubsets; i2++) {
                b_csiFromEachPacket_data[i2] = csiFromEachPacket_data[i2 +
                  boffset * nm1d2];
              }

              b_csiFromEachPacket_size[0] = b_loop_ub_tmp + 1;
              for (i2 = 0; i2 <= b_loop_ub_tmp; i2++) {
                c_csiFromEachPacket_data[i2] = csiFromEachPacket_data[(i1 + i2)
                  + boffset * nm1d2];
              }

              hankel(b_csiFromEachPacket_data, csiFromEachPacket_size,
                     c_csiFromEachPacket_data, b_csiFromEachPacket_size, r7);
              i = r7->size[1];
              for (i2 = 0; i2 < i; i2++) {
                remaining = r7->size[0];
                for (i3 = 0; i3 < remaining; i3++) {
                  D->data[(i3 + D->size[0] * i2) + D->size[0] * D->size[1] *
                    nm1d2] = r7->data[i3 + r7->size[0] * i2];
                }
              }
            }

            i2 = De->size[0] * De->size[1];
            De->size[0] = numberOfAntennaInSubset * numberOfSubcarrierSubsets;
            De->size[1] = columnsNum;
            emxEnsureCapacity_creal_T(De, i2);
            for (i2 = 0; i2 < b_loop_ub; i2++) {
              De->data[i2].re = 0.0;
              De->data[i2].im = 0.0;
            }

            for (remaining = 0; remaining < numberOfAntennaInSubset; remaining++)
            {
              i2 = tmp->size[0] * tmp->size[1];
              tmp->size[0] = numberOfSubcarrierSubsets;
              tmp->size[1] = columnsNum_tmp * (k - numberOfSubcarrierSubsets);
              emxEnsureCapacity_creal_T(tmp, i2);
              for (i2 = 0; i2 < coffset; i2++) {
                tmp->data[i2].re = 0.0;
                tmp->data[i2].im = 0.0;
              }

              for (j = 0; j <= columnsNum_tmp_tmp; j++) {
                i2 = j * (k - numberOfSubcarrierSubsets) + 1;
                if (i2 > (1 + j) * (k - numberOfSubcarrierSubsets)) {
                  i2 = 0;
                } else {
                  i2--;
                }

                boffset = D->size[0];
                i = D->size[1];
                b_index = remaining + j;
                i3 = r1->size[0] * r1->size[1];
                r1->size[0] = boffset;
                r1->size[1] = i;
                emxEnsureCapacity_creal_T(r1, i3);
                for (i3 = 0; i3 < i; i3++) {
                  for (nm1d2 = 0; nm1d2 < boffset; nm1d2++) {
                    r1->data[nm1d2 + r1->size[0] * i3] = D->data[(nm1d2 +
                      D->size[0] * i3) + D->size[0] * D->size[1] * b_index];
                  }
                }

                boffset = r1->size[1];
                for (i3 = 0; i3 < boffset; i3++) {
                  i = r1->size[0];
                  for (nm1d2 = 0; nm1d2 < i; nm1d2++) {
                    tmp->data[nm1d2 + tmp->size[0] * (i2 + i3)] = r1->data[nm1d2
                      + r1->size[0] * i3];
                  }
                }
              }

              start_idx = (short)(remaining * numberOfSubcarrierSubsets);
              for (i2 = 0; i2 < numberOfSubcarrierSubsets; i2++) {
                b_tmp_data[i2] = (short)((y_data[i2] + start_idx) - 1);
              }

              boffset = tmp->size[1];
              for (i2 = 0; i2 < boffset; i2++) {
                i = tmp->size[0];
                for (i3 = 0; i3 < i; i3++) {
                  De->data[b_tmp_data[i3] + De->size[0] * i2] = tmp->data[i3 +
                    tmp->size[0] * i2];
                }
              }
            }

            i2 = aoffset * columnsNum + 1;
            if (i2 > (1 + aoffset) * columnsNum) {
              i2 = 0;
            } else {
              i2--;
            }

            boffset = De->size[1];
            for (i3 = 0; i3 < boffset; i3++) {
              i = De->size[0];
              for (nm1d2 = 0; nm1d2 < i; nm1d2++) {
                matrixCSI->data[(nm1d2 + matrixCSI->size[0] * (i2 + i3)) +
                  matrixCSI->size[0] * matrixCSI->size[1] * t] = De->data[nm1d2
                  + De->size[0] * i3];
              }
            }
          }
        }

        /*  smoothing completed */
        if (floor(a) == a) {
          remaining = (int)floor(-(b_b - a));
          b_index = remaining + 1;
          for (i0 = 0; i0 <= remaining; i0++) {
            b_y_data[i0] = a - (double)i0;
          }
        } else {
          b_index = (int)floor((b_b - a) / -1.0 + 0.5);
          apnd = a + -(double)b_index;
          cdiff = b_b - apnd;
          if (fabs(cdiff) < 4.4408920985006262E-16 * fmax(a, fabs(b_b))) {
            b_index++;
            apnd = b_b;
          } else if (cdiff > 0.0) {
            apnd = a + -((double)b_index - 1.0);
          } else {
            b_index++;
          }

          b_y_data[0] = a;
          if (b_index > 1) {
            b_y_data[b_index - 1] = apnd;
            nm1d2 = (b_index - 1) / 2;
            for (k = 0; k <= nm1d2 - 2; k++) {
              b_y_data[1 + k] = a + -(1.0 + (double)k);
              b_y_data[(b_index - k) - 2] = apnd - (-(1.0 + (double)k));
            }

            if (nm1d2 << 1 == b_index - 1) {
              b_y_data[nm1d2] = (a + apnd) / 2.0;
            } else {
              b_y_data[nm1d2] = a + -(double)nm1d2;
              b_y_data[nm1d2 + 1] = apnd - (-(double)nm1d2);
            }
          }
        }

        for (i0 = 0; i0 < 181; i0++) {
          dcv0[i0].re = dv0[i0];
          dcv0[i0].im = 0.0;
        }

        tmp_size[0] = b_index;
        tmp_size[1] = 181;
        for (i0 = 0; i0 < b_index; i0++) {
          for (i1 = 0; i1 < 181; i1++) {
            apnd = b_y_data[i0] * -0.0;
            cdiff = b_y_data[i0] * -6.2831853071795862;
            i2 = i0 + b_index * i1;
            tmp_data[i2].re = apnd * dcv0[i1].re - cdiff * dcv0[i1].im;
            tmp_data[i2].im = apnd * dcv0[i1].im + cdiff * dcv0[i1].re;
          }
        }

        c_exp(tmp_data, tmp_size);
        for (i0 = 0; i0 < numberOfSubcarrierSubsets; i0++) {
          b_csiFromEachPacket_data[i0].re = -0.0;
          b_csiFromEachPacket_data[i0].im = 312500.0 * ((double)
            subCarrInd_data[i0] * -6.2831853071795862);
        }

        for (i0 = 0; i0 < 601; i0++) {
          dcv1[i0].re = dv1[i0];
          dcv1[i0].im = 0.0;
        }

        i0 = r6->size[0] * r6->size[1];
        r6->size[0] = numberOfSubcarrierSubsets;
        r6->size[1] = 601;
        emxEnsureCapacity_creal_T(r6, i0);
        for (i0 = 0; i0 < numberOfSubcarrierSubsets; i0++) {
          for (i1 = 0; i1 < 601; i1++) {
            r6->data[i0 + r6->size[0] * i1].re = -0.0 * dcv1[i1].re -
              b_csiFromEachPacket_data[i0].im * dcv1[i1].im;
            r6->data[i0 + r6->size[0] * i1].im = -0.0 * dcv1[i1].im +
              b_csiFromEachPacket_data[i0].im * dcv1[i1].re;
          }
        }

        b_exp(r6);
        kron(tmp_data, tmp_size, r6, steeringVector);
        nsDelayAngleSpotfiEstimated->size[0] = 2;
        nsDelayAngleSpotfiEstimated->size[1] = 0;
        for (t = 0; t < numberOfSpectrums; t++) {
          loop_ub = matrixCSI->size[0];
          b_loop_ub = matrixCSI->size[1];
          i0 = mat->size[0] * mat->size[1];
          mat->size[0] = loop_ub;
          mat->size[1] = b_loop_ub;
          emxEnsureCapacity_creal_T(mat, i0);
          for (i0 = 0; i0 < b_loop_ub; i0++) {
            for (i1 = 0; i1 < loop_ub; i1++) {
              mat->data[i1 + mat->size[0] * i0] = matrixCSI->data[(i1 +
                matrixCSI->size[0] * i0) + matrixCSI->size[0] * matrixCSI->size
                [1] * t];
            }
          }

          i0 = b->size[0] * b->size[1];
          b->size[0] = mat->size[1];
          b->size[1] = mat->size[0];
          emxEnsureCapacity_creal_T(b, i0);
          loop_ub = mat->size[0];
          for (i0 = 0; i0 < loop_ub; i0++) {
            b_loop_ub = mat->size[1];
            for (i1 = 0; i1 < b_loop_ub; i1++) {
              b->data[i1 + b->size[0] * i0].re = mat->data[i0 + mat->size[0] *
                i1].re;
              b->data[i1 + b->size[0] * i0].im = -mat->data[i0 + mat->size[0] *
                i1].im;
            }
          }

          i0 = matrixCSI->size[1];
          if ((i0 == 1) || (b->size[0] == 1)) {
            i0 = Rxx->size[0] * Rxx->size[1];
            Rxx->size[0] = mat->size[0];
            Rxx->size[1] = b->size[1];
            emxEnsureCapacity_creal_T(Rxx, i0);
            loop_ub = mat->size[0];
            for (i0 = 0; i0 < loop_ub; i0++) {
              b_loop_ub = b->size[1];
              for (i1 = 0; i1 < b_loop_ub; i1++) {
                Rxx->data[i0 + Rxx->size[0] * i1].re = 0.0;
                Rxx->data[i0 + Rxx->size[0] * i1].im = 0.0;
                coffset = mat->size[1];
                for (i2 = 0; i2 < coffset; i2++) {
                  apnd = mat->data[i0 + mat->size[0] * i2].re * b->data[i2 +
                    b->size[0] * i1].re - mat->data[i0 + mat->size[0] * i2].im *
                    b->data[i2 + b->size[0] * i1].im;
                  cdiff = mat->data[i0 + mat->size[0] * i2].re * b->data[i2 +
                    b->size[0] * i1].im + mat->data[i0 + mat->size[0] * i2].im *
                    b->data[i2 + b->size[0] * i1].re;
                  Rxx->data[i0 + Rxx->size[0] * i1].re += apnd;
                  Rxx->data[i0 + Rxx->size[0] * i1].im += cdiff;
                }
              }
            }
          } else {
            i0 = matrixCSI->size[0];
            i1 = matrixCSI->size[1];
            nm1d2 = b->size[1];
            i2 = matrixCSI->size[0];
            i3 = Rxx->size[0] * Rxx->size[1];
            Rxx->size[0] = i2;
            Rxx->size[1] = b->size[1];
            emxEnsureCapacity_creal_T(Rxx, i3);
            for (j = 0; j < nm1d2; j++) {
              coffset = j * i0;
              boffset = j * i1;
              for (i = 0; i < i0; i++) {
                i2 = coffset + i;
                Rxx->data[i2].re = 0.0;
                Rxx->data[i2].im = 0.0;
              }

              for (k = 0; k < i1; k++) {
                aoffset = k * i0;
                b_index = boffset + k;
                apnd = b->data[b_index].re;
                cdiff = b->data[b_index].im;
                for (i = 0; i < i0; i++) {
                  b_index = aoffset + i;
                  temp_re = apnd * mat->data[b_index].re - cdiff * mat->
                    data[b_index].im;
                  temp_im = apnd * mat->data[b_index].im + cdiff * mat->
                    data[b_index].re;
                  i2 = coffset + i;
                  Rxx->data[i2].re += temp_re;
                  Rxx->data[i2].im += temp_im;
                }
              }
            }
          }

          eig(Rxx, Utmp);
          b_abs(Rxx, r8);
          diag(r8, d_data, csiFromEachPacket_size);
          sort(d_data, csiFromEachPacket_size, iidx_data,
               b_csiFromEachPacket_size);
          loop_ub = b_csiFromEachPacket_size[0];
          for (i0 = 0; i0 < loop_ub; i0++) {
            d_data[i0] = iidx_data[i0];
          }

          /*  eig completed */
          /*                                  Qn = U(:,1:numberOfSourses); */
          if (1 > b_csiFromEachPacket_size[0] - 2) {
            loop_ub = 0;
          } else {
            loop_ub = b_csiFromEachPacket_size[0] - 2;
          }

          b_loop_ub = Utmp->size[0];
          coffset = Utmp->size[0];
          i0 = Rxx->size[0] * Rxx->size[1];
          Rxx->size[0] = coffset;
          Rxx->size[1] = b_csiFromEachPacket_size[0];
          emxEnsureCapacity_creal_T(Rxx, i0);
          boffset = b_csiFromEachPacket_size[0];
          for (i0 = 0; i0 < boffset; i0++) {
            for (i1 = 0; i1 < coffset; i1++) {
              Rxx->data[i1 + Rxx->size[0] * i0] = Utmp->data[i1 + Utmp->size[0] *
                ((int)d_data[i0] - 1)];
            }
          }

          i0 = Qn->size[0] * Qn->size[1];
          Qn->size[0] = b_loop_ub;
          Qn->size[1] = loop_ub;
          emxEnsureCapacity_creal_T(Qn, i0);
          for (i0 = 0; i0 < loop_ub; i0++) {
            for (i1 = 0; i1 < b_loop_ub; i1++) {
              Qn->data[i1 + Qn->size[0] * i0] = Rxx->data[i1 + Rxx->size[0] * i0];
            }
          }

          i0 = b->size[0] * b->size[1];
          b->size[0] = Qn->size[1];
          b->size[1] = Qn->size[0];
          emxEnsureCapacity_creal_T(b, i0);
          b_loop_ub = Qn->size[0];
          for (i0 = 0; i0 < b_loop_ub; i0++) {
            coffset = Qn->size[1];
            for (i1 = 0; i1 < coffset; i1++) {
              b->data[i1 + b->size[0] * i0].re = Qn->data[i0 + Qn->size[0] * i1]
                .re;
              b->data[i1 + b->size[0] * i0].im = -Qn->data[i0 + Qn->size[0] * i1]
                .im;
            }
          }

          if ((loop_ub == 1) || (b->size[0] == 1)) {
            i0 = Rxx->size[0] * Rxx->size[1];
            Rxx->size[0] = Qn->size[0];
            Rxx->size[1] = b->size[1];
            emxEnsureCapacity_creal_T(Rxx, i0);
            loop_ub = Qn->size[0];
            for (i0 = 0; i0 < loop_ub; i0++) {
              b_loop_ub = b->size[1];
              for (i1 = 0; i1 < b_loop_ub; i1++) {
                Rxx->data[i0 + Rxx->size[0] * i1].re = 0.0;
                Rxx->data[i0 + Rxx->size[0] * i1].im = 0.0;
                coffset = Qn->size[1];
                for (i2 = 0; i2 < coffset; i2++) {
                  apnd = Qn->data[i0 + Qn->size[0] * i2].re * b->data[i2 +
                    b->size[0] * i1].re - Qn->data[i0 + Qn->size[0] * i2].im *
                    b->data[i2 + b->size[0] * i1].im;
                  cdiff = Qn->data[i0 + Qn->size[0] * i2].re * b->data[i2 +
                    b->size[0] * i1].im + Qn->data[i0 + Qn->size[0] * i2].im *
                    b->data[i2 + b->size[0] * i1].re;
                  Rxx->data[i0 + Rxx->size[0] * i1].re += apnd;
                  Rxx->data[i0 + Rxx->size[0] * i1].im += cdiff;
                }
              }
            }
          } else {
            i0 = Utmp->size[0];
            nm1d2 = b->size[1];
            i1 = Utmp->size[0];
            i2 = Rxx->size[0] * Rxx->size[1];
            Rxx->size[0] = i1;
            Rxx->size[1] = b->size[1];
            emxEnsureCapacity_creal_T(Rxx, i2);
            for (j = 0; j < nm1d2; j++) {
              coffset = j * i0;
              boffset = j * loop_ub;
              for (i = 0; i < i0; i++) {
                i1 = coffset + i;
                Rxx->data[i1].re = 0.0;
                Rxx->data[i1].im = 0.0;
              }

              for (k = 0; k < loop_ub; k++) {
                aoffset = k * i0;
                apnd = b->data[boffset + k].re;
                cdiff = b->data[boffset + k].im;
                for (i = 0; i < i0; i++) {
                  b_index = aoffset + i;
                  temp_re = apnd * Qn->data[b_index].re - cdiff * Qn->
                    data[b_index].im;
                  temp_im = apnd * Qn->data[b_index].im + cdiff * Qn->
                    data[b_index].re;
                  i1 = coffset + i;
                  Rxx->data[i1].re += temp_re;
                  Rxx->data[i1].im += temp_im;
                }
              }
            }
          }

          /*  Pn completed */
          if ((Rxx->size[1] == 1) || (steeringVector->size[0] == 1)) {
            i0 = b_y->size[0] * b_y->size[1];
            b_y->size[0] = Rxx->size[0];
            b_y->size[1] = 108781;
            emxEnsureCapacity_creal_T(b_y, i0);
            loop_ub = Rxx->size[0];
            for (i0 = 0; i0 < loop_ub; i0++) {
              for (i1 = 0; i1 < 108781; i1++) {
                b_y->data[i0 + b_y->size[0] * i1].re = 0.0;
                b_y->data[i0 + b_y->size[0] * i1].im = 0.0;
                b_loop_ub = Rxx->size[1];
                for (i2 = 0; i2 < b_loop_ub; i2++) {
                  apnd = Rxx->data[i0 + Rxx->size[0] * i2].re *
                    steeringVector->data[i2 + steeringVector->size[0] * i1].re -
                    Rxx->data[i0 + Rxx->size[0] * i2].im * steeringVector->
                    data[i2 + steeringVector->size[0] * i1].im;
                  cdiff = Rxx->data[i0 + Rxx->size[0] * i2].re *
                    steeringVector->data[i2 + steeringVector->size[0] * i1].im +
                    Rxx->data[i0 + Rxx->size[0] * i2].im * steeringVector->
                    data[i2 + steeringVector->size[0] * i1].re;
                  b_y->data[i0 + b_y->size[0] * i1].re += apnd;
                  b_y->data[i0 + b_y->size[0] * i1].im += cdiff;
                }
              }
            }
          } else {
            nm1d2 = Rxx->size[0];
            remaining = Rxx->size[1];
            i0 = b_y->size[0] * b_y->size[1];
            b_y->size[0] = Rxx->size[0];
            b_y->size[1] = 108781;
            emxEnsureCapacity_creal_T(b_y, i0);
            for (j = 0; j < 108781; j++) {
              coffset = j * nm1d2;
              boffset = j * remaining;
              for (i = 0; i < nm1d2; i++) {
                i0 = coffset + i;
                b_y->data[i0].re = 0.0;
                b_y->data[i0].im = 0.0;
              }

              for (k = 0; k < remaining; k++) {
                aoffset = k * nm1d2;
                b_index = boffset + k;
                apnd = steeringVector->data[b_index].re;
                cdiff = steeringVector->data[b_index].im;
                for (i = 0; i < nm1d2; i++) {
                  b_index = aoffset + i;
                  temp_re = apnd * Rxx->data[b_index].re - cdiff * Rxx->
                    data[b_index].im;
                  temp_im = apnd * Rxx->data[b_index].im + cdiff * Rxx->
                    data[b_index].re;
                  i0 = coffset + i;
                  b_y->data[i0].re += temp_re;
                  b_y->data[i0].im += temp_im;
                }
              }
            }
          }

          i0 = b_steeringVector->size[0] * b_steeringVector->size[1];
          b_steeringVector->size[0] = 108781;
          b_steeringVector->size[1] = steeringVector->size[0];
          emxEnsureCapacity_creal_T(b_steeringVector, i0);
          loop_ub = steeringVector->size[0];
          for (i0 = 0; i0 < loop_ub; i0++) {
            for (i1 = 0; i1 < 108781; i1++) {
              apnd = steeringVector->data[i0 + steeringVector->size[0] * i1].re;
              cdiff = -steeringVector->data[i0 + steeringVector->size[0] * i1].
                im;
              temp_re = b_y->data[i0 + b_y->size[0] * i1].re;
              temp_im = b_y->data[i0 + b_y->size[0] * i1].im;
              i2 = i1 + 108781 * i0;
              b_steeringVector->data[i2].re = apnd * temp_re - cdiff * temp_im;
              b_steeringVector->data[i2].im = apnd * temp_im + cdiff * temp_re;
            }
          }

          sum(b_steeringVector, dcv2);
          c_abs(dcv2, SpotfiSpectrum);
          for (i0 = 0; i0 < 108781; i0++) {
            SpotfiSpectrum[i0] = 1.0 / SpotfiSpectrum[i0];
          }

          if (!rtIsNaN(SpotfiSpectrum[0])) {
            remaining = 1;
          } else {
            remaining = 0;
            k = 2;
            exitg1 = false;
            while ((!exitg1) && (k < 108782)) {
              if (!rtIsNaN(SpotfiSpectrum[k - 1])) {
                remaining = k;
                exitg1 = true;
              } else {
                k++;
              }
            }
          }

          if (remaining == 0) {
            apnd = SpotfiSpectrum[0];
          } else {
            apnd = SpotfiSpectrum[remaining - 1];
            i0 = remaining + 1;
            for (k = i0; k < 108782; k++) {
              cdiff = SpotfiSpectrum[k - 1];
              if (apnd > cdiff) {
                apnd = cdiff;
              }
            }
          }

          for (i0 = 0; i0 < 108781; i0++) {
            SpotfiSpectrum[i0] -= apnd;
          }

          /*  spotfi completed */
          imregionalmax(SpotfiSpectrum, isPeak);
          remaining = 0;
          i0 = ii->size[0];
          ii->size[0] = 108781;
          emxEnsureCapacity_int32_T(ii, i0);
          nm1d2 = 0;
          exitg1 = false;
          while ((!exitg1) && (nm1d2 < 108781)) {
            if (isPeak[nm1d2]) {
              remaining++;
              ii->data[remaining - 1] = nm1d2 + 1;
              if (remaining >= 108781) {
                exitg1 = true;
              } else {
                nm1d2++;
              }
            } else {
              nm1d2++;
            }
          }

          if (1 > remaining) {
            ii->size[0] = 0;
          } else {
            i0 = ii->size[0];
            ii->size[0] = remaining;
            emxEnsureCapacity_int32_T(ii, i0);
          }

          i0 = ii->size[0];
          emxEnsureCapacity_int32_T(ii, i0);
          loop_ub = ii->size[0];
          for (i0 = 0; i0 < loop_ub; i0++) {
            ii->data[i0]--;
          }

          i0 = vk->size[0];
          vk->size[0] = ii->size[0];
          emxEnsureCapacity_uint8_T(vk, i0);
          loop_ub = ii->size[0];
          for (i0 = 0; i0 < loop_ub; i0++) {
            vk->data[i0] = (unsigned char)(ii->data[i0] / 601);
          }

          i0 = ii->size[0];
          emxEnsureCapacity_int32_T(ii, i0);
          loop_ub = ii->size[0];
          for (i0 = 0; i0 < loop_ub; i0++) {
            ii->data[i0] -= vk->data[i0] * 601;
          }

          i0 = ii->size[0];
          emxEnsureCapacity_int32_T(ii, i0);
          loop_ub = ii->size[0];
          for (i0 = 0; i0 < loop_ub; i0++) {
            ii->data[i0]++;
          }

          i0 = vk->size[0];
          emxEnsureCapacity_uint8_T(vk, i0);
          loop_ub = vk->size[0];
          for (i0 = 0; i0 < loop_ub; i0++) {
            vk->data[i0]++;
          }

          b_index = 0;
          for (i = 0; i < 108781; i++) {
            if (isPeak[i]) {
              b_index++;
            }
          }

          i0 = r4->size[0];
          r4->size[0] = b_index;
          emxEnsureCapacity_int32_T(r4, i0);
          remaining = 0;
          for (i = 0; i < 108781; i++) {
            if (isPeak[i]) {
              r4->data[remaining] = i + 1;
              remaining++;
            }
          }

          i0 = varargin_1->size[0];
          varargin_1->size[0] = r4->size[0];
          emxEnsureCapacity_real_T(varargin_1, i0);
          loop_ub = r4->size[0];
          for (i0 = 0; i0 < loop_ub; i0++) {
            varargin_1->data[i0] = SpotfiSpectrum[r4->data[i0] - 1];
          }

          nm1d2 = r4->size[0];
          if (varargin_1->size[0] <= 2) {
            if (varargin_1->size[0] == 1) {
              apnd = SpotfiSpectrum[r4->data[0] - 1];
            } else if ((SpotfiSpectrum[r4->data[0] - 1] < SpotfiSpectrum
                        [r4->data[1] - 1]) || (rtIsNaN(SpotfiSpectrum[r4->data[0]
              - 1]) && (!rtIsNaN(SpotfiSpectrum[r4->data[1] - 1])))) {
              apnd = SpotfiSpectrum[r4->data[1] - 1];
            } else {
              apnd = SpotfiSpectrum[r4->data[0] - 1];
            }
          } else {
            if (!rtIsNaN(varargin_1->data[0])) {
              remaining = 1;
            } else {
              remaining = 0;
              k = 2;
              exitg1 = false;
              while ((!exitg1) && (k <= varargin_1->size[0])) {
                if (!rtIsNaN(varargin_1->data[k - 1])) {
                  remaining = k;
                  exitg1 = true;
                } else {
                  k++;
                }
              }
            }

            if (remaining == 0) {
              apnd = SpotfiSpectrum[r4->data[0] - 1];
            } else {
              apnd = SpotfiSpectrum[r4->data[remaining - 1] - 1];
              i0 = remaining + 1;
              for (k = i0; k <= nm1d2; k++) {
                if (apnd < SpotfiSpectrum[r4->data[k - 1] - 1]) {
                  apnd = SpotfiSpectrum[r4->data[k - 1] - 1];
                }
              }
            }
          }

          cdiff = 0.1 * apnd;
          i0 = isStrongEnough->size[0];
          isStrongEnough->size[0] = r4->size[0];
          emxEnsureCapacity_boolean_T(isStrongEnough, i0);
          loop_ub = r4->size[0];
          for (i0 = 0; i0 < loop_ub; i0++) {
            isStrongEnough->data[i0] = (SpotfiSpectrum[r4->data[i0] - 1] > cdiff);
          }

          nm1d2 = isStrongEnough->size[0] - 1;
          b_index = 0;
          for (i = 0; i <= nm1d2; i++) {
            if (isStrongEnough->data[i]) {
              b_index++;
            }
          }

          remaining = 0;
          for (i = 0; i <= nm1d2; i++) {
            if (isStrongEnough->data[i]) {
              ii->data[remaining] = ii->data[i];
              remaining++;
            }
          }

          i0 = ii->size[0];
          ii->size[0] = b_index;
          emxEnsureCapacity_int32_T(ii, i0);
          nm1d2 = isStrongEnough->size[0] - 1;
          b_index = 0;
          for (i = 0; i <= nm1d2; i++) {
            if (isStrongEnough->data[i]) {
              b_index++;
            }
          }

          remaining = 0;
          for (i = 0; i <= nm1d2; i++) {
            if (isStrongEnough->data[i]) {
              vk->data[remaining] = vk->data[i];
              remaining++;
            }
          }

          i0 = vk->size[0];
          vk->size[0] = b_index;
          emxEnsureCapacity_uint8_T(vk, i0);
          i0 = newEstimation->size[0] * newEstimation->size[1];
          newEstimation->size[0] = 2;
          newEstimation->size[1] = ii->size[0];
          emxEnsureCapacity_real_T(newEstimation, i0);
          loop_ub = ii->size[0];
          for (i0 = 0; i0 < loop_ub; i0++) {
            newEstimation->data[i0 << 1] = (-3.0000000000000004E-7 + ((double)
              ii->data[i0] - 1.0) * 1.0E-9) * 1.0E+9;
          }

          loop_ub = vk->size[0];
          for (i0 = 0; i0 < loop_ub; i0++) {
            newEstimation->data[1 + (i0 << 1)] = -90.0 + ((double)vk->data[i0] -
              1.0);
          }

          loop_ub = newEstimation->size[1];
          i0 = r2->size[0] * r2->size[1];
          r2->size[0] = 1;
          r2->size[1] = loop_ub;
          emxEnsureCapacity_boolean_T(r2, i0);
          for (i0 = 0; i0 < loop_ub; i0++) {
            r2->data[i0] = (newEstimation->data[1 + (i0 << 1)] > -89.0);
          }

          loop_ub = newEstimation->size[1];
          i0 = r3->size[0] * r3->size[1];
          r3->size[0] = 1;
          r3->size[1] = loop_ub;
          emxEnsureCapacity_boolean_T(r3, i0);
          for (i0 = 0; i0 < loop_ub; i0++) {
            r3->data[i0] = (newEstimation->data[1 + (i0 << 1)] < 89.0);
          }

          nm1d2 = r2->size[1] - 1;
          b_index = 0;
          for (i = 0; i <= nm1d2; i++) {
            if (r2->data[i] && r3->data[i]) {
              b_index++;
            }
          }

          i0 = r5->size[0] * r5->size[1];
          r5->size[0] = 1;
          r5->size[1] = b_index;
          emxEnsureCapacity_int32_T(r5, i0);
          remaining = 0;
          for (i = 0; i <= nm1d2; i++) {
            if (r2->data[i] && r3->data[i]) {
              r5->data[remaining] = i + 1;
              remaining++;
            }
          }

          i0 = b_newEstimation->size[0] * b_newEstimation->size[1];
          b_newEstimation->size[0] = 2;
          b_newEstimation->size[1] = r5->size[1];
          emxEnsureCapacity_real_T(b_newEstimation, i0);
          loop_ub = r5->size[1];
          for (i0 = 0; i0 < loop_ub; i0++) {
            i1 = i0 << 1;
            b_newEstimation->data[i1] = newEstimation->data[(r5->data[i0] - 1) <<
              1];
            b_newEstimation->data[1 + i1] = newEstimation->data[1 + ((r5->
              data[i0] - 1) << 1)];
          }

          i0 = newEstimation->size[0] * newEstimation->size[1];
          newEstimation->size[0] = 2;
          newEstimation->size[1] = b_newEstimation->size[1];
          emxEnsureCapacity_real_T(newEstimation, i0);
          loop_ub = b_newEstimation->size[0] * b_newEstimation->size[1];
          for (i0 = 0; i0 < loop_ub; i0++) {
            newEstimation->data[i0] = b_newEstimation->data[i0];
          }

          i0 = b_nsDelayAngleSpotfiEstimated->size[0] *
            b_nsDelayAngleSpotfiEstimated->size[1];
          b_nsDelayAngleSpotfiEstimated->size[0] = 2;
          b_nsDelayAngleSpotfiEstimated->size[1] =
            nsDelayAngleSpotfiEstimated->size[1] + newEstimation->size[1];
          emxEnsureCapacity_real_T(b_nsDelayAngleSpotfiEstimated, i0);
          loop_ub = nsDelayAngleSpotfiEstimated->size[1];
          for (i0 = 0; i0 < loop_ub; i0++) {
            i1 = i0 << 1;
            b_nsDelayAngleSpotfiEstimated->data[i1] =
              nsDelayAngleSpotfiEstimated->data[i1];
            i1++;
            b_nsDelayAngleSpotfiEstimated->data[i1] =
              nsDelayAngleSpotfiEstimated->data[i1];
          }

          loop_ub = newEstimation->size[1];
          for (i0 = 0; i0 < loop_ub; i0++) {
            i1 = i0 << 1;
            b_nsDelayAngleSpotfiEstimated->data[(i0 +
              nsDelayAngleSpotfiEstimated->size[1]) << 1] = newEstimation->
              data[i1];
            b_nsDelayAngleSpotfiEstimated->data[1 + ((i0 +
              nsDelayAngleSpotfiEstimated->size[1]) << 1)] = newEstimation->
              data[1 + i1];
          }

          i0 = nsDelayAngleSpotfiEstimated->size[0] *
            nsDelayAngleSpotfiEstimated->size[1];
          nsDelayAngleSpotfiEstimated->size[0] = 2;
          nsDelayAngleSpotfiEstimated->size[1] =
            b_nsDelayAngleSpotfiEstimated->size[1];
          emxEnsureCapacity_real_T(nsDelayAngleSpotfiEstimated, i0);
          loop_ub = b_nsDelayAngleSpotfiEstimated->size[0] *
            b_nsDelayAngleSpotfiEstimated->size[1];
          for (i0 = 0; i0 < loop_ub; i0++) {
            nsDelayAngleSpotfiEstimated->data[i0] =
              b_nsDelayAngleSpotfiEstimated->data[i0];
          }

          /*  peaks completed */
          /*                                  fileID = fopen(directory+"SpotfiEigen" + seed_str + ".txt", 'a'); */
          /*                                  fprintf(fileID, "noise: "); */
          /*                                  for i = 1:numberOfSourses */
          /*                                      fprintf(fileID, "%.3f ", d(i)); */
          /*                                  end */
          /*                                  fprintf(fileID, "signal: "); */
          /*                                  for i = numberOfSourses+1:length(d) */
          /*                                      fprintf(fileID, "%.3f ", d(i)); */
          /*                                  end */
          /*                                  fprintf(fileID, "\n"); */
          /*                                  fclose(fileID); */
        }

        obj_Value[0] = 'r';
        obj_Value[1] = '_';
        for (i0 = 0; i0 < 5; i0++) {
          obj_Value[i0 + 2] = seed_str[i0];
          obj_Value[i0 + 7] = cv2[i0];
        }

        string_string(b_ant, obj1_Value_data, obj1_Value_size);
        string_plus(obj_Value, obj1_Value_data, obj1_Value_size, name_Value_data,
                    name_Value_size);
        b_string_plus(name_Value_data, name_Value_size, obj1_Value_data,
                      obj1_Value_size);
        name_Value_size[0] = 1;
        name_Value_size[1] = obj1_Value_size[1] + 1;
        if (0 <= obj1_Value_size[1] - 1) {
          memcpy(&name_Value_data[0], &obj1_Value_data[0], (unsigned int)
                 (obj1_Value_size[1] * (int)sizeof(char)));
        }

        name_Value_data[obj1_Value_size[1]] = '1';
        c_string_plus(name_Value_data, name_Value_size, obj1_Value_data,
                      obj1_Value_size);
        name_Value_size[0] = 1;
        name_Value_size[1] = obj1_Value_size[1] + 1;
        if (0 <= obj1_Value_size[1] - 1) {
          memcpy(&name_Value_data[0], &obj1_Value_data[0], (unsigned int)
                 (obj1_Value_size[1] * (int)sizeof(char)));
        }

        name_Value_data[obj1_Value_size[1]] = '0';
        d_string_plus(name_Value_data, name_Value_size, obj1_Value_data,
                      obj1_Value_size);
        e_string_plus(obj1_Value_data, obj1_Value_size, name_Value_data,
                      name_Value_size);
        f_string_plus(name_Value_data, name_Value_size, obj1_Value_data,
                      obj1_Value_size);
        string_string(1.0 + (double)perSpec, name_Value_data, name_Value_size);
        g_string_plus(obj1_Value_data, obj1_Value_size, name_Value_data,
                      name_Value_size, t0_Value_data, t0_Value_size);
        h_string_plus(t0_Value_data, t0_Value_size, obj1_Value_data,
                      obj1_Value_size);
        i_string_plus(obj1_Value_data, obj1_Value_size, name_Value_data,
                      name_Value_size);
        j_string_plus(name_Value_data, name_Value_size, obj1_Value_data,
                      obj1_Value_size);
        string_string(dec, name_Value_data, name_Value_size);
        g_string_plus(obj1_Value_data, obj1_Value_size, name_Value_data,
                      name_Value_size, t0_Value_data, t0_Value_size);
        k_string_plus(t0_Value_data, t0_Value_size, name_Value_data,
                      name_Value_size);
        b_obj_Value[0] = '.';
        b_obj_Value[1] = '/';
        for (i0 = 0; i0 < 11; i0++) {
          b_obj_Value[i0 + 2] = subdir_Value[i0];
        }

        b_obj_Value[13] = '/';
        l_string_plus(b_obj_Value, name_Value_data, name_Value_size,
                      obj1_Value_data, obj1_Value_size);
        fileid = c_cfopen(obj1_Value_data, obj1_Value_size, "wb");
        i0 = nsDelayAngleSpotfiEstimated->size[1];
        for (j = 0; j < i0; j++) {
          b_NULL = NULL;
          getfilestar(fileid, &filestar, &autoflush);
          if (!(filestar == b_NULL)) {
            fprintf(filestar, "%.1f ", nsDelayAngleSpotfiEstimated->data[j << 1]);
            if (autoflush) {
              fflush(filestar);
            }
          }

          if (!(filestar == b_NULL)) {
            fprintf(filestar, "%.1f ", nsDelayAngleSpotfiEstimated->data[1 + (j <<
                     1)]);
            if (autoflush) {
              fflush(filestar);
            }
          }
        }

        b_fclose(fileid);
      }
    }
  }

  emxFree_real_T(&b_nsDelayAngleSpotfiEstimated);
  emxFree_real_T(&b_newEstimation);
  emxFree_creal_T(&b_steeringVector);
  emxFree_real_T(&r8);
  emxFree_creal_T(&r7);
  emxFree_creal_T(&r6);
  emxFree_real_T(&varargin_1);
  emxFree_uint8_T(&vk);
  emxFree_int32_T(&ii);
  emxFree_creal_T(&b_y);
  emxFree_creal_T(&b);
  emxFree_int32_T(&r5);
  emxFree_int32_T(&r4);
  emxFree_boolean_T(&r3);
  emxFree_boolean_T(&r2);
  emxFree_creal_T(&r1);
  emxFree_creal_T(&Utmp);
  emxFree_real_T(&newEstimation);
  emxFree_boolean_T(&isStrongEnough);
  emxFree_creal_T(&Qn);
  emxFree_creal_T(&Rxx);
  emxFree_creal_T(&mat);
  emxFree_real_T(&nsDelayAngleSpotfiEstimated);
  emxFree_creal_T(&steeringVector);
  emxFree_creal_T(&tmp);
  emxFree_creal_T(&De);
  emxFree_creal_T(&D);
  emxFree_creal_T(&smoothedMatrixCSI);
  emxFree_creal_T(&matrixCSI);

  /*  Spotfi */
}

/*
 * File trailer for forCoder.c
 *
 * [EOF]
 */
