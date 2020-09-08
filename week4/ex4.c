#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>

int main() {
    char command[] = "";
    printf("Terminal:\n");
    while (strcmp(command, "exit")) {
        printf("> ");
        scanf("%s", &command);
        system(command);
    }
    system(command);
}