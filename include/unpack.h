#ifndef _UNPACK_H
#define _UNPACK_H
#include "archiver.h"

/**
 * Unpacks the specified archive using the provided Archiver configuration.
 * Extracts files from the archive to the destination directory, logging as specified.
 * @param ar The Archiver configuration containing source, destination, log file, verbosity, and archive type.
 * @return 0 on success, 1 on failure.
 */
int unpack_archive(Archiver ar);

#endif /* _UNPACK_H */