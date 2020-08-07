#include  "cm_argv_parse.h"

#include <string.h>

namespace cm {

	extern char* find_arg(int argc, char* argv[], char *arg)
	{
		int i;
		for (i = 0; i < argc; ++i) {
			if (!argv[i]) continue;
			if (0 == strcmp(argv[i], arg)) {
				return argv[i + 1];
			}
		}
		return NULL;
	}

}

