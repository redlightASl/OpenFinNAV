# FinNAV 快速入门

> ![icon-tip](../pic_resources/icon-tip.gif)欢迎使用鳍航FinNAV——一款针对水下机器人（ROV/AUV)设计的飞控固件库

本文档仅对如何编译FinNAV固件并进行烧录提供说明，为初学者了解FinNAV的使用提供便利。更多深入内容请参考其他文档

## 概述

FinNAV SDK 是一款支持多种SoC、多种RTOS、多种外设驱动库、多种编译器混合编译的嵌入式软件开发工具，几乎完全基于自由的GNU工具链构建。目前FinNAV支持在Windows和Linux主机上编译多种嵌入式平台目标程序，并允许用户不使用FinNAV库文件（Lib-ROV），仅将SDK作为嵌入式开发工具使用。

FinNAV支持以下RTOS：

* FreeRTOS：一款经典可靠的开源RTOS，目前由亚马逊托管
* LiteOS/OpenHarmony：由华为研发的面向小型互联终端的开源RTOS
* RT-Thread：一款面向物联网的小而美的开源RTOS

FinNAV支持以下外设驱动库形式：

* ST HAL：使用回调函数封装，有一定层次结构的外设库，适用于高性能MCU
* CMSIS STP：CMSIS标准通用外设库，适用于中高性能MCU
* Peripheral Register Map：外设寄存器直接映射，适用于低性能MCU和无原厂驱动的MCU

FinNAV支持以下编译器：

* Clang（LLVM）
* GCC

FinNAV支持以下处理器指令集：

* ARMv7e、ARMv8e
* RV32

作为快速入门，本文档将介绍使用GCC编译ARM程序并烧录到STM32F407VET6设备的过程，使用HAL库和FreeRTOS，启用FinNAV LibROV

## 基本需求

### 硬件

* 一块FinNAV支持的SoC开发板/核心板
* 支持OpenOCD的烧录器和线缆
* 电脑

### 软件

**根据运行系统不同，FinNAV有不同的依赖**

* 64位Windows或Linux操作系统
* FinNAV SDK源码
* GNU/Make工具或其他兼容的Make工具
* 目标设备需要的交叉编译器（Cross Compiler）
* OpenOCD源码

### 安装依赖

FinNAV需要使用**make**工具来完成构建，并使用目标设备对应的**gcc**交叉编译器进行可执行文件的编译，基于**openocd**烧录可执行文件。FinNAV的构建系统采用Kconfig进行可视化配置，在Linux系统中需要使用本地gcc编译器对Kconfig源码进行编译；在Windows系统中使用时需要提前安装Python环境和**kconfig**-python包。如果用户本地没有FinNAV源码，还需要使用**git**工具从远端下载代码。如果用户希望在本地查看FinNAV库文档，可以选择安装**doxygen**工具导出API文档

因此，用户需要在使用前完成下列软件的安装，并添加到环境变量

