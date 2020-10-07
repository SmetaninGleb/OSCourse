#include <stdlib.h>
#include <sys/resource.h>
#include <stdio.h>

int main() {
    int *ptr;
    struct rusage var;
    for (int i = 1; i <= 10; i++) {
        ptr = malloc(10 * 1024 * 1024);
        memset(ptr, 0, sizeof(ptr));
        getrusage(RUSAGE_SELF, &var);
        printf("%d\n", var.ru_maxrss);
        sleep(1);
    }
}