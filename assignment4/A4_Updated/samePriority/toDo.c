/*
 * CS 261 Assignment 4
 * Name: 
 * Date: 
 */
#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
    while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

void addTask(DynamicArray* list){
   printf("Enter the task name:\n");
   char taskName[256]; 
   scanf("%s", taskName);
   printf("Enter the task priority:\n");
   int taskPriority;
   scanf("%d", &taskPriority);

   Task* newTask = taskNew(taskPriority, taskName);
      
   dyHeapAdd(list, newTask, taskCompare);  

    while (getchar() != '\n');
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    // FIXME: Implement
    FILE *ifp; 
    FILE *ofp;
    switch(command){
        case 'l':
            ifp = fopen("./toDo.txt", "r");
            listLoad(list, ifp); 
            fclose(ifp);
            break;
        case 's':
            ofp = fopen("./toDo.txt", "w");
            listSave(list, ofp);
            fclose(ofp);
            break;
        case 'a':
            addTask(list);
            break;
        case 'g':
            if(dySize(list) > 0){
                taskPrint(dyHeapGetMin(list));
            }
            else{
                printf("The list is empty\n\n");
            }
            printf("\n");
            break;
        case 'r':
            if(dySize(list) > 0){
                Task* temp = dyHeapGetMin(list);
                free(temp);
            }
            dyHeapRemoveMin(list, taskCompare);
            break;
        case 'p':
            listPrint(list);
            break;
        case 'e':
            break;

    }
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
    int i;
    for(i = 0; i < dySize(list); i++) {
        taskDelete(dyGet(list, i));
    };
    dyDelete(list);
    return 0;
}
