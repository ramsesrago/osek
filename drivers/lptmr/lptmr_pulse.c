/*
 * lptmr_pulse.c
 *
 *  Created on: Mar 13, 2016
 *      Author: uidj2420
 */

#include "lptmr.h"

void lptmr_pulse_counter(char pin_select)
{
  unsigned int compare_value=1000;
  char input;
  printf("\n\n****************************\n");
  printf("LPTMR Pulse Counting Example on LPTMR_ALT%d\n\n",pin_select);

  //Reset LPTMR module
  lptmr_clear_registers();

  //Set up GPIO
  if(pin_select == LPTMR_ALT1)
  {
    SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; //Turn on PORTA clock
    PORTA_PCR19=PORT_PCR_MUX(0x6); //Use ALT6 on PTA19

    printf("Testing ALT1 pin on PORTA19\n");
    printf("\tTWR-K40X256: ALT1 is connected to XTAL and should not be driven\n");
    printf("\tTWR-K60N512: ALT1 is conected to pin 18 on J15\n");
  }
  else if(pin_select == LPTMR_ALT2)
  {
    SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK; //Turn on PORTC clock
    PORTC_PCR5=PORT_PCR_MUX(0x4); //Use ALT4 on PTC5

    printf("Testing ALT2 pin on PORTC5\n");
    printf("\tTWR-K40X256: ALT2 is connected to pin 18 on J15\n");
    printf("\tTWR-K60N512: ALT2 is conected A70 on TWR-ELEV\n");
  }
  else
  {
    printf("Invalid pin selected\n");
    printf("****************************\n");
    return;
  }

  /* Test requires external hardware. Need to confirm if want to run test or not */
  printf("\nThis test requires a function generator, or another way of producing a pulse signal on the pin specified above. ");
  printf("Please connect that device to the specified pin (Except if using ALT1 on the TWR-K40X256)\n\n");
  printf("If you would like to continue with this example, press \"y\". To skip press any other key\n");
  input=in_char(); //wait for keyboard press
  printf("\n");
  if(input!='y' && input!='Y')
  {
    printf("Exiting LPTMR Pulse Counting Example on LPTMR_ALT%d\n",pin_select);
    printf("****************************\n");
    return;
  }

  LPTMR0_PSR=LPTMR_PSR_PCS(0x1)|LPTMR_PSR_PBYP_MASK; //Use LPO clock but bypass glitch filter
  LPTMR0_CMR=LPTMR_CMR_COMPARE(compare_value);  //Set compare value
  LPTMR0_CSR=LPTMR_CSR_TPS(pin_select)|LPTMR_CSR_TMS_MASK; //Set LPT to use the pin selected, and put in pulse count mode, on rising edge (default)

  printf("Press any key to start pulse counter\n");
  in_char(); //wait for keyboard press

  LPTMR0_CSR|=LPTMR_CSR_TEN_MASK; //Turn on LPT

  //Wait for compare flag to be set
  while((LPTMR0_CSR&LPTMR_CSR_TCF_MASK)==0)
  {
    //This may not get proper counter data if the CNR is read at the same time it is incremented
    printf("Current value of pulse count register CNR is %d\n",LPTMR0_CNR);
  }

  printf("Detected %d pulses on LPTMR_ALT%d\n",compare_value,pin_select);
  printf("End of Pulse Counting Example\n");
  printf("****************************\n");
}
