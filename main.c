#define _GNU_SOURCE
#include "header.h"
stack_t *head = NULL;
/**
 * main - where the program starts
 * @argc: count of arguments given to program
 * @argv: list of values of arguments given to program
 * Return: 0 for normal run; 1 if there's an error
 */
int main(int argc, char **argv)
{
	char *command;
	size_t len = 0;
	FILE *in;

	if (argc != 2)
	{
		printf("Usage: ./monty <filename>\n");
		return (1);
	}
	in = fopen(argv[1], "r");
	for (; getline(&command, &len, in) != EOF;)
		parser(command);
	fclose(in);
	free(command);
	return (0);
}
/**
 * parser - function to tokenize commands and pass for execution
 * @command: raw command taken from file
 * Return: Always 0
 */
int parser(char *command)
{
	char *token, *value;
	const char *delim = " \n";

	token = strtok(command, delim);
	value = strtok(NULL, delim);
	if (value == NULL)
		value = "";
	if (token[0] == '#')
		return (0);
	exec(token, atoi(value));
	return (0);
}
/**
 * exec - function to execute commands passed from parser
 * @func: the tokenized command
 * @value: a number that the command may need
 * Return: None
 */
void exec(char *func, int value)
{
	if (strcmp(func, "push") == 0)
		head = push(head, value);
	else if (strcmp(func, "pop") == 0)
		head = pop(head);
	else if (strcmp(func, "pall") == 0)
		pall(head);
	else
		printf("Error");
}
