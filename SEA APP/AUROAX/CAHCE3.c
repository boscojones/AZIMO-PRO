#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_TASKS 8 // Maximum number of tasks

// Structure for Kernel Task
typedef struct {
    char *provider; // Storage provider (AWS, Azure, Google, Local)
    char *path;     // Path in the file system
    int taskId;     // Task ID
} KernelTask;

// Global variables
KernelTask tasks[MAX_TASKS];
int currentTask = 0;
pthread_mutex_t lock;

// Function to simulate processing a task
void* processTask(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock);
        if (currentTask >= MAX_TASKS) {
            pthread_mutex_unlock(&lock);
            break; // No remaining tasks
        }
        KernelTask task = tasks[currentTask];
        currentTask++;
        pthread_mutex_unlock(&lock);

        // Simulate task processing
        printf("Kernel: Processing task %d in %s - path: %s\n", task.taskId, task.provider, task.path);
        sleep(1); // Simulate processing time
        printf("Kernel: Finished task %d\n", task.taskId);
    }
    return NULL;
}

// Main function
int main() {
    // Define tasks to be processed by the kernel
    tasks[0] = (KernelTask){"AWS", "s3://bucket1/data", 1};
    tasks[1] = (KernelTask){"Azure", "azure://container/data", 2};
    tasks[2] = (KernelTask){"Google", "gcs://bucket2/data", 3};
    tasks[3] = (KernelTask){"Local", "/local/disk1/data", 4};
    tasks[4] = (KernelTask){"AWS", "s3://bucket2/data", 5};
    tasks[5] = (KernelTask){"Azure", "azure://container2/data", 6};
    tasks[6] = (KernelTask){"Google", "gcs://bucket3/data", 7};
    tasks[7] = (KernelTask){"Local", "/local/disk2/data", 8};

    pthread_t threads[4]; // Array to hold thread IDs
    pthread_mutex_init(&lock, NULL); // Initialize the mutex

    // Create threads to process tasks
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, processTask, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock); // Destroy the mutex
    printf("Kernel: All tasks have been processed.\n");

    return 0;
}
