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
    Output verbose;
    ArchiveType ar_t;
} Archiver;



Archiver new_archiver(const char* src, const char* dist, Output verbose, ArchiveType ar_t);

void free_archiver(Archiver* ar);


#endif /* _ARCHIVER_H */