/*
 * Sunya Linux Init System v0.2.0
 * Language: C
 * Fast, minimal, low overhead boot
 * Features: Service management, filesystem mounting, signal handling
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <signal.h>
#include <dirent.h>

#define VERSION "0.2.0"
#define MAX_SERVICES 50
#define MAX_PATH_LEN 256

typedef struct {
    char name[MAX_PATH_LEN];
    char path[MAX_PATH_LEN];
    pid_t pid;
    int running;
} Service;

Service services[MAX_SERVICES];
int service_count = 0;

/* Signal handler for SIGCHLD - reap zombie processes */
void handle_sigchld(int sig) {
    (void)sig;
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        for (int i = 0; i < service_count; i++) {
            if (services[i].pid == pid) {
                printf("[sunya-init] Service %s (pid %d) terminated with status %d\n",
                       services[i].name, pid, WEXITSTATUS(status));
                services[i].running = 0;
                break;
            }
        }
    }
}

/* Signal handler for SIGTERM - graceful shutdown */
void handle_sigterm(int sig) {
    (void)sig;
    printf("[sunya-init] Received SIGTERM, initiating shutdown...\n");
    
    /* Stop all services */
    for (int i = 0; i < service_count; i++) {
        if (services[i].running) {
            printf("[sunya-init] Stopping service: %s (pid %d)\n",
                   services[i].name, services[i].pid);
            kill(services[i].pid, SIGTERM);
        }
    }
    
    /* Unmount filesystems */
    printf("[sunya-init] Unmounting filesystems...\n");
    umount("/proc");
    umount("/sys");
    umount("/dev");
    
    printf("[sunya-init] System halted.\n");
    exit(0);
}

/* Mount essential filesystems */
void mount_essential(void) {
    printf("[sunya-init] Mounting essential filesystems...\n");
    
    if (mount("proc", "/proc", "proc", 0, NULL) == 0) {
        printf("[sunya-init] ✓ /proc mounted\n");
    }
    
    if (mount("sysfs", "/sys", "sysfs", 0, NULL) == 0) {
        printf("[sunya-init] ✓ /sys mounted\n");
    }
    
    if (mount("devtmpfs", "/dev", "devtmpfs", 0, NULL) == 0) {
        printf("[sunya-init] ✓ /dev mounted\n");
    }
    
    printf("[sunya-init] Essential filesystems mounted.\n");
}

/* Set up signal handlers */
void setup_signals(void) {
    signal(SIGCHLD, handle_sigchld);
    signal(SIGTERM, handle_sigterm);
    printf("[sunya-init] Signal handlers installed.\n");
}

/* Start a service */
void start_service(const char *name, const char *path) {
    if (service_count >= MAX_SERVICES) {
        fprintf(stderr, "[sunya-init] Error: Too many services\n");
        return;
    }
    
    pid_t pid = fork();
    if (pid == 0) {
        /* Child process */
        execl(path, name, NULL);
        perror("[sunya-init] execl failed");
        exit(1);
    } else if (pid > 0) {
        /* Parent process */
        strncpy(services[service_count].name, name, MAX_PATH_LEN - 1);
        strncpy(services[service_count].path, path, MAX_PATH_LEN - 1);
        services[service_count].pid = pid;
        services[service_count].running = 1;
        printf("[sunya-init] Started service: %s (pid %d)\n", name, pid);
        service_count++;
    } else {
        perror("[sunya-init] fork failed");
    }
}

/* Load services from directory */
void load_services(const char *service_dir) {
    printf("[sunya-init] Loading services from %s...\n", service_dir);
    
    DIR *dir = opendir(service_dir);
    if (!dir) {
        printf("[sunya-init] Warning: Could not open service directory: %s\n", service_dir);
        return;
    }
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char path[MAX_PATH_LEN];
            snprintf(path, MAX_PATH_LEN, "%s/%s", service_dir, entry->d_name);
            start_service(entry->d_name, path);
        }
    }
    
    closedir(dir);
}

/* Show system information */
void show_info(void) {
    printf("\n");
    printf("╔════════════════════════════════════╗\n");
    printf("║   Sunya Linux Init System v%s  ║\n", VERSION);
    printf("╚════════════════════════════════════╝\n");
    printf("\n");
}

/* Main init process */
int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    
    show_info();
    
    /* Mount essential filesystems */
    mount_essential();
    
    /* Set up signal handlers */
    setup_signals();
    
    /* Load and start services */
    printf("[sunya-init] Starting services...\n");
    start_service("syslogd", "/sbin/syslogd");
    start_service("udevd", "/sbin/udevd");
    
    printf("[sunya-init] System initialization complete.\n");
    printf("[sunya-init] Waiting for services...\n\n");
    
    /* Stay alive as PID 1 */
    while (1) {
        pause();
    }
    
    return 0;
}
