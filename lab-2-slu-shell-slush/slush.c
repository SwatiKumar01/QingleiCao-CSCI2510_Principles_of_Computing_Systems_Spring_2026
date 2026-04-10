//SLUSH - The SLU SHELL
//
//This assignment reads user input, and executes that input as a sequence of
//programs to execute.
//
//Program execution commands have the form:
//
//prog_n [args] ( ... prog_3 [args] ( prog_2 [args] ( prog_1 [args]
//
//For example, "grep slush ( sort -r ( ls -l -a" returns a reverse sorted list
//of all files in the current directory that contain the string "slush" in
//
//See the lab writeup for more details and other requirements.
// SLUSH - The SLU SHELL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 256

int main() {
    char line[MAX_LINE];

    while (1) {
        printf("slush> ");
        fflush(stdout);

        
        if (fgets(line, MAX_LINE, stdin) == NULL) {
            printf("\n");
            break; // EOF (Ctrl+D)
        }

        
        line[strcspn(line, "\n")] = 0;

        if (strlen(line) == 0) continue;

        
        if (strncmp(line, "cd ", 3) == 0) {
            char *dir = line + 3;
            if (chdir(dir) != 0) {
                perror("cd failed");
            }
            continue;
        }

        
        char *commands[10];
        int count = 0;

        char *token = strtok(line, "(");
        while (token != NULL) {
            while (*token == ' ') token++; // trim spaces
            commands[count++] = token;
            token = strtok(NULL, "(");
        }

        
        if (count == 1) {
            pid_t pid = fork();

            if (pid == 0) {
                char *args[16];
                int i = 0;

                char *token = strtok(commands[0], " ");
                while (token != NULL && i < 15) {
                    args[i++] = token;
                    token = strtok(NULL, " ");
                }
                args[i] = NULL;

                execvp(args[0], args);
                perror(args[0]);
                exit(1);
            } else {
                wait(NULL);
            }
        }

        
        else {
            int i;
            int fd[2];
            int prev_fd = -1;

            for (i = 0; i < count; i++) {
                pipe(fd);

                if (fork() == 0) {
                    // Input from previous pipe
                    if (prev_fd != -1) {
                        dup2(prev_fd, 0);
                        close(prev_fd);
                    }

                    // Output to next pipe
                    if (i < count - 1) {
                        dup2(fd[1], 1);
                    }

                    close(fd[0]);

                    char *args[16];
                    int j = 0;

                    char *token = strtok(commands[i], " ");
                    while (token != NULL && j < 15) {
                        args[j++] = token;
                        token = strtok(NULL, " ");
                    }
                    args[j] = NULL;

                    execvp(args[0], args);
                    perror(args[0]);
                    exit(1);
                }

                close(fd[1]);
                if (prev_fd != -1) close(prev_fd);
                prev_fd = fd[0];
            }

            for (i = 0; i < count; i++) {
                wait(NULL);
            }
        }
    }

    return 0;
}