#include "writer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kutil.h"

/**
 * Opens an existing file for reading and writing, and initializes a Writer structure.
 * @param path The path to the file to open.
 * @return A Writer structure for the opened file.
 */
Writer w_open(const char* path)
{
    FILE* fp = fopen(path, "r+");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    Writer wt = { .context = format_string(""), .fp = fp };
    return wt;
}

/**
 * Creates a new file for writing and initializes a Writer structure.
 * @param path The path to the file to create.
 * @return A Writer structure for the created file.
 */
Writer w_create(const char* path)
{
    FILE* fp = fopen(path, "w+");

    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    Writer wt = { .context = format_string(""), .fp = fp };
    return wt;
}

/**
 * Appends a string to the Writer's context buffer.
 * @param wt Pointer to the Writer structure.
 * @param str The string to append.
 * @return 0 on success, -1 on allocation failure.
 */
int w_add_string(Writer* wt, const char* str)
{
    char* old = safe_strdup(wt->context);
    if (old == NULL) {
        fprintf(stderr, "Allocate failed: safe_strdup");
        return -1;
    }

    free(wt->context);

    wt->context = format_string("%s%s", old, str);
    free(old);

    return 0;
}

/**
 * Writes the context buffer to the file associated with the Writer.
 * @param wt Pointer to the Writer structure.
 */
void w_flush_write(Writer* wt)
{
    fputs(wt->context, wt->fp);
    return;
}

/**
 * Frees the memory used by the Writer's context and closes the file.
 * @param wt Pointer to the Writer structure to free.
 */
void w_free_writer(Writer* wt)
{
    free(wt->context);
    fclose(wt->fp);
}