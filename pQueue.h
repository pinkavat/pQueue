#ifndef PQUEUE
#define PQUEUE

#include <stdlib.h>

/* pQueue.h
 *
 * A rudimentary attempt to stay awake by coding a
 * Binary-MinHeap backed Priority Queue; October 2019
 * Refactored in November with AoS format
 * Refactored into header-only in March 2020
 *
 * Supports peek, pop, and push, with intuitive behaviour.
 * Argument format: queue, [newElement], [priority]    (optional args if pushing)
 * Heap-resident, allocation with newQueue(backing size), deallocation with freeQueue(queue)
 *
 * written October 2019 by Thomas Pinkava; refactored into AoS format November 2019; made header-only in March 2020.
*/


// An element of the priority queue
struct pQueueNode {
    void *element;          // A Pointer to the Queued thing
    int priority;           // The Priority of this Element
};

// A Priority Queue
typedef struct {
    struct pQueueNode *heap;// MaxHeap backing, larger integer values are higher-priority

    unsigned int size;      // The size of the queue
    unsigned int maxSize;   // The size of the memory block allocated for the backing array
} pQueue;




// Returns a pointer to the least element in the queue without removing it
// Returns NULL if the queue is empty
static void *peek(pQueue *queue){
    return (queue->size == 0) ? NULL: queue->heap[0].element;
}



// Removes the least element from the queue and returns a pointer to it
// Returns NULL if the queue is empty
static void *pop(pQueue *queue){
    // Emptiness check
    if(queue->size == 0) return NULL;
    // Remove the root
    void *extracted = queue->heap[0].element;
    // Promote the last leaf
    queue->heap[0] = queue->heap[--(queue->size)];
    // Heapify to restore heap order
    for(unsigned int smallestChildIndex = 0, curIndex = 0; ; curIndex = smallestChildIndex){
        // Left Child Comparison
        unsigned int childIndex = (curIndex << 1) + 1;
        if(childIndex < queue->size && queue->heap[childIndex].priority < queue->heap[curIndex].priority) smallestChildIndex = childIndex;
        // Right Child Comparison
        childIndex++;
        if(childIndex < queue->size && queue->heap[childIndex].priority < queue->heap[smallestChildIndex].priority) smallestChildIndex = childIndex;
        if(smallestChildIndex == curIndex) break;
        // Downswap
        struct pQueueNode temp = queue->heap[curIndex];
        queue->heap[curIndex] = queue->heap[smallestChildIndex];
        queue->heap[smallestChildIndex] = temp;
    }
    return extracted;
}



// Adds a new element to the queue with the indicated priority
static void push(pQueue *queue, void *element, int priority){
    // Update size and reallocate if necessary
    if(queue->size == queue->maxSize){
        // Double the size of the backing array
        queue->maxSize *= 2;
        queue->heap = (struct pQueueNode *)realloc(queue->heap, sizeof(struct pQueueNode) * queue->maxSize);
    }
    // Append new element to bottom of heap
    queue->heap[queue->size].element = element;
    queue->heap[queue->size].priority = priority;
    // Percolate upwards to restore heap order
    unsigned int parentIndex = 0;
    for(unsigned int curIndex = (queue->size)++; curIndex > 0; curIndex = parentIndex){
        // If child and parent are ordered, stop.
        parentIndex = (curIndex - 1) >> 1;
        if(queue->heap[parentIndex].priority <= queue->heap[curIndex].priority) break;
        // Otherwise, swap.
        struct pQueueNode temp = queue->heap[curIndex];
        queue->heap[curIndex] = queue->heap[parentIndex];
        queue->heap[parentIndex] = temp;        
    }
        
}



// Allocates and returns a new Priority Queue
static pQueue *newQueue(size_t initialSize){
    pQueue *newQueue = (pQueue *)malloc(sizeof(pQueue));
    newQueue->heap = (struct pQueueNode *)malloc(sizeof(struct pQueueNode) * initialSize);
    newQueue->maxSize = initialSize;
    newQueue->size = 0;
    return newQueue;
}



// Deallocates the indicated Priority Queue
static void freeQueue(pQueue *queue){
    free(queue->heap);
    free(queue);
}

#endif
