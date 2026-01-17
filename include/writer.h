#ifndef _INTERNAL_WRITE_H
#define _INTERNAL_WRITE_H
#include <stdio.h>

typedef struct {
    FILE* fp;
    char* context;
} Writer;

/**
 * Opens an existing file for reading and writing, and initializes a Writer structure.
 * @param path The path to the file to open.
 * @return A Writer structure for the opened file.
 */
Writer w_open(const char* path);
/**
 * Creates a new file for writing and initializes a Writer structure.
 * @param path The path to the file to create.
 * @return A Writer structure for the created file.
 */
Writer w_create(const char* path);

/**
 * Appends a string to the Writer's context buffer.
 * @param wt Pointer to the Writer structure.
 * @param str The string to append.
 * @return 0 on success, -1 on allocation failure.
 */
int w_add_string(Writer* wt, const char* str);

/**
 * Writes the context buffer to the file associated with the Writer.
 * @param wt Pointer to the Writer structure.
 */
void w_flush_write(Writer* wt);

/**
 * Frees the memory used by the Writer's context and closes the file.
 * @param wt Pointer to the Writer structure to free.
 */
void w_free_writer(Writer* wt);

#endif /* _INTERNAL_WRITE_H */

