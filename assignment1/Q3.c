/* CS261- Assignment 1 - Q.3*/
/* Name: Tyler Freitas
 * Date: 09/21/2018 
 * Solution description: This program prompts the user to enter a string and
 * converts it to lower camel case. If the string is invalid (i.e. it doesn't
 * have at least two groups of alphabetical characters) "invalid input string"
 * is printed to the console. Otherwise, the converted string is printed.
 */
#include <stdio.h>
#include <stdlib.h>


/******************************************************************************
 * Function : char toUpperCase(char ch)
 * Description: This funciton returns the uppercase version of a character.
 * Parameters: 
 * - char ch : the character to be converted
 * Pre-Conditions: A valid lowercase alphabetical character is passed to the
 * function.
 * Post-Conditions: The function returns the uppercase version of the passed 
 * character.
 ******************************************************************************/
char toUpperCase(char ch){
  /*Convert ch to upper case, assuming it is in lower case currently*/
    return ch - 32;
}


/******************************************************************************
 * Function : char toLowerCase(char ch)
 * Description: This funciton returns the lowercase version of a character.
 * Parameters: 
 * - char ch : the character to be converted
 * Pre-Conditions: A valid uppercase alphabetical character is passed to the
 * function.
 * Post-Conditions: The function returns the lowercase version of the passed 
 * character.
 ******************************************************************************/
char toLowerCase(char ch){
  /*Convert ch to lower case, assuming it is in upper case currently*/                         
    return ch + 32;
}


/******************************************************************************
 * Function : int stringLength(char s[])
 * Description: This function returns the number of characters in the passed
 * string. 
 * Parameters: 
 * - char s[]: string that is having its size determined. 
 * Pre-Conditions: A valid c-string is passed to the funciton.
 * Post-Conditions: The function returns the number of characters in the 
 * c-string.
 ******************************************************************************/
int stringLength(char s[]) {
   /*Return the length of the string*/
    int size = 0;

    while(s[size] != 0){
        size++;
    }
    return size;
}


/******************************************************************************
 * Function : void makeValid(char* word)
 * Description: This function takes a string of characters and modifies it so
 * that it consists of alphabetical characters separated by single underscores
 * where non alphabetical characters appeared in the original string.
 * Parameters: 
 * - char* word: String to be converted.
 * Pre-Conditions: A c-string is passed to the funciton.
 * Post-Conditions: The passed string is converted to the appropriate form 
 * described above. 
 ******************************************************************************/
void makeValid(char* word){
    int read = 0;
    int write = 0;

    /*Make alphabet characters lowercase and convert all blocks of
     * non-alphabet characters into a single underscore
     */
    while(word[read] != 0){
        if(word[read] >= 'a' && word[read] <= 'z'){
            word[write] = word[read];
            write++;
        }
        else if(word[read] >= 'A' && word[read] <= 'Z'){
            word[write] = toLowerCase(word[read]); 
            write++;
        }
        else if(word[write - 1] != '_' && 
                write != 0 && 
                word[read + 1] != 0){
            word[write] = '_';
            write++;
        }
        read++;
    }

    /*Remove trailing underscore*/
    if(word[write - 1] == '_'){
        write--;
    }

    /*Add null terminator to string*/
    word[write] = 0;
}


/******************************************************************************
 * Function : int isValid(char* word)
 * Description: This function takes a string as an argument and returns 1 if the
 * string contains at least two separte groups of alphabetical characters and
 * 0 otherwise. 
 * Parameters: 
 * - char* word: String to be tested.
 * Pre-Conditions: A c-string is passed to the funciton.
 * Post-Conditions: The function returns 1 if the string has at least two groups
 * of alphabetical characters separated by a single underscore. 
 ******************************************************************************/
int isValid(char* word){
    int first = 0;
    int underscore = 0;
    int second = 0;
    int i = 0;

    /*Check to see if word is made of two groups of alphabetical characters
     * separated by an underscore*/
    while(word[i] != 0){
        if(!first && (word[i] <= 'z' && word[i] >= 'a')){
            first = 1;
        }
        else if(first && word[i] == '_'){
            underscore = 1;
        }
        else if(first && underscore && (word[i] <= 'z' && word[i] >= 'a')){
            second = 1;
        }
        i++;
    }

    return first && underscore && second;
}


/******************************************************************************
 * Function : void camelCase(char* word)
 * Description: This function takes a string as an argument, removes 
 * non-alphabetical characters, inserts underscores between groups of 
 * alphabetical characters and converts the string to lower camel case 
 * (intercapped words with a leading lowercase character). 
 * Parameters: 
 * - char* word: String to be converted.
 * Pre-Conditions: A c-string is passed to the funciton.
 * Post-Conditions:  
 * - the string is converted to lower camel case.
 ******************************************************************************/
void camelCase(char* word){
	/*Convert to camelCase*/
    int index = 0;	
    int read = 0;
    int write = 0;


    /*Convert characters to appropriate case*/
    while(word[index] != 0){
        if((word[index - 1] == '_') && word[index] != '_'){
            word[index] = toUpperCase(word[index]);
        }
        index++;
    }

    /*Remove  underscore characters*/
    while(word[read] != 0){
        if(word[read] != '_'){
            word[write] = word[read];
            write++;
        }
        read++;
    }
    word[write] = 0;
}


/******************************************************************************
 * Function : int main()
 * Description: This function reads in a string from the user and prints 
 * the string converted to lower camel case. If the string is not valie (i.e.
 * it doesn't have at least two groups of alphabetical characters) "invalid
 * input string" is printed to the console. 
 * Parameters: N/A
 * Pre-Conditions: A c-string is passed to the funciton.
 * Post-Conditions:  
 * - the string is converted to lower camel case.
 ******************************************************************************/
int main(){

	/*Read the string from the keyboard*/
    char str[70];
    scanf("%69[^\n]", str);
    makeValid(str);
    printf("%s\n", str);


    /*Check if the user provided a valid string*/
    if(isValid(str)){
        camelCase(str);
        printf("%s\n", str);
    }
    else{
        printf("invalid input string\n");
    }
	
	
    
	
	return 0;
}

