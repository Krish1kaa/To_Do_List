#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define priority levels
enum Priority {
    HIGH,
    MEDIUM,
    LOW
};

// Define a structure for a task
struct Task {
    char description[100];
    enum Priority priority;  // New field for priority
    struct Task* next;
};

// Global variable for the head of the linked list
struct Task* head = NULL;

// Function to add a task to the to-do list with a priority
void addTask(const char* description, enum Priority priority) {
    struct Task* newTask = (struct Task*)malloc(sizeof(struct Task));
    if (newTask == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    strcpy(newTask->description, description);
    newTask->priority = priority;
    newTask->next = head;
    head = newTask;
    
    // Map priority levels to strings
    const char* priorityStrings[] = {"High", "Medium", "Low"};
    
    printf("Task added: %s (Priority: %s)\n", description, priorityStrings[priority]);
}

// Function to remove a task from the to-do list
void removeTask(const char* description) {
    struct Task* current = head;
    struct Task* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->description, description) == 0) {
            if (previous == NULL) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Task removed: %s\n", description);
            return;
        }

        previous = current;
        current = current->next;
    }

    printf("Task not found: %s\n", description);
}

// Function to display tasks in order of priority
void displayTasksByPriority() {
    const char* priorityStrings[] = {"High", "Medium", "Low"};
    int priority;

    // Iterate through each priority level starting from HIGH
    for (priority = HIGH; priority <= LOW; priority++) {
        struct Task* current = head;
        int found = 0;

        printf("\nTasks with Priority: %s\n", priorityStrings[priority]);

        // Traverse the linked list
        while (current != NULL) {
            if (current->priority == priority) {
                printf("- %s\n", current->description);
                found = 1;
            }
            current = current->next;
        }

        // If no task with the current priority is found, display a message
        if (!found) {
            printf("No tasks with Priority: %s\n", priorityStrings[priority]);
        }
    }
}


// Function to free the memory used by the linked list
void freeList() {
    struct Task* current = head;
    while (current != NULL) {
        struct Task* next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    int choice;
    char description[100];
    int priority;

    while (1) {
        printf("\n1. Add Task\n2. Remove Task\n3. Display Tasks\n4. Quit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter task description: ");
                scanf(" %[^\n]", description);
                printf("Enter task priority (0: High, 1: Medium, 2: Low): ");
                scanf("%d", &priority);
                addTask(description, priority);
                break;
            case 2:
                printf("Enter task description to remove: ");
                scanf(" %[^\n]", description);
                removeTask(description);
                break;
            case 3:
                // Display tasks sorted by priority
                displayTasksByPriority();
                break;

            case 4:
                freeList();
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}