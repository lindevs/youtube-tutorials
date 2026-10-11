# Hello World Program Without libc on Linux

A C program that prints one line of text without the C standard library. No headers, no `printf`, no startup files.
What is left is `_start` and two syscalls, `write` and `exit`, called from inline assembly.

`-nostdlib` leaves out libc and the startup files, so the linker uses `_start` from `main.c` as the entry point instead
of the one `crt1.o` normally provides.

Tested on Ubuntu, x86-64, GCC. The syscall numbers (write = 1, exit = 60) are x86-64 specific - other architectures
use different numbers.

Video: https://youtu.be/6g0-eHmhsrw

## Compilation

* Compile the code:

```shell
gcc -nostdlib src/main.c -o test
```

* Run the program:

```shell
./test
```

Output:

```
Hello, no-libc world!
```

## Look inside the result

* No libraries are linked:

```shell
ldd test
```

* Only three functions, all defined in `main.c`:

```shell
nm test | grep ' T '
```

* The entry point is the address of `_start`:

```shell
readelf -h test | grep Entry
```
