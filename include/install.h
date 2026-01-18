#ifndef _INSTALL_H
#define _INSTALL_H
#include "archiver.h"

typedef struct {
    Output verbose;
    char* prefix;
    char* installed_file;
    int post_script;
} InstallOptions;

/**
 * Installs an amp package from the given source path with the specified options.
 * Extracts the amp archive, unpacks its contents, and installs files to the target location.
 * @param src The path to the amp package file.
 * @param options The installation options (verbosity, prefix, installed file path).
 * @return 0 on success, non-zero error code on failure.
 */
int install_amp(char* src, InstallOptions options);

#endif /* _INSTALL_H */