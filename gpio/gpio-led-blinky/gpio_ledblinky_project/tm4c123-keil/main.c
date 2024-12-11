/*----------------------------------------------------------------------------------*/
/* Copyright (C) 2024 Sigma eLabs, <https:/github.com/Sigma-eLabs>.                 */
/*                                                                                  */
/*                               S i g m a  e L a b s                               */
/*                    -------------------------------------------                   */
/*                    Embedded Software Education & Research Labs                   */
/*                                                                                  */
/* This is an opened source software for studying and researching purposes with     */
/* a non-comercial license.                                                         */
/*                                                                                  */
/* However, redistributions in source code must retain this top-level               */
/* comment block, to respect the contributions of the Sigma eLabs's authors.        */
/*                                                                                  */
/* Contact information:                                                             */
/*  <thienaiho95@gmail.com>                                                         */
/*  <https:/www.linkedin.com/in/thien-ai-ho>                                        */
/*----------------------------------------------------------------------------------*/

#include <stdint.h> /* standard integers library */
#include "TM4C123GH6PM.h" /* the TM4C MCU Peripheral Access Layer (TI) */

/* on-board LEDs */
#define LED_RED   (1U << 1) /* PF1 - red LED */

/* this function is required by start-up file, will be called when systen failed */
void assert_failed(char const * const module, int const id);

/* delay for interations  */
void delay(uint32_t volatile iter);

int main(void) {
	
	/* Configuration for modules to enable their functions */
	SYSCTL->RCGCGPIO  |= (1U << 5); /* enable Run mode for GPIOF */
    SYSCTL->GPIOHBCTL |= (1U << 5); /* enable AHB bus for GPIOF */
    GPIOF_AHB->DIR |= LED_RED; /* configure PF1 pin - red LED as output pin */
    GPIOF_AHB->DEN |= LED_RED; /* configure PF1 pin - red LED with digital mode */
	
	/* endless loop */
    while (1) {
		GPIOF_AHB->DATA_Bits[LED_RED] = LED_RED; /* turn on PF1 pin - red LED on */
		delay(5000); /* delay for 5000 interations */
		GPIOF_AHB->DATA_Bits[LED_RED] = ~LED_RED; /* turn on PF1 pin - red LED on */
		delay(3000); /* delay for 3000 interations */
    }

    return 0;
}

void delay(uint32_t volatile iter) {
	while(iter > 0U){
		--iter;
	}
}

void assert_failed(char const * const module, int const id) {
    (void)module; /* unused parameter */
    (void)id;     /* unused parameter */
    NVIC_SystemReset();
}