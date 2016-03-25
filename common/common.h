/*
 * File:        common.h
 * Purpose:     File to be included by all project files
 *
 * Notes:
 */

#ifndef _COMMON_H_
#define _COMMON_H_

/********************************************************************/

/*
 * Debug prints ON (#define) or OFF (#undef)
 */
#define DEBUG
#define DEBUG_PRINT

/* 
 * Include the generic CPU header file 
 */
#include "arm_cm4.h"

#define TWR_K60N512 1

#if 0 //kevin
/* 
 * Include the platform specific header file 
 */
#if (defined(TWR_K40X256))
  #include "k40_tower.h"
#elif (defined(TWR_K60N512))
 #include "k60_tower.h"
#else
  #error "No valid platform defined"
#endif

/* 
 * Include the cpu specific header file 
 */
#if (defined(CPU_MK40N512VMD100))
  #include "MK40N512VMD100.h"
#elif (defined(CPU_MK60N512VMD100))
  #include "MK60N512VMD100.h"
#else
  #error "No valid CPU defined"
#endif
#endif

//kevin
#include "k60_tower.h"
#include "MK60N512VMD100.h"
//kevin


/* 
 * Include common utilities
 */
#include "assert.h"
#include "io.h"
//#include "startup.h"
#include "stdlib.h"


/********************************************************************/

#endif /* _COMMON_H_ */