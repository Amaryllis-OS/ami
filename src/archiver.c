#include "archiver.h"
#include "kutil.h"
#include <stdlib.h>

/*
 * Creates a new Archiver instance with the specified source, destination, log file, verbosity, and archive type.
 * 
 * @param src The source path for the archiver.
 * @param dist The destination path for the archiver.
 * @param log_file The path to the log file.
 * @param verbose The verbosity level of the output.
 * @param ar_t The type of archive to create.
 * @return A new Archiver instance.
 */
Archiver new_archiver(const char* src, const char* dist, const char* log_file, Output verbose, ArchiveType ar_t) {
    Archiver ar = { safe_strdup(src), safe_strdup(dist) , safe_strdup(log_file), verbose, ar_t};

    return ar;
}

/*
 * Frees the memory allocated for the Archiver instance.
 * 
 * @param ar A pointer to the Archiver instance to free.
 */
void free_archiver(Archiver* ar) {
    free(ar->src);
    free(ar->dist);
    free(ar->log_file);
}