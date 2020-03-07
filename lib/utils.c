#include "utils.h"

//validate the arrival time and burst time inputs
void validateInputs(int argc_real, int arrivalTime_arr[], int burstTime_arr[])
{
    for (int i = 0; i < (argc_real / 2); ++i)
    {
        if (arrivalTime_arr[i] >= 0)
        {
            // printf("%d is valid.\n", arrivalTime_arr[i]);

            if (burstTime_arr[i] > 0)
            {
                // printf("%d is valid.\n", burstTime_arr[i]);
            }
            else
            {
                printf("ERROR! Invalid Input detected.\n");
                printf("Burst Time must be more than 0.\n");
                printf("Program ended.\n");
                exit(0);
            }
        }
        else
        {
            printf("ERROR! Invalid Input detected.\n");
            printf("Arrival Time must be more than and equals to 0.\n");
            printf("Program ended.\n");
            exit(0);
        }
    }
}

//print all processes sorted with processID
void printAllProcesses(Process processes[], int argc_real)
{
    qsort(processes, argc_real / 2, sizeof(struct Process), compareProcessID);

    for (int i = 0; i < argc_real / 2; ++i)
    {
        printf("P%d\n", processes[i].processID);
        printf("arrival: %d\n", processes[i].arrivalTime);
        printf("  burst: %d\n", processes[i].burstTime);
        printf("\n");
    }

    menu(processes, argc_real);
}

