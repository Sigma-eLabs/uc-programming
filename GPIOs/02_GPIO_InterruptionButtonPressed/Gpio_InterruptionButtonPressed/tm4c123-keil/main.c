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
#define LED_RED   	(1U << 1) /* PF1 - red LED */
#define LED_BLUE   	(1U << 2) /* PF2 - blue LED */
#define LED_GREEN   (1U << 3) /* PF3 - green LED */

/* on-board Buttons */
#define USR_SW1		(1U << 4) /* PF4 - User button switch 1 */

/* state type of on-board Buttons */
typedef enum {
	RELEASED = 0U,
	PRESSED
} ButtonState;

/* User button switch 1 pressed signal, initialized with Released state */
ButtonState volatile UsrSw1_State = RELEASED;

/* this function is required by start-up file, will be called when systen failed */
void assert_failed(char const * const module, int const id);

/* delay for interations  */
void delay(uint32_t volatile iter);

/* Red LED Blinky */
void Led_Blinky(void);

int main(void) {
	
	/* configuration to enable GPIOF module */
	SYSCTL->RCGCGPIO  |= (1U << 5);	/* enable Run mode for GPIOF */
    SYSCTL->GPIOHBCTL |= (1U << 5);	/* enable AHB bus for GPIOF */
	
	/* even PF2, PF3 pins unused, but explicitly configured them as output pins to prevent unwanted behavior */
    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN); /* configure PF1, PF2, PF3 pins - red, blue, green LEDs as output pin */
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN); /* configure PF1, PF2, PF3 pins - red, blue, green LEDs with digital mode */
	
	/* configure User button switch 1 - PF4 pin as digital input pin with pull-up resistor */
	GPIOF_AHB->DIR &= ~USR_SW1;	/* configure PF4 pin - red LED as input pin */
    GPIOF_AHB->DEN |= USR_SW1;	/* configure PF4 pin - red LED with digital mode */
	GPIOF_AHB->PUR |= USR_SW1;	/* confgiure PF4 pin with pull-up resistor */
	
	/* Interrupt setup for User button switch 1 - PF4 pin: falling edge interrupt detection */
	GPIOF_AHB->IS &= ~USR_SW1;	/* edge-sensitive interrupt detection */
	GPIOF_AHB->IBE &= ~USR_SW1;	/* interrupt event is controller by GPIOIEV */
	GPIOF_AHB->IEV &= ~USR_SW1;	/* falling edge interrupt trigger */
	GPIOF_AHB->IM |= USR_SW1;	/* enable GPIOF interrupt for this pin */
	
	/* set interrupt priority for GPIOF */
	NVIC_SetPriority(GPIOF_IRQn, 1U); /* for now, stick to 1 but avoid 0 (highest priority), the reason will be explained in another lesson */
	
	/* enable GPIOF_IRQn in NVIC */
	NVIC_EnableIRQ(GPIOF_IRQn);

	/* endless loop */
    while (1) {
		if (UsrSw1_State == PRESSED) {
			/* Blink red LED for a while */
			Led_Blinky();
			
			/* reset the state of User button switch 1 */
			UsrSw1_State = RELEASED;
		}
    }

    return 0;
}

void delay(uint32_t volatile iter) {
	while(iter > 0U){
		--iter;
	}
}

void Led_Blinky(void) {
	uint8_t volatile iter = 0U;
	
	for (iter = 5U; iter != 0U; --iter) {
		GPIOF_AHB->DATA_Bits[LED_RED] = LED_RED; /* turn on PF1 pin - red LED on */
		delay(2000000); /* delay for 2000000 interations */
		GPIOF_AHB->DATA_Bits[LED_RED] = 0U; /* turn on PF1 pin - red LED on */
		delay(1000000); /* delay for 1000000 interations */
	}
}

/* interrupt function is invoked when GPIOF interrupt happened */
void GPIOPortF_IRQHandler(void) {
	if ((GPIOF_AHB->RIS & USR_SW1) != 0U) { /* check if the interrupt caused by User button switch 1 - PF4 pin pressed */
		UsrSw1_State = PRESSED;	/* signal the system that User button switch 1 has been pressed */
	}
	
	GPIOF_AHB->ICR = USR_SW1;	/* clear the interrupt source caused by User button switch 1, otherwise it is remained forever */
}

void assert_failed(char const * const module, int const id) {
    (void)module; /* unused parameter */
    (void)id;     /* unused parameter */
    NVIC_SystemReset();
}