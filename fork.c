#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid = fork();

    if (pid == 0) {
        char* child_argv[] = {"ls", "-l", NULL};
        char* child_prog = child_argv[0];

        execvp(child_prog, child_argv);
    } else {
        waitpid(pid, NULL, 0);
        printf("Parent PID: %d\n", getpid());
    }

    return 0;
}
