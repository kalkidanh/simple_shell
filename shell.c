#include "shell.h"

/**
 * main - a simple command line interpreter
 * @ac: number of arguments
 * @av: argument vector
 * @environ: pointer to env_var
 *
 * Return: always 0
 */

int main(int ac, char **av, char **environ)
{
	int token_count, status = 0;
	ssize_t count = 0;
	size_t n;
	pid_t child_pid;
	char *copy, *delim = " \n", *buffer = NULL, **argv;

	(void)ac;
	(void)av;
	do {
		count = getline(&buffer, &n, stdin);
		if (count == -1)
		{
			perror(NULL);
			return (1);
		}
		copy = copy_buffer(buffer);
		token_count = tokenize(buffer, delim);
		argv = malloc(sizeof(char *) * token_count);
		if (argv == NULL)
			return (1);
		argv = buff_split(copy, delim, token_count);
		child_pid = fork();
		if (child_pid == 0)
		{
			status = execve(argv[0], argv, environ);
			if (status == -1)
			{
				perror("Error");
				return (1);
			}
		} wait(NULL);
	} while (count != -1);
	return (0);
}
