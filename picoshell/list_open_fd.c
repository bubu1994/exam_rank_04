#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//from chatgpt
void list_open_fds() {
    char path[256];
    char buf[1024];
    struct dirent *entry;
    DIR *dir;

    pid_t pid = getpid();

    snprintf(path, sizeof(path), "/proc/%d/fd", pid);

    dir = opendir(path);
    if (dir == NULL) {
        perror("Unable to open /proc/[pid]/fd");
        return;
    }

    printf("Open file descriptors for PID %d:\n", pid);
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(buf, sizeof(buf), "%s/%s", path, entry->d_name);

        ssize_t len = readlink(buf, buf, sizeof(buf) - 1);
        if (len != -1) {
            buf[len] = '\0';
            printf("FD %s -> %s\n", entry->d_name, buf);
        }
    }

    closedir(dir);
}