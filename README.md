<p align="center">
  <a href="." title="Sigma eLabs">
    <img src="/Assets/SigmaeLabsBannerv2.png" title="Sigma eLabs" style="width: 100vw; min-width: 200px"/>
  </a>
</p>

[Microcontroller Programming](https://github.com/Sigma-eLabs/uc-programming) will focus on familiarizing with microcontroller programming activities like:
* Reading the techincal documents to gain knowledge about the hardware of microcontroller, which is very important and very helpful when working with microcontroller.
* Knowing how to interact (read/write) with the registers, which place the "connection gate" between software and hardware.
* Learn about the functionality of peripherals and how to use them to fullfil the requirements.

The topics may be simple, but I believe that it is a launchpad for you to approach the much higher complex technical topic in embedded programming world!
# uc-programming 

<p align="center">
  <a href="." title="Microcontroller Programming">
    <img src="/Assets/uCprogramming.png" title="Microcontroller Programming" style="width: 100vw; min-width: 200px"/>
  </a>
</p>

# Topics
Summary of the topics are already available:
* [GPIOs](/GPIOs/) - GPIO module

# Requisitions
## Hardware
Development Kit used in the most of topics is [Tiva C Series TM4C123G LaunchPad Evaluation Kit - EK-TM4C123GXL](https://www.ti.com/tool/EK-TM4C123GXL). The main microcontroller on the development kit is ARM Cortex-M4F 32-bit produced by Texas Instruments. Moreover, there is on-board Debugger/Programmer (Stellaris ICDI) that enable user quickly flashes and debugs easily.
<p align="center">
  <a href="." title="Tiva C Series TM4C123G LaunchPad Evaluation Kit">
    <img src="/Assets/ek-tm4c123gxl.png" title="Tiva C Series TM4C123G LaunchPad Evaluation Kit" style="min-width: 200px"/>
  </a>
</p>

Additionally, during testing và debugging, I also use Logic Analyzer to measure and capture the signal of microcontroller input/output pins.
<p align="center">
  <a href="." title="Logic Analyzer">
    <img src="/Assets/LogicAnalyzer.png" title="Logic Analyzer" style="min-width: 200px"/>
  </a>
</p>

## Software
[Keil C](https://www.keil.com/demo/eval/arm.htm) is an IDE developed by ARM company. It is a very powerful tool supports software engineer to compose, edit, compile, flash code and debug. Especially, with non-comercial version, I think it fully supports all your needs to study and research.
<p align="center">
  <a href="." title="Keil C">
    <img src="/Assets/KeilC.PNG" title="Keil C" style="width: 100vw; min-width: 200px"/>
  </a>
</p>

To visualize the measured signals of microcontroller pins from Logic Analyzer and easy to analyze the logs, [Logic 2](https://www.saleae.com/pages/downloads) tool is one of the suitale choice.
<p align="center">
  <a href="." title="Logic 2">
    <img src="/Assets/Logic2.PNG" title="Logic 2" style="width: 100vw; min-width: 200px"/>
  </a>
</p>

## Documents
* [Tiva™ C Series TM4C123G LaunchPad Evaluation Board User's Guide](https://github.com/Sigma-eLabs/technical-resources/blob/main/tiva-c-series/spmu296.pdf)
* [Tiva™ TM4C123GH6PM Microcontroller Datasheet](https://github.com/Sigma-eLabs/technical-resources/blob/main/tiva-c-series/tm4c123gh6pm.pdf)
* [Cortex Microcontroller Software Interface Standard (CMSIS)](https://github.com/Sigma-eLabs/technical-resources/tree/main/tiva-c-series/CMSIS)
* [Tiva™ TM4C123GH6PM Microcontroller Software Support Package](https://github.com/Sigma-eLabs/technical-resources/tree/main/tiva-c-series/ek-tm4c123gxl)

# Assumptions
When I'm doing this series, I have below assumptions:
* Reader has a basic knowledge of C programming language.
* Reader has a knwledge about microcontroller hardware.
* The target objects are used: Tiva™ TM4C123GH6PM Microcontroller và Tiva C Series TM4C123G LaunchPad Evaluation Kit.

# Contact & Discussion
If you have any thing would like to discuss or cooperate with me, please don't hesitate to contact me via:
* Email [Ho Thien Ai](mailto:thienaiho95@gmail.com)
* LinkedIn [Thien Ai Ho](https://www.linkedin.com/in/thien-ai-ho/).

I'm always welcome your ideas and thank for your insteresting!
