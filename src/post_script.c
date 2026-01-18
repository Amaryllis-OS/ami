#include <stdio.h>
#include <unistd.h>


#include "post_script.h"


int execute_post_install(const char* sh_file) {
    if (execl("/usr/bin/env", "sh", "-c", ".", sh_file, ";", "post_install") == -1) {
        perror("Failed to execute post-install script");
        return -1;
    }

    return 0;
}

