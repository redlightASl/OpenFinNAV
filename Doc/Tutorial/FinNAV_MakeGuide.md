# FinNAV Make 功能用户手册

FinNAV使用**GNU Make**作为构建系统，使用Linux主线/kconfiglib库的**Kconfig**作为条件编译配置工具（在Windows系统下使用kconfiglib-python包进行条件编译配置）。用户可以跟随本文档了解make工具和menuconfig的使用方法。

## GNU Make

用户可以在本项目根目录启动make工具，通过利用下列make目标，用户可以根据特定需求和目标硬件配置高效地配置、构建、编程和测试基于FinNAV的项目。

> [!NOTE]
>
> 本节由AI辅助编写

### 环境设置

这些目标负责设置FinNAV SDK所需的工具、库及依赖项。

#### `freertos-prepare`, `liteos-prepare`, `rtt-prepare`

- 分别为FreeRTOS、华为LiteOS、RT-Thread实时操作系统进行准备。
- 运行相应脚本下载并对指定的RTOS进行预配置。

#### `gcc-prepare`

- 设置GCC编译器工具链。
- 运行`download_toolchain.sh`脚本下载工具链并安装到Toolchain目录。

#### `openocd-prepare`

- 设置OpenOCD调试与编程工具。
- 运行`download_openocd.sh`脚本下载工具链并安装到Toolchain目录。

### SDK配置

这些目标使用Kconfig系统对SDK的配置。

#### `menuconfig`

- 启动图形化交互配置工具（mconf）以修改Kconfig选项。
- 选择的选项存储在`.config`中，用于条件编译。
- 将自动运行gconf生成`menuconfig.h`文件供代码调用

#### `saveconfig`

- 将当前`.config`文件保存到`build/configs/<SAVE>`（默认值为`FinNAV_defconfig`）

#### `delmconf`

- 删除mconf工具链。这在对Kconfig源码进行更新时才有必要执行
- **如无必要请勿使用该选项**

#### `cleanconfig`

- 重置Kconfig配置。这将移除`.config`、`.config.old`、`include`目录以及`.last_conf`文件。

### 构建目标

这些目标针对SDK的不同组件执行各种构建操作。

#### `lib`

- 编译`Lib/main`目录中所有和`Boards`目录中部分的芯片厂商提供的通用外设库。

#### `cleanlib`

- 对外设库编译结果进行清理（移除目标文件和生成的库）。

#### `kernel`

- 编译位于`Kernel`目录的RTOS内核。

#### `cleankernel`

- 对RTOS内核进行清理（移除目标文件和生成的内核库）。

#### `librov`

- 编译FinNAV中间件（LibROV）。

#### `cleanlibrov`

- 对FinNAV中间件（LibROV）进行清理（移除目标文件和生成的LibROV库）。

#### `app`

- 编译位于`App`目录的应用程序。
- 此目标依赖于`lib`、`kernel`和`librov`，确保在构建应用程序前先构建这些组件。

#### `cleanapp`

- 对应用程序进行清理（移除目标文件和生成的应用程序二进制文件）。

#### `lib_test`

- 编译位于`Lib/test`的单元测试依赖库。

#### `run_ut`

- 运行所有单元测试。

#### `run_tb`

- 运行所有位于`Testbench`目录的实机测试（评估板台测）目标。

### 其他目标

#### `force`

- 打印详细的调试日志，包含各种环境变量和基础设置。
- **该选项仅用于开发调试**

#### `flash`, `debug`, `erase`, `dump_img`

- 使用OpenOCD执行底层编程与调试操作：
    - `flash`: 将编译好的可执行文件烧录到目标设备上。
    - `debug`: 启动GDB会话调试目标设备。
    - `erase`: 清除目标设备上的Flash内存。
    - `dump_img`: 将目标设备Flash内存的内容转储到文件。

#### `gen_doc`, `clean_doc`

- 使用**Doxygen**工具生成或清理API文档：
    - `gen_doc`: 在`Doc`目录下创建基于HTML/Latex的代码文档。
    - `clean_doc`: 移除生成的文档文件。

#### `sdkversion`

- 显示FinNAV SDK版本信息。

#### `help`

- 提供使用说明及可用目标及其参数的概览。

#### `clean`, `cleanall`

- 清理项目输出：
    - `clean`: 移除当前目标的输出目录`build/out/<活动目标>`。
    - `cleanall`: 移除`build/out`目录中的所有输出目录和文件。

## Menuconfig

本节旨在帮助用户理解并有效使用Kconfig系统来配置FinNAV SDK项目。Kconfig提供了丰富的选项集，使用户能够根据实际需求自定义项目属性，如目标应用名称、所选SoC系列、BSP支持包、RTOS内核、内存与闪存配置、工具链设定等。

> [!NOTE]
>
> 本节由AI辅助编写

### 全局配置

**Target Application name**

- `CONFIG_TARGET_APP`
    - 描述: 输入目标应用名称，默认为"f407_finnav"。
    - 操作: 根据实际项目更改为相应的应用名。

### 工具链配置

**Compiler Selection**

- `CONFIG_COMPILER_*`
    - 描述: 选择编译器类型，包括GNU C Compiler（gcc）、Arm C Compiler（armcc）或自定义编译器。
    - 默认: GNU C Compiler（gcc）

**Built-in Toolchain**

- `CONFIG_BUILTIN_TOOLCHAIN`
    - 描述: 选择是否使用FinNAV内置工具链。
    - 默认: 是（y）
    - 注意: 只有当未选择自定义编译器时该选项才可用。

