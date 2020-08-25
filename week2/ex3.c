#include <stdio.h>

int main(int argc, char *argv[]) {
	int n;
	sscanf(argv[1], "%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= 2*n-1; j++) {
			if (j > n-i && j < n+i) {
				printf("*");
			} else {
				printf(" ");
			}
		}
		if (i < n) {
			printf("\n");
		}
	}
	return 0;
}
