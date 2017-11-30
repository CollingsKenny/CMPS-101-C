// Kenneth Collings
// Keacolli
// PA5
#include <stdio.h>
#include <stdlib.h>
#include "List.h"


//based off of code found here
//https://classes.soe.ucsc.edu/cmps101/Fall17/Examples/C/Queue/Queue.c

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;

// Returns reference to new Node object. Initializes next, prev, and data fields.
// Private.
Node newNode(int data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
 }

// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
    if( pN!=NULL && *pN!=NULL ){
        free(*pN);
        *pN = NULL;
    }
 }

// Constructors-Destructors ---------------------------------------------------

// Returns new empty list
List newList(void) {
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = NULL;
    L->length = 0;
    L->cursor = NULL;
    L->index = -1;
    return L;
 }


// Frees all heap memory associated with List *pL, and sets *pL to NULL
void freeList(List* pL){
    if(pL!=NULL && *pL!=NULL) { 
       while( length(*pL) != 0 ) { 
          deleteFront(*pL);
       }
       free(*pL);
       *pL = NULL;
    }
 }

// Access functions -----------------------------------------------------------

int length(List L) {
    if( L == NULL ){
        printf("List Error: length() called on NULL List reference\n");
        exit(1);
    }
    return L->length;
}
//Returns the index of the cursor element
//Precon:   The list exists
int index(List L) {
    if( L==NULL ){
        printf("List Error: index() called on NULL List reference\n");
        exit(1);
    }
    if(L->front == NULL)
        return -1;
    return L->index;
}

int front(List L) {
    if( L==NULL ){
        printf("List Error: front() called on NULL List reference\n");
        exit(1);
    }
    return L->front->data;
}

int back(List L) {
    if( L==NULL ){
        printf("List Error: back() called on NULL List reference\n");
        exit(1);
    }
    return L->back->data;
}

int get(List L) {
    if( length(L) <= 0) {
        printf("List Error: get() called on empty List\n");
        exit(1);
    }

    if( index(L) >= 0) {
        return L->cursor->data;
    }
    return -1;
}

int equals(List A, List B) {
    if(length(A) != length(B))
        return 0;
    if(length(A) <= 0)
        return 1;

    Node N1 = A->front;
    Node N2 = B->front;
    for(int i = 0 ; i < length(A); i++) {
        if( N1->data != N2->data) {
            return 0;
        }
        N1 = N1->next;
        N2 = N2->next;
    }
    return 1;
}

// Manipulation procedures ----------------------------------------------------
void clear(List L){
    while( length(L) != 0 ) { 
        deleteFront(L);
    }
    L->front = L->back = NULL;
    L->cursor = NULL;   
    L->index = -1; 
}

// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
    if (length(L) >= 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}
// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L) {
    if (L->length >= 0) {
        L->cursor = L->back;
        L->index = L->length-1;
    }
}

void movePrev(List L) {
    if( length(L) <= 0) {
        printf("List Error: movePrev() called on empty List\n");
        exit(1);
    }
    if (L->cursor != NULL) {
        if (L->cursor != L->front) {
            L->cursor = L->cursor->prev;
            L->index--;
        }
        else {
            L->cursor = NULL;
            L->index = -1;
        }
    }
}
void moveNext(List L) {
    if( length(L) <= 0) {
        printf("List Error: moveNext() called on empty List\n");
        exit(1);
    }
    if (L->cursor != NULL) {
        if (L->cursor != L->back) {
            L->cursor = L->cursor->next;
            L->index++;
        }
        else {
            L->cursor = NULL;
            L->index = -1;
        }
    }
}
// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data) {
    Node N = newNode(data);
    if (L->length == 0) {
        L->front = L->back = N;
        L->length++;  
    }
    else {
        N->next = L->front;
        L->front->prev = N;
        L->front = N;
        L->length++;
    }
    if(L->index != -1 )
        L->index++; 
}

void append(List L, int data) {
    Node N = newNode(data);
    if(L->length == 0) {
        L->front = L->back = N;
        L->length++;
        return;
    }
    N->prev = L->back;
    L->back->next = N;
    L->back = N;
    L->length++;
}

