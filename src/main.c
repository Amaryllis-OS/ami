#include <stdio.h>

#include "archiver.h"
#include "argtable3.h"
#include "install.h"

/**
 * The main entry point of the program. Parses command-line arguments and executes the install command if specified.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line argument strings.
 * @return 0 on success, non-zero on failure.
 */
int main(int argc, char* argv[]) 
{
	struct arg_str* arg_install = arg_str1(NULL, "install", "AMP_FILE", "install specified .amp file");
	struct arg_str* arg_installed = arg_str1(NULL, "installed-file", "INSTALLED_LOCATION", "outputs extracted files list to specified location");
	struct arg_lit* verbose = arg_lit0("v", "verbose", "Display verbose output");
	struct arg_lit* help = arg_lit0("h", "help", "show help");
	struct arg_end* end = arg_end(10);
	void* argtable[] = { arg_install, verbose, arg_installed, help, end };

	InstallOptions install_options = {NORMAL, NULL, NULL};
	
	
	int nerrors = arg_parse(argc, argv, argtable);
	if (nerrors > 0) {
		arg_print_errors(stderr, end, argv[0]);
		printf("\n");
		arg_print_syntax(stdout, argtable, "\n");
		goto cleanup;
	}

	if (help->count > 0) {
		printf("Usage: %s", argv[0]);
		arg_print_syntax(stdout, argtable, "\n");
		printf("\nOptions\n");
		arg_print_glossary(stdout, argtable, "    %-25s %s\n");
		goto cleanup;
	}


	if (verbose->count > 0) {
		install_options.verbose = VERBOSE;
	}

	if (arg_installed->count > 0) {
		install_options.installed_file = (char*)arg_installed->sval[0];
	}

	if (arg_install->count > 0) {
		const char* amp_file = arg_install->sval[0];
		int res = install_amp((char*)amp_file, install_options);
		if (res != 0) {
			fprintf(stderr, "Failed to install package: %s\n", amp_file);
			goto cleanup;
		}
	}

cleanup:
	arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[3]));
	return 0;
}
