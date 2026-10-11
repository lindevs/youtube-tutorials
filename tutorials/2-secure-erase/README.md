# Securely Erase Secret Data from Memory in C

`problem.c` reads a password, uses it and wipes it with `memset`. In an optimized build the compiler removes that
`memset`: nothing reads the password afterward, so the compiler treats the zeros as a dead store. The password  stays in
memory and ends up in a crash dump.

`main.c` fixes it with `secure_erase`: a normal `memset` followed by an empty inline assembly barrier, which tells the
compiler the zeros may still be read. glibc builds `memset_explicit` and `explicit_bzero` the same way.

Both programs crash on purpose after the password is erased, so their memory can be saved to a file and searched.

Tested on Ubuntu, x86-64, GCC and Clang.

Video: https://youtu.be/tkYVdzk6YW8

## The problem

* Compile `problem.c` with optimization:

```shell
gcc -O3 src/problem.c -o test
```

* Run it in gdb with the password `secret123`, and save its memory when it crashes:

```shell
printf 'secret123' | gdb -batch -ex run -ex 'gcore crash_dump' ./test
```

* Search the crash dump for the password:

```shell
strings crash_dump | grep secret123
```

Output:

```
secret123
```

The `memset` did not erase it.

## The fix

* Compile `main.c` with the same optimization:

```shell
gcc -O3 src/main.c -o test
```

* Run it in gdb:

```shell
printf 'secret123' | gdb -batch -ex run -ex 'gcore crash_dump' ./test
```

* Search the crash dump again:

```shell
strings crash_dump | grep secret123
```

No output: the password is no longer in memory.

## Look at the assembly

* Write the assembly of both programs:

```shell
gcc -O3 -S src/problem.c -o problem.s
```

```shell
gcc -O3 -S src/main.c -o main.s
```

In `problem.s`, `process_password` calls `read` and returns, without writing a single zero. In `main.s`, the `memset`
is still there, turned into a few instructions that write zeros over the password.
