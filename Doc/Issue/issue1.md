# FinNAV目录结构修改

在上个迭代中，初步确定Port组件和Driver组件统一作为FinNAV驱动框架。

在本迭代中，引入了统一编译框架，因此考虑将需要开发者移植时参与编写的Port组件移入FinNAV/Board目录，这样在SoC/板级移植时可以统一管理文件。FinNAV/FinNAV/Port/bsp目录会被删除，对应每个SoC的头文件（如FinNAV/FinNAV/Port/bsp/stm32f407vet/bsp_stm32f407vet.h）会被转移到FinNAV/Board/对应SoC/Port/目录下，由开发者自行处理。编译时，根据menuconfig中的soc target和bsp选项来决定使用哪份文件。

同时，Driver组件仍保留在FinNAV/FinNAV目录。