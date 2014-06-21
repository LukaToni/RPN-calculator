#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define N 10

//-------FUNCTIONS----------//
void space(double *stack , int *stack_len)
{
	double *nov= malloc( sizeof(double) * 2 * (*stack_len));
	memcpy(nov, stack, sizeof(double) * (*stack_len));
	free(stack);
	stack= nov;
	(*stack_len) = (*stack_len) * 2;
}

int is_int(char *line)
{
    int i;
    int len=strlen(line);
    if( ( line[0]== '+' || line[0] == '-') && len > 1)
    {

        for(i = 1; i < len; i++)
        {
            if(isdigit(line[i])  == 0 )
               return -1; //error
        }
        return 1;
    }
    else
    for(i = 0; i < len; i++)
    {
            if(isdigit(line[i]) == 0 )
               return -1; //error
    }
    return 1;
}

double top(double *pstack, int counter)
{
	return pstack[--counter];
}

double pop(double *pstack, int *pcounter)
{
 	double val=top(pstack, (*pcounter));
	(*pcounter)--;
	return val;
}

void push(double *pstack, double line, int *pcounter)
{
		pstack[(*pcounter)] = line;
		(*pcounter)++;//defirenciranje pointerja- prideš do vrednosti od pointer
}

void izpis(double *pstack, int counter)
{
	int i;
	for(i = 0; i < counter; i++)
		printf("%lf\n", pstack[i]);
}


//------ARTITMETICS OPERATIONS--------//
void arithmetic_operation(double *stack, char *line, int *counter)
{
    if(strcmp(line, "e") == 0)
    {
    	push(stack, M_E, counter);
    	return;
    }

    if(strcmp(line, "pi") == 0)
    {
    	push(stack, M_PI, counter);
    	return;
    }

    if((*counter) >= 2)
    {


	if ( strcmp(line,"+") == 0)
	{
		double var1 = pop(stack,counter);
		double var2 = pop(stack,counter);
		push(stack, (var1 + var2), counter);
		return;
	}
    if ( strcmp(line,"-") == 0)
    {
	double var1 = pop(stack,counter);
	double var2 = pop(stack,counter);
	push(stack, (var2-var1), counter);
	return;
    }

    if ( strcmp(line,"*") == 0)
    {
	double var1 = pop(stack,counter);
	double var2 = pop(stack,counter);
	push(stack, (var1 * var2), counter);
	return;
    }

    if ( strcmp(line,"/") == 0)
    {
	double var1 = pop(stack,counter);
	double var2 = pop(stack,counter);
	push(stack, (var2/var1), counter);
	return;
    }

    if ( strcmp(line,"^") == 0)
    {
	double var1 = pop(stack,counter);
	double var2 = pop(stack,counter);
	double exp = pow(var2,var1);
	push(stack, exp, counter);
	return;
    }

    if ( strcmp(line,"mod") == 0)
    {
	double var1 = pop(stack,counter);
	double var2 = pop(stack,counter);
	double mod = fmod(var2, var1);
	push(stack, mod, counter);
	return;
    }

     if(strcmp(line, "xchg") == 0)
    {
	double var1 = pop(stack, counter);
	double var2 = pop(stack, counter);
	push(stack, var1, counter);
	push(stack, var2, counter);
	return;
    }
}
    if((*counter) >= 1)
    {

	    if ( strcmp(line,"inv") == 0)
	    {
		double var1 = pop(stack,counter);
		double inv = 1/var1;
		push(stack, inv, counter);
		return;
	    }


	    if(strcmp(line,"print") == 0)
	    {
		double print = top(stack, *counter);
		printf("%lf\n", print);
		return;
	    }

	    if(strcmp(line, "dup") == 0)
	    {
		double var1 = top(stack, *counter);
		push(stack, var1, counter);
		return;
	    }

	    if (strcmp(line,"drop") == 0)
	    {
		pop(stack,counter);
		return;
	    }

	    if(strcmp(line, "sqrt") == 0)
	    {
		double var1 = pop(stack,counter);
		double sqrt1 = sqrt(var1);
		push(stack, sqrt1, counter);
		return;
	    }

	    if(strcmp(line,"sin") == 0)
	    {
		double var1 = pop(stack,counter);
		double sin1 = sin(var1);
		push(stack, sin1, counter);
		return;
	    }

	    if(strcmp(line, "cos") == 0)
	    {
		double var1 = pop(stack,counter);
		double cos1 =cos(var1);
		push(stack, cos1, counter);
		return;
	    }

	    if(strcmp(line, "tan") == 0)
	    {
		double var1 = pop(stack, counter);
		double tan1 = tan(var1);
		push(stack, tan1, counter);
		return;
	    }

	    if(strcmp(line, "log") == 0)
	    {
		double var1 = pop(stack, counter);
	        if(var1 <= 0)
	        {
	            printf("ERR\n");
	            return;
	        }
		double log1 = log10(var1);
		push(stack, log1, counter);
		return;
	    }

	    if(strcmp(line, "ln") == 0)
	    {
		double var1 = pop(stack,counter);
		if(var1 <= 0) 
	        {
	            printf("ERR\n");
	            return;
	        }
		double ln1 = log(var1);
		push(stack, ln1, counter);
		return;
	    }

    }
    printf("ERR\n");
}

 //-------MAIN PROGRAM--------//
int main (int argc, char *argv[])
{
	int counter = 0;
	char line[20];
	double *stack = malloc(sizeof(double) * 10);
	int stack_len = 10;
	while (scanf("%s", &line) != EOF)
	{
		if(is_int(line) == 1)
		{
			if(counter == stack_len)
				space(stack, &stack_len);

            		push(stack, strtod(line, NULL), &counter);
		}
		else
			arithmetic_operation(stack, line, &counter);
	}

	return 0;
}
