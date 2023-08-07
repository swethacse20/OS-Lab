#include <stdio.h>
#include <stdbool.h>

// Constants
#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

// Function prototypes
void requestResources(int process, int request[]);
bool isSafeState();
void printAvailableResources();
void printAllocatedResources();
void printMaxResources();
void printNeedMatrix();

// Global variables
int available[MAX_RESOURCES] = {10, 5, 7}; // Available resources
int allocated[MAX_PROCESSES][MAX_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
}; // Allocated resources
int maxRequired[MAX_PROCESSES][MAX_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
}; // Maximum required resources

int main() {
    printf("Initial state:\n");
    printAvailableResources();
    printAllocatedResources();
    printMaxResources();
    printNeedMatrix();

    if (isSafeState()) {
        printf("\nSafe state detected. Starting resource requests.\n");
        
        // Simulate resource requests
        requestResources(0, (int[]){0, 1, 0});
        requestResources(1, (int[]){2, 0, 0});
        requestResources(2, (int[]){3, 0, 2});
        requestResources(3, (int[]){2, 1, 1});
        requestResources(4, (int[]){0, 0, 2});
    } else {
        printf("\nUnsafe state detected. Exiting.\n");
    }

    return 0;
}

void requestResources(int process, int request[]) {
    printf("\nProcess %d requesting resources: {%d, %d, %d}\n", process, request[0], request[1], request[2]);

    // Check if the request is within bounds
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > maxRequired[process][i] || request[i] > available[i]) {
            printf("Request denied: Invalid request or exceeding maximum required resources.\n");
            return;
        }
    }

    // Temporarily allocate resources to check for safety
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= request[i];
        allocated[process][i] += request[i];
    }

    // Check if the new state is safe
    if (isSafeState()) {
        printf("Request granted. New state is safe.\n");
    } else {
        printf("Request denied: Unsafe state detected. Reverting changes.\n");

        // Revert changes
        for (int i = 0; i < MAX_RESOURCES; i++) {
            available[i] += request[i];
            allocated[process][i] -= request[i];
        }
    }

    // Print updated state
    printAvailableResources();
    printAllocatedResources();
    printNeedMatrix();
}

bool isSafeState() {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};

    // Initialize work and finish arrays
    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }

    // Find a process that can complete its resource needs
    bool found;
    do {
        found = false;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < MAX_RESOURCES; j++) {
                    if (maxRequired[i][j] - allocated[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute) {
                    // Process i can complete its resource needs
                    finish[i] = true;
                    found = true;
                    for (int j = 0; j < MAX_RESOURCES; j++) {
                        work[j] += allocated[i][j];
                    }
                }
            }
        }
    } while (found);

    // Check if all processes are finished
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (!finish[i]) {
            return false;
        }
    }
    return true;
}

void printAvailableResources() {
    printf("Available resources: {%d, %d, %d}\n", available[0], available[1], available[2]);
}

void printAllocatedResources() {
    printf("Allocated resources:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("Process %d: {%d, %d, %d}\n", i, allocated[i][0], allocated[i][1], allocated[i][2]);
    }
}

void printMaxResources() {
    printf("Maximum required resources:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("Process %d: {%d, %d, %d}\n", i, maxRequired[i][0], maxRequired[i][1], maxRequired[i][2]);
    }
}

void printNeedMatrix() {
    printf("Need matrix:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("Process %d: {%d, %d, %d}\n", i, maxRequired[i][0] - allocated[i][0], maxRequired[i][1] - allocated[i][1], maxRequired[i][2] - allocated[i][2]);
    }
}
