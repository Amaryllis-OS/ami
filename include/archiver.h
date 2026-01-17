#ifndef _ARCHIVER_H
#define _ARCHIVER_H

typedef enum {
    AMP,
    TAR,
} ArchiveType;

typedef enum {
    VERBOSE,
    NORMAL,
    SILENT,
} Output;

typedef struct {
    char* src;
    char* dist;
    char* log_file;
    Output verbose;
    ArchiveType ar_t;
} Archiver;



/**
 * Creates a new Archiver instance with the specified parameters.
 * @param src The source path for the archiver.
 * @param dist The destination path for the archiver.
 * @param log_file The path to the log file.
 * @param verbose The verbosity level of the output.
 * @param ar_t The type of archive to create.
 * @return A new Archiver instance.
 */
Archiver new_archiver(const char* src, const char* dist, const char* log_file, Output verbose, ArchiveType ar_t);

/**
 * Frees the memory allocated for the Archiver instance.
 * @param ar A pointer to the Archiver instance to free.
 */
void free_archiver(Archiver* ar);


#endif /* _ARCHIVER_H */