#include "header.h"
/**
 * push - function to push values onto stack
 * @head: head of list/stack
 * @num: value to add onto stack
 * Return: new pointer to head
 */
stack_t *push(stack_t *head, int num)
{
	stack_t *new, *temp;

	if (head == NULL)
	{
		new = malloc(sizeof(stack_t));
		head = new;
		new->n = num;
		new->next = NULL;
		new->prev = head;
	}
	else
	{
		temp = head;
		new = malloc(sizeof(stack_t));
		new->n = num;
		head = new;
		new->prev = head;
		new->next = temp;
	}
	return (head);
}
/**
 * pall - function to print all elements in stack
 * @head: pointer to head of list
 * Return: Nothing
 */
void pall(stack_t *head)
{
	while (head)
	{
		printf("%d\n", head->n);
		head = head->next;
	}
}
/**
 * pop - function to remove the top most element from stack
 * @head: pointer to head of stack/list
 * Return: a pointer to new head of list
 */
stack_t *pop(stack_t *head)
{
	head = head->next;
	return (head);
}
