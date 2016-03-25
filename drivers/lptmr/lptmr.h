/*
 * lptmr.h
 *
 *  Created on: Mar 13, 2016
 *      Author: uidj2420
 */

#ifndef LPTMR_H_
#define LPTMR_H_

#include "common.h"

//Pin Select constants for CSR[TPS]
#define HSCMP    0x0
#define LPTMR_ALT1 0x1
#define LPTMR_ALT2 0x2
#define LPTMR_ALT3 0x3

//CSR[TPP] constants
#define RISING 0
#define FALLING LPTMR_CSR_TPP_MASK

void lptmr_clear_registers();
void lptmr_time_counter();
void lptmr_prescale();
void lptmr_internal_ref_input();
void lptmr_lpo_input();
void lptmr_32khz_input();
void lptmr_external_clk_input();
void lptmr_interrupt();
void lptmr_pulse_counter(char pin_select);

#endif /* LPTMR_H_ */
