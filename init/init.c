/*
 * Sunya Linux Init System
 * Language: C
 * Fast, minimal, low overhead boot
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define VERSION "0.1.0"

/* Reap zombie processes */
void reap_children(int sig) {
    (void)sig;
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

/* Mount essential filesystems */
void mount_essential(void) {
    printf("[sunya-init] Mounting essential filesystems...\n");
    system("mount -t proc proc /proc");
    system("mount -t sysfs sysfs /sys");
    system("mount -t devtmpfs devtmpfs /dev");
    printf("[sunya-init] Filesystems mounted.\n");
}

/* Start a service */
void start_service(const char *name, const char *path) {
    pid_t pid = fork();
    if (pid == 0) {
        execl(path, name, NULL);
        perror("execl");
        exit(1);
    } else if (pid < 0) {
        perror("fork");
    } else {
        printf("[sunya-init] Started service: %s (pid %d)\n", name, pid);
    }
}

int main(void) {
    printf("Sunya Linux Init v%s\n", VERSION);

    /* Handle zombie processes */
    signal(SIGCHLD, reap_children);

    /* Mount filesystems */
    mount_essential();

    /* Start essential services */
    start_service("syslogd", "/sbin/syslogd");
    start_service("udevd",   "/sbin/udevd");

    printf("[sunya-init] System ready.\n");

    /* Stay alive as PID 1 */
    while (1) {
        pause();
    }

    return 0;
}
