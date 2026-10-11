#include <string.h>
#include <unistd.h>

void secure_erase(void *ptr, size_t len) {
    memset(ptr, 0, len);
    __asm__ volatile("" : : "r"(ptr) : "memory");
}

void process_password(void) {
    char password[32];

    if (read(STDIN_FILENO, password, sizeof(password)) > 0) {
        // Use the password ...
    }

    secure_erase(password, sizeof(password));
}

int main(void) {
    process_password();

    *(volatile int *) 0 = 0;  // Crash on purpose

    return 0;
}
