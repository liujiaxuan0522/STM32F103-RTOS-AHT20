# STM32F103C8T6：uC/OS-III 多任务 + AHT20 温湿度检测

本仓库包含嵌入式课程的两个实验源码：

- **任务一**：在 STM32F103C8T6 上移植 uC/OS-III，建立三个任务——LED1 每 1 s 翻转、LED2 每 3 s 翻转、USART1 每 2 s 发送 hello 信息；
- **任务二**：在 RTOS 工程中接入 AHT20 温湿度传感器（软件 I2C，PB6/PB7），每 2 s 读取一次温湿度并通过 USART1 输出。

## 目录

```text
.
├─ RTOS/                    # 任务一：uC/OS-III 三任务工程
│  ├─ Core/                 # CubeMX 生成 + main.c / stm32f1xx_it.c
│  ├─ App/                  # app.c、app_cfg.h、os_cfg.h、cpu_cfg.h 等
│  ├─ Middlewares/
│  │  ├─ uC-CPU/
│  │  ├─ uC-LIB/
│  │  └─ uC-OS3/            # Source + Cortex-M3/ARMv7-M Ports
│  └─ MDK-ARM/              # Keil 工程与启动文件
├─ AHT20/                   # 任务二：AHT20 裸机工程
│  ├─ Core/                 # main.c、aht20.c、soft_i2c.c
│  └─ MDK-ARM/
├─ docs/                    # 博客、接线图、实验报告
├─ ThirdPartyNotices/       # uC/CPU、uC-LIB、uC/OS-III 的 License/Notice
└─ README.md
```

## 硬件

- STM32F103C8T6（Blue Pill，72 MHz，64 KB Flash，20 KB SRAM）
- ST-Link V2
- USB-TTL（PA9/PA10，115200-8-N-1）
- LED1：PC13（板载）；LED2：PB12（外接 + 330 Ω）
- AHT20：VCC=3.3 V、GND、SCL=PB6、SDA=PB7，SDA/SCL 各 4.7 kΩ 上拉到 3.3 V

## 任务一：uC/OS-III

- uC/OS-III V3.08（Micrium 源码）
- 1 kHz OS tick
- 任务优先级：LED1=2、LED2=3、UART=4
- 栈：LED 128 words，UART 256 words
- 串口输出：

```text
hello uc/OS! 欢迎来到RTOS多任务环境！
```

关键配置：

1. `PendSV` 向量指向 `OS_CPU_PendSVHandler`，不是 `PendSV_Handler`；
2. `SysTick_Handler` 同时调用 `HAL_IncTick()` 和 `OS_CPU_SysTickHandler()`；
3. `OSStart()` 之后，在第一个任务里调用 `OS_CPU_SysTickInitFreq(SystemCoreClock)`；
4. **Cortex-M3 没有 FPU**，`OS_CPU_ARM_FP_EN` 必须为 `0u`，否则任务栈帧与端口汇编不一致，`OSStart()` 后不切任务。

## 任务二：AHT20

- 软件 I2C：PB6=SCL，PB7=SDA，开漏输出
- AHT20 7 位地址：`0x38`，写 `0x70`，读 `0x71`
- 初始化：`0xBE 0x08 0x00`
- 触发测量：`0xAC 0x33 0x00`，等待约 80 ms
- 读取 7 字节：状态 + 5 字节数据 + CRC
- CRC8：多项式 `0x31`，初值 `0xFF`
- 串口输出示例：

```text
AHT20: T=26.4 C, RH=55.3 %
```

> 温湿度数值随环境变化，示例仅为当时实测。

## 编译

### Keil MDK

分别打开：

```text
RTOS/MDK-ARM/RTOS.uvprojx
AHT20/MDK-ARM/AHT20.uvprojx
```

选择 ST-Link，Build，Download。两个工程都已整理为相对路径，不再引用仓库外的文件。

### 注意

- `RTOS` 工程使用 uC/OS-III，编译前确认 `Middlewares` 三个源码目录完整；
- `AHT20` 工程是裸机版本，使用 `HAL_Delay()`；`RTOS` 工程的任务里不能用 `HAL_Delay()`；
- Keil 的 `Objects/`、`Listings/`、`*.axf`、`*.map` 等构建产物已在 `.gitignore` 中排除。

## 文档

- [任务一 & 任务二博客](docs/任务一与任务二博客.md)
- [AHT20 实验报告 PDF](docs/STM32F103_uCOSIII_AHT20实验报告.pdf)

## License

本仓库中的第三方 uC/CPU、uC-LIB、uC/OS-III 源码遵循其原始 Apache-2.0 许可，许可与 NOTICE 文件见 `ThirdPartyNotices/`。STM32 HAL/CMSIS 遵循 ST 原始许可。
