#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "path.h"
#include "kutil.h"


int check_exists(const char* path) {
    FILE* file = fopen(path, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0; 
}

/** Returns the path to the distribution directory, creating it if necessary.
** please free the returned string after use.
 */
char* dist_path() {
    if (!check_exists(BASE_PATH)) {
        if (mkdir(BASE_PATH, S_IRWXU)) {
            perror("Failed to create base path directory");
            return NULL;
        }
    }

    char* pkginstall_path = format_string("%s/pkginstall", BASE_PATH);
    if (!check_exists(pkginstall_path)) {
        if (mkdir(pkginstall_path, S_IRWXU)) {
            perror("Failed to create pkginstall directory");
            free(pkginstall_path);
            return NULL;
        }
    }

    return pkginstall_path;
}



