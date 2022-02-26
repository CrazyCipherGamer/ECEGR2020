#include <stdio.h>
#include <stdlib.h>

// Data structure to represent a stack as a linked list.
typedef struct Stack
{
    int length;
    float item;
    struct Stack *next;
} Stack;


// Utility function to check if the stack is empty or not. Stack * is used as we are not manipulating any values in the Stack.
int isEmpty(Stack *pStack) {
    return pStack == NULL;
}

 
// Utility function to return the size of the stack. Stack * is used as we are not manipulating any values.
int size(Stack *pStack) {
    return isEmpty(pStack) ? 0 : pStack->length;
}
 
//This function no longer applies as a linked list can be dynamic and will not overflow. 
// Utility function to check if the stack is full or not
// int isFull(Stack *pStack) {
//     return pStack->top == pStack->maxsize - 1;
// }
 
// Utility function to add an element `x` to the stack. We take a type of Stack ** as we are actually changing the value of the Stack.
int push(Stack **ppStack, float x)
{
    //If the stack is getting its first element
    if (*ppStack == NULL)
    {
        *ppStack = (Stack *)malloc(sizeof(Stack));
        printf("Inserting %f\n", x);
        (*ppStack)->item = x;
        (*ppStack)->length = 1;
        (*ppStack)->next = NULL;
        return 0;
    }

    //Case if the stack had stuff already.
    Stack *tmp = (Stack*)malloc(sizeof(Stack));
    printf("Inserting %f\n", x);
    tmp->length = (*ppStack)->length + 1;
    (*ppStack)->length = 0;
    tmp->item = x;
    tmp->next = *ppStack;
    *ppStack = tmp;

    return 0;
}
 
// Utility function to pop a top element from the stack. Same as push function with Stack ** input.
int pop(Stack **ppStack, float* x)
{
    // check for stack underflow
    if (isEmpty(*ppStack))
    {
        printf("Stack Empty!\n");
        return -1;
    }
 
    Stack *tmp;
    tmp = *ppStack;
    float n = tmp->item;
    printf("Removing %f\n", n);
    *x = n;

    //We check if there is a next node in the list or not and then make a decision on which value we set to proper value for the length.
    if((*ppStack)->next != NULL)
    {
        (*ppStack)->next->length = tmp->length - 1;
    }
    else
    {
        (*ppStack)->length = tmp->length - 1;
    }
    *ppStack = (*ppStack)->next;
    //Free the node with the value.
    free(tmp);

    return 0;
}
 
// Utility function to peek at top element from the stack
int peek(Stack *pStack, float* x)
{
    // check for stack underflow
    if (isEmpty(pStack))
    {
        printf("Stack Empty!\n");
        return -1;
    }
 
    // return top of stack value
    *x = pStack->item;
    return 0;
}
 
int main()
{
    //Declare Stack
    Stack *pt = NULL;
    float  value;

    //Push values onto stack
    push(&pt, 1.0);
    push(&pt, 2.0);
    push(&pt, 3.0);
 
    printf("The stack size is %d\n", size(pt));
    peek(pt, &value);
    printf("Top val on stack is %f\n", value);
    
    //Popping values off the stack.
    pop(&pt, &value);
    pop(&pt, &value);
    //pop(&pt, &value);

    printf("The stack size is %d\n", size(pt));
    peek(pt, &value);
    printf("Top val on stack is %f\n", value);
 
    if (isEmpty(pt)) {
        printf("The stack is empty");
    }
    else {
        printf("The stack is not empty");
    }
 
    return 0;
}