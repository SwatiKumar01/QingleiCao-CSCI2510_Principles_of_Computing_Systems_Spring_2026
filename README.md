Deadlock Detection Program (CSCI 2510)

This program simulates how processes request and release resources and checks for deadlock using a resource allocation graph.

Each process can either acquire or release a resource. When a process requests a resource that is already being used, it has to wait. The program keeps track of these relationships and checks for cycles in the graph. If a cycle is found, that means a deadlock has occurred.

To detect deadlock, the program uses a depth-first search (DFS). It starts from a process and follows the chain of requests and allocations. If it reaches the same process again, a cycle exists.

How to compile:
gcc deadlock.c -o deadlock

How to run:
./deadlock < test1.txt

Example input:
0 a 0
1 a 1
0 a 1
1 a 0

Example output:
PROCESS 1 -> RESOURCE 0
RESOURCE 0 -> PROCESS 0
PROCESS 0 -> RESOURCE 1
RESOURCE 1 -> PROCESS 1

Notes:

* The program supports up to 15 processes and 15 resources
* It stops immediately when deadlock is detected
* If no deadlock occurs, the program exits normally

Author: Swati Kumar

