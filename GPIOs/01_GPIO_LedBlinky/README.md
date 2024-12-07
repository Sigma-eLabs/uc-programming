Được thực hiện bởi Sigma-eLabs
<p align="center">
  <a href="." title="Sigma eLabs">
    <img src="/Assets/SigmaeLabsBannerv2.png" title="Sigma eLabs" style="width: 100vw; min-width: 200px"/>
  </a>
</p>

# GPIO LED Blinky

<p align="center">
  <a href="." title="Microcontroller Programming">
    <img src="/Assets/uCprogramming.png" title="Microcontroller Programming" style="width: 100vw; min-width: 200px"/>
  </a>
</p>

# General Requirements (#general-requirements)
Thiết kế một chương trình điều khiển chân GPIO để tạo sóng PWM với duty cycle 62.5%.

# Requisitions
## Hardware
Kit phát triển được sửa dụng đa số trong các chủ đề là [Tiva C Series TM4C123G LaunchPad Evaluation Kit - EK-TM4C123GXL](https://www.ti.com/tool/EK-TM4C123GXL). Vi xử lý chính trên kit là ARM Cortex-M4F được sản xuất bởi Texas Instruments. Trên kit còn có một mạch Debugger/Programmer (Stellaris ICDI) cho phép người dùng dễ dàng nạp code, debug một cách dễ dàng.

<p align="center">
  <a href="." title="Tiva C Series TM4C123G LaunchPad Evaluation Kit">
    <img src="/Assets/ek-tm4c123gxl.png" title="Tiva C Series TM4C123G LaunchPad Evaluation Kit" style="min-width: 200px"/>
  </a>
</p>

Ngoài ra, trong quá trình testing và debug, mình còn dùng thêm Logic Analyzer (phiên bản shoppee) để đo tín hiệu điện trên các chân của vi điều khiển.
<p align="center">
  <a href="." title="Logic Analyzer">
    <img src="/Assets/LogicAnalyzer.png" title="Logic Analyzer" style="min-width: 200px"/>
  </a>
</p>

## Software
[Keil C](https://www.keil.com/demo/eval/arm.htm) là một IDE được phát triển bởi Arm. Đây là một công cụ mạnh mẽ để giúp các lập trình viên soạn thảo code, biên dịch chương trình, nạp code và debug. Đặc biệt hơn, với phiên bản miễn phí thì nó có thể đáp ứng hầu như mọi nhu cầu học tập và nghiên cứu của các bạn.
<p align="center">
  <a href="." title="Keil C">
    <img src="/Assets/KeilC.PNG" title="Keil C" style="width: 100vw; min-width: 200px"/>
  </a>
</p>

Để có thể quan sát và ghi lại các tính hiệu điện trên các chân của vi điều khiển được thu thập từ Logic Analyze một cách trực quan, thì phần mềm [Logic 2](https://www.saleae.com/pages/downloads) là sự lựa chọn phù hợp.
<p align="center">
  <a href="." title="Logic 2">
    <img src="/Assets/Logic2.PNG" title="Logic 2" style="width: 100vw; min-width: 200px"/>
  </a>
</p>

Lưu ý: Các bạn có thể thực hiện dự án này với hardware, software khác vì ở trên chỉ là sự lựa chọn cá nhân. Mục tiêu ta cần tập trung đó chính là giải quyết yêu cầu ở [General Requirements](#general-requirements).

## Documents
* [Tiva™ C Series TM4C123G LaunchPad Evaluation Board User's Guide](https://github.com/Sigma-eLabs/technical-resources/blob/main/tiva-c-series/spmu296.pdf)
* [Tiva™ TM4C123GH6PM Microcontroller Datasheet](https://github.com/Sigma-eLabs/technical-resources/blob/main/tiva-c-series/tm4c123gh6pm.pdf)
* [Cortex Microcontroller Software Interface Standard (CMSIS)](https://github.com/Sigma-eLabs/technical-resources/tree/main/tiva-c-series/CMSIS)
* [Tiva™ TM4C123GH6PM Microcontroller Software Support Package](https://github.com/Sigma-eLabs/technical-resources/tree/main/tiva-c-series/ek-tm4c123gxl)
# Assumptions
Khi thực hiện chủ đề này, mình giả định các bạn đã có kiến thức cơ bản về lập trình ngôn C và vi điều khiển. Đối tương nghiên cứu là Tiva™ TM4C123GH6PM Microcontroller và Tiva C Series TM4C123G LaunchPad Evaluation Kit.

# Implementation
Để hiện hiện thực bài này, các bạn nên đọc [Tiva™ TM4C123GH6PM Microcontroller Datasheet](https://github.com/Sigma-eLabs/technical-resources/blob/main/tiva-c-series/tm4c123gh6pm.pdf), các chương liên quan đến GPIO module, System Control module để biết được chức năng của các thanh ghi phổ biến. Ví dụ: GPIODATA, GPIODIR, GPIODEN, RCGCGPIO, GPIOHBCTL. Đọc thêm [Tiva™ C Series TM4C123G LaunchPad Evaluation Board User's Guide](https://github.com/Sigma-eLabs/technical-resources/blob/main/tiva-c-series/spmu296.pdf) để biết được thiết kế hardware của Developmment Kit đang sử dụng.  Thêm nữa, bạn cần phải học cách sử dụng thư viện chuẩn được cung cấp như [Cortex Microcontroller Software Interface Standard (CMSIS)](https://github.com/Sigma-eLabs/technical-resources/tree/main/tiva-c-series/CMSIS), [Tiva™ TM4C123GH6PM Microcontroller Software Support Package](https://github.com/Sigma-eLabs/technical-resources/tree/main/tiva-c-series/ek-tm4c123gxl) hỗ trợ cho dòng Arm-Cortex và TM4C123GHPM controller.

:rocket:  Source Code: [Gpio_LedBlinky](/GPIOs/01_GPIO_LedBlinky/Gpio_LedBlinky/)
```C
/*--------------------------------------*/

/* delay for interations  */
void delay(uint32_t volatile iter) {
	while(iter > 0U){
		--iter;
	}
}

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

# Deploy
Sau khi thực hiện compile và flash code lên [Tiva C Series TM4C123G LaunchPad Evaluation Kit - EK-TM4C123GXL](https://www.ti.com/tool/EK-TM4C123GXL), tiến hành debug và test thì mình thu được kết quả đo bằng Logic Analyzer trên chân PF1 - LED đỏ, như sau:
<p align="center">
  <a href="." title="PWM Waveform">
    <img src="/GPIOs/01_GPIO_LedBlinky/PWM_Waveform.png" title="PWM Waveform" style="width: 100vw; min-width: 200px"/>
  </a>
</p>
Đối với setup hiện tại cho hàm delay() thì LED đỏ nhấp nháy với tần số cao, đến đến hiệu ứng lưu ảnh trong mắt mà ta không thể thấy được LED đang thực sự nhấp nháy. Để có thể thấy được bằng mắt, các bạn có thể tăng iteration đầu vào của hàm và quan sát kết quả.

Chúc các bạn thành công!
# Contact & Discussion
Vui lòng liên hệ [Sigma eLabs](https://github.com/Sigma-eLabs) qua email: [Ho Thien Ai](mailto:thienaiho95@gmail.com) để đóng góp ý kiến và trao đổi. Mình rất trân trọng và chân thành cảm ơn!