void fifo(Process processes[], int argc_real)
{
    //sort the Process array based on Arrival Time
    qsort(processes, argc_real / 2, sizeof(struct Process), compareArrivalTime);
    //printAllProcesses(processes, argc_real);
    int cumulativeBurstTime = 0;
    int totalTurnaroundTime = 0;
    float averageTurnaroundTime = 0;
    int totalResponseTime = 0;
    float averageResponseTime = 0;

    //completion time array is cumulative of burst time
    //turnaround time = completion - arrival
    for (int i = 0; i < argc_real / 2; ++i)
    {
        processes[i].completionTime = cumulativeBurstTime += processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    averageTurnaroundTime = (double)totalTurnaroundTime / (argc_real / 2);

    //first turn time for the first process is always 0
    processes[0].firstTurnTime = 0;

    //following first turn time are obtained from completion time array
    //response time = first turn - arrival
    for (int i = 0; i < argc_real / 2; ++i)
    {
        processes[i + 1].firstTurnTime = processes[i].completionTime;
        processes[i].responseTime = processes[i].firstTurnTime - processes[i].arrivalTime;
        totalResponseTime += processes[i].responseTime;
    }

    averageResponseTime = (double)totalResponseTime / (argc_real / 2);

    printf("FIFO Timeline:\n");
    printf("------------------------------\n");

    for (int i = 0; i < argc_real / 2; ++i)
    {
        printf("T = %d\t P%d\n", processes[i].firstTurnTime, processes[i].processID);
    }

    printf("------------------------------\n");
    printf("Average Turnaround Time: %.2f\n", averageTurnaroundTime);
    printf("Average Response Time: %.2f\n", averageResponseTime);

    menu(processes, argc_real);
}

float fifoAvgTurnaroundTime(Process processes[], int argc_real)
{
    //sort the Process array based on Arrival Time
    qsort(processes, argc_real / 2, sizeof(struct Process), compareArrivalTime);
    //printAllProcesses(processes, argc_real);
    int cumulativeBurstTime = 0;
    int totalTurnaroundTime = 0;
    float averageTurnaroundTime = 0;

    //completion time array is cumulative of burst time
    //turnaround time = completion - arrival
    for (int i = 0; i < argc_real / 2; ++i)
    {
        processes[i].completionTime = cumulativeBurstTime += processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    averageTurnaroundTime = (double)totalTurnaroundTime / (argc_real / 2);

    return averageTurnaroundTime;
}

float fifoAvgResponseTime(Process processes[], int argc_real)
{
    //sort the Process array based on Arrival Time
    qsort(processes, argc_real / 2, sizeof(struct Process), compareArrivalTime);
    //printAllProcesses(processes, argc_real);
    int cumulativeBurstTime = 0;
    int totalTurnaroundTime = 0;
    int totalResponseTime = 0;
    float averageResponseTime = 0;

    //completion time array is cumulative of burst time
    //turnaround time = completion - arrival
    for (int i = 0; i < argc_real / 2; ++i)
    {
        processes[i].completionTime = cumulativeBurstTime += processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    //first turn time for the first process is always 0
    processes[0].firstTurnTime = 0;

    //following first turn time are obtained from completion time array
    //response time = first turn - arrival
    for (int i = 0; i < argc_real / 2; ++i)
    {
        processes[i + 1].firstTurnTime = processes[i].completionTime;
        processes[i].responseTime = processes[i].firstTurnTime - processes[i].arrivalTime;
        totalResponseTime += processes[i].responseTime;
    }

    averageResponseTime = (double)totalResponseTime / (argc_real / 2);

    return averageResponseTime;
}

void sjf(Process processes[], int argc_real)
{
    if (processes[(argc_real / 2) - 1].arrivalTime > processes[0].arrivalTime)
    {
        //works for varying arrival time
        qsort(processes, argc_real / 2, sizeof(struct Process), compareBurstTimeVAT);
    }
    else
    {
        //works for simultaneous arrival time
        qsort(processes, argc_real / 2, sizeof(struct Process), compareBurstTime);
    }

    int cumulativeBurstTime = 0;
    int totalTurnaroundTime = 0;
    float averageTurnaroundTime = 0;
    int totalResponseTime = 0;
    float averageResponseTime = 0;

    //completion time array is cumulative of burst time
    //turnaround time = completion - arrival
    for (int i = 0; i < argc_real / 2; ++i)
    {
        processes[i].completionTime = cumulativeBurstTime += processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    averageTurnaroundTime = (double)totalTurnaroundTime / (argc_real / 2);

    //first turn time for the first process is always 0
    processes[0].firstTurnTime = 0;

    //following first turn time are obtained from completion time array
    //response time = first turn - arrival
    for (int i = 0; i < argc_real / 2; ++i)
    {
        processes[i + 1].firstTurnTime = processes[i].completionTime;
        processes[i].responseTime = processes[i].firstTurnTime - processes[i].arrivalTime;
        totalResponseTime += processes[i].responseTime;
    }

    averageResponseTime = (double)totalResponseTime / (argc_real / 2);

    printf("SJF Timeline:\n");
    printf("------------------------------\n");

    for (int i = 0; i < argc_real / 2; ++i)
    {
        printf("T = %d\t P%d\n", processes[i].firstTurnTime, processes[i].processID);
    }

    printf("------------------------------\n");
    printf("Average Turnaround Time: %.2f\n", averageTurnaroundTime);
    printf("Average Response Time: %.2f\n", averageResponseTime);

    menu(processes, argc_real);
}

float sjfAvgTurnaroundTime(Process processes[], int argc_real)
{
    if (processes[(argc_real / 2) - 1].arrivalTime > processes[0].arrivalTime)
    {
        //works for varying arrival time
        qsort(processes, argc_real / 2, sizeof(struct Process), compareBurstTimeVAT);
    }
    else
    {
        //works for simultaneous arrival time
        qsort(processes, argc_real / 2, sizeof(struct Process), compareBurstTime);
    }

    int cumulativeBurstTime = 0;
    int totalTurnaroundTime = 0;

    //completion time array is cumulative of burst time
    //turnaround time = completion - arrival
    for (int i = 0; i < argc_real / 2; ++i)
    {
        processes[i].completionTime = cumulativeBurstTime += processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    float averageTurnaroundTime = (double)totalTurnaroundTime / (argc_real / 2);

    return averageTurnaroundTime;
}

float sjfAvgResponseTime(Process processes[], int argc_real)
{
    if (processes[(argc_real / 2) - 1].arrivalTime > processes[0].arrivalTime)
    {
        //works for varying arrival time
        qsort(processes, argc_real / 2, sizeof(struct Process), compareBurstTimeVAT);
    }
    else
    {
        //works for simultaneous arrival time
        qsort(processes, argc_real / 2, sizeof(struct Process), compareBurstTime);
    }

    int cumulativeBurstTime = 0;
    int totalTurnaroundTime = 0;
    int totalResponseTime = 0;
    float averageResponseTime = 0;

    //completion time array is cumulative of burst time
    //turnaround time = completion - arrival
    for (int i = 0; i < argc_real / 2; ++i)
    {
        processes[i].completionTime = cumulativeBurstTime += processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    //averageTurnaroundTime = (double)totalTurnaroundTime / (argc_real / 2);

    //first turn time for the first process is always 0
    processes[0].firstTurnTime = 0;

    //following first turn time are obtained from completion time array
    //response time = first turn - arrival
    for (int i = 0; i < argc_real / 2; ++i)
    {
        processes[i + 1].firstTurnTime = processes[i].completionTime;
        processes[i].responseTime = processes[i].firstTurnTime - processes[i].arrivalTime;
        totalResponseTime += processes[i].responseTime;
    }

    averageResponseTime = (double)totalResponseTime / (argc_real / 2);

    return averageResponseTime;
}

// void stcf(Process processes[], int argc_real)
// {
//     if (processes[(argc_real / 2) - 1].arrivalTime > processes[0].arrivalTime)
//     {
//         //works for varying arrival time
//         qsort(processes, argc_real / 2, sizeof(struct Process), compareBurstTimeVAT);
//     }
//     else
//     {
//         //works for simultaneous arrival time
//         qsort(processes, argc_real / 2, sizeof(struct Process), compareBurstTime);
//     }

//     //implement preemptive scheduler for stcf timeline
//     int *timeline;
//     int numOfProcess = argc_real / 2;
//     int remainingTime = 0;
//     timeline = (int *)malloc(numOfProcess * sizeof(int));

//     for (int i = 0; i < argc_real / 2; ++i)
//     {

//         while ()
//     }
// }

int compareArrivalTime(const void *a, const void *b)
{

    Process *ProcessA = (Process *)a;
    Process *ProcessB = (Process *)b;

    return (ProcessA->arrivalTime - ProcessB->arrivalTime);
}

int compareBurstTimeVAT(const void *a, const void *b)
{

    Process *ProcessA = (Process *)a;
    Process *ProcessB = (Process *)b;

    if (ProcessA->arrivalTime == 0)
    {
        return 0;
    }
    else
    {
        return (ProcessA->burstTime - ProcessB->burstTime);
    }
}

int compareBurstTime(const void *a, const void *b)
{

    Process *ProcessA = (Process *)a;
    Process *ProcessB = (Process *)b;

    return (ProcessA->burstTime - ProcessB->burstTime);
}

int compareProcessID(const void *a, const void *b)
{

    Process *ProcessA = (Process *)a;
    Process *ProcessB = (Process *)b;

    return (ProcessA->processID - ProcessB->processID);
}

// Process *assignProcessID(int argc_real, int arrivalTime_arr[], int burstTime_arr[])
// {
//     Process processes[argc_real / 2];
//     int processCount = 0;

//     for (int i = 0; i < argc_real / 2; ++i)
//     {
//         processes[i].processID = processCount += 1;
//         processes[i].arrivalTime = arrivalTime_arr[i];
//         processes[i].burstTime = burstTime_arr[i];
//     }

//     return processes;
// }

void compare(Process processes[], int argc_real)
{
    //should return fifo avg turnaround and response time
    //should return sjf avg turnarorund and response time
    float fifoAverageTurnaroundTime = 0;
    float fifoAverageResponseTime = 0;
    float sjfAverageTurnaroundTime = 0;
    float sjfAverageResponseTime = 0;
    float savedAverageTurnaroundTime = 0;
    float savedAverageResponseTime = 0;

    fifoAverageTurnaroundTime = fifoAvgTurnaroundTime(processes, argc_real);
    fifoAverageResponseTime = fifoAvgResponseTime(processes, argc_real);
    sjfAverageTurnaroundTime = sjfAvgTurnaroundTime(processes, argc_real);
    sjfAverageResponseTime = sjfAvgResponseTime(processes, argc_real);

    savedAverageTurnaroundTime = ((fifoAverageTurnaroundTime - sjfAverageTurnaroundTime) / fifoAverageTurnaroundTime) * 100;
    savedAverageResponseTime = ((fifoAverageResponseTime - sjfAverageResponseTime) / fifoAverageResponseTime) * 100;
    printf("--------------------------------------------\n");
    printf("Metric \t\t\t FIFO \t SJF \t Saving \n");
    printf("Average Turnaround Time\t %.2f \t %.2f \t %.f%%\n", fifoAverageTurnaroundTime, sjfAverageTurnaroundTime, savedAverageTurnaroundTime);
    printf("Average Response Time\t %.2f \t %.2f \t %.f%%\n", fifoAverageResponseTime, sjfAverageResponseTime, savedAverageResponseTime);

    menu(processes, argc_real);
}

void menu(Process processes[], int argc_real)
{
    char userInput[10];
    printf("\n");
    printf("1. fifo\n");
    printf("2. sjf\n");
    printf("3. stcf\n");
    printf("4. compare\n");
    printf("5. printall\n");
    printf("6. quit\n");
    printf("\n");
    printf("Please type an option to proceed: ");
    fgets(userInput, 10, stdin);
    printf("\n");

    //fgets attached a newline to the input by default
    //using strcspn to replace that newline with null character
    userInput[strcspn(userInput, "\n")] = '\0';

    //if both strings are equal will return 0
    if (strcmp(userInput, "fifo") == 0)
    {
        fifo(processes, argc_real);
    }
    else if (strcmp(userInput, "sjf") == 0)
    {
        sjf(processes, argc_real);
    }
    else if (strcmp(userInput, "stcf") == 0)
    {
        printf("stcf is not working at the moment. Please return later.\n");
        //stcf(processes, argc_real);
        menu(processes, argc_real);
    }
    else if (strcmp(userInput, "compare") == 0)
    {
        compare(processes, argc_real);
    }
    else if (strcmp(userInput, "printall") == 0)
    {
        printAllProcesses(processes, argc_real);
    }
    else if (strcmp(userInput, "quit") == 0)
    {
        printf("quitting.....\n");
        printf("Program Ended!\n");
        exit(0);
    }
    else
    {
        printf("Invalid Input. Please type an available option!\n");
        menu(processes, argc_real);
    }
}