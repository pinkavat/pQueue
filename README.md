# pQueue.h

A barebones (and unoptimized) binary-minheap-backed priority queue, as a header-only C library (for portability and rapid prototyping)

## Installation

Put [pQueue.h](pQueue.h) in a project directory and include it:
```
#include "pQueue.h"
```
The file has no nonstandard dependencies.

## Usage

The file exposes five functions.

Create a pQueue with
```
pQueue *newQueue(size_t initialSize)
```
where initialSize is a guess used to allocate space for the heap's backing array. 

Deallocate a pQueue with
```
void freeQueue(pQueue *queue)
``` 

### Queue operations

* The pQueue deals in void pointers; managing the objects referred to by these pointers is not the pQueue's responsibility.
* The pQueue is a min-queue: elements with lower priority will be returned first.

Add new elements with
```
void push(pQueue *queue, void *element, int priority)
```

Access the first (lowest-priority) element with
```
void *peek(pQueue *queue)
```
which does not modify the pQueue, or with
```
void *pop(pQueue *queue)
```
which removes the first element.

