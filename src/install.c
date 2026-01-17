#include <stdio.h>
#include <string.h>
#include "install.h"
#include "kutil.h"
#include "unpack.h"
#include "errortype.h"



int check_is_amp(const char* file_name) {
    char** splited = split_string(file_name, '.');
    int len = 0;

    for(int i=0; splited[i] != NULL; i++) len++;

    if (strcmp(splited[len], "amp") != 0) {
        free_str_array(splited);
        return 0;
    }

    free_str_array(splited);
    return 1;
}



int install_amp(const char *src) {
    if (!check_is_amp(src)) {
        fprintf(stderr, "File is not amp file!\n");
        return E_COMPARE;
    }

    Archiver ar = {.src = src, .dist = ""}

    return 0;
}







