#include "shell.h"

/**
 * _strnconcat - concatenate 2 strings
 * @s1: first string, malloc'ed or realloc'ed
 * @s2: Buffer of length BUF_LENGTH to add to first string
 * @nr: length to copy
 * Return: pointer to modified first string
 */
char *_strnconcat(char *s1, char *s2, int nr)
{
	unsigned int l1, i;

	if (s2 == NULL)
		return (s1);

	i = 0;
	l1 = 0;
	if (s1 == NULL)
	{
		printf("%s %i malloc\n", __FILE__, __LINE__);
		s1 = malloc(sizeof(*s1) * (nr + 1));
		if (s1 == NULL)
			return (NULL);
	}
	else
	{
		printf("%s original line %s\n", __FILE__, s1);
		l1 = _strlen(s1);
		printf("realloc buffer\n");
		s1 = _realloc(s1, l1, l1 + nr + 1);
	}
	i = l1;
	while (i < (l1 + nr))
		*(s1 + i++) = *s2++;

	*(s1 + i) = '\0';
	printf("%s return line %s\n", __FILE__, s1);
	return (s1);
}
