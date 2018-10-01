/* CS261- Assignment 1 - Q.1*/
/* Name: Tyler Freitas  
 * Date: 09/21/2018
 * Solution description: Functions created to specifications of Q1 prompt.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
	int id;
	int score;
};


/*******************************************************************************
 * Function: struct student* allocate();
 * Description: This function creates an array of struct student objects and
 * returns a pointer to the first element in the array.
 * Parameters: N/A
 * Pre-Conditions: N/A
 * Post-Conditions: Return value of function is a pointer to the start
 * of an array of struct student objects.
 ******************************************************************************/
struct student* allocate(){
     /*Allocate memory for ten students*/
    struct student* studentArray = malloc(10 * sizeof(struct student));
     
     /*Return the pointer*/
    return studentArray;
}


/******************************************************************************
 * Function: void swap(int* a, int* b)
 * Description: This function swaps the values of two integers.
 * Parameters: 
 * - int* a : pointer to first integer to be swapped
 * - int* b : pointer to second integer to be swapped
 * Pre-Conditions : Function receives the addresses of two integers stored in
 * memory.
 * Post-Conditions: The values stored at the passed addresses are swapped.
 ******************************************************************************/
void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


/******************************************************************************
 * Function: void generate(struct student* students) 
 * Description: This function generates random IDs for each of the students in 
 * the passed array. 
 * Parameters: 
 * - struct student* students : array of struct student objects
 * Pre-Conditions : Valid array of student objects is passed to function.
 * Post-Conditions: Each student in the array is assigned a unique ID. 
 ******************************************************************************/
void generate(struct student* students){
     /*Generate random and unique IDs and random scores for ten students, 
IDs being between 1 and 10, scores between 0 and 100*/
    int numStudents = 10;
    int ids[numStudents];
    int i;
    int j;
    int random;

    /*Generate unique sequential IDs for students in array*/
    for(i = 0; i < numStudents; i++){
        ids[i] = i + 1;
    } 

    /*Shuffle the IDs and assign them to students*/
    for(j = 0; j < numStudents - 1; j++){
        random = rand() % (numStudents - j) + j;
        swap(&ids[j], &ids[random]);
    } 
    for(i = 0; i < numStudents; i++){
        students[i].id = ids[i];
        students[i].score = rand() % 101;
    } 
}


/******************************************************************************
 * Function: void output(struct student* students) 
 * Description: This function ouputs the ID and score for each student to the 
 * console. 
 * Parameters: 
 * - struct student* students : array of struct student objects
 * Pre-Conditions : Valid array of student objects is passed to function.
 * Post-Conditions: Each student's ID and score are printed to the console. 
 ******************************************************************************/
void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
    int i;
    for(i = 0; i < 10; i++){
        printf("%-3d %-3d\n", students[i].id, students[i].score);
    }
}


/******************************************************************************
 * Function: void summary(struct student* students)
 * Description: This funciton computes and prints the min, max, and avg
 * scores of the students in the passed array. 
 * Parameters: 
 * - struct student* students : array of struct student objects
 * Pre-Conditions : Valid array of student objects is passed to function.
 * Post-Conditions: The min, max, and avg scores are printed to the console. 
 ******************************************************************************/
void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the 
ten students*/
    int min = students[0].score;
    int max = 0;
    double avg = 0;
    int i;

    /*Establish running total of scores in avg and check whether each score
     * is the new min or max.*/
    for(i = 0; i < 10; i++){
        avg += students[i].score;
        if(students[i].score > max){
            max = students[i].score;
        }
        else if(students[i].score < min){
            min = students[i].score;
        }
    }

    /*Calculate average from running total*/
    avg = avg / 10.0;

    printf("max score: %d\nmin score: %d\navg score: %.2f\n", max, min, avg);
     
}


/******************************************************************************
 * Function: deallocate(struct student* stud)
 * Description: frees memory allocate for the passed array.
 * Parameters: 
 * - struct student* stud : Valid array of student objects.
 * Pre-Conditions: Valid array of student objects is passed to function.
 * Post-Conditions: Memory allocated for array is freed.
 ******************************************************************************/
void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
    free(stud);
}

int main(){
    struct student* stud = NULL;
    srand(time(NULL));
    rand();
    
    /*Call allocate*/
    stud = allocate();
    
    /*Call generate*/
    generate(stud);
    
    /*Call output*/
    output(stud);
    
    /*Call summary*/
    summary(stud);
    
    /*Call deallocate*/
    deallocate(stud);

    return 0;
}

