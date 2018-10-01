/*******************************************************************************
 * Program Filename: HeronsFormula
 * Author: Tyler Freitas
 * Date: 09/21/2018 
 * Description: This program calculates the area of a triangle given the length 
 * each side using Heron's Formula.
 * Input: Three doubles for the side lengths of the triangle.
 * Output: The area of the triangle.
*******************************************************************************/
#include <stdio.h>
#include <math.h>
#include "CalculateArea.h"


/*******************************************************************************
 * Function: main()
 * Description: Calls calculateArea with three double values that describe the
 * sides of a valid triangle.
 * Parameters: NA
 * Pre-Conditions: Double values describe sides of a valid triangle.
 * Post-Conditions: The area of the triangle is printed to the console.
*******************************************************************************/
int main(int argc, char** argv) {
    double a = 5;
    double b = 4;
    double c = 7;
    printf("The area of a triangle with sides %.2f, %.2f,"
           " and %.2f is: %.2f\n", a,
                             b,
                             c,
                             calculateArea(a, b, c));
    return 0;
}
