# LHA7928 Firmware Demo

基于 **STM32H750VBT6** 与 **LHA7928** 高精度 Delta-Sigma ADC 的演示固件工程。

---

## 1. 项目简介

本工程基于 STM32CubeMX 和 Keil MDK-ARM (v5) 开发，演示了使用 STM32H750 高性能微控制器通过 SPI 接口驱动国产高精度模数转换器芯片 **LHA7928** 进行采样、配置与数据读取的完整流程。

### 主要特性
- **主控芯片**：STM32H750VBT6 (Arm Cortex-M7，主频最高 480 MHz)
- **目标芯片**：LHA7928 (内置 PGA、温度传感器、可编程数据速率的高精度 ADC)
- **通信接口**：标准 SPI 接口 + 中断/READY 引脚检测
- **调试与日志**：USART 串口日志输出

---

## 2. 目录结构

```text
LHA7928_demo_firmware_v2/
├── Core/               # CubeMX 生成的系统与外设初始化代码及用户主程序
│   ├── Inc/
│   └── Src/
├── Drivers/            # CMSIS 核心库与 STM32H7xx HAL 库
├── LHLX/               # LHA7928 驱动源码 (LHA7928.c / LHA7928.h)
├── MDK-ARM/            # Keil MDK-ARM 工程文件及启动代码
│   ├── firmware.uvprojx # Keil 工程主文件
│   └── keilkill.bat    # Keil 编译产物一键瘦身脚本
├── .gitignore          # Git 忽略规则
├── firmware.ioc        # STM32CubeMX 工程配置文件
└── README.md           # 工程说明文档
```

---

## 3. 硬件引脚参考

| 信号名称 | STM32 引脚 | 功能描述 |
| :--- | :--- | :--- |
| **SPI_SCK** | 引脚按 `.ioc` 配置 | SPI 串行时钟 |
| **SPI_MISO (DOUT)** | 引脚按 `.ioc` 配置 | ADC 数据输出 |
| **SPI_MOSI (DIN)** | 引脚按 `.ioc` 配置 | ADC 数据输入 / 寄存器写入 |
| **CS / SS** | GPIO 控制 | 片选信号（低电平使能） |
| **DRDY / INT** | GPIO 外部中断 | 数据转换完成就绪标志 |
| **USART_TX / RX**| 串口外设 | 串口调试与数据打印 |

*详细引脚映射请查阅 `firmware.ioc` 文件。*

---

## 4. 开发与编译

### 开发环境要求
- **IDE**：Keil MDK-ARM v5.28 或更高版本
- **器件支持包**：Keil STM32H7xx_DFP
- **配置工具**：STM32CubeMX (可选，用于重新配置时钟与引脚)

### 编译步骤
1. 打开 `MDK-ARM/firmware.uvprojx`。
2. 点击 **Build** (F7) 进行全工程编译。
3. 连接 J-Link / ST-Link 等调试器，点击 **Download** (F8) 烧录固件。

### 清理与瘦身
在每次编译生成大体积中间文件（如 `.crf`、`.o` 等）后，可随时双击运行 `MDK-ARM/keilkill.bat` 释放磁盘空间。
