My Assigned State Machine
Form: <CurrentState> <NextStateIf_0> <NextStateIf_1>
A D B
B H G
C E C
D C F
E A B
F G D
G H C
H F A

Your starting state is: B 

No Command: 
Once the program is called, the current/starting state gets printed

'1' Command: 
The state moves to the next state using the "1's" path

'0' Command: 
The state moves to the next state using the "0's" path

Change('c 0/1 A-H') command: 
This command modifies the transition path for the current state. It allows you to change the next state for either the 0 or 1 input path to a specified state A through H. 

Print Command:
Prints out the list of states with their paths, with any modifications done to it.

Garbage Identify command:
Finds the unreachable states and marks them for garbage

Delete command:
Two Functions:
First: when called alone (Ex. "d") deletes all of the states that are present in the garbage.
Second: when called with a state (Ex. "d H") deletes that state only if it is unreachable 
otherwise this function will not delete any states


All commands listed above work as intended.

  
c 0 B
1
c 0 D
0
c 1 A 
