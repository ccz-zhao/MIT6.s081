## Chapter4 Traps and System calls

### 4.3 Code:Calling system calls

在内核中，用户是怎么调用 `exec` 系统调用的

`initcode.S` 将 `exec` 的参数放在寄存器 `a0` 和 `a1`，将系统调用号码放在 `a7`，系统调用号码匹配 `syscalls` 数组表，包含了函数指针（kernel/syscall.c:108）。 `ecall` 指令进入 kernel ，造成 `uservec` `usertrap`，然后执行`syscall`

syscall 从 a7 中取出调用号码，用来指定 syscalls。第一个系统调用包含了 `SYS_exec`，执行系统调用函数 sys_exec。

sys_exec 返回时，syscall 将返回值保存在 p->trapframe->a0。这样用户空间的exec() 就可以返回该值（RISC-V C调用返回值在寄存器 a0）。

### 4.4 Code:System call arguments

如何通过系统调用读取用户虚拟地址里的内容。