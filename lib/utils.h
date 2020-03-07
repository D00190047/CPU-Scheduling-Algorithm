//#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Process
{
    int processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int firstTurnTime;
    int responseTime;
} Process;

void validateInputs(int, int[], int[]);
//Process *assignProcessID(int argc_real, int arrivalTime_arr[], int burstTime_arr[]);
void printAllProcesses(Process[], int);
void fifo(Process[], int argc_real);
float fifoAvgTurnaroundTime(Process[], int argc_real);
float fifoAvgResponseTime(Process[], int argc_real);
void sjf(Process[], int argc_real);
float sjfAvgTurnaroundTime(Process[], int argc_real);
float sjfAvgResponseTime(Process[], int argc_real);
//void stcf(Process[], int argc_real);
int compareArrivalTime(const void *a, const void *b);
int compareBurstTimeVAT(const void *a, const void *b);
int compareBurstTime(const void *a, const void *b);
int compareProcessID(const void *a, const void *b);
void compare(Process[], int);
void menu(Process[], int);