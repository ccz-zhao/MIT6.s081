# Lab: Xv6 and Unix utilities

## 准备工具

[lab tools](https://pdos.csail.mit.edu/6.828/2021/tools.html)

环境：Ubuntu20.04

```bash
sudo apt-get install git build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu

```

Fetch the xv6 source for the lab and check out the util branch:

```bash
git clone git://g.csail.mit.edu/xv6-labs-2021
cd xv6-labs-2021
git checkout util
```

Build and run xv6:

```bash
make qemu
```

`Ctrl+p` 查看进程
`Ctrl+a x` 退出qemu

## Grading and hand-in procedure

### Sleep

>Implement the UNIX program sleep for xv6; your sleep should pause for a user-specified number of ticks. A tick is a notion of time defined by the xv6 kernel, namely the time between two interrupts from the timer chip. Your solution should be in the file user/sleep.c.

