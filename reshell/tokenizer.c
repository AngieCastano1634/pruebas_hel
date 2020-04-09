#include "shell.h"

char** tokenizer(char *line)
{
	char **argv;
	char *argc;
	char *writer;
	char *linecpy = (char *) malloc(100);
	int iter1 = 0, iter2 = 0;

	printf ("tokenizer bienvenue\n");
	strcpy(linecpy, line);
	printf ("line copied: %s\n", linecpy);
	argc = strtok(line, DELIMITER);
	while (argc != NULL)
	{
		argc = strtok(NULL, DELIMITER);
		iter1++;
	}
	argv = malloc((iter1 + 1) * sizeof(char *));
	if (argv == NULL)
	{
		write(1,"failed line allocation\n", 23);
		free(argv);
		exit(0);
	}
	writer = strtok(linecpy, DELIMITER);
	while (writer != NULL && iter2 <= iter1)
	{
		argv[iter2] = malloc(strlen(writer) * sizeof(char));
		if (argv[iter2] == NULL)
		{
			write(1, "failed command allocation\n", 26);
			while (iter2 >= 0)
			{
				free(argv[iter2]);
				iter2--;
			}
			exit(0);
		}
		strcpy(argv[iter2], writer);
		argv[iter2][strlen(writer)] = '\0';
		writer = strtok(NULL, DELIMITER);
		iter2++;
	}
	argv[iter1] = '\0';
	return (argv);

}
