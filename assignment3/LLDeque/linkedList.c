/*******************************************************************************
 * Name: Tyler Freitas
 * Email: freitast@oregonstate.edu
*******************************************************************************/ 
#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	// FIXME: you must write this
    // Allocate space for front and back sentinels
    assert(list != NULL);
    struct Link* frontSent = malloc(sizeof(struct Link));
    struct Link* backSent = malloc(sizeof(struct Link));
    assert(frontSent != NULL);
    assert(backSent != NULL);

    // Initialize members of the sentinels
    frontSent->next = backSent;
    frontSent->prev = NULL;
    backSent->prev = frontSent;
    backSent->next = NULL;

    list->frontSentinel = frontSent;
    list->backSentinel = backSent;
    list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
    assert(list != NULL);
    assert(link != NULL);
	// FIXME: you must write this
    // Allocate space for the new link
    struct Link* newLink = malloc(sizeof(struct Link));
    newLink->value = value;

    // Insert the link before the speciied link 
    newLink->next = link;
    newLink->prev = link->prev;
    newLink->next->prev = newLink;
    newLink->prev->next = newLink;

    list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
    assert(list != NULL);
    assert(link != NULL);
	// FIXME: you must write this
    // Adjust links to remove target link and free target link
    struct Link* prev = link->prev;
    struct Link* next = link->next;
    if(list->size > 0){
        prev->next = next;
        next->prev = prev;
        free(link);

        list->size--;
    }
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
    // Remove all links in the list and free the sentinels and the list itself
    assert(list != NULL);
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
    addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
    assert(list != NULL);
	// FIXME: you must write this
    addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
    assert(list != NULL);
	// FIXME: you must write this
    return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
    assert(list != NULL);
	// FIXME: you must write this
    return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
    assert(list != NULL);
	// FIXME: you must write this
    removeLink(list, list->frontSentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
    assert(list != NULL);
	// FIXME: you must write this
    removeLink(list, list->backSentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
    assert(list != NULL);
	// FIXME: you must write this
    
    return EQ(list->size, 0);
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
    assert(list != NULL);
	// FIXME: you must write this
    // Print values stored at all links in list
    struct Link* printLink = list->frontSentinel->next;
    while(printLink != list->backSentinel){
        printf("%d ", printLink->value);
        printLink = printLink->next;
    }
        printf("\n");
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
    assert(list != NULL);
	// FIXME: you must write this
    addLinkBefore(list, list->backSentinel, value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
    assert(list != NULL);
	// FIXME: you must write this
    int contains = 0;

    // Search for value until it is found or the end of the list is reached
    // Return 1 if the value was found and 0 otherwise
    struct Link* test = list->frontSentinel->next;
    while(!contains && test != list->backSentinel){
        if(EQ(test->value, value)){
            contains = 1;
        }
        test = test->next;
    }

    return contains;
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
    assert(list != NULL);
	// FIXME: you must write this
    int removed = 0;
    struct Link* search = list->frontSentinel->next;
    struct Link* next = search->next;

    // Search for value and remove the appropriate link if it is found
    while(!removed && search != list->backSentinel){
        if(EQ(search->value, value)){
            removeLink(list, search);
            removed = 1;
        }
        search = next;
    }
}
