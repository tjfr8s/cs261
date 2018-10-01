/*******************************************************************************
 * Program Filename: HeronsFormula
 * Author: Tyler Freitas
 * Date: 09/21/2018 
 * Description: This program calculates the area of a triangle given the length 
 * each side using Heron's Formula.
 * Input: Three doubles for the side lengths of the triangle.
 * Output: The area of the triangle.
*******************************************************************************/
#include "CalculateArea.h"


/*******************************************************************************
 * Function: double calculateArea(double a, double b, double c);
 * Description: This funciton calculates the area of a triangle given its side
 * lengths.
 * Parameters:
 * - double a: side length.
 * - double b: side length.
 * - double c: side length.
 * Pre-Conditions: Side length arguments describe the sides of a valid triangle.
 * Post-Conditions: The function returns the area of a tringle with specified 
 * side lengths.
*******************************************************************************/
double calculateArea(double a, double b, double c){

    // Calculate semiperimeter and use this to calculate area.
    double semiPerim = (a + b + c) / 2.0;
    double area = sqrt(semiPerim * (semiPerim - a) * (semiPerim - b) * 
            (semiPerim - c));

    return area;

}
