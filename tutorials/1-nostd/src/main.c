void print(const char* msg) {
    long len = 0;
    while (msg[len]) {
        ++len;
    }

    // Syscall: write(1, msg, len)
    __asm__ volatile (
        "movq $1, %%rax\n"    // syscall: write
        "movq $1, %%rdi\n"    // fd: stdout
        "movq %0, %%rsi\n"    // buf
        "movq %1, %%rdx\n"    // count
        "syscall\n"
        :
        : "r"(msg), "r"(len)
        : "%rax", "%rdi", "%rsi", "%rdx"
    );
}

int main(void) {
    print("Hello, no-libc world!\n");

    return 0;
}

void _start(void) {
    int retval = main();

    // Exit syscall: syscall number 60, exit code in rdi
    __asm__ volatile (
        "movq $60, %%rax\n"   // syscall number for exit
        "movq %0, %%rdi\n"    // exit code
        "syscall\n"
        :
        : "r" ((long)retval)
        : "%rax", "%rdi"
    );
}
