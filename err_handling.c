#include "monty.h"

/**
 * err - prints appropirate error messages determined by their error code
 * @error_dcode: the error codes identifier
 * error_codes {1, 2, 3, 4, 5}.
 */
void err(int error_code, ...){
	
	va_list arg;
	char *op;

	va_start(arg, error_code);
	switch (error_code){
		case 1:
		printf("USAGE: monty file\n");
		break;
		case 2:
		printf("Error: Can't open file %s\n", va_arg(arg, char *));
		break;
		case 3:
		op = va_arg(arg, char *);
		printf("L%d: unknown instruction %s\n", va_arg(arg, int), op);
		break;
		case 4:
		printf("Error: malloc faild\n");
		break;
		case 5:
		printf("L%d: usage: push integer\n", va_arg(arg, int));
		break;
		default:
		break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}


/**
 * more_err - headles errors
 * @error_cde: the error identifier
 * Error code {6, 7, 8, 9}
 */
void more_err(int error_code, ...){
	
	va_list arg;
	char *op;

	va_start(arg, error_code);
	switch (error_code){
		case 6:
		printf("L%d: can't pint, stack empty\n", va_arg(arg, int));
		break;	
		case 7:
		printf("L%d: can't pop an empty stack\n", va_arg(arg, int));
		break;
		case 8:
		op = va_arg(arg, char *);
		printf("L%d: can't %s, stack too short\n",
				va_arg(arg, unsigned int), op);
		break;
		case 9:
		printf("L%d: division by zero\n", va_arg(arg, unsigned int));
		break;
		default:
		break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}

/**
 * string_err - handles errors
 * @error_code: the error code identifier
 * Error code {10, 11}
 */
void string_err(int error_code, ...){

	va_list arg;

	va_start(arg, error_code);
	switch (error_code){
		case 10:
		printf("L%d: can't pchar, value out of range\n", va_arg(arg, int));
		break;
		case 11:
		printf("L%d: can't pchar, stack empty\n", va_arg(arg, int));
		break;
		default:
		break;
	}
	free_nodes();
	exit(EXIT_FAILURE);
}


