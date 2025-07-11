#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

extern int pop();
extern void push(int value);
extern void toXML(int rootIndex);
extern int isEmpty();
extern void addHeap(int value);
extern int heapSize();
extern int heapDelete();

#define MAX_HEAP_CAPACITY 100

int main(int argc, char * argv[])
{
    int inputValue;
    
    // Read and process input values
    while (scanf("%d", &inputValue) != EOF) {
        fprintf(stderr, "Processing input: %d\n", inputValue);
        addHeap(inputValue);
    }
    
    // Print heap structure as XML
    printf("Heap Structure (XML representation):\n");
    toXML(0);  // Start from root
    printf("\n\n");
    
    // Extract and display values in descending order
    printf("Values in Descending Order:\n");
    const int totalValues = heapSize();
    for (int i = 0; i < totalValues; i++) {
        const int currentMax = heapDelete();
        printf("%d\n", currentMax);
        push(currentMax);  // Store in stack for ascending order
    }
    
    // Display values in ascending order from stack
    printf("\nValues in Ascending Order:\n");
    while (!isEmpty()) {
        printf("%d\n", pop());
    }
    
    return EXIT_SUCCESS;
}