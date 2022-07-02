## 环境安装问题

```console
gdb-multiarch : Depends: gdb (= 9.2-0ubuntu1~20.04.1) but 10.2-0ubuntu1~18.04~2 is to be installed
```

解决方法：

先卸载gdb，再重新安装gdb
```bash
sudo apt-get remove gdb
sudo apt install gdb
```