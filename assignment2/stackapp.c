/*******************************************************************************
 * Name: Tyler Freitas
 * Date: 10/9/18
*******************************************************************************/
/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post: funciton returns 0 if string is not balanced and 1 if it is.	
*/
int isBalanced(char* s)
{
	/* FIXME: You will write this function */		
    DynArr* parens = newDynArr(5);
    char next = nextChar(s);
    int isBalanced = 1;

    // Check if parens are closed in the correct order.
    while(next != '\0' && isBalanced){
        if(next == '('){
            pushDynArr(parens, ')');
        }
        else if(next == '{'){
            pushDynArr(parens, '}');
        }
        else if(next == '['){
            pushDynArr(parens, ']');
        }
        else if((next == ')' ||
                 next == '}' ||
                 next == ']')){

            // Check if closing symbol is paired with the correct opening symbol
            if(isEmptyDynArr(parens)){
                isBalanced = 0;
            }
            else if(topDynArr(parens) != next){
                isBalanced = 0;
            }
            else{
                popDynArr(parens);
            }

        }

        next = nextChar(s);
    }

    // The string is not balanced if some parens were not closed.
    if(!isEmptyDynArr(parens)){
        isBalanced = 0;
    }

    deleteDynArr(parens);

    return isBalanced;
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

