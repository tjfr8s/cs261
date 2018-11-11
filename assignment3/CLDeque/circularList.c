/*******************************************************************************
 * Name: Tyler Freitas
 * Email: freitast@oregonstate.edu
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	// FIXME: you must write this
    // Allocate memory for sentinel, initialize its values, and insert it
    // into the list.
    struct Link* newLink = malloc(sizeof(struct Link));
    assert(newLink != NULL);
    newLink->next = newLink;
    newLink->prev = newLink;

    // Initialize the lists members
    list->sentinel = newLink;
    list->size = 0;

}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	// FIXME: you must write this
    struct Link* newLink = malloc(sizeof(struct Link));
    // Allocate memory for the new link, assign appropriate values to members,
    // and return it;
    assert(newLink != NULL);
    newLink->value = value;
    newLink->next = NULL;
    newLink->prev = NULL;

	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this
    assert(list != NULL);
    assert(link != NULL);
    
    // Create link with specified value and insert it after the target link
    struct Link* newLink = createLink(value);

    newLink->next = link->next;
    newLink->prev = link;
    link->next = newLink;
    newLink->next->prev = newLink;
    
    // Adjust size of list
    list->size++;

}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	// FIXME: you must write this
    // Remove the target link from the list
    assert(list != NULL);
    assert(link != NULL);
    if(list->size > 0){
        link->prev->next = link->next;
        link->next->prev = link->prev;
        free(link);
        list->size--;
    }
    else{
        printf("error: list is empty\n");
    }
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	// FIXME: you must write this
    struct Link* remove;
    while(!circularListIsEmpty(list)){
        remove = list->sentinel->next;
        list->sentinel->next = remove->next;
        removeLink(list, remove);
    }
    free(list->sentinel);
    free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
    addLinkAfter(list, list->sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	// FIXME: you must write this
    addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	// FIXME: you must write this
	return list->sentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	// FIXME: you must write this
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	// FIXME: you must write this
    removeLink(list, list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	// FIXME: you must write this
    removeLink(list, list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
	// FIXME: you must write this
	return list->size == 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
	// FIXME: you must write this
    struct Link* printLink = list->sentinel->next;
    while(printLink != list->sentinel){
        printf("%g ", printLink->value);
        printLink = printLink->next;
    }
    printf("\n");
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	// FIXME: you must write this
    struct Link* reverseLink = list->sentinel->next;
    struct Link* temp;

    // Swap the next and prev links of the sentinel
    temp = list->sentinel->next;
    list->sentinel->next = list->sentinel->prev;
    list->sentinel->prev = temp;  

    // Swap next and prev links of all links in list
    while(reverseLink != list->sentinel){
        temp = reverseLink->next;
        reverseLink->next = reverseLink->prev;
        reverseLink->prev = temp;
        reverseLink = temp;
    }
}
