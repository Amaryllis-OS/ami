#include <stdio.h>

#include "archiver.h"
#include "argtable3.h"
#include "install.h"

int main(int argc, char* argv[]) 
{
	struct arg_str* arg_install = arg_str1(NULL, "install", "AMP_FILE", "install specified .amp file");
	struct arg_lit* verbose = arg_lit0("v", "verbose", "Display verbose output");
	struct arg_lit* help = arg_lit0("h", "help", "show help");
	struct arg_end* end = arg_end(10);
	void* argtable[] = { arg_install, verbose, help, end };

	InstallOptions install_options = {NORMAL, NULL};
	
	
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

	if (arg_install->count > 0) {
		const char* amp_file = arg_install->sval[0];
		int res = install_amp((char*)amp_file, install_options);
		if (res != 0) {
			fprintf(stderr, "Failed to install package: %s\n", amp_file);
			goto cleanup;
		}
	}

cleanup:
	arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[2]));
	return 0;
}
