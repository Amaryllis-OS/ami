#ifndef _INTERNAL_PATH_H
#define _INTERNAL_PATH_H

#define BASE_PATH "/var/lib/ami"

/**
 * Returns the path to the distribution directory, creating it if necessary.
 * The returned string should be freed by the caller after use.
 * @return The path to the distribution directory, or NULL on failure.
 */
char* dist_path();

#endif /* _INTERNAL_PATH_H */