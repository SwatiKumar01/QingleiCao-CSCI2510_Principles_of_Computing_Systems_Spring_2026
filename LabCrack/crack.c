#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <crypt.h>

int found = 0;
char target[100];
char salt[3];
int maxlen;

pthread_mutex_t lock;

typedef struct {
    int start;
    int end;
} ThreadData;

void check_word(char *word, struct crypt_data *data) {
    if(found) return;

    char *hash = crypt_r(word, salt, data);

    if(strcmp(hash, target) == 0) {
        pthread_mutex_lock(&lock);
        if(!found) {
            found = 1;
            printf("%s\n", word);
        }
        pthread_mutex_unlock(&lock);
    }
}

void brute(char *word, int pos, int len, struct crypt_data *data) {
    if(found) return;

    if(pos == len) {
        word[len] = '\0';
        check_word(word, data);
        return;
    }

    for(char c='a'; c<='z'; c++) {
        word[pos] = c;
        brute(word, pos + 1, len, data);
        if(found) return;
    }
}

void *worker(void *arg) {
    ThreadData *td = (ThreadData *)arg;
    struct crypt_data data;
    data.initialized = 0;

    char word[20];

    for(int len = 1; len <= maxlen && !found; len++) {
        for(int i = td->start; i < td->end && !found; i++) {
            word[0] = 'a' + i;

            if(len == 1) {
                word[1] = '\0';
                check_word(word, &data);
            } else {
                brute(word, 1, len, &data);
            }
        }
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    if(argc != 4) {
        printf("Usage: ./crack threads keysize target\n");
        return 1;
    }

    int threads = atoi(argv[1]);
    maxlen = atoi(argv[2]);
    strcpy(target, argv[3]);

    strncpy(salt, target, 2);
    salt[2] = '\0';

    pthread_t tid[threads];
    ThreadData data[threads];

    pthread_mutex_init(&lock, NULL);

    int chunk = 26 / threads;
    int current = 0;

    for(int i=0; i<threads; i++) {
        data[i].start = current;
        data[i].end = (i == threads - 1) ? 26 : current + chunk;
        current = data[i].end;

        pthread_create(&tid[i], NULL, worker, &data[i]);
    }

    for(int i=0; i<threads; i++)
        pthread_join(tid[i], NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}