void insertBefore(List L, int data) {
    if(index(L) < 0) {
        printf("List Error: insertBefore() called with undefined cursor");
        exit(1);
    }
    //first, if adding to the front, use prepend...
    if(index(L) <= 0) {
        prepend(L, data);
        return;
    }
    Node N = newNode(data);
    N->prev = L->cursor->prev;
    L->cursor->prev = N;
    if(N->prev != NULL)
        N->prev->next = N;
    N->next = L->cursor;
    L->index++;
    L->length++;
}

void insertAfter(List L, int data) {
    if( length(L) <= 0) {
        printf("List Error: insertAfter() called on empty List\n");
        exit(1);
    }
    if(length(L) <= 0 ) {
        printf("List Error: insertAfter() called on empty List");
        exit(1);
    }
    if(index(L) < 0) {
        printf("List Error: insertAfter() called with undefined cursor");
        exit(1);
    }
    //first, if adding to the back, use append...
    if(index(L) == length(L)-1) {
        append(L, data);
        return;
    }

    Node N = newNode(data);
    L->cursor->next->prev = N;
    N->prev = L->cursor;
    N->next = L->cursor->next;
    L->cursor->next = N;
    
    L->length++;
}
void deleteFront(List L) {
    if (length(L) <= 0)
    {
        printf("List Error: deleteFront() called on empty List");
        exit(1);
    }
    Node N = L->front;

    //In the case that the length is 1,
    //the list will be emtpy. The nodes must be set as such.
    if(length(L) == 1) {
        L->front = L->back = NULL;
        L->index = -1;
    }
    else {
        //if the cursor is at the front, make the cursor undefined.
        if(L->cursor == L->front) {
            L->index = -1;
        }
        //else, as long as the cursor is not already unddefined, move it back one.
        else if(L->index != -1) { 
            L->index--;
        }

        //remove the refrences to the front node
        L->front = L->front->next;
    }
    freeNode(&N);
    L->length--;
    
}

//Deletes the back element
//Precon:  List is not empty
void deleteBack(List L) {
    if( length(L) <= 0) {
        printf("List Error: deleteBack() called on empty List\n");
        exit(1);
    }

    //if the list is going to be empty
    //OR if the cursor is on the last element,
    //  reset the index
    if(length(L) == 0 || L->cursor == L->back)
    L->index = -1;

    Node N = L->back;
    L->back = L->back->prev;
    L->length--;

    freeNode(&N);
}
//Deletes the element at the cursor
//Precon:   List is not empty
//          Valid cursor is set
void delete(List L) {
    if( length(L) <= 0) {
        printf("List Error: delete() called on empty List\n");
        exit(1);
    }
    if(index(L) < 0) {
        printf("List Error: delete() called with undefined cursor");
        exit(1);
    }

    //if trying to delete the front, deleteFront
    if(index(L) == 0) {
        deleteFront(L);
        return;
    }
    //if trying to delete the back, deleteBack
    if(index(L) == length(L)-1) {
        deleteBack(L);
        return;
    }

    Node N = L->cursor;
    if(L->cursor->prev != NULL)
        L->cursor->prev->next = L->cursor->next;
    if(L->cursor->next != NULL)
        L->cursor->next->prev = L->cursor->prev;
    
    L->length--;
    //If the new length is 0, then the list is emtpy, adjust accordingly
    if(length(L) == 0) {
        L->front = L->back = NULL;  
    }
    //the index will always be deleted
    L->index = -1;
    freeNode(&N);
}

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L) {
    if(length(L) <= 0)
        return;
    Node N = L->front;
    for(int i = 0; i < length(L); i++) {
        fprintf(out, "%i ", N->data);
        N = N->next;
    }
}

List copyList(List L) {
    List newL = newList();
    if(length(L) <= 0)
        return newL;
    Node N = L->front;
    while( N != NULL ) {
        append(newL, N->data);
        N = N->next;
    }
    return newL;
}
