#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Please, enter the size N for an array: ");
    scanf("%d", &n);
    int *arr = (int*) malloc(n*sizeof(int));
    // int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    free(arr);
    arr = NULL;
    return 0;
}