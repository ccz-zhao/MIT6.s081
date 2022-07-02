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