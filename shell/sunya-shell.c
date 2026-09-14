#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 256

int main(void) {
    char cmd[MAX_CMD_LEN];
    printf("Sunya Shell v0.1.0\n");
    while (1) {
        printf("sunya> ");
        fgets(cmd, MAX_CMD_LEN, stdin);
        cmd[strcspn(cmd, "\n")] = 0;
        if (strlen(cmd) == 0) continue;
        if (strcmp(cmd, "exit") == 0) break;
        system(cmd);
    }
    return 0;
}
