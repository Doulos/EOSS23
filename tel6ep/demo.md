### How to compile 
Assuming a Linux dev box, just run `make` at the ``tel6ep`` directory.
```console
cd tel6ep
make
```
If you want to cross compile for your target, configure first your toolchain.
The makefile assumes that the toolchain sets $CC. Below an example, using a SDK generated by yocto:
```console
source /opt/DwEL/poky/qemu/2.3.3/environment-setup-armv5e-poky-linux-gnueabi
make
```

### Running the demo
#### demo1/hello
We can use `strace` to figure out why the thread doesn't seem to start:
```console
strace -f ./hello
```
The next step is to use man (on the dev machine) to check what is calling `exit_group`.
The issue shown here results of:
- `main()` and `hello_eoss` thread, which run concurrently.
- returning from `main()`, which calls `exit()` causing all the threads of execution to terminate.

The C-runtime libary call `main()` as follows: ```exit(main(argc, argv, envp))```. This behaviour was implemented on Unix before threads existed, and has been retained for backward compatibility.

#### demo2/stack-overflow
The binary `stack-overflow` will pause until you type ENTER. Only then, the recursion starts until it overflows the stack. Prior to starting the test, you can run pmap in another terminal to check the process virtual memory mapping:
```console
pmap -x `pidof stack-overflow`
```

#### demo3/rt-drink
To trigger the bug, press Ctrl-C continuously. Depending on the target machine, it might be difficult to get the "right timing" to trigger the bug. 
In this case, you might want to "hammer" the program with SIGINT from another shell using a command similar to:
```console
while (true); do kill -s INT `pidof rt-drink`; done 
```
Once you manage to deadlock the program, you can either use strace or gdb from another shell to investigate the problem using `strace` or `gdb`

### Using grepai 
[<img src="./ai_meme.jpg" height="250" align="right"/>](ai_meme.jpg)
To use grepai on the musl source, simply:
- source grepai
- go to the top musl source directory
- ask grepai.

So far, we have hard-coded answer for demo1/hello and demo3/rt-drink
```console
grepai "who is calling exit_group?"
grepai "why does printf deadlock in signal handler?"
```
Tested with musl v1.2.4.