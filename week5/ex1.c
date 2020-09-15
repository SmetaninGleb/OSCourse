#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
    Before the fixing program it's threads could run independently and execution of a thread might be
    after not only creating but also after something in other threads.

    Also some moment about id of the first created thread. I do not know why it is not similar before the thread starts
    but I may assume that before creating the first thread thread's id is not defined. 
*/

void *func(int thread_number) {
    printf("This is the number of the thread: %d. This is the thread's id: %d. Goodbye!\n", thread_number, pthread_self());
    pthread_exit(NULL);
}

int main() {
    int thread_count;
    printf("Please, enter number of threads\n");
    scanf("%d", &thread_count);
    pthread_t thread_id;
    for (int thread_number = 0; thread_number < thread_count; thread_number++) {
        printf("The thread with the number %d and id %d is created\n", thread_number, (int) thread_id);
        pthread_create(&thread_id, NULL, &func, thread_number);
        pthread_join(thread_id, NULL);
    }

    pthread_exit(NULL);
    return 0;
}