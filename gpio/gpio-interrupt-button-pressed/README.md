<p align="center">
  <a href="." title="Sigma eLabs">
    <img src="/assets/SigmaeLabsBannerv2.png" title="Sigma eLabs" style="width: 100vw; min-width: 200px"/>
  </a>
</p>

# GPIO Interrupt with on-board button pressed
Perform blinking LED for a while when identify the interrupt triggered from GPIO pin.
<p align="center">
  <a href="." title="GPIO Interrupt with on-board button pressed">
    <img src="/gpio/gpio-interrupt-button-pressed/InterruptButtonPressedSetup.png" title="GPIO Interrupt with on-board button pressed" style="min-width: 200px"/>
  </a>
</p>

# General Requirements
Design a software is able to identify the interrupt triggered from GPIO PF4 pin (on-board User button switch 1) and peform blinking red LED for a seconds.

# Requisitions
## Hardware
* [Tiva C Series TM4C123G LaunchPad Evaluation Kit - EK-TM4C123GXL](https://www.ti.com/tool/EK-TM4C123GXL)
* Logic Analyzer

## Software
* [Keil C](https://www.keil.com/demo/eval/arm.htm)
* [Logic 2](https://www.saleae.com/pages/downloads)

Note: For this project, you can choose your own hardware and software. It doesn't matter, because the selection is personal choice. The main purpose needs to be focused is resolving the problem in [General Requirements](#general-requirements) and the knowledge you get after this lesson. You can try to do the similar thing on the different hardware and software.

## Documents
* [Tiva™ C Series TM4C123G LaunchPad Evaluation Board User's Guide](https://github.com/Sigma-eLabs/technical-resources/blob/main/tiva-c-series/spmu296.pdf)
* [Tiva™ TM4C123GH6PM Microcontroller Datasheet](https://github.com/Sigma-eLabs/technical-resources/blob/main/tiva-c-series/tm4c123gh6pm.pdf)
* [Cortex Microcontroller Software Interface Standard (CMSIS)](https://github.com/Sigma-eLabs/technical-resources/tree/main/tiva-c-series/CMSIS)
* [Tiva™ TM4C123GH6PM Microcontroller Software Support Package](https://github.com/Sigma-eLabs/technical-resources/tree/main/tiva-c-series/ek-tm4c123gxl)

# Implementation
* To implement this software, you should read [Tiva™ TM4C123GH6PM Microcontroller Datasheet](https://github.com/Sigma-eLabs/technical-resources/blob/main/tiva-c-series/tm4c123gh6pm.pdf), the chapters related to GPIO, System Control modules to know about the functionality of common registers. Especially, the you should read about the interrupt related registers.

* You also should read [Tiva™ C Series TM4C123G LaunchPad Evaluation Board User's Guide](https://github.com/Sigma-eLabs/technical-resources/blob/main/tiva-c-series/spmu296.pdf) to know about the hardware design of the development kit which is being used.

* Additionally, you understand and know how to use the provided standard libraries like [Cortex Microcontroller Software Interface Standard (CMSIS)](https://github.com/Sigma-eLabs/technical-resources/tree/main/tiva-c-series/CMSIS), [Tiva™ TM4C123GH6PM Microcontroller Software Support Package](https://github.com/Sigma-eLabs/technical-resources/tree/main/tiva-c-series/ek-tm4c123gxl), which support Arm-Cortex architecture processor and TM4C123GHPM controller.

* :rocket:  Source Code: [gpio_interrupt_button_project](/gpio/gpio-interrupt-button-pressed/gpio_interrupt_button_project/) :rocket:

* I define a new enumeration type for button state and creat one variable to store its state.
  ```C
  /* state type of on-board Buttons */
  typedef enum {
    RELEASED = 0U,
    PRESSED
  } ButtonState;

  /* User button switch 1 pressed signal, initialized with Released state */
  ButtonState volatile UsrSw1_State = RELEASED;
  ```

* Interrupt setup for GPIOF pin PF4 (USR_SW1):
  ```C
  /* Interrupt setup for User button switch 1 - PF4 pin: falling edge interrupt detection */
  GPIOF_AHB->IS &= ~USR_SW1;	/* edge-sensitive interrupt detection */
  GPIOF_AHB->IBE &= ~USR_SW1;	/* interrupt event is controller by GPIOIEV */
  GPIOF_AHB->IEV &= ~USR_SW1;	/* falling edge interrupt trigger */
  GPIOF_AHB->IM |= USR_SW1;	/* enable GPIOF interrupt for this pin */

  /* set interrupt priority for GPIOF */
  NVIC_SetPriority(GPIOF_IRQn, 1U); /* for now, stick to 1 but avoid 0 (highest priority), the reason will be explained in another lesson */

  /* enable GPIOF_IRQn in NVIC */
  NVIC_EnableIRQ(GPIOF_IRQn);
  
  ```
* Application code to be called when interrupt occured:
  ```C
  /* inside of main() function */
  while (1) {
    if (UsrSw1_State == PRESSED) {
      /* Blink red LED for a while */
      Led_Blinky();
      
      /* reset the state of User button switch 1 */
      UsrSw1_State = RELEASED;
    }
  }
  ```
* Implement GPIOF interrup handler function:
  ```C
  /* interrupt function is invoked when GPIOF interrupt happened */
  void GPIOPortF_IRQHandler(void) {
    if ((GPIOF_AHB->RIS & USR_SW1) != 0U) { /* check if the interrupt caused by User button switch 1 - PF4 pin pressed */
      UsrSw1_State = PRESSED;	/* signal the system that User button switch 1 has been pressed */
    }
    
    GPIOF_AHB->ICR = USR_SW1;	/* clear the interrupt source caused by User button switch 1, otherwise it is remained forever */
  }
  ```

# Deployment
After composed the source code, compiled and flashed it on [Tiva C Series TM4C123G LaunchPad Evaluation Kit - EK-TM4C123GXL](https://www.ti.com/tool/EK-TM4C123GXL), I started to debug and test my code.

Firstly, I check if the interrupt is trigger after the User button switch is pressed. The interrupt handler function is invoked as expectation. Inside of the interrupt handler function, the software check if the interrupt source is from PF4 pin and signal the information that the user button 1 is pressed:
<p align="center">
  <a href="." title="Interrupt Trigged">
    <img src="/gpio/gpio-interrupt-button-pressed/InterruptTrigged.png" title="Interrupt Trigged" style="width: 100vw; min-width: 200px"/>
  </a>
</p>

Secondly, the main function check if the user button switch 1 is pressed, then invokes the application.
<p align="center">
  <a href="." title="Application Invoked">
    <img src="/gpio/gpio-interrupt-button-pressed/ApplicationInvoked.png" title="Application Invoked" style="width: 100vw; min-width: 200px"/>
  </a>
</p>

The actual result are measured by Logic Analyzer on User User button switch 1 - PF4 pin and red LED - PF1 pin, see as below:
<p align="center">
  <a href="." title="Signals Measurement">
    <img src="/gpio/gpio-interrupt-button-pressed/SignalsMeasurement.PNG" title="Signals Measurement" style="width: 100vw; min-width: 200px"/>
  </a>
</p>

When User button switch 1 is pressed, the falling edge dectected on PF4 and the interrupt is triggered. The red LED is blinked for 5 cycles in seconds. You can see that the software seems to sastify general requirements. 

However, there is a found unexpected behavior. While testing and debugging the software, I see blue and green LEDs also are turned on. The only reason at this momment I can think is because PF2, PF3 pins functionality (corresponding to blue, green LEDs) are not configured explicitly, which mean their values are undetermined at runtime. In the consequence, when manipulating the value of PF1, it somehow causes the value of PF2, PF3 changed. The workaround I use to eliminate the issue is explicitly configured they are output pins.

If you has any good idea, you can implement your own application when the interrupt happened.I believe that you'll do it great!
# Contact & Discussion
If you have any thing would like to discuss or cooperate with me, please don't hesitate to contact me via:
* Email [Ho Thien Ai](mailto:thienaiho95@gmail.com)
* LinkedIn [Thien Ai Ho](https://www.linkedin.com/in/thien-ai-ho/).

I'm always welcome your ideas and thank for your insteresting!
