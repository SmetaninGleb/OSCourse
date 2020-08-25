#include <stdio.h>
#include <string.h>

#define LEN 256

int main() {
	char str[LEN];
	fgets(str, LEN, stdin);
	for (int i = strlen(str) - 1; i >= 0; i--) {
		printf("%c", *(str+i));
	}
	return 0;
}
