#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void handle_sigint(int signum) {
    printf("Ignoring SIGINT\n");
}

int main() {
    signal(SIGINT, handle_sigint);

    pid_t pid = fork();

    if (pid == 0) {
        execl("./sleep", "sleep", NULL);
    } else {
        wait(NULL);
        printf("Successfully waited for child\n");
    }

    return 0;
}
