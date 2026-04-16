#include <stdio.h>
#include <pthread.h>
#include <string.h>

struct thread_args
{
    int arg1;
    char arg2[100];
    int ret;
};

void* thread_entry(void* args)
{
    struct thread_args* arg_ptr = (struct thread_args*) args;

    printf("Thread %d says: %s\n", arg_ptr->arg1, arg_ptr->arg2);

    arg_ptr->ret = arg_ptr->arg1 * 10;

    return NULL;
}

int main()
{
    int i;
    int num_threads = 5;

    pthread_t tids[5];
    struct thread_args args[5];

    for(i = 0; i < num_threads; i++)
    {
        args[i].arg1 = i;
        snprintf(args[i].arg2, 100, "This is thread %d", i);
        args[i].ret = 0;

        pthread_create(&tids[i], NULL, thread_entry, &args[i]);
    }

    for(i = 0; i < num_threads; i++)
    {
        pthread_join(tids[i], NULL);
        printf("Main got ret from thread %d = %d\n", i, args[i].ret);
    }

    return 0;
}
