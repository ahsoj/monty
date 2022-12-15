#define _GNU_SOURCE
#include <stdio.h>
#include "monty.h"

stack_t *head = NULL;

/**
 * main - entry point
 * @argc: number of CMD.
 * @argv: an array containing the arguments.
 *
 * Return: always Zero.
 */
int main(int argc, char *argv[]){
	if (argc < 2 || argc > 2)
		err(1);
	open_file(argv[1]);
	free_nodes();
	return 0;
}

/**
 * open_file - opens a file
 * @file_name: String with the name of the file
 */

void open_file(char *file_name){
	int file_check;
	FILE *file;
	
	if (file_name == NULL)
		err(2, file_name);
	file_check = access(file_name, R_OK);
	if (file_check == -1)
		err(2, file_name);
	file = fopen(file_name, "r");
	if (file == NULL)
		err(2, file_name);

	read_file(file);
	fclose(file);
}

/**
 * read_file - reads the content of a file line by line
 * @file: pointer to a file descriptor of an open file
 */

void read_file(FILE *file){

	int line_n;
       	int format;
	char *lineprt;
	size_t n;

	lineprt = NULL;
	n = 0;
	format = 0;

	if (file == NULL)
		err(2, "file_name");

	for (line_n = 1; getline(&lineprt, &n, file) != EOF; line_n++){
		format = interpret_line(lineprt, line_n, format);
	}
	free(lineprt);
}

/**
 * free_nodes - frees nodes in the stack
 */
void free_nodes(void)
{
	stack_t *tmp;
	if (head == NULL)
		return;
	while (head != NULL){
		tmp = head;
		head = head->next;
		free(tmp);
	}
}
/**
 * create_node - create and populates a node
 * @n: number to go inside the node
 *
 * Return: upon succes a pointer to the node. otherwise NULL
 */
stack_t *create_node(int n){
	
	stack_t *node;
	node = malloc(sizeof(stack_t));

	if (node == NULL)
		err(4);
	node->next = NULL;
	node->prev = NULL;
	node->n = n;
	return (node);
}

/**
 * interpret_line - separates each line tokens to determine which
 * function to call
 * @lineptr: string representing a line in a file.
 * @line_number: line number for the opcode.
 * @format: Format specifier
 *
 * Return: returns 0 if the opcode is stack. 1 if queue
 */

int interpret_line(char *lineptr, int line_number, int format){
	
	const char *delim;
	char *opcode;
	char *value;

	if (lineptr == NULL)
		err(4);
	delim = "\n";
	opcode = strtok(lineptr, delim);

	if (opcode == NULL)
		return (format);
	value = strtok(NULL, delim);

	if (strcmp(opcode, "queue") == 0)
		return 1;
	else if (strcmp(opcode, "stack") == 0)
		return 0;

	find_func(opcode, value, line_number, format);
	return (format);
}

/**
 * find_func - finds the appropirate function to run the opcode instructions.
 * @opcode: the operation code, ti could be push, pall, ....
 * @value: The possible value for the operation.
 * @ln: line number for the opcode.
 * @format: Format specifier 
 */

void find_func(char *opcode, char *value, int ln, int format){
	
	int i, flag;

	instruction_t func_list[] = {
		{"push", add_to_stack},
		{"pall", print_stack},
		{"pint", print},
		{"pop", pop},
		{"nop", nop},
		{"swap", swap_nodes},
		{"add", add_nodes},
		{"sub", sub_nodes},
		{"div", div_nodes},
		{"mul", mul_nodes},
		{"mod", mod_nodes},
		{"pchar", print_char},
		{"pstr", print_str},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};
	if (opcode[0] == '#')
		return;
	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++){
		if (strcmp(opcode, func_list[i].opcode) == 0){
			call_fun(func_list[i].f, opcode, value, ln, format);
			flag = 0;
		}
	}
	if (flag == 1)
		err(3, ln, opcode);
}

/**
 * cal_fun - calls the required function.
 * @f: pointer to the function that is about to be called
 * @op: string representing the opcode.
 * @val: string representing a numeric value
 * @ln: line number for the instruction
 * @format: format specifier 
 */

void call_fun(op_func f, char *op, char *val, int ln, int format){
	
	stack_t *node;
	int i, flag;

	flag = 1;
	if (strcmp(op, "push") == 0){
		
		if (val != NULL && val[0] == '-'){
			val = val + 1;
			flag = -1;
		}
		if (val == NULL)
			err(5, ln);
		
		for (i = 0;val[i] != '\0'; i++){
			
			if (isdigit(val[i]) == 0)
				err(5, ln);
		}
		node = create_node(atoi(val) * flag);
		if (format == 0)
			f(&node, ln);
		if (format == 1)
			add_to_queue(&node, ln);
	}
	else
		f(&head, ln);
}

