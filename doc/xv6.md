## xv6 代码结构

![](img/Screenshot%20from%202022-08-11%2010-25-53.png)

### 启动过程

[启动过程分析](https://blog.csdn.net/lhwhit/article/details/108164092)

RISC-V 电脑上电后，启动过程：

1. 运行bootloader。 运行保存在只读内存的 bootloader。BootLoader 将 xv6 的内核加载进内存，开始于地址 0x80000000。(0x0 : 0x80000000 地址范围包含了 I/O 设备) (**Q:**这部分是loader完成？) 见 [entry.S](../xv6-labs-2021/kernel/entry.S)的注释。 [kernel.ld](../xv6-labs-2021/kernel/kernel.ld) 
2. 设置一个栈用于运行 c 语言。见 [entry.S](../xv6-labs-2021/kernel/entry.S)，在 machine mode，跳转到 [start.c](../xv6-labs-2021/kernel/start.c) 的start 函数，start对环境进行必要的配置后通过mret 指令切换到监督模式，并执行main函数。
3. 运行[main.c](../xv6-labs-2021/kernel/main.c). 

### 代码阅读