**Debug Build**

- `CONFIG_COMPILE_DEBUG`
    - 描述: 选择是否编译为调试版本。
    - 默认: 是（y）
    - 注意: 只有当未选择自定义编译器时该选项才可用。

**Optimization Level**

- `CONFIG_COMPILE_OPT`
    - 描述: 设置编译优化级别。
    - 默认: `-Og`
    - 注意: 只有当未选择自定义编译器时该选项才可用。

**One ELF Section per Function**

- `CONFIG_COMPILE_ONE_SECTION_PER_FUNC`
    - 描述: 选择是否为每个函数生成独立的ELF节区。
    - 默认: 是（y）
    - 注意: 只有当未选择自定义编译器时该选项才可用。

**Standard C Library Usage**

- `CONFIG_COMPILE_NO_LIBC`
    - 描述: 选择是否不使用标准C库。
    - 默认: 否（n）
    - 注意: 只有当未选择自定义编译器时该选项才可用。

**Custom CFLAGS**

- `CONFIG_CFLAGS_CUSTOM`
    - 描述: 选择是否使用自定义CFLAGS。
    - 默认: 是（y）
    - 注意: 仅当选择自定义编译器时该选项才可用。

**OpenOCD Path**

- `CONFIG_OPENOCD_PATH`
    - 描述: 输入OpenOCD路径。

**Debugger Interface**

- `CONFIG_DEBUGGER_INTERFACE`
    - 描述: 选择调试器接口，默认为"cmsis-dap"。

**Flash Binary Type**

- `CONFIG_OPENOCD_FLASH_*`
    - 描述: 选择要烧写的二进制文件类型，包括.hex、.elf或.bin。
    - 默认: .hex

**Flash Speed**

- `CONFIG_OPENOCD_FLASH_SPEED`
    - 描述: 设置Flash烧写速度（单位kHz）。
    - 默认: 10000 kHz

### BSP配置

**SoC Family Selection**

- `CONFIG_TARGET_SOC_FAMILY_*`
    - 描述: 从FinNAV支持的SoC系列中选择目标SoC。
    - 默认: STM32F4

**Peripheral Library Standard**

- `CONFIG_TARGET_HAL_*`
    - 描述: 选择符合SoC的外设库标准，如HAL、标准库或直接操作寄存器。
    - 默认: HAL

**Target SoC Chip**

- `CONFIG_TARGET_SOC`
    - 描述: 输入目标SoC芯片型号，例如"STM32F407xx"。
    - 帮助: 确保选择一个支持的SoC。

**Target BSP Name**

- `CONFIG_TARGET_BSP`
    - 描述: 输入目标板级支持包（BSP）名称，例如"stm32f407_lite"。
    - 帮助: 确保选择一个已存在的BSP。

**SoC Features**

- `CONFIG_SOC_USE_*`
    - 描述: 根据SoC选择启用或禁用FPU、DSP、MPU、Cache（含ICache和DCache）。

**Oscillator Frequencies**

- `CONFIG_SOC_MAIN_OSC_VALUE`与`CONFIG_SOC_INNER_OSC_VALUE`
    - 描述: 设置外部主振荡器频率（默认25MHz）和内部RC振荡器频率（默认16MHz）。

**Board-Specific Features**

- `CONFIG_BSP_USE_*`
    - 描述: 根据实际需求启用或禁用USB OTG FS/HS、FATFS、lwIP、mbedTLS、OpenAMP等库支持。

### 内存与闪存配置

**External Storage Bootloader Support**

- `CONFIG_EXSBOOT`
    - 描述: 选择是否编译为支持外部存储启动加载器。

**RAM-Based Target Loading**

- `CONFIG_RAM_BASED`
    - 描述: 选择是否编译为目标加载到RAM中运行。

**Reserve Space for Custom Defaults**

- `CONFIG_CUSTOM_DEFAULTS_EXTENDED`
    - 描述: 选择是否预留空间存放自定义默认值。

**SoC Flash Size**

- `CONFIG_MCU_FLASH_SIZE`
    - 描述: 设置SoC闪存大小（以KBytes为单位）。
    - 默认: 512 KB

**Bootloader Base Address**

- `CONFIG_BOOTLOADER_BASE_ADDRESS`
    - 描述: 设置Bootloader基地址。
    - 默认: 0x08000000

**MultiBoot Bootloader Memory Address**

- `CONFIG_MULTIBOOT_MEM_ADDR`
    - 描述: 设置MultiBoot Bootloader内存地址。
    - 默认: 0x08100000

### RTOS内核配置

**RTOS Kernel Selection**

- `CONFIG_TARGET_RTOS_*`
    - 描述: 从无RTOS、FreeRTOS、LiteOS、RT-Thread中选择需要的一个。
    - 默认: FreeRTOS

**CMSIS-RTOS Version**

- `CONFIG_CMSIS_RTOS_VERSION_*`
    - 描述: 选择是否使用CMSIS-RTOS，并选择V1或V2版本。
    - 默认: CMSIS-RTOS V2

**Memory Pool Type**

- `CONFIG_RTOS_MEM_POOL_TYPE`
    - 描述: 确定RTOS内存池类型，默认为"heap_4"。

**FinNAV Configured RTOS**

- `FINNAV_*_CONFIG`
    - 描述: 选择是否由FinNAV系统配置FreeRTOS或RT-Thread。
    - 注意: 仅当选择对应RTOS内核时，这些选项才可用。

### LibROV配置

本文档没有收录LibROV的menuconfig配置，相关内容请参考LibROV的menuconfig文档
