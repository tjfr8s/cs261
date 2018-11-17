/*
 * CS 261 Assignment 4
 * Name: Tyler Freitas
 * Date: 11/12/2018
 */

#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Creates a new task with the given priority and name.
 * @param priority
 * @param name
 * @return  The new task.
 */

Task* taskNew(int priority, char* name)
{
    // FIXME: implement
    static int count = 0;
    Task* newTask = malloc(sizeof(Task));
    newTask->priority = priority;
    newTask->order = count; 
    count++;
    strcpy(newTask->name, name);
    return newTask;
}

/**
 * Frees a dynamically allocated task.
 * @param task
 */
void taskDelete(Task* task)
{
    free(task);
}

/**
 * Casts left and right to Task pointers and returns
 * -1 if left's priority < right's priority,
 *  1 if left's priority > right's priority,
 *  0 if left's priority == right's priority.
 * @param left  Task pointer.
 * @param right  Task pointer.
 * @return 
 */
int taskCompare(void* left, void* right)
{
    // FIXME: implement
    if(((Task*)left)->priority > ((Task*)right)->priority){
        return 1;
    }
    else if(((Task*)left)->priority < ((Task*)right)->priority){
        return -1;
    }
    else if(((Task*)left)->order > ((Task*)right)->order){
        return 1;
    }
    else if(((Task*)left)->order < ((Task*)right)->order){
        return -1;
    }
    return 0;
}


/**
 * Prints a task as a (priority, name) pair.
 * @param value  Task pointer.
 */
void taskPrint(void* value)
{
    Task* task = (Task*)value;
    printf("(%d, %s, %d)", task->priority, task->name, task->order);
}
