/**
 * The functions in this module implement a Stack data structure
 * of integers. (Note that chars are also integers so this
 * integer Stack can be used for chars as well.)
 *
 * NOTE: the stack is implemented as a fixed size array (size = 100).
 * Consequently, no more than 100 integers can be pushed onto
 * the Stack at any given time.
 */

#include <stdio.h>
#include <stdlib.h>

#define STACK_CAPACITY 100

static int stackTop = 0;
static int integerStack[STACK_CAPACITY];

/**
 * pop() removes the top integer on the stack and returns it.
 *
 * If pop() is attempted on an empty stack, an error message
 * is printed to stderr and the value -1 (minus one) is returned.
 */
int pop()
{
    if (stackTop <= 0) {
        fprintf(stderr, "Error: Cannot pop from empty stack\n");
        return -1;
    }
    
    stackTop--;
    const int topValue = integerStack[stackTop];
    return topValue;
}

/**
 * push(value) adds the integer "value" to the top of the stack.
 *
 * If there is no more space available on the Stack, an error
 * message is printed to stderr.
 */
void push(int value)
{
    if (stackTop >= STACK_CAPACITY) {
        fprintf(stderr, "Error: Stack full (capacity %d)\n", STACK_CAPACITY);
        return;
    }
    
    integerStack[stackTop] = value;
    stackTop++;
}

/**
 * isEmpty() returns a non-zero integer (not necessarily 1) if the
 * stack is empty; otherwise, it returns 0 (zero).
 */
int isEmpty()
{
    return stackTop == 0;
}