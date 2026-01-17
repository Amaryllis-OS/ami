#include <archive.h>
#include <archive_entry.h>
#include <stdio.h>
#include <stdlib.h>

#include "unpack.h"
#include "writer.h"
#include "archiver.h"
#include "kutil.h"


int unpack_archive(Archiver ar) {
    struct archive* reader;
    struct archive* writer;
    struct archive_entry* entry;
    Writer wt;
    int r;

    reader = archive_read_new();
    if (ar.log_file == NULL) {
        wt = w_open("/dev/null");
    } else {
        wt = w_create(ar.log_file);
    }

    if (ar.ar_t == AMP) {
        archive_read_support_filter_zstd(reader);
        archive_read_support_format_tar(reader);
    } else if (ar.ar_t == TAR) {
        archive_read_support_format_tar(reader);
    }


    writer = archive_write_disk_new();
    archive_write_disk_set_options(writer, ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM);

    if ((r = archive_read_open_filename(reader, ar.src, 10240))) {
        fprintf(stderr, "Error opening archive: %s\n", archive_error_string(reader));

        archive_read_close(reader);
        archive_read_free(reader);

        archive_write_close(writer);
        archive_write_free(writer);

        w_free_writer(&wt);
        return 1;
    }

    while (archive_read_next_header(reader, &entry) == ARCHIVE_OK) {
        if (ar.verbose == VERBOSE) {
            printf("archive extract: %s\n", archive_entry_pathname_utf8(entry));
        }

        // Set the output directory
        const char* entry_pathname = archive_entry_pathname_utf8(entry);
        char *full_path = format_string("%s/%s", ar.dist, entry_pathname);
        archive_entry_set_pathname(entry, full_path);

        char* log = format_string("%s\n", full_path);
        w_add_string(&wt, (const char*)log);
        free(log);

        r = archive_write_header(writer, entry);
        if (r != ARCHIVE_OK) {
            fprintf(stderr, "Error: %s\n", archive_error_string(writer));
        } else {
            const void *buff;
            size_t size;
            int64_t offset;

            while ((r = archive_read_data_block(reader, &buff, &size, &offset)) == ARCHIVE_OK) {
                archive_write_data_block(writer, buff, size, offset);
            };
        }

        free(full_path);
        archive_write_finish_entry(writer);
    }


    w_flush_write(&wt);

    archive_read_close(reader);
    archive_read_free(reader);

    archive_write_close(writer);
    archive_write_free(writer);
    w_free_writer(&wt);

    return 0;
}


