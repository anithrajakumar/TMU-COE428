/**
 * The functions in this module implement a Heap data structure
 * of integers.
 */

#include <stdio.h>
#include <stdlib.h>

static int heapArray[100];
static int currentHeapSize = 0;

/**
 * heapDelete() removes the biggest integer in the heap and returns it.
 */
int heapDelete()
{
    if (currentHeapSize <= 0) {
        fprintf(stderr, "Error: Cannot delete from empty heap\n");
        return -1;
    }

    const int rootValue = heapArray[0];
    const int lastIndex = currentHeapSize - 1;
    
    // Replace root with last element
    heapArray[0] = heapArray[lastIndex];
    currentHeapSize--;
    
    // Restore heap property starting from root
    int currentIndex = 0;
    while (currentIndex < currentHeapSize) {
        const int leftChild = 2 * currentIndex + 1;
        const int rightChild = 2 * currentIndex + 2;
        int largestValueIndex = currentIndex;

        // Find which node has the largest value
        if (leftChild < currentHeapSize && heapArray[leftChild] > heapArray[largestValueIndex]) {
            largestValueIndex = leftChild;
        }
        
        if (rightChild < currentHeapSize && heapArray[rightChild] > heapArray[largestValueIndex]) {
            largestValueIndex = rightChild;
        }

        // Stop if heap property is satisfied
        if (largestValueIndex == currentIndex) {
            break;
        }

        // Swap with the larger child
        const int temp = heapArray[currentIndex];
        heapArray[currentIndex] = heapArray[largestValueIndex];
        heapArray[largestValueIndex] = temp;
        
        currentIndex = largestValueIndex;
    }

    return rootValue;
}

/**
 * addHeap(thing2add) adds the "thing2add" to the Heap.
 */
void addHeap(int newValue)
{
    if (currentHeapSize >= 100) {
        fprintf(stderr, "Error: Heap at maximum capacity\n");
        return;
    }

    // Add new value at the end
    heapArray[currentHeapSize] = newValue;
    int currentIndex = currentHeapSize;
    currentHeapSize++;

    // Restore heap property by moving the new value up
    while (currentIndex > 0) {
        const int parentIndex = (currentIndex - 1) / 2;
        
        if (heapArray[parentIndex] >= heapArray[currentIndex]) {
            break;
        }

        // Swap with parent if parent is smaller
        const int temp = heapArray[parentIndex];
        heapArray[parentIndex] = heapArray[currentIndex];
        heapArray[currentIndex] = temp;
        
        currentIndex = parentIndex;
    }
}

/**
 * heapSize() returns the number of items in the Heap.
 */
int heapSize()
{
    return currentHeapSize;
}

/**
 * toXML() prints the heap as an XML tree structure
 */
void toXML(int nodeIndex)
{
    if (nodeIndex >= currentHeapSize) {
        return;
    }
    
    printf("<node id='%d'>", heapArray[nodeIndex]);
    
    const int leftChild = 2 * nodeIndex + 1;
    const int rightChild = 2 * nodeIndex + 2;
    
    // Recursively process children
    if (leftChild < currentHeapSize) {
        toXML(leftChild);
    }
    if (rightChild < currentHeapSize) {
        toXML(rightChild);
    }
    
    printf("</node>");
}