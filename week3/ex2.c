#include <stdio.h>

void bubble_sort(int (*arr)[], int size);

int main() {
	printf("Enter size of the array \n");
	int n;
	scanf("%d", &n);
	int a[n];
	printf("\nEnter integer elements of the array \n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	bubble_sort(&a, n);
	printf("\nSorted array:\n");
	for (int i = 0; i < n; i++) {
		printf ("%d ", a[i]);
	}
	return 0;
}

void bubble_sort(int (*arr)[], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((*arr)[j] > (*arr)[j+1]) {
				int temp = (*arr)[j];
				(*arr)[j] = (*arr)[j+1];
				(*arr)[j+1] = temp;
			}
		}
	}
}
