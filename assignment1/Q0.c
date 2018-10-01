/* CS261- Assignment 1 - Q. 0*/
/* Name: Tyler Freitas
 * Date: 09/21/2018
 * Solution description: Code and comments completed as per the instructions 
 * Q0 of assignment1.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fooA(int* iptr){
  
     /*Print the value and address of the integer pointed to by iptr*/
    printf("value of iptr: %d\naddress of iptr: %p\n", *iptr, iptr);
          
     /*Increment the value of the integer pointed to by iptr by 5*/
    *iptr += 5;
          
     /*Print the address of iptr itself*/
    printf("address of iptr: %p\n\n", iptr);
}


void fooB(int* jptr){
  
     /*Print the value and address of the integer pointed to by jptr*/
    printf("value of jptr: %d\naddress of jptr: %p\n", *jptr, jptr);
               
     /*Decrement jptr by 1*/
    jptr--;
      
     /*Print the address of jptr itself*/
    printf("address of jptr: %p\n\n", jptr);
}


int main(){
    
    /*Declare an integer x and initialize it randomly to a value in [0,10] 
*/
    srand(time(NULL));
    int x = rand() % 11;
    
    /*Print the value and address of x*/
    printf("value of x: %d\naddress of x: %p\n\n", x, &x);
    
    /*Call fooA() with the address of x*/
    fooA(&x);
    
    /*Print the value of x*/
    printf("value of x: %d\n\n", x);
    /* The value of x has increased by 5. x was passed by address to fooA(). 
     * As such, fooA()'s iptr parameter pointed to x's address. When the value 
     * iptr is pointing to is incremented by 5, this is effectively incrementing
     * x by 5 (since iptr is pointing to the address of x in memory).
     */
    
    /*Call fooB() with the address of x*/
    fooB(&x);
    
    /*Print the value and address of x*/
    printf("value of x: %d\naddress of x: %p\n\n", x, &x);
    /* The value and address of x remain the same after calling fooB(). x was 
     * passed to fooB() by address. Thus, fooB()'s parameter jptr stored  
     * x's address. When jptr itself is incremented it is made to point to a 
     * different location in memory (no longer the address of x). Thus, no 
     * changes are made to x through jptr. 
     */
 
    
    return 0;
}


