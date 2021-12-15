#include <stdlib.h>
#include <sys/env.h>
#include <string.h>
#include <stdio.h>

char* getenv(const char* name) {
	size_t name_len = strlen((char*) name);

	char** envp = env(ENV_ENVP);

	for (size_t i = 0; envp[i] != NULL; i++) {
		if (strncmp(name, envp[i], name_len) == 0) {
			// Assume vars have the format VAR=VALUE.
			return envp[i] + name_len + 1;
		}
	}

    return NULL;
}

void resolve(char* path, char* output) {
	char* cwd = (char*) env(ENV_GET_CWD);
	memcpy(output, cwd, strlen(cwd));

	char tmp[256];
	memset(tmp, 0, sizeof(tmp));

	strcpy(tmp, path);

	char* colon = strchr(tmp, ':');
	if (colon == NULL) {
		if (output[strlen(output) - 1] == '/') {
			output[strlen(output) - 1] = '\0';
		}

		if (tmp[0] == '/') {
			printf("Unsupported path: '%s'\n", tmp);
			return;
		}

		if (tmp[strlen(tmp) - 1] == '/') {
			tmp[strlen(tmp) - 1] = '\0';
		}

		strcat(output, "/");
		strcat(output, tmp);
	} else {
		memset(output, 0, sizeof(output));
		strcpy(output, tmp);
	}
}
