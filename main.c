#include "./lib/utils.h"

int main(int argc, char *argv[])
{
    int argc_real = argc - 1;
    //sanitise the inputs
    //Conditions: Argument counts must be divisible by 2 and not zero
    if ((argc_real % 2 == 0) && (argc_real != 0))
    {
        // printf("valid, argument count is %d, Proceed.\n", argc_real);
        //convert arguments into int and insert into process_arr[]
        int process_arr[argc_real];
        for (int i = 0; i < argc_real; ++i)
        {
            process_arr[i] = atoi(argv[i + 1]);
        }

        int arrivalTime_arr[argc_real / 2];
        int burstTime_arr[argc_real / 2];
        int arrivalCount = 0;
        int burstCount = 0;

        //split into 2 arrays, arrivalTimes_arr and burstTimes_arr based on the index
        for (int i = 0; i < argc_real; ++i)
        {
            if ((i % 2 == 0))
            {
                arrivalTime_arr[arrivalCount++] = process_arr[i];
            }
            else
            {
                burstTime_arr[burstCount++] = process_arr[i];
            }
        }
        //validate the inputs, exit if invalid input found
        validateInputs(argc_real, arrivalTime_arr, burstTime_arr);

        //   Process* processes;
        //  processes = assignProcessID(argc_real, arrivalTime_arr, burstTime_arr);

        Process processes[argc_real / 2];
        int processCount = 0;

        //assign Process ID
        for (int i = 0; i < argc_real / 2; ++i)
        {
            processes[i].processID = processCount += 1;
            processes[i].arrivalTime = arrivalTime_arr[i];
            processes[i].burstTime = burstTime_arr[i];
        }
        
        menu(processes, argc_real);
        //fifo(processes, argc_real);
        //sjf(processes, argc_real);
        // stcf(processes, argc_real);
        //print out all existing process
        //printAllProcesses(processes, argc_real);

        //  printf("%d\n", processes[(argc_real / 2) - 1].arrivalTime);

        return 0;
    }
    else{
        printf("Error! Argument size must be divisible by 2 and not empty!\n");
        printf("Program Ended.\n");
        exit(0);
    }
}
