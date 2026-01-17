#ifndef _INSTALL_H
#define _INSTALL_H
#include "archiver.h"

typedef struct {
    Output verbose;
    char* prefix;
} InstallOptions;

int install_amp(char* src, InstallOptions options);

#endif /* _INSTALL_H */