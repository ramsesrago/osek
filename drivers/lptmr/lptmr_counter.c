/*
 * lptmr_counter.c
 *
 *  Created on: Mar 13, 2016
 *      Author: uidj2420
 */

#include "lptmr.h"

void lptmr_prescale()
{
  int compare_value = 250;  //value must be less than 0xFFFF or 65535

  //Reset LPTMR module
  lptmr_clear_registers();

  /* Configure LPTMR */
  LPTMR0_CMR = LPTMR_CMR_COMPARE(compare_value);  //Set compare value
  LPTMR0_PSR = LPTMR_PSR_PCS(0x1) | LPTMR_PSR_PRESCALE(0x4);  //Use LPO clock and divide by 32

  printf("LPTMR using LPO clock with PRESCALE=4 and compare value=250 (8 seconds)\n");

  LPTMR0_CSR |= LPTMR_CSR_TEN_MASK; //Turn on LPTMR with default settings

  //Wait for Timer Compare Flag to be set
  while((LPTMR0_CSR & LPTMR_CSR_TCF_MASK) == 0)
  {
    //This may not get proper counter data if the CNR is read at the same time it is incremented
    printf("Current value of counter register CNR is %d\n",LPTMR0_CNR);
  }

  printf("Waited for %d counts\n",compare_value);
  printf("End of Time Counting Example with Prescale\n");
  printf("****************************\n\n");
  
}
