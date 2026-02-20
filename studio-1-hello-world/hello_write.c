// Swati Kumar
// February 17, 2026
// Hello World using write() system call

#include <unistd.h>

int main(int argc, char* argv[]) {
    const char message[] = "Hello, world!\n";
    write(STDOUT_FILENO, message,1000);
    return 0;
}

