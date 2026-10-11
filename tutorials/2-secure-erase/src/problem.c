#include <string.h>
#include <unistd.h>

void process_password(void) {
    char password[32];

    if (read(STDIN_FILENO, password, sizeof(password)) > 0) {
        // Use the password ...
    }

    memset(password, 0, sizeof(password));
}

int main(void) {
    process_password();

    *(volatile int *) 0 = 0;  // Crash on purpose

    return 0;
}
