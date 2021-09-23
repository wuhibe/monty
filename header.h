#ifndef HEADER_H
#define HEADER_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;
extern stack_t *head;
typedef void (*op_func)(stack_t **, unsigned int);
int parse_line(char *buffer, int line_number, int format);
int len_chars(FILE *);
void find_func(char *, char *, int, int);
stack_t *create_node(int n);
void free_nodes(void);
void pall(stack_t **, unsigned int);
void push_in(stack_t **, unsigned int);
void add_to_queue(stack_t **, unsigned int);
void call_fun(op_func, char *, char *, int, int);
void pint_all(stack_t **, unsigned int);
void pop(stack_t **, unsigned int);
void nop(stack_t **, unsigned int);
void swap(stack_t **, unsigned int);
void add(stack_t **, unsigned int);
void sub(stack_t **, unsigned int);
void divide(stack_t **, unsigned int);
void mul(stack_t **, unsigned int);
void mod(stack_t **, unsigned int);
void pchar(stack_t **, unsigned int);
void pstr(stack_t **, unsigned int);
void rotl(stack_t **, unsigned int);
void err(int error_code, ...);
void more_err(int error_code, ...);
void string_err(int error_code, ...);
void rotr(stack_t **, unsigned int);

#endif
