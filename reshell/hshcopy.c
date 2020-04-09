#include "shell.h"

int main (
	int ac __attribute__((unused)),
	char *av[] __attribute__((unused)),
	char *env[]
	)
{
        char *line = NULL;
        char **argv;
        pid_t __attribute__((unused)) pid1;
        ssize_t line_chk = 0;
        size_t size = IP_SIZE;
	char *path = "PATH";
	char *location = malloc(256);
	char **pathoken;
	int iter;

	path = finds_path(env, path);

        write(STDIN_FILENO, "$>", 3);
        line_chk = getline(&line, &size, stdin);

        while (strcmp(line, SH_KILLER) != 0)
        {
                if (line_chk == -1)
		{
                        write(STDIN_FILENO, "failed reading input\n", 22);
			free(line);
			exit (0);
		}
                if (line_chk > 0)
		{
			printf("%s\n", path);
			printf("tokenizer entering\n");
			pathoken = tokenizer(path);
			printf("pathoken: %s\n", pathoken[1]);
                        argv = tokenizer(line);
			printf("argv: %s\n", argv[0]);
			printf("getting location for execveing\n");
			for (iter = 1; pathoken[iter]; iter++)
			{
				location = matcher(argv[0], pathoken[iter]);
				if (location == NULL)
					printf("\njumping\n");
				else
					break;
			}
			printf("ls is in %s\n", location);
		}
		write(STDIN_FILENO, "$>", 3);
		line_chk = getline(&line, &size, stdin);
        }
	free(line);
        printf("bye! bitches\n");
        return (0);
}