* [git](https://git-scm.com/)
* make
* 本地编译器gcc
* 交叉编译器gcc
* [openocd](https://www.openocd.org/)
* [python](https://www.python.org/)
* [doxygen](https://www.doxygen.nl/)

在Linux下，只需要使用

```shell
sudo apt-get install git make gcc arm-none-eabi-gcc bison flex openocd doxygen
```

来安装基础软件依赖，完成简单配置后即可开始使用FinNAV

> arm-none-eabi-gcc是针对ARM嵌入式平台的交叉编译器，如果需要针对RV32平台进行交叉编译，需要安装riscv-none-embed-gcc

****

在Windows下，用户需要自行下载并安装以上提到的所有软件，推荐直接使用[MinGW](https://www.mingw-w64.org/downloads/)套件，通过内置的包管理器安装上述依赖

```shell
pacman -S git make gcc arm-none-eabi-gcc bison flex openocd doxygen python python-pip
```

您也可以直接通过上述软件提供的官网链接分开安装依赖软件

> Windows的Chocolatey工具或Cygwin也是可用的

安装完成后，使用下列指令安装Python包依赖

```shell
pacman -S install python3-setuptools python3-pip
```

请确保成功安装了`python`和`pip`，支持*python3.2+*；`pip`依赖`setuptools`，如果您采用离线安装的方式，还务必安装`setuptools`。随后可以使用下面的指令将pip升级到最新版本

```shell
pip3 install --upgrade pip
```

使用下列指令安装`Kconfig-python`依赖包

```shell
pip install kconfiglib
```

完成工具安装后才能在Windows下使用Kconfig图形化配置功能

### 下载源码

连接到**OurEDA内网**，使用

```shell
git clone http://nas.oureda.cn:8418/Redlight/FinNAV.git
```

来下载本项目的源码

完成后，使用

```shell
cd FinNAV
```

切换到**FinNAV根目录**。现在您已完成了FinNAV的所有基础配置

### 配置选项

在项目根目录使用指令

```shell
make menuconfig
```

进行图形化配置

Linux下，FinNAV使用Linux主线版本的Kconfig，会在第一次运行时自动进行编译；Windows下，FinNAV采用python的kconfiglib库运行menuconfig界面，因此二者的操作方式有所不同，可以参考界面内的操作说明。

> ![icon-caution](../pic_resources/icon-caution.gif) **Bug提示**
>
> 在Linux下，请不要直接选用RT-Thread，因为目前RT-Thread需要重新修改文件 `Kernel/RTT/components/net/lwip/Kconfig` 中的所有不兼容Linux主线kconfig语法的string类型才能正确完成menuconfig
>
> 比如将
>
> ```c
>     menu "Static IPv4 Address"
>             config RT_LWIP_IPADDR
>                 string "IPv4: IP address"
>                 default 192.168.1.30
> ```
>
> 改为
>
> ```c
>     menu "Static IPv4 Address"
>             config RT_LWIP_IPADDR
>                 string "IPv4: IP address"
>                 default "192.168.1.30"
> ```

完成配置后保存并退出menuconfig界面，生成的`.config`配置文件和`menuconfig.h`头文件保存在`build/target/kconfig`目录，FinNAV将在构建过程和代码中自动引用

> ![icon-tip](../pic_resources/icon-notice.gif) **如何选择默认配置选项**
>
> 在项目根目录使用参数`CONF=<默认配置选项文件名>`，例如
>
> ```shell
> make CONF=FinNAV_defconfig
> ```
>
> 默认配置选项文件来自于`build/configs`目录
>

### 编译

在项目根目录使用指令

```shell
make build
```

来进行全局编译，FinNAV支持`-j`选项以开启多核编译加速

也可以使用指令

```shell
make lib
```

单独编译**原厂外设驱动库**

使用

```shell
make librov
```

单独编译**FinNAV中间件**（**Lib-ROV**）

使用

```shell
make kernel
```

单独编译**嵌入式操作系统内核**

使用

```shell
make app
```

单独编译**应用程序**和**板级支持包**（**BSP**）

使用

```shell
make clean
```

可以**清除**当前项目的编译结果

使用

```shell
make clean-<subtarget>
```

可以清除单独某个编译节点的输出（静态库文件和目标文件）。可用的目标有`clean-app`、`clean-kernel`、`clean-librov`、`clean-lib`。

您可以

```shell
make CONF=FinNAV_defconfig
```

使用默认的`FinNAV_defconfig`配置文件编译FinNAV的示例工程

### 烧录设备

完成编译后就可以烧录了。将您的开发板/核心板通过调试线/调试器连接到PC，使用JTAG完成对设备的烧录。如果您基于本文档的说明采用默认的`FinNAV_defconfig`配置，则需要一块**stm32f407vet6开发板**，**要求其PC13连接到调试指示LED**

使用指令

```shell
make flash
```

执行烧录

> 如果要选择不同于刚刚编译好的可执行文件进行烧录，可以使用参数`FLASH_ELF=<目标二进制文件>`，例如
>
> ```shell
> make FLASH_ELF=<target_binary>.elf
> ```
>
> 可以使用的参数包括*FLASH_ELF*、*FLASH_BIN*、*FLASH_HEX*
