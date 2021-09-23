#include "header.h"
stack_t *head;
/**
 * main - start of program
 * @argc: count of arguments
 * @argv: list of values of arguments
 * Return: always 0
 */
int main(int argc, char *argv[])
{
	FILE *fd;
	int line_number, format = 0;
	char *buffer = NULL, *filename;
	size_t len = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty <file>\n");
		exit(EXIT_FAILURE);
	}
	filename = argv[1];
	fd = fopen(filename, "r");
	if (filename == NULL || fd == NULL)
		err(2, filename);
	for (line_number = 1; getline(&buffer, &len, fd) != EOF; line_number++)
		format = parse_line(buffer, line_number, format);
	free(buffer);
	fclose(fd);
	free_nodes();
	return (0);
}
/**
 * parse_line - parses command into tokens and calls appropriate func.
 * @buffer: line from the file
 * @line_number: line number
 * @format:  storage format. 0 for stack. 1 for queue.
 * Return: Returns 0 if stack. 1 if queue.
 */
int parse_line(char *buffer, int line_number, int format)
{
	char *cmd_tok, *value;
	const char *delim = "\n ";

	if (buffer == NULL)
		err(4);
	cmd_tok = strtok(buffer, delim);
	if (cmd_tok == NULL)
		return (format);
	value = strtok(NULL, delim);
	if (strcmp(cmd_tok, "stack") == 0)
		return (0);
	if (strcmp(cmd_tok, "queue") == 0)
		return (1);
	find_func(cmd_tok, value, line_number, format);
	return (format);
}
/**
 * find_func - find the appropriate function for the command
 * @cmd_tok: filtered main command
 * @value: argument that command may take
 * @format:  storage format. If 0 for stack. 1 for queue.
 * @ln: line number
 * Return: None
 */
void find_func(char *cmd_tok, char *value, int ln, int format)
{
	int i;
	int flag;

	instruction_t func_list[] = {
		{"push", push_in},
		{"pall", pall},
		{"pint", pint_all},
		{"pop", pop},
		{"nop", nop},
		{"swap", swap},
		{"add", add},
		{"sub", sub},
		{"div", divide},
		{"mul", mul},
		{"mod", mod},
		{"pchar", pchar},
		{"pstr", pstr},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	if (cmd_tok[0] == '#')
		return;
	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(cmd_tok, func_list[i].opcode) == 0)
		{
			call_fun(func_list[i].f, cmd_tok, value, ln, format);
			flag = 0;
		}
	}
	if (flag == 1)
		err(3, ln, cmd_tok);
}
/**
 * call_fun - Calls the required function.
 * @func: Pointer to the function that is about to be called.
 * @op: string representing the opcode.
 * @val: string representing a numeric value.
 * @ln: line numeber for the instruction.
 * @format: Format specifier. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 */
void call_fun(op_func func, char *op, char *val, int ln, int format)
{
	stack_t *node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			flag = -1;
		}
		if (val == NULL)
			err(5, ln);
		for (i = 0; val[i] != '\0'; i++)
		{
			if (isdigit(val[i]) == 0)
				err(5, ln);
		}
		node = create_node(atoi(val) * flag);
		if (format == 0)
			func(&node, ln);
		if (format == 1)
			add_to_queue(&node, ln);
	}
	else
		func(&head, ln);
}
/**
 * add_to_queue - Adds a node to the queue.
 * @new_node: Pointer to the new node.
 * @ln: line number of the opcode.
 */
void add_to_queue(stack_t **new_node, __attribute__((unused))unsigned int ln)
{
	stack_t *tmp;

	if (new_node == NULL || *new_node == NULL)
		exit(EXIT_FAILURE);
	if (head == NULL)
	{
		head = *new_node;
		return;
	}
	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = *new_node;
	(*new_node)->prev = tmp;
}
