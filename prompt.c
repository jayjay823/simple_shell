#include "shell.h"
#include <stdio.h>


/**
 * main - read a line
 *
 * Return: number of characters read
 */
char *prompt(char **remainder)
{
	ssize_t nline;
	size_t length;
	char *line;
/*	int i;*/

	length = LINE_LENGTH;
/*I have to use malloc*/
	printf("%s %i malloc\n", __FILE__, __LINE__);
	write(1, "$ ", 2);
	printf("%s\n", isatty(STDIN_FILENO) ? "oui" : "non");
	if (isatty(STDIN_FILENO))
	{
		line = malloc(sizeof(char) * length);
		if (line == NULL)
			return (NULL);
		nline = _getline(&line, &length, STDIN_FILENO);
	}
	else
	{
		printf("%s %i before call remainder is %s\n", __FILE__, __LINE__, *remainder);
		nline = _getlinewithbuffer(&line, remainder, STDIN_FILENO);
		printf("%s %i after call remainder is %s\n", __FILE__, __LINE__, *remainder);
	}
/*	printf("Prompt - prints the line in ascii digits\n");
	for (i = 0; i < nline; ++i)
		printf("%d-", line[i]);
	puts("");
*/	if (nline <= 0)
	{
		printf("prompt: _getline did not work or EOF\n");
		free(line);
		printf("freeline in prompt\n");
		exit(1);
		return (NULL);
	}
	line[nline -1] = '\0'; /*get rid of newline*/
	return (line);
}
