## [未完工]用C++来写STM32程序
## [Working]Use STM32 with C++
==============

C++的一些特性，例如对类、命名空间的运用，重载运算符等功能，如果运用在性能较高的单片机中，可以极大地增强程序的可读性，使设计更为简明迅速。大部分ARM处理器的开发环境都直接具备了编译C++的能力。而我手头上这块STM32F103RCT6开发板（ALIENTEK的MINI）在V3.5.0版的固件库中，加入了_CPLUSPLUS宏定义，相应的在建立基于库函数的工程时，只要把文件从*.c*变成*.cpp*即可。

目前的想法是建立小部分的库，简化一些常用的基本操作。

---------

#文件结构

>CORE(核心的cm3、startup)
>LIB
>>PPP(基本的片上外设，直接复制自3.5版的官方库)
>>PPPC(自己定义的外设，正在逐步完善)
>>OTH(常用外接器件，例如传感器)
>OBJ(输出hex文件)
>USER(工程文件存放处)

----------

#相关引用

延时函数使用了 ALIENTEK STM32开发板 的相关函数

------------

#开发环境

OS:Windows8.1
IDE:MDK-ARM.V5
LIB:STM32F10x_StdPeriph_Lib_V3.5.0

#Try to use some convenient features of C++ in buliding a ARM project
