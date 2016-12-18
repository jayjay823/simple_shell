#include "shell.h"
#include <stdio.h>


/**
 * main - get a line containing a command, parses it and executes
 *
 * Return: always 0
 */
int main(void)
{
	char *line;
	char **args;
	char *function;
	pid_t childpid;
	int status;
/*	int i;*/
	int return_value;
	int fork_flag;
	node_t *envl;
	node_t *pathl;
	node_t *histl;

	fork_flag = 1;
	envl = NULL;
	printf("%s %i\n", __FILE__, __LINE__);
	env_link(&envl);
	pathl = NULL;
	printf("%s %i\n", __FILE__, __LINE__);
	link_path(&pathl, envl);
	histl = NULL;
	history_init(&histl);
	while (1)
	{
		set_to_catch();
		printf("%s %i\n", __FILE__, __LINE__);
		line = prompt();
		if (line == NULL)
		{
			printf("simple shell: prompt did not work\n");
			return (-1);
		}
		printf("simple shell: The line is %s\n", line);
		if (_strlen(line) == 0)
		{
			fork_flag = 0;
		}
		else
		{
			args = strtow(line, ' ');
			printf("%s %i free\n", __FILE__, __LINE__);
			free(line);
			if (args == NULL)
			{
				printf("simple shell: strtow ran into error\n");
				exit(98);
			}
			return_value = bi_function(args, &envl, &pathl, &histl);
			if (return_value !=101)
			{
				fork_flag = 0;
			}
			else
			{
				function = what_path(args[0], pathl);
				if (function == NULL)
					fork_flag = 0;
			}
		}
/*		for(i = 0; args[i] != NULL; ++i)
		printf("-%s-",args[i]);*/
/*		puts("HELLO");*/
/*		function = which(args[0]);
		printf("simple shell function %s\n", function);*/
		if (fork_flag)
		{
			childpid = fork();
/*		puts("WORLD");*/
			if (childpid == 0)
			{
				set_to_kill();
				printf("simple shell: in child process\n");
				if (execve(function, (char *const *) args, environ) == -1)
				{
					perror("Child Error:");
					return (-1);
				}
			}
			else
			{
				waitpid(childpid, &status, 0);
				free_strtow(args);
				free(function);
				printf("%s %i free\n", __FILE__, __LINE__);
				printf("in parent: child process is %u status is %i current pid is %u\n", childpid, status, getpid());
			}
		}
		fork_flag = 1;
	}
	free_list(envl);
	free_list(pathl);
	return (0);
}
