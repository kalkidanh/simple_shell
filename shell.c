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

/**
 * _strlen - length of string
 * @str: string
 *
 * Return: length
 */
int _strlen(const char *str)
{
	int index = 0;

	while (str[index])
		index++;
	return (index);
}

/**
 * tokenize - split user input into tokens
 * @buffer: string to be tokenized
 * @delim: value of delimiter
 *
 * Return: number of tokens
 */
int tokenize(char *buffer, char *delim)
{
	int token_count;
	char *token;

	token = strtok(buffer, delim);
	token_count = 1;
	while (token)
	{
		token = strtok(NULL, delim);
		token_count++;
	}
	return (token_count);
}

/**
 * buff_split - splits a buffer into an array of tokens
 * @buffer: string to split
 * @delim: value of delimiter
 * @token_count: number of tokens
 *
 * Return: array of splitted buffer
 */
char **buff_split(char *buffer, char *delim, int token_count)
{
	char *token, **argv;
	int index = 0;

	argv = malloc(sizeof(char *) * token_count);
	if (argv == NULL)
		return (NULL);
	token = strtok(buffer, delim);
	while (token)
	{
		argv[index] = malloc(sizeof(char) * _strlen(token));
		if (argv[index] == NULL)
		{
			free(argv[index]);
			free(argv);
			return (NULL);
		}
		strcpy(argv[index], token);
		index++;
		token = strtok(NULL, delim);
	}
	argv[index] = NULL;
	return (argv);
}

/**
 * copy_buffer - copy the content of a buffer
 * @buffer: string to copy
 *
 * Return: a pointer to duplicate buffer
 */
char *copy_buffer(char *buffer)
{
	char *copy;

	copy = malloc(sizeof(char) * _strlen(buffer));
	if (copy == NULL)
		return (NULL);
	strcpy(copy, buffer);
	return (copy);
}
