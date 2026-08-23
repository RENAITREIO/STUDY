# 操作系统原理

## 绪论
### 操作系统定义
> Operating System: A body of software, in fact, that is responsible for making it easy to run programs (even allowing you to seemingly run many at the same time), allowing programs to share memory, enabling programs to interact with devices, and other fun stuff like that. (OSTEP)
### 发展历程
库函数批处理 -> 设备保护 -> 多程序调度 -> 资源虚拟化 -> 现代OS

### 软件视角
#### 最小程序 (JustForFun)
从`void _start()`开始，仅使用系统调用`write` `exit`实现 hello world 输出，并裁切多余节头，体积减少了将近90倍。
#### 系统调用指令：请求操作系统系统服务
syscall (x86-64), ecall (risc-v), svc (aarch64)\
只有它可以打破 “程序状态” (memory/register) 的边界
#### OS上的程序
- Applications
- Utilities
- Daemons
#### 操作系统中的任何程序
- 总是从被操作系统加载开始
    - 通过另一个进程执行 execve 设置为初始状态
- 经历状态机执行 (计算 + syscalls)
    - 进程管理：fork, execve, exit, …
    - 文件/设备管理：open, close, read, write, …
    - 存储管理：mmap, brk, …
- 最终调用 _exit (exit_group) 退出

应用程序 = 计算 + 操作系统 API

### 硬件视角
执行机器指令的状态机\
从 CPU Reset 开始执行，首先执行 **Firmware** 的代码
#### Firmware
厂商固定在计算机里的代码
- 完成硬件扫描，初始化和配置
- 不严格的说，加载操作系统

firmware 可以说就是一个小“操作系统”，初始化硬件，对接 Boot Loader

Legacy BIOS (Basic I/O System) -> UEFI (Unified Extensible Firmware Interface)

#### IBM PC/PC-DOS 2.0 (1983)
Firmware (BIOS) 会加载磁盘的前 512 字节到 0x7c00\
让我们试试：
```bash
(printf "\xeb\xfe"; cat /dev/zero | head -c 508; printf "\x55\xaa") > a.img
qemu-system-x86_64 a.img
```
qemu显示：Booting from Hard Disk.\
开头的`eb` `fe`是`jmp $-2`，跳转回自身，形成死循环\
结尾的`55` `aa`是 Boot Signature，表示这是一个合法的 Boot Sector

#### Grub 的例子
- Stage 1: 扫描磁盘，找到附近的 ELF 文件头，加载到内存
    - 根据文件系统，可能会需要 Stage 1.5
- Stage 2: 这个 ELF 文件是 Grub; 弹出熟悉的选择系统窗口
- Stage 3: 加载 Linux Kernel

## 虚拟化

## 并发

## 持久化
