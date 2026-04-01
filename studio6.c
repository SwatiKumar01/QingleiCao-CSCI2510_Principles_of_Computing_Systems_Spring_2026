#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    char input_string[100];

    printf("Enter input: ");
    fgets(input_string, sizeof(input_string), stdin);

    input_string[strcspn(input_string, "\n")] = '\0';

    int max_args = 15;
    int max_argv_size = max_args + 2;
    char* cmd;
    char* my_argv[max_argv_size];

    cmd = strtok(input_string, " ");

  
    my_argv[0] = cmd;

    int i = 1;
    char* res;

    while ((res = strtok(NULL, " ")) != NULL) {
        my_argv[i] = res;
        i++;
    }


    my_argv[i] = NULL;


    execvp(cmd, my_argv);

    return 0;
}