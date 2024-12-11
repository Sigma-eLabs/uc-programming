<p align="center">
  <a href="." title="Sigma eLabs">
    <img src="/assets/SigmaeLabsBannerv2.png" title="Sigma eLabs" style="width: 100vw; min-width: 200px"/>
  </a>
</p>

# GPIO LED Blinky and Generate PWM 
Perform blinking LED and generating simple PWM waveform with specific duty cycle.
<p align="center">
  <a href="." title="Red LED Blinky">
    <img src="/gpio/gpio-led-blinky/LedBlinky.png" title="Red LED Blinky" style="min-width: 200px"/>
  </a>
</p>

# General Requirements
Design a software that performs controlling the GPIO pin to blink red LED and generating PWM waveform with duty cycle 62.5%.

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
* To implement this software, you should read [Tiva™ TM4C123GH6PM Microcontroller Datasheet](https://github.com/Sigma-eLabs/technical-resources/blob/main/tiva-c-series/tm4c123gh6pm.pdf), the chapters related to GPIO, System Control modules to know about the functionality of common registers. Example: GPIODATA, GPIODIR, GPIODEN, RCGCGPIO, GPIOHBCTL.

* You also should read [Tiva™ C Series TM4C123G LaunchPad Evaluation Board User's Guide](https://github.com/Sigma-eLabs/technical-resources/blob/main/tiva-c-series/spmu296.pdf) to know about the hardware design of the development kit which is being used.

* Additionally, you understand and know how to use the provided standard libraries like [Cortex Microcontroller Software Interface Standard (CMSIS)](https://github.com/Sigma-eLabs/technical-resources/tree/main/tiva-c-series/CMSIS), [Tiva™ TM4C123GH6PM Microcontroller Software Support Package](https://github.com/Sigma-eLabs/technical-resources/tree/main/tiva-c-series/ek-tm4c123gxl), which support Arm-Cortex architecture processor and TM4C123GHPM controller.

* :rocket:  Source Code: [gpio_ledblinky_project](/gpio/gpio-led-blinky/gpio_ledblinky_project/) :rocket:
```C
/*--------------------------------------*/

/* delay for interations  */
void delay(uint32_t volatile iter) {
	 while(iter > 0U){
		--iter;
	 }
}

/*--------------------------------------*/

/* Configuration for modules to enable their functions */
SYSCTL->RCGCGPIO  |= (1U << 5); /* enable Run mode for GPIOF */
SYSCTL->GPIOHBCTL |= (1U << 5); /* enable AHB bus for GPIOF */
GPIOF_AHB->DIR |= LED_RED; /* configure PF1 pin - red LED as output pin */
GPIOF_AHB->DEN |= LED_RED; /* configure PF1 pin - red LED with digital mode */

/*--------------------------------------*/

/* endless loop inside main() function */
while (1) {
	GPIOF_AHB->DATA_Bits[LED_RED] = LED_RED; /* turn on PF1 pin - red LED on */
	delay(5000); /* delay for 5000 interations */
	GPIOF_AHB->DATA_Bits[LED_RED] = ~LED_RED; /* turn on PF1 pin - red LED on */
	delay(3000); /* delay for 3000 interations */
}

/*--------------------------------------*/

```

# Deployment
After composed the source code, compiled and flashed it on [Tiva C Series TM4C123G LaunchPad Evaluation Kit - EK-TM4C123GXL](https://www.ti.com/tool/EK-TM4C123GXL), I started to debug and test my code. The actual result are measured by Logic Analyzer on PF1 pin - red LED, see as below:
<p align="center">
  <a href="." title="PWM Waveform">
    <img src="/gpio/gpio-led-blinky/PWM_Waveform.png" title="PWM Waveform" style="width: 100vw; min-width: 200px"/>
  </a>
</p>

You can see that the software sastifies general requirements.

With the current setup of delay() function, read LED is blinked with the high frequency, that leads to can't see the it's blinking by eyes. To observe by eyes clearly, I suggest you should increase the value of iter paramter, an input of delay() function, and see the wonderful result.
<p align="center">
  <a href="." title="Red LED Blinky">
    <img src="/gpio/gpio-led-blinky/LedBlinky.png" title="Red LED Blinky" style="min-width: 200px"/>
  </a>
</p>

I believe that you'll do it great!
# Contact & Discussion
If you have any thing would like to discuss or cooperate with me, please don't hesitate to contact me via:
* Email [Ho Thien Ai](mailto:thienaiho95@gmail.com)
* LinkedIn [Thien Ai Ho](https://www.linkedin.com/in/thien-ai-ho/).

I'm always welcome your ideas and thank for your insteresting!
