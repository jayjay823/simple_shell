#include "shell.h"

/**
 * sig_kill - signal for killing child process
 * @sig: signal to change
 * Return: nothing
 */
void sig_kill(int sig)
{
	if (sig == SIGINT)
	{
		printf("ending current process with exit code 0\n");
		_exit(0);
	}
}

/**
 * set_to_kill - set signal to kill
 * Return: nothing
 */
void set_to_kill(void)
{
	if (signal(SIGINT, sig_kill) == SIG_ERR)
	{
		printf("failed to change ctrl+c to kill, abort\n");
		exit(98);
	}
}

/**
 * sig_catch - set signal to be caught
 * @sig: signal to check
 * Return: nothing
 */
void sig_catch(int sig)
{
	if (sig == SIGINT)
		write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * set_to_catch - change signal to be caught
 * Return: nothing
 */
void set_to_catch(void)
{
	if (signal(SIGINT, sig_catch) == SIG_ERR)
	{
		printf("failed to change ctrl+c to catch, abort\n");
		exit(98);
	}
}
