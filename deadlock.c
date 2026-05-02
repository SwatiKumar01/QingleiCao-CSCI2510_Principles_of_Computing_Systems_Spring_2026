#include <stdio.h>
#include <stdlib.h>

#define MAX 15

int request[MAX][MAX];
int allocation[MAX];

// for tracking path
int parent_proc[MAX];
int parent_res[MAX];

void init() {
    for (int i = 0; i < MAX; i++) {
        allocation[i] = -1;
        parent_proc[i] = -1;
        parent_res[i] = -1;
        for (int j = 0; j < MAX; j++) {
            request[i][j] = 0;
        }
    }
}

// forward declarations
int search_process(int start, int current, int visited[]);
int search_resource(int start, int r, int visited[]);

void print_cycle(int start, int current) {
    int p = current;

    while (1) {
        int r = parent_proc[p];
        printf("PROCESS %d -> RESOURCE %d\n", p, r);

        int next_p = parent_res[r];
        printf("RESOURCE %d -> PROCESS %d\n", r, next_p);

        p = next_p;
        if (p == start) break;
    }
}

// DFS from process
int search_process(int start, int current, int visited[]) {
    if (visited[current]) return 0;
    visited[current] = 1;

    for (int r = 0; r < MAX; r++) {
        if (request[current][r]) {
            parent_proc[current] = r;

            if (search_resource(start, r, visited)) return 1;
        }
    }
    return 0;
}

// DFS from resource
int search_resource(int start, int r, int visited[]) {
    int holder = allocation[r];

    if (holder == -1) return 0;

    parent_res[r] = holder;

    if (holder == start) {
        print_cycle(start, start);
        return 1;
    }

    return search_process(start, holder, visited);
}

// acquire resource
void acquire(int p, int r) {
    if (allocation[r] == -1) {
        allocation[r] = p;
    } else {
        request[p][r] = 1;

        int visited[MAX] = {0};

        if (search_process(p, p, visited)) {
            exit(-1);
        }
    }
}

// release resource
void release(int p, int r) {
    if (allocation[r] != p) return;

    allocation[r] = -1;

    for (int i = 0; i < MAX; i++) {
        if (request[i][r]) {
            request[i][r] = 0;
            allocation[r] = i;

            int visited[MAX] = {0};

            if (search_process(i, i, visited)) {
                exit(-1);
            }
            break;
        }
    }
}

int main() {
    int p, r;
    char action;

    init();

    while (scanf("%d %c %d", &p, &action, &r) == 3) {
        if (action == 'a') {
            acquire(p, r);
        } else if (action == 'r') {
            release(p, r);
        }
    }

    return 0;
}
