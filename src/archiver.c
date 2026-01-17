#include "archiver.h"
#include "kutil.h"
#include <stdlib.h>

Archiver new_archiver(const char* src, const char* dist, const char* log_file, Output verbose, ArchiveType ar_t) {
    Archiver ar = { safe_strdup(src), safe_strdup(dist) , safe_strdup(log_file), verbose, ar_t};

    return ar;
}


void free_archiver(Archiver* ar) {
    free(ar->src);
    free(ar->dist);
    free(ar->log_file);
}