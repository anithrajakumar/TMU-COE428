#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STR_LEN 16
#define STATES 8

// My Assigned State Machine
/*
 * Starting State: B
 *
 *    C 0 1    Assigned Values
 * 0: A D B  |     A = 0
 * 1: B H G  |     B = 1
 * 2: C E C  |     C = 2
 * 3: D C F  |     D = 3
 * 4: E A B  |     E = 4
 * 5: F G D  |     F = 5
 * 6: G H C  |     G = 6
 * 7: H F A  |     H = 7
 */

// -1 indicates deleted state
static int STATE_MACHINE[STATES][3] = {
    {0, 3, 1},  // A D B
    {1, 7, 6},  // B H G
    {2, 4, 2},  // C E C
    {3, 2, 5},  // D C F
    {4, 0, 1},  // E A B
    {5, 6, 3},  // F G D
    {6, 7, 2},  // G H C
    {7, 5, 0}   // H F A
};

// Starting at State B
static int CURRENT_STATE = 1;

// Track whether garbage has been identified
static int GARBAGE_IDENTIFIED = 0;
static int GARBAGE_STATES[STATES];
static unsigned int garbageLength = 0;

int* getStatePosition(int state) {
    for (int i = 0; i < STATES; i++)
        if (STATE_MACHINE[i][0] == state)
            return STATE_MACHINE[i];
    return NULL;
}

// Converts the integer Value to the upper case letter
char intToChar(int val) { 
    return val + 65; 
}

// Transition to the next state using the 0 path
void zero() {
    int* statePosition = getStatePosition(CURRENT_STATE);
    if (statePosition != NULL) {
        CURRENT_STATE = statePosition[1]; // Next state for input 0
        printf("%c\n", intToChar(CURRENT_STATE));
    }
}

// Transition to the next state using the 1 path
void one() {
    int* statePosition = getStatePosition(CURRENT_STATE);
    if (statePosition != NULL) {
        CURRENT_STATE = statePosition[2]; // Next state for input 1
        printf("%c\n", intToChar(CURRENT_STATE));
    }
}

void change_next(int from_state, int to_state, int next) {
    int* statePosition = getStatePosition(from_state);
    if (statePosition != NULL) {
        statePosition[next + 1] = to_state;
    }
}

void print_state_machine() {
    for (int s = 0; s < STATES; s++) {
        int* statePosition = getStatePosition(s);
        if (statePosition != NULL && statePosition[0] != -1)
            printf("%c %c %c\n", intToChar(statePosition[0]), intToChar(statePosition[1]), intToChar(statePosition[2]));
    }
}

// Recursive function to mark reachable states
void traverse(int state, int* seenStates) {
    if (seenStates[state] || state == -1) return; // Skip if already seen or deleted
    seenStates[state] = 1; // Mark as reachable

    int* statePosition = getStatePosition(state);
    if (statePosition != NULL) {
        traverse(statePosition[1], seenStates); // Traverse 0 path
        traverse(statePosition[2], seenStates); // Traverse 1 path
    }
}

// garbage_identify function
unsigned int garbage_identify(int* garbage_states) {
    // Initialize all states as not seen
    int seenStates[STATES] = {0}; 
    unsigned int garbageLength = 0;

    // Start traversal from the current state
    traverse(CURRENT_STATE, seenStates);

    // Identify unreachable states
    for (int i = 0; i < STATES; i++) {
        if (!seenStates[i] && STATE_MACHINE[i][0] != -1) {
            garbage_states[garbageLength++] = i; // Add unreachable state to garbage list
        }
    }

    return garbageLength;
}

void delete_state(int state) {
    getStatePosition(state)[0] = -1;
}

int main() {
    char command[STR_LEN];

    // Print the initial state
    printf("%c\n", intToChar(CURRENT_STATE));

    // Loop to continuously read commands from the user
    while (1) {
        if (fgets(command, STR_LEN, stdin)) {
            // Remove newline character from the input
            command[strcspn(command, "\n")] = 0;

            // Exit loop if user types 'exit'
            if (strcmp(command, "exit") == 0) {
                break;
            }

            // 0 command
            if (command[0] == '0') {
                zero();
            }

            // 1 command
            if (command[0] == '1') {
                one();
            }

            // change_next command
            if (command[0] == 'c') {
                int next = command[2] - '0';
                int to_state = command[4] - 'A';
                change_next(CURRENT_STATE, to_state, next);
            }

            // print_state_machine command
            if (command[0] == 'p') {
                print_state_machine();
            }

            // garbage_identify command
            if (command[0] == 'g') {
                garbageLength = garbage_identify(GARBAGE_STATES);
                GARBAGE_IDENTIFIED = 1; // Mark that garbage has been identified
                if (garbageLength == 0) {
                    printf("No garbage.\n");
                } else {
                    printf("Garbage: ");
                    for (int i = 0; i < garbageLength; i++)
                        printf("%c ", intToChar(GARBAGE_STATES[i]));
                    printf("\n");
                }
            }

            // delete_state command
            if (command[0] == 'd') {
                if (strlen(command) == 1) {
                    // Delete all unreachable states only if garbage has been identified
                    if (GARBAGE_IDENTIFIED) {
                        if (garbageLength == 0)
                            printf("No states deleted.\n");
                        else {
                            printf("Deleted: ");
                            for (int i = 0; i < garbageLength; i++) {
                                printf("%c ", intToChar(GARBAGE_STATES[i]));
                                delete_state(GARBAGE_STATES[i]);
                            }
                            printf("\n");
                        }
                        GARBAGE_IDENTIFIED = 0; // Reset garbage identification
                    } else {
                        printf("No states deleted.\n");
                    }
                } else {
                    // Delete a specific state if it is unreachable
                    int state_to_delete = command[2] - 'A';
                    unsigned int garbageLength = 0;
                    int garbage_states[STATES];
                    garbageLength = garbage_identify(garbage_states);

                    int is_unreachable = 0;
                    for (int i = 0; i < garbageLength; i++) {
                        if (garbage_states[i] == state_to_delete) {
                            is_unreachable = 1;
                            break;
                        }
                    }

                    if (is_unreachable) {
                        delete_state(state_to_delete);
                        printf("Deleted.\n");
                    } else {
                        printf("Not deleted.\n");
                    }
                }
            }
        }
    }

    return 0;
}