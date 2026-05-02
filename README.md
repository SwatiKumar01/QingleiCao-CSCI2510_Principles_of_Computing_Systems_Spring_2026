# Deadlock Detection (CSCI 2510)

## Overview

This program detects deadlock in a system using a Resource Allocation Graph (RAG).
Processes request and release resources, and the program checks for cycles after each request.

## How It Works

* PROCESS → RESOURCE = waiting
* RESOURCE → PROCESS = holding
* Uses Depth-First Search (DFS) to detect cycles
* If a cycle is found, the program prints the cycle and exits with -1

## Compilation

gcc deadlock.c -o deadlock

## Usage

./deadlock < test1.txt

## Example Input

0 a 0
1 a 1
0 a 1
1 a 0

## Example Output

PROCESS 1 -> RESOURCE 0
RESOURCE 0 -> PROCESS 0
PROCESS 0 -> RESOURCE 1
RESOURCE 1 -> PROCESS 1

## Notes

* Maximum of 15 processes and 15 resources
* Program exits immediately when deadlock is detected
* If no deadlock occurs, the program exits normally

## Author

Swati Kumar
# QingleiCao-CSCI2510_Principles_of_Computing_Systems_Spring_2026
