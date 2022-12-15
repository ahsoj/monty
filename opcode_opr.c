#include "monty.h"

/**
 * nop - does nothing
 * @stack: pointer to a pointer pointing to top node of the stack
 * @line_number: integer representing the line number of the opcode
 */

void nop(stack_t **stack, unsigned int line_number){
	(void)stack;
	(void)line_number;
}

/**
 * swap_nodes - swaps the top two elements of the stack
 * @line_number: integer representing the line number of the opcode
 */
void swap_nodes(stack_t **stack, unsigned int line_number){
	
	stack_t *tmp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "swap");
	tmp = (*stack)->next;
	(*stack)->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = *stack;
	tmp->next = *stack;
	(*stack)->prev = tmp;
	tmp->prev = NULL;
	*stack = tmp;
}

/**
 * add_nodes - add the two elements of the stack
 * @stack: pointer to a pointer pointing to top node of the stack
 * @line_number: integer representing the line number of the opcode
 */
void add_nodes(stack_t **stack, unsigned int line_number){
	
	int sum;
	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "add");
	(*stack) = (*stack)->next;
	sum = (*stack)->n + (*stack)->prev->n;
	(*stack)->n = sum;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}

/**
 * sub_nodes - adds the top two elements of the stack
 * @stack: pointer to apointer pointing to top node of the stack
 * @line_number: integer representing the line number of the opcode
 */

void sub_nodes(stack_t **stack, unsigned int line_number){
	
	int sum;
	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "sub");
	(*stack) = (*stack)->next;
	sum = (*stack)->n - (*stack)->n;
	(*stack)->n = sum;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}


/**
 * div_nodes - adds the top two elements of he stack.
 * @stack: pointer to pointer pointing to top node of the stack
 * @line_number: integer representing the line number of the opcode
 */

void div_nodes(stack_t **stack, unsigned int line_number){
	
	int sum;
	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "div");
	if ((*stack)->n == 0)
		more_err(9, line_number);
	(*stack) = (*stack)->next;
	sum = (*stack)->n / (*stack)->prev->n;
	(*stack)->n = sum;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}

/**
 * mu-_nodes - adds the top two elements of te stack
 * @stack: pointer to a pointer pointing to top node of the stack
 * @line_number: integer representing the line number of the opcode
 */

void mul_nodes(stack_t **stack, unsigned int line_number){
	
	int sum;
	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "mul");
	(*stack) = (*stack)->next;
	sum = (*stack)->n * (*stack)->prev->n;
	(*stack)->n = sum;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}

/**
 * mod_nodes - adds the top two elements of the stack
 * @stack: pointer to a pointer pointing to top node of the stack
 * @line_number: integer representing the line number of the opcode
 */

void mod_nodes(stack_t **stack, unsigned int line_number){
	
	int sum;
	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "mod");
	if ((*stack)->n == 0)
		more_err(9, line_number);
	(*stack) = (*stack)->next;
	sum = (*stack)->n % (*stack)->prev->n;
	(*stack)->n = sum;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}
