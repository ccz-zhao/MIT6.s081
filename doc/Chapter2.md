# Chapter 2: OS Organization and System call

使用操作系统的原因：
multiplexing and isolation

通过硬件实现强隔离性：
1. user/kernel mod
2. page table virtual memory

## 2.3 kernel organization

**宏内核(monolithic kernel)与微内核(micro kernel)**

宏内核：整个OS处于内核，所有system call在supervisor mode下执行。

微内核：最小化操作系统代码在supervisor mode的数量，大部分OS操作在user mode下。

优缺点：
宏内核：便于开发，不用考虑OS哪部分不需要全部权限；OS不同部分可以更容易合作。**缺点**：OS开发容易犯错，一旦在supervisor mode下出现error，会导致整个kernel失败，进而导致电脑停止工作，所有进程也随即停止，只能重启。

微内核：内核相对简单，**缺点**性能，更多的用户<->内核空间转换

## 2.5 Process overview

process: a unit of isolation

进程防止一个进程破坏或监视其他进程的内存，CPU，文件描述符等，并防止损坏内核。

进程抽象一个程序拥有自己私有的机器的假象，拥有其他进程无法读写的地址，仿佛拥有自己的CPU执行指令。

利用page table来将virtual address 映射到 physical address。

每个process拥有两个栈：user stack 和 kernel stack；用于user mode和supervisor mode 的执行。

## 2.6 Code: starting xv6, the first process and system call

RISC-V 电脑上电后，启动过程：

1. 运行bootloader。 运行保存在只读内存的 bootloader。BootLoader 将 xv6 的内核加载进内存，开始于地址 0x80000000。(0x0 : 0x80000000 地址范围包含了 I/O 设备) (**Q:**这部分是loader完成？)
2. 