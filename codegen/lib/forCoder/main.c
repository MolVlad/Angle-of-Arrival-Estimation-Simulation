/*
 * File: main.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 13-Jul-2020 14:02:50
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include Files */
#include "rt_nonfinite.h"
#include "forCoder.h"
#include "main.h"
#include "forCoder_terminate.h"
#include "forCoder_initialize.h"
#include "stdio.h"
#include "stdlib.h"
#include"string.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* Function Declarations */
static double argInit_real_T(void);
static void main_forCoder(int seed);

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_forCoder(int seed)
{
  /* Initialize function 'forCoder' input arguments. */
  /* Call the entry-point 'forCoder'. */
  forCoder(seed);
}

char* concat(char *s1, char *s2) {

        size_t len1 = strlen(s1);
        size_t len2 = strlen(s2);

        char *result = malloc(len1 + len2 + 1);

        if (!result) {
            fprintf(stderr, "malloc() failed: insufficient memory!\n");
            return NULL;
        }

        memcpy(result, s1, len1);
        memcpy(result + len1, s2, len2 + 1);

        return result;
    }


/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, char * const argv[])
{
  char name[] = "music_";
  char *s = concat(name, argv[1]);
  mkdir(s, S_IRUSR | S_IWUSR);
  chdir(s);
  free(s);

  (void)argc;
  (void)argv;

  int seed = atoi(argv[1]);

  /* Initialize the application.
     You do not need to do this more than one time. */
  forCoder_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_forCoder(seed);

  /* Terminate the application.
     You do not need to do this more than one time. */
  forCoder_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
