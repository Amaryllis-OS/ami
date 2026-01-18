#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "path.h"
#include "kutil.h"


/**
 * Checks if the specified file or directory exists.
 * @param path The path to check for existence.
 * @return 1 if the file or directory exists, 0 otherwise.
 */
int check_exists(const char* path) {
    FILE* file = fopen(path, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0; 
}

/**
 * Returns the path to the distribution directory, creating it if necessary.
 * The returned string should be freed by the caller after use.
 * @return The path to the distribution directory, or NULL on failure.
 */
char* dist_path() {
    if (!check_exists("/tmp/ami_dist")) {
        if (mkdir("/tmp/ami_dist", S_IRWXU)) {
            perror("Failed to create base path directory");
            return NULL;
        }
    }

    char* pkginstall_path = format_string("%s/pkginstall", "/tmp/ami_dist");
    if (!check_exists(pkginstall_path)) {
        if (mkdir(pkginstall_path, S_IRWXU)) {
            perror("Failed to create pkginstall directory");
            free(pkginstall_path);
            return NULL;
        }
    }
    return pkginstall_path;
}



