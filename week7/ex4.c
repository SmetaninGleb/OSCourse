#include <stdio.h>
#include <stdlib.h>

void* my_realloc(void *ptr, int new_size) {
    if (ptr == NULL) {
        ptr = malloc(new_size);
        return;
    }
    if (new_size <= 0) {
        free(ptr);
        return;
    }
    void *new_ptr = malloc(new_size);
    new_ptr = memcpy(new_ptr, ptr, new_size);
    free(ptr);
    ptr = new_ptr;
    return new_ptr;
}

int main() {
    int n;
    printf("Please, enter the size N of the array: ");
    scanf("%d", &n);
    int *arr = malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = 100;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nPlease, enter new size of the array: ");
    scanf("%d", &n);
    arr = my_realloc(arr, n*sizeof(int));
    for (int i = 0; i < n; i++) {
        printf ("%d ", arr[i]);
    }
    return 0;
}