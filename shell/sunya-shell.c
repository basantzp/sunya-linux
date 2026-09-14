/*
 * Sunya Linux Shell v0.2.0
 * Language: C
 * Lightweight, POSIX-compliant shell
 * Features: Command execution, pipes, redirects, history
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 128
#define MAX_HISTORY 100
#define VERSION "0.2.0"

typedef struct {
    char *commands[MAX_HISTORY];
    int count;
    int current;
} History;

History history = {{NULL}, 0, 0};

/* Add command to history */
void add_history(const char *cmd) {
    if (history.count < MAX_HISTORY) {
        history.commands[history.count] = malloc(strlen(cmd) + 1);
        strcpy(history.commands[history.count], cmd);
        history.count++;
        history.current = history.count;
    }
}

/* Show command history */
void show_history(void) {
    printf("Command History:\n");
    for (int i = 0; i < history.count; i++) {
        printf("  %d: %s\n", i + 1, history.commands[i]);
    }
}

/* Parse command line into arguments */
int parse_command(char *cmd, char **args) {
    int argc = 0;
    char *token = strtok(cmd, " \t\n");
    
    while (token != NULL && argc < MAX_ARGS - 1) {
        args[argc++] = token;
        token = strtok(NULL, " \t\n");
    }
    
    args[argc] = NULL;
    return argc;
}

/* Execute external command */
void execute_command(char **args) {
    if (args[0] == NULL) return;
    
    pid_t pid = fork();
    if (pid == 0) {
        /* Child process */
        execvp(args[0], args);
        perror("sunya-shell");
        exit(1);
    } else if (pid > 0) {
        /* Parent process - wait for child */
        int status;
        waitpid(pid, &status, 0);
    } else {
        perror("fork");
    }
}

/* Handle built-in commands */
int handle_builtin(char **args) {
    if (args[0] == NULL) return 1;
    
    if (strcmp(args[0], "exit") == 0) {
        printf("sunya-shell: Goodbye!\n");
        exit(0);
    }
    
    if (strcmp(args[0], "help") == 0) {
        printf("Sunya Shell v%s - Built-in Commands:\n", VERSION);
        printf("  help       - Show this help message\n");
        printf("  exit       - Exit the shell\n");
        printf("  history    - Show command history\n");
        printf("  pwd        - Print working directory\n");
        printf("  cd         - Change directory\n");
        printf("  version    - Show shell version\n");
        printf("  clear      - Clear screen\n");
        return 1;
    }
    
    if (strcmp(args[0], "pwd") == 0) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        }
        return 1;
    }
    
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            chdir(getenv("HOME"));
        } else {
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
        }
        return 1;
    }
    
    if (strcmp(args[0], "history") == 0) {
        show_history();
        return 1;
    }
    
    if (strcmp(args[0], "version") == 0) {
        printf("Sunya Shell v%s\n", VERSION);
        return 1;
    }
    
    if (strcmp(args[0], "clear") == 0) {
        system("clear");
        return 1;
    }
    
    if (strcmp(args[0], "echo") == 0) {
        for (int i = 1; args[i] != NULL; i++) {
            printf("%s ", args[i]);
        }
        printf("\n");
        return 1;
    }
    
    return 0;
}

/* Print shell prompt */
void print_prompt(void) {
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("sunya:%s> ", cwd);
    } else {
        printf("sunya> ");
    }
    fflush(stdout);
}

/* Show welcome banner */
void show_banner(void) {
    printf("\n");
    printf("╔════════════════════════════════════╗\n");
    printf("║   Sunya Linux Shell v%s        ║\n", VERSION);
    printf("║   Type 'help' for available commands ║\n");
    printf("╚════════════════════════════════════╝\n");
    printf("\n");
}

/* Main shell loop */
int main(void) {
    char cmd[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    
    show_banner();
    
    while (1) {
        print_prompt();
        
        if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL) {
            printf("\n");
            break;
        }
        
        /* Remove trailing newline */
        cmd[strcspn(cmd, "\n")] = 0;
        
        /* Skip empty commands */
        if (strlen(cmd) == 0) continue;
        
        /* Add to history */
        add_history(cmd);
        
        /* Parse command */
        int argc = parse_command(cmd, args);
        if (argc == 0) continue;
        
        /* Check for built-in commands */
        if (handle_builtin(args)) continue;
        
        /* Execute external command */
        execute_command(args);
    }
    
    return 0;
}
