## 1.2 I/O and file descriptors

**关于IO重定向**：

使用fork()后，子进程会复制父进程的内存包括fd表，子进程可以重定向已存在的fd，而父进程中的不受影响，如：

```c
if (fork() == 0) {
    close(0);
    int fd = open("input.txt", O_RDONLY);
    exec("cat", argv);
}
```

fork()与exec() 分离设计，cat可以只实现标准IO的读取写入，而交给子进程来进行重定向。

dup()和fork()中文件的offset是共享的。

**2>&1**：

将文件描述符2定义为1的拷贝，这样输出到std err的信息也会重定向到 std out.

测试一下吧。

文件列表：
```console
.
└── exists
    └── found_exists
```

```bash
ls exists
ls nonexists
```

```bash
ls exists nonexists > out.txt 2>&1
cat out.txt
```

没加`2>&1`时，`out.txt`只会保存std out（正确执行的）

```console
$cat out.txt 
exists:
found_exists
```

添加重定向后，stderr也会一并保存

```console
$cat out.txt 
ls: cannot access 'nonexists': No such file or directory
exists:
found_exists
```