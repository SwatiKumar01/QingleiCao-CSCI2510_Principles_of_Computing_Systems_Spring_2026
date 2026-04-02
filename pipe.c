#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pipe(fd);

    int pid1 = fork();

    if (pid1 == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);

        char* cmd = "./print";
        char* args[] = {"print", NULL};
        execvp(cmd, args);
    }

    int pid2 = fork();

    if (pid2 == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);

        char* cmd = "./input";
        char* args[] = {"input", NULL};
        execvp(cmd, args);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
