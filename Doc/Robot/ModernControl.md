# FinNAV 现代控制算法API

FinNAV提供一些常用现代控制算法的实现，包括 `ADRC` 、 `LADRC` 、 `卡尔曼滤波` 和 `LQR` 

## 自抗扰控制 ADRC

自抗扰控制（Active Disturbance Rejection Control，ADRC）是一种现代控制技术，能够在面对未知扰动和模型不确定性时提供更好的控制性能。它主要依赖三个核心构建：

* 跟踪微分器（Tracking Differentiator，**TD**）：用于安排过渡过程并给出合理的控制信号，解决响应速度和超调之间的矛盾
* 扩张状态观测器（Expanded State Observer，**ESO**）：用于估计和控制无模型的对象和外部扰动的状态，将系统内未建模部分和外部状态统一成扰动，从而实现补偿
* 非线性状态误差反馈律（Nonlinear State Error Feedback Law，**NLSEF**）：将包含微分量、积分量的误差反馈进行非线性组合，得到控制量

ADRC对于模型的依赖性较低，能够自适应地调节控制器参数从而实时估计补偿内外扰动

> 基于ADRC可以很好实现多旋翼无人机（一般视为二阶系统）姿态自稳和定高任务，增强机器人抵抗大风的能力



### 线性自抗扰控制 LADRC

TODO

## 卡尔曼滤波 Kalman Filter

TODO

### 一阶卡尔曼滤波

TODO

### 扩展卡尔曼滤波

TODO

## 线性二次型调节控制 LQR

TODO