#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "install.h"
#include "archiver.h"
#include "kutil.h"
#include "path.h"
#include "unpack.h"
#include "errortype.h"



int check_is_amp(const char* file_name) {
    char** splited = split_string(file_name, '.');
    int len = 0;

    for(int i=0; splited[i] != NULL; i++) len++;

    if (strcmp(splited[len - 1], "amp") != 0) {
        free_str_array(splited);
        return 0;
    }

    free_str_array(splited);
    return 1;
}



int install_amp(char *src, InstallOptions options) {
    printf("installing: %s\n", src);
    if (!check_is_amp(src)) {
        fprintf(stderr, "File is not amp file!\n");
        return E_COMPARE;
    }

    char* dist = dist_path();
    Archiver ar = new_archiver(src, dist, options.verbose, AMP);

    if (unpack_archive(ar)) {
        fprintf(stderr, "Failed to unpack amp package!\n");
        fprintf(stderr, "Source: %s\n", src);
        free(dist);
        free_archiver(&ar);
        return E_INSTALL;
    }
    free_archiver(&ar);

    char* source_tar = format_string("%s/package/data.tar", dist);


    if (options.prefix == NULL) {
        options.prefix = "/";
    }
    Archiver ar_tar = new_archiver(source_tar, options.prefix, options.verbose, TAR);

    if (unpack_archive(ar_tar)) {
        fprintf(stderr, "Failed to unpack data.tar!\n");
        goto cleanup;
    }

    free_archiver(&ar_tar);
    free(source_tar);
    free(dist);

    printf("\x1b[1A\x1b[2K%s: done\n", src);

    return 0;

cleanup:
    free_archiver(&ar_tar);
    free(dist);
    free(source_tar);
    return E_INSTALL;
}







