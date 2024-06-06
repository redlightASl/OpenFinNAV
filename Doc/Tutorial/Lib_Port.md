# FinNAV 原厂外设库移植

> ![icon-tip](../pic_resources/icon-tip.gif) 本文档将介绍如何为FinNAV移植一个不被支持的外设库。

目前FinNAV支持如下外设库类型

* **HAL**：硬件抽象层（Hardware Abstract Layer），原厂SDK或外设抽象类库都属于HAL层次，以更低的运行效率换取更高的开发效率，往往能用来实现很复杂的功能
* **STDPERIPH**：标准外设库（Standard Peripheral Lib），最标准的嵌入式外设库，具有平衡的运行效率和开发效率，如果您希望使用标准外设库实现网络驱动这样的复杂功能，往往会耗费大量的开发时间
* **REGISTER**：寄存器直接映射（Register Direct Map），最低层次的API，如果您希望适配一个运行效率最高的驱动，那就可以使用它

> [!WARNING]
>
> 一般而言，推荐用户使用HAL和STDPERIPH，这样能发挥出FinNAV函数库的最大性能——使用到寄存器直接映射API的设备往往受到内存和NVM容量限制，需要关闭大量FinNAV内置功能才可以使用。

在您将一个新的SoC及其工具链移植到FinNAV后，一般都需要适配一套原厂提供的外设库，您可以选择一种大致符合您需求且在上述三种外设库涵盖内的原厂库，遵循本文档来快速适配一个新的外设库

## Lib目录

FinNAV中，所有的SoC外设库源码都被放在 `Lib` 目录下。Lib目录下有两个子目录：

* main目录：存放外设库源文件
* test目录：存放单元测试（unit test）所需的GTest库和外设库Mock文件，以及测试样例

这里先只讨论main目录中的内容。您应该将外设库整理后放置到 `Lib/main/<SoC Family Lib>/` 目录中。同时， `Lib` 目录中还包含了一个Makefile，用于管理编译SoC外设库源码的行为。适配者需要完成的主要工作就是将源码放在目录中，并修改Makefile。

该Makefile包含一个主要目标**build**，它通过自动执行目标 `$(LIB_TARGET)` 来构建外设库目标文件和静态库文件。这个目标是FinNAV预定义的，通过 `$(call add_sources)` 函数来读入 `$(C_SOURCES)` 变量和 `$(ASM_SOURCES)` 变量代表的RTOS的C源文件和汇编源文件，并自动完成构建。

> `$(call add_sources)` 所执行的函数位于 `build/libtarget.mk` 文件中，需要的移植者可以自行查看

需要注意，`$(C_SOURCES)` 自动包含了下列变量

```makefile
SOC_HEADER_SRC # SoC外设库核心源文件列表
SOC_PERIPHERAL_LIB_SRC # SoC外设库源文件列表
THIRD_PARTY_LIB_SRC # 第三方库列表
```

`$(ASM_SOURCES)` 变量自动包含了下列变量

```makefile
BOOTLOADER_SRC # Bootloader文件列表
```

同时，用户还需要额外定义下列头文件变量

```makefile
CORE_SUPPORT_INC
SOC_HEADER_INC
SOC_PERIPHERAL_LIB_INC
$(TARGET_HAL)_CONF_INC
```

## 关键变量概述

下面依次说明上述变量的含义

* `$(SOC_HEADER_SRC)` ：某个系列SoC（Family）的共用源文件列表
* `$(SOC_HEADER_INC)` ：某个系列SoC（Family）的共用头文件列表
* `$(SOC_PERIPHERAL_LIB_SRC)` ：某个系列SoC（Family）的普通源文件列表，外设库中的功能函数都在这些源文件里定义
* `$(SOC_PERIPHERAL_LIB_INC)` ：某个系列SoC（Family）的普通头文件列表
* `$($(TARGET_HAL)_CONF_INC)` ：原厂外设库的配置头文件，用于对外设库的子模块进行选择性编译
* `$(BOOTLOADER_SRC)` ：SoC的启动文件，该文件应当是汇编文件
* `$(CORE_SUPPORT_INC)` ：SoC内核支持头文件，这个文件通常是CPU内核IP维护者提供（比如ARM的CMSIS-Core）
* `$(THIRD_PARTY_LIB_SRC)` ：第三方库文件，如果您的应用中使用到了诸如FatFS、lwIP等库，就需要在这里填写库的源文件目录。**在目前的版本中，FinNAV无法自动管理源文件和头文件列表**

## 在SoC Target Makefile中进行移植

上述的变量都应当写入一个核心Makefile，并将其放入 `build/target/soc` 目录，从而让FinNAV可以自动找到目标

> [!WARNING]
>
> FinNAV强制这个Makefile命名为 `<SoC_target>.mk` ，否则FinNAV将无法找到目标文件，也就不能进行构建

如果您需要更多内容参考，可使用 `build/target/soc/Template.mk` 文件模板，并参考其他SoC移植文件

## 如果需要移植单元测试

> [!NOTE]
>
> TODO

## 使用原厂DSP库或预编译的其他原厂库文件

您可以在 `build/target/soc/Template.mk` 中看到如下代码

```makefile
DSP_LIB_INC :=
DSP_LIB_SRC :=
DSP_LIB_STATIC :=
DSP_LIB :=
```

这是为原厂DSP库预留的接口。如果您需要使用原厂的DSP库或其他预编译好的原厂库文件，可以直接将其路径写入变量。

* `DSP_LIB_INC`和`DSP_LIB_SRC`：DSP头文件和源文件路径。由于一般的DSP库都非常庞大，需要额外的编译时间，因此推荐直接使用原厂提供编译好的静态库，不推荐从源文件构建
* `DSP_LIB_STATIC` ：原厂提供编译好的静态库文件搜索路径
* `DSP_LIB` ：原厂提供编译好的静态库文件名称

## 更多SDK功能

如果您要适配一个复杂的SDK，甚至是不兼容Makefile构建的SDK（比如基于CMake的架构），推荐您直接修改 `Lib/main/Makefile` 中的目标，使用原厂提供的构建工具预编译SDK的静态库，并在链接阶段将其与FinNAV链接到一起——这需要大量修改Makefile。

为避免麻烦，不推荐在复杂的SDK中使用FinNAV的构建框架，而是只使用FinNAV的

```shell
make menuconfig
make librov
```

编译出带有需要功能的*librov.a*静态库，并将其作为子模块添加到SDK中

