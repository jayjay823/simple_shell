#include "shell.h"


/**
 * main - get a line containing a command, parses it and executes
 *
 * Return: always 0
 */
int main(void)
{
	char *line;
/*	int i;*/
	node_t *pathl;
	char **enva;
	int check;
	node_t *histl;
	char *remainder;

	printf("%s %i\n", __FILE__, __LINE__);
	histl = NULL;

	check =	initialize_shell(&enva, &pathl, &histl, &remainder);
	if (check == -1)
		return (0);
	printf("end initialize %s %i\n", __FILE__, __LINE__);
	while (1)
	{
		set_to_catch();
		printf("%s %i\n", __FILE__, __LINE__);
		line = prompt(&remainder, enva, pathl, histl);
		if (line != NULL)
/*line is NULL if nothing or only comments, EOF caught before*/
		{
/*		printf("simple shell: The line is %s\n", line);*/
			add_node_end(&histl, line, NULL);
			execute_command(line, &enva, &pathl, &histl);
		}
	}
	printf("RETURN %s\n", __FILE__);
	free_enva(enva);
	free_list(pathl);
	free_list(histl);
	return (0);
}
