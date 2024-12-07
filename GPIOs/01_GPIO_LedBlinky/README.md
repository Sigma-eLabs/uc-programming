<p align="center">
  <a href="." title="Sigma eLabs">
    <img src="/Assets/SigmaeLabsBannerv2.png" title="Sigma eLabs" style="width: 100vw; min-width: 200px"/>
  </a>
</p>

# GPIO LED Blinky
Tạo sóng PWM và nhấp nháy Led.
<p align="center">
  <a href="." title="Red LED Blinky">
    <img src="/GPIOs/01_GPIO_LedBlinky/LedBlinky.png" title="Red LED Blinky" style="min-width: 200px"/>
  </a>
</p>

# General Requirements
Thiết kế một chương trình điều khiển chân GPIO để tạo sóng PWM với duty cycle 62.5%.

# Requisitions
## Hardware
* [Tiva C Series TM4C123G LaunchPad Evaluation Kit - EK-TM4C123GXL](https://www.ti.com/tool/EK-TM4C123GXL)
* Logic Analyzer

## Software
* [Keil C](https://www.keil.com/demo/eval/arm.htm)
* [Logic 2](https://www.saleae.com/pages/downloads)

Lưu ý: Các bạn có thể thực hiện dự án này với hardware, software khác vì ở trên chỉ là sự lựa chọn cá nhân. Mục tiêu ta cần tập trung đó chính là giải quyết yêu cầu ở [General Requirements](#general-requirements).

## Documents
* [Tiva™ C Series TM4C123G LaunchPad Evaluation Board User's Guide](https://github.com/Sigma-eLabs/technical-resources/blob/main/tiva-c-series/spmu296.pdf)
* [Tiva™ TM4C123GH6PM Microcontroller Datasheet](https://github.com/Sigma-eLabs/technical-resources/blob/main/tiva-c-series/tm4c123gh6pm.pdf)
* [Cortex Microcontroller Software Interface Standard (CMSIS)](https://github.com/Sigma-eLabs/technical-resources/tree/main/tiva-c-series/CMSIS)
* [Tiva™ TM4C123GH6PM Microcontroller Software Support Package](https://github.com/Sigma-eLabs/technical-resources/tree/main/tiva-c-series/ek-tm4c123gxl)

# Implementation
* Để hiện hiện thực bài này, các bạn nên đọc [Tiva™ TM4C123GH6PM Microcontroller Datasheet](https://github.com/Sigma-eLabs/technical-resources/blob/main/tiva-c-series/tm4c123gh6pm.pdf), các chương liên quan đến GPIO module, System Control module để biết được chức năng của các thanh ghi phổ biến. Ví dụ: GPIODATA, GPIODIR, GPIODEN, RCGCGPIO, GPIOHBCTL.

* Các bạn nên đọc thêm [Tiva™ C Series TM4C123G LaunchPad Evaluation Board User's Guide](https://github.com/Sigma-eLabs/technical-resources/blob/main/tiva-c-series/spmu296.pdf) để biết được thiết kế hardware của Developmment Kit đang sử dụng.

* Thêm nữa, bạn cần phải học cách sử dụng thư viện chuẩn được cung cấp như [Cortex Microcontroller Software Interface Standard (CMSIS)](https://github.com/Sigma-eLabs/technical-resources/tree/main/tiva-c-series/CMSIS), [Tiva™ TM4C123GH6PM Microcontroller Software Support Package](https://github.com/Sigma-eLabs/technical-resources/tree/main/tiva-c-series/ek-tm4c123gxl) hỗ trợ cho dòng Arm-Cortex và TM4C123GHPM controller.

* :rocket:  Source Code: [Gpio_LedBlinky](/GPIOs/01_GPIO_LedBlinky/Gpio_LedBlinky/) :rocket:
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
Sau khi thực hiện compile và flash code lên [Tiva C Series TM4C123G LaunchPad Evaluation Kit - EK-TM4C123GXL](https://www.ti.com/tool/EK-TM4C123GXL), tiến hành debug và test thì mình thu được kết quả đo bằng Logic Analyzer trên chân PF1 - LED đỏ, như sau:
<p align="center">
  <a href="." title="PWM Waveform">
    <img src="/GPIOs/01_GPIO_LedBlinky/PWM_Waveform.png" title="PWM Waveform" style="width: 100vw; min-width: 200px"/>
  </a>
</p>

Đối với setup hiện tại cho hàm delay() thì LED đỏ nhấp nháy với tần số cao, dẫn đến hiệu ứng lưu ảnh trong mắt mà ta không thể thấy được LED đang thực sự nhấp nháy. Để có thể thấy được bằng mắt, các bạn có thể tăng giá trị iteration đầu vào của hàm và quan sát kết quả.
<p align="center">
  <a href="." title="Red LED Blinky">
    <img src="/GPIOs/01_GPIO_LedBlinky/LedBlinky.png" title="Red LED Blinky" style="min-width: 200px"/>
  </a>
</p>

Chúc các bạn thành công!
# Contact & Discussion
Vui lòng liên hệ [Sigma eLabs](https://github.com/Sigma-eLabs) qua email: [Ho Thien Ai](mailto:thienaiho95@gmail.com) để đóng góp ý kiến và trao đổi. Mình rất trân trọng và chân thành cảm ơn!


