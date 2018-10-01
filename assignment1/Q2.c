/* CS261- Assignment 1 - Q.2*/
/* Name: Tyler Freitas
 * Date: 09/21/2018
 * Solution description: Functions completed as per the instructions for Q2.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){
    /*Swap the addresses stored in the pointer variables a and b*/
    int* temp = a;
    a = b;
    b = temp;
    
    /*Decrement the value of integer variable c*/
    c--;
    
    /*Return c*/
    return c;
}

int main(){
    srand(time(NULL));
    rand();
    /*Declare three integers x,y and z and initialize them randomly to values in [0,10] */
    int x = rand() % 11;
    int y = rand() % 11;
    int z = rand() % 11;
    int res;
    
    /*Print the values of x, y and z*/
    printf("x: %d, y: %d, z: %d\n", x, y, z);
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
    res = foo(&x, &y, z);
    
    /*Print the values of x, y and z*/
    printf("x: %d, y: %d, z: %d\n", x, y, z);
    
    /*Print the value returned by foo*/
    printf("returned by foo: %d\n", res);
 
    
    return 0;
}
/*
 * a) The return value is different than z. z was passed to foo() by value, 
 * which means that c stored a copy of the value stored by z. foo() decremented
 * this value by one and returned it. Thus, the value that is returned by foo()
 * is one less than z.
 *
 * b) The values of x and y are not different. x and y were passed by address
 * to foo. This means that the values of x and y could be changed through the 
 * parameters that store their addresses. However, foo() never acceses the 
 * values stored at these addresses, it simply swaps which parameter is pointing
 * to which address. This has no effect on the values of x and y. 
 */
    
    


