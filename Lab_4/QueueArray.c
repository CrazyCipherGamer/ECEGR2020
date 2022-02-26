#include <stdio.h>
#include <stdlib.h>

//Data structure to be the linked list represented by the queue
typedef struct Node
{
    float item;
    struct Node* next;
} Node;

// Modified data structure to represent a queue
typedef struct Queue
{
    int size;
    Node* front;
    Node* rear;
} Queue;
 
// Utility function to initialize the queue
Queue* newQueue(void)
{
    Queue *pQueue = (Queue*)malloc(sizeof(Queue));
 
    pQueue->size = 0;
    pQueue->front = NULL;
    pQueue->rear  = NULL;
 
    return pQueue;
}
 
// Utility function to return the size of the queue
int size(Queue *pQueue) {
    return pQueue->size;
}
 
// Utility function to check if the queue is empty or not
int isEmpty(Queue *pQueue) {
    return (pQueue->size == 0);       
}

// Unneeded function as Linked Lists are dynamic and will never be full.
// Utility function to check if the queue is full or not
// int isFull(Queue *pQueue) {
//     return (pQueue->size == pQueue->maxsize);  
// }
 
// Utility function to add an element `x` to the queue
int enqueue(Queue *pQueue, float x)
{
    Node* tmp = (Node *)malloc(sizeof(Node));
    tmp->item = x;
    tmp->next = NULL;

    printf("Inserting %f\n", x);

    // check if the queue is totally empty.
    if (isEmpty(pQueue))
    {
        //Set both the front and the rear to the same node.
        pQueue->front = pQueue->rear = tmp;
    }
    else
    {
        //Set the rear node's next to tmp and then move the rear to point to this new node.
        pQueue->rear->next = tmp;
        pQueue->rear = tmp;
    }

    pQueue->size++;

    return 0;
}
 
// Utility function to remove an element from the queue
int dequeue(Queue *pQueue, float* x)
{
    // check for queue underflow
    if (isEmpty(pQueue))
    {
        printf("Queue Empty!\n");
        return -1;
    }
 
    // remove element decrement queue size by 1
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp = pQueue->front;                //Copy the front node into tmp.
    *x = tmp->item;                     //Extract the value.
    pQueue->front = tmp->next;          //Set the front node to now point to the node next in line.
    pQueue->size--;                     //Decrement the size.
    free(tmp);                          //Free the node we just extracted.
    
    printf("Removing %f\n", *x);
    return 0;
}
 
// Utility function to peek at first element from the queue
int peek(Queue *pQueue, float* x)
{
    // check for queue underflow
    if (isEmpty(pQueue))
    {
        printf("Queue Empty!\n");
        return -1;
    }
 
    // return front of queue value. Very easy, just copies the value of the front node into the variable.
    *x = pQueue->front->item;
    return 0;
}
 
int main()
{
    // create a queue
    Queue *qt = newQueue();
    float  value;
 
    enqueue(qt, 1.0);
    enqueue(qt, 2.0);
    enqueue(qt, 3.0);
 
    printf("The queue size is %d\n", size(qt));
    peek(qt, &value);
    printf("Top val on queue is %f\n", value);
    dequeue(qt, &value);
    dequeue(qt, &value);
    dequeue(qt, &value);
 
    if (isEmpty(qt)) {
        printf("The queue is empty");
    }
    else {
        printf("The queue is not empty");
    }
 
    return 0;
}