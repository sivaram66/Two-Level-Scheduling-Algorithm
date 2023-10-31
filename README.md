# Two-Level-Scheduling-Algorithm
# Multi-Level Queue Scheduling Program

## Introduction

This program is designed to implement a multi-level queue scheduling algorithm with two priority levels:

- **Level 1**: Fixed priority preemptive scheduling.
- **Level 2**: Round Robin scheduling.

In this scheduling system, the processes are initially placed in the Level 1 queue with priorities. The priority 0 is the highest, and lower numbers indicate higher priority. If a process in Level 1 is running, and a new process with a higher priority arrives, the new process will preempt the currently running process and push it down to the Level 2 queue.

Processes in the Level 2 queue are scheduled to execute in a round-robin manner. The time slice for each process's execution is strictly considered in multiples of 2.

Two key considerations in this scheduling program are:
1. Level 2 queue will only be processed after Level 1 becomes empty.
2. The priority of Level 2 has a lower priority than Level 1.

## Usage

1. Compile and run the program.
2. Define processes with their priority and burst times in the code.
3. The program will simulate the scheduling of processes based on the two-level queue system.
4. It will display the Gantt chart showing the order of process execution.
