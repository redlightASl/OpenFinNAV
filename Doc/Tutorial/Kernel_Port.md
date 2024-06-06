# FinNAV RTOS内核移植

> ![icon-tip](../pic_resources/icon-tip.gif) 本文档将介绍如何为FinNAV移植一个不被支持的RTOS内核。

目前FinNAV支持如下RTOS内核

* FreeRTOS：一款开源RTOS，使用广泛，久经时间考验，但标准标不提供外设驱动框架
* LiteOS：一款国产的开源RTOS，具有相对较高的安全性和丰富的系统调用，提供不完整的外设驱动框架
* RT-Thread：一款国产的面向AIOT的开源RTOS，采用Linux-Like的代码与API风格，标准版提供整套外设/传感器驱动，但Lite版不提供这些支持

并采用CMSIS-RTOS来作为标准的RTOS系统调用接口。

尽管如此，若您认为上述内核无法满足自己的需求，也可以遵循本文档来快速适配一个新的RTOS内核。

## Kernel目录

FinNAV中，所有的RTOS内核源码都被放在 `Kernel` 目录下，您的新RTOS也应当被放在 `Kernel/<RTOS name>/` 目录下。

同时， `Kernel` 目录中还包含了一个Makefile，它用于管理编译RTOS内核源码的行为。适配者需要完成的主要工作就是将源码放在目录中，并修改Makefile。

主要需要修改的部分是 `prepare_<RTOS_name>` 目标和 `build_<RTOS_name>` 目标。前者负责编译前的准备工作，包括调用脚本下载源码、进行初始化配置（如果RTOS使用非Makefile工具链，您可能需要预备一个完整的配置文件用来对RTOS内核进行初始化）、获取预编译二进制文件等等。后者负责具体的构建工作。

一般地， `build_<RTOS_name>` 目标会调用 `$(LIB_TARGET)` 目标来完成生成工作，这个目标是FinNAV预定义的，通过 `$(call add_sources)` 函数来读入 `$(C_SOURCES)` 变量和 `$(ASM_SOURCES)` 变量代表的RTOS的C源文件和汇编源文件，并自动完成构建。因此，适配者可以编写定义这两个变量的*RTOS-spec Makefile*来让FinNAV完成构建编译工作

> [!WARNING]
>
> FinNAV强制这个Makefile命名为 `<RTOS_name>.mk`，并将其放置在 `build/target/rtos` 目录。
>
> 不过该文件仅作为menuconfig选取RTOS时使用，您仍可以将所有文件和变量声明在 `Kernel/Makefile` 内

## 编写Makefile

FinNAV中，目录 `build/target/rtos` 管理了所有RTOS的源文件编译规则。这些源文件在最后会被加入下列变量

```makefile
OS_SRC # C源文件
OS_INC # C头文件
OS_ASM # 汇编源文件
```

如果您要移植的RTOS包含外设驱动，那么它往往采用BSP-Driver-Application结构，即有一个BSP需要移植人员编写。那么您在移植到FinNAV时，还需要额外编写如下变量来将BSP单独添加待编译文件列表

```makefile
OS_BSP_SRC # BSP C源文件
OS_BSP_INC # BSP C头文件
```

此外，如果RTOS需要特殊的**编译指令**或**编译器传入的宏定义**才能工作，您可以在Makefile内添加如下变量

```makefile
OS_ASM_CFLAG # 特殊的汇编文件编译指令
OS_DEFS # 需要编译器传入的宏定义
```

最后，FinNAV支持CMSIS-RTOS作为兼容层，您也可以自行编写或采用RTOS自带的CMSIS-RTOS兼容文件，并在Makefile内添加如下变量

```makefile
CMSIS_RTOS_INC # CMSIS-RTOS兼容头文件
CMSIS_RTOS_SRC # CMSIS-RTOS兼容源文件
```

注意：FinNAV支持CMSIS-RTOS v1/v2/不使用，您可能需要使用到如下模板

```makefile
# CMSIS-RTOS support
ifeq ($(CMSIS_RTOS_VERSION),V1)
CMSIS_RTOS_INC :=
CMSIS_RTOS_SRC :=
else ifeq ($(CMSIS_RTOS_VERSION),V2)
CMSIS_RTOS_INC :=
CMSIS_RTOS_SRC :=
else ifeq ($(CMSIS_RTOS_VERSION),NO)
CMSIS_RTOS_INC :=
CMSIS_RTOS_SRC :=
endif
```
