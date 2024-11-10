/*
- Project: Automatic Medicine Dispenser
- Description:This system manages multiple containers of medicines, where each container can hold a specific type of medicine.
             The system allows the user to refill, dispense, and view medicines in containers.
             It provides an option to set dispensing times and alerts when the quantity of a medicine is low.
- Version: 1.0
- File: AMD.c
- Author: Gowri A Sankar
- Date: 10-11-24
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEDICINES 10         // Maximum number of medicines in a container
#define NUM_CONTAINERS 5         // Number of containers
#define LOW_QUANTITY_THRESHOLD 2 // Threshold to alert low quantity

// Define a structure for a container (each container holds one type of medicine)
typedef struct Node
{
    char medicine;     // Medicine representation
    struct Node *next; // Pointer to the next node
} Node;

typedef struct Container
{
    char name[50];       // Name of the medicine in this container
    Node *front;         // Front pointer of the queue
    Node *rear;          // Rear pointer of the queue
    int quantity;        // Current quantity of medicines in the container
    int motorStatus;     // Motor status (0 = off, 1 = on)
    int dispenseTime[3]; // Dispense time in HH MM SS
} Container;

Container containers[NUM_CONTAINERS]; // Array of containers

// Function prototypes
void initializeContainers();
void setup();
void instructions();
void refillMedicine();
void updateSettings();
void displayContainerInfo();
void dispenseMedicine(int containerIndex);
void exitSystem();
void alertLowQuantity();
void dispenseAtSetTime();

void main()
{
    initializeContainers();

    instructions();

    printf("\nSmart Medicine Dispenser System\n");
    void (*menuFunctions[])() = {setup, refillMedicine, updateSettings, displayContainerInfo, dispenseAtSetTime, instructions, exitSystem};
    int choice = 0;

    while (1)
    {
        printf("\n--- MENU ---\n");
        printf("1. Setup\n");
        printf("2. Refill Medicine\n");
        printf("3. Update Settings\n");
        printf("4. View All Containers\n");
        printf("5. Dispense Medicine at Set Time\n");
        printf("6. Instruction Manual\n");
        printf("7. Exit\n");
        alertLowQuantity();
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 7)
        {
            (*menuFunctions[choice - 1])();
        }
        else
        {
            printf("Invalid choice! Please select a valid option.\n");
        }
    }
}

// Function to initialize containers
void initializeContainers()
{
    for (int i = 0; i < NUM_CONTAINERS; i++)
    {
        containers[i].name[0] = '\0';
        containers[i].front = NULL;
        containers[i].rear = NULL;
        containers[i].quantity = 0;
        containers[i].motorStatus = 0;
        containers[i].dispenseTime[0] = -1; // Default unset time
        containers[i].dispenseTime[1] = -1;
        containers[i].dispenseTime[2] = -1;
    }
}

// Function to display the instruction manual
void instructions()
{
    printf("\n--- Instruction Manual ---\n");
    printf("Welcome to the Smart Medicine Dispenser System.\n");
    printf("You can manage up to 5 containers, each holding a maximum of 10 medicines.\n");

    printf("\n1. Setup: Choose a container (1-5) and Iniatilize Name and Time of dispenisning.\n");
    printf("2. Refill Medicine: Choose a container and refill up to the max capacity (10). If full, refill is rejected.\n");
    printf("3. Update Settings: Change the medicine name, Change Time, or reset a container.\n");
    printf("4. View All Containers: See current medicine, quantity and time set for each container.\n");
    printf("5. Dispense Medicine at Set Time: Current time has to be entered and medicine will be automatically dispensed when the current time matches the pre-set dispense time for a container.\n");
    printf("6. Instruction Manual: View Instruction Manual again.\n");
    printf("7. Exit: Exit the system.\n");
}

// Function to add medicine to a container
void setup()
{
    int containerIndex;
    int time[3];

    printf("Enter container number (1-5): ");
    scanf("%d", &containerIndex);

    // Validate container number Input
    while (containerIndex < 1 || containerIndex > NUM_CONTAINERS)
    {
        printf("Invalid Input! Please enter a value between 1 and 5: ");
        scanf("%d", &containerIndex);
    }

    containerIndex--;

    if (strlen(containers[containerIndex].name) == 0)
    {
        printf("Enter medicine name for this container: ");
        scanf("%s", containers[containerIndex].name);

        printf("Enter dispense time (HH MM SS): ");
        scanf("%d %d %d", &time[0], &time[1], &time[2]);

        // Validate Time Input
        while (time[0] < 0 || time[0] >= 24 || time[1] < 0 || time[1] >= 60 || time[2] < 0 || time[2] >= 60)
        {
            printf("Invalid time entered! Please enter a valid time (HH MM SS): ");
            scanf("%d %d %d", &time[0], &time[1], &time[2]);
        }

        containers[containerIndex].dispenseTime[0] = time[0];
        containers[containerIndex].dispenseTime[1] = time[1];
        containers[containerIndex].dispenseTime[2] = time[2];
    }
    else
    {
        printf("Container %d already Setup\n", containerIndex + 1);
    }
}

// Function to refill medicine
void refillMedicine()
{
    char medicine;
    int containerIndex;

    printf("Enter container number (1-5): ");
    scanf("%d", &containerIndex);

    while (containerIndex < 1 || containerIndex > NUM_CONTAINERS)
    {
        printf("Invalid Input! Please enter a value between 1 and 5: ");
        scanf("%d", &containerIndex);
    }

    containerIndex--;

    if (strlen(containers[containerIndex].name) == 0)
    {
        printf("Container %d not setup\nPlease setup the cointainer before refilling\n", containerIndex + 1);
        return;
    }

    printf("Medicine: %s\n", containers[containerIndex].name);

    printf("Enter medicines to add (enter O for medicine). Enter '1' to stop.\n");
    while (1)
    {
        if (containers[containerIndex].quantity >= MAX_MEDICINES)
        {
            printf("Maximum Medicines Entered!!\n");
            printf("You cannot Enter Futher\n");
            return;
        }

        printf("Medicine: ");
        scanf(" %c", &medicine);
        if (medicine == '1')
        {
            break;
        }

        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->medicine = medicine;
        newNode->next = NULL;

        if (containers[containerIndex].rear == NULL)
        {
            containers[containerIndex].front = containers[containerIndex].rear = newNode;
        }
        else
        {
            containers[containerIndex].rear->next = newNode;
            containers[containerIndex].rear = newNode;
        }

        containers[containerIndex].quantity++;
    }

    printf("Refilled medicines in container %d.\n", containerIndex + 1);
}

// Function to display pictorial representation and container info
void displayContainerInfo()
{
    Node *current;
    int index;
    int all_empty = 1;

    for (index = 0; index < NUM_CONTAINERS; index++)
    {
        if (containers[index].name[0] == '\0')
        {
            continue;
        }

        all_empty = 0;
        printf("\n--- Container %d ---\n", index + 1);
        printf("Medicine Name: %s\n", containers[index].name);
        printf("Current Quantity: %d\n", containers[index].quantity);
        printf("Dispense Time: %d:%d:%d\n", containers[index].dispenseTime[0], containers[index].dispenseTime[1], containers[index].dispenseTime[2]);

        if (containers[index].quantity != 0)
        {
            printf("Medicine Stack:\n");
            current = containers[index].front;
            while (current != NULL)
            {
                printf("|%c|\n", current->medicine);
                current = current->next;
            }
        }
    }

    if (all_empty)
    {
        printf("All Containers Empty");
    }
}

// Function to alert low quantity
void alertLowQuantity()
{
    int i;
    for (i = 0; i < NUM_CONTAINERS; i++)
    {
        if (containers[i].name[0] != '\0')
        {
            if (containers[i].quantity < LOW_QUANTITY_THRESHOLD)
            {
                printf("ALERT: Low quantity in container %d! Only %d medicines left.\n", i + 1, containers[i].quantity);
            }
        }
    }
}

// Function to dispense medicine from a container
void dispenseMedicine(int containerIndex)
{
    Node *temp;
    if (containers[containerIndex].quantity > 0)
    {
        temp = containers[containerIndex].front;
        containers[containerIndex].front = containers[containerIndex].front->next;
        free(temp);
        containers[containerIndex].quantity--;

        containers[containerIndex].motorStatus = 1; // Turn motor ON
        printf("Dispensed one medicine from container %d. Remaining quantity: %d\n", containerIndex + 1, containers[containerIndex].quantity);
        printf("\n      \\__O__/\n");
        containers[containerIndex].motorStatus = 0; // Turn motor OFF

        alertLowQuantity();
    }
    else
    {
        printf("Container %d is empty! Cannot dispense medicine.\n", containerIndex + 1);
    }
}

// Function to check time and dispense medicine
void dispenseAtSetTime()
{
    int currentTime[3];
    int all_empty = 1;

    printf("Enter current time (HH MM SS): ");
    scanf("%d %d %d", &currentTime[0], &currentTime[1], &currentTime[2]);

    for (int i = 0; i < NUM_CONTAINERS; i++)
    {
        if (containers[i].dispenseTime[0] == currentTime[0] &&
            containers[i].dispenseTime[1] == currentTime[1] &&
            containers[i].dispenseTime[2] == currentTime[2])
        {
            all_empty = 0;
            printf("Time match found for container %d. Dispensing medicine...\n", i + 1);
            dispenseMedicine(i);
        }
    }

    if (all_empty)
    {
        printf("Time match not found\n");
    }
}

// Function to update container settings
void updateSettings()
{
    int containerIndex, choice;
    char flag;
    int time[3];

    printf("Enter the container number (1-5): ");
    scanf("%d", &containerIndex);

    while (containerIndex < 1 || containerIndex > NUM_CONTAINERS)
    {
        printf("Invalid Input! Please enter a value between 1 and 5: ");
        scanf("%d", &containerIndex);
    }

    containerIndex--;

    if (containers[containerIndex].name[0] == '\0')
    {
        printf("Container %d not setup\nPlease setup the cointainer before updating\n", containerIndex + 1);
        return;
    }

    printf("1. Change Medicine Name\n");
    printf("2. Change Time\n");
    printf("3. Delete Container Information\n");
    printf("4. Go Back\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
        printf("Are you sure you want to change name of container %d (y/n): ", containerIndex + 1);
        scanf(" %c", &flag);
        if (flag == 'y' || flag == 'Y')
        {
            printf("Enter new medicine name: ");
            scanf("%s", containers[containerIndex].name);
        }
        else
        {
            printf("Change Name Cancelled");
        }
        break;
    }
    case 2:
    {
        printf("Are you sure you want to change name of container %d (y/n): ", containerIndex + 1);
        scanf(" %c", &flag);
        if (flag == 'y' || flag == 'Y')
        {
            printf("Enter medicine name for this container: ");
            scanf("%s", containers[containerIndex].name);

            printf("Enter dispense time (HH MM SS): ");
            scanf("%d %d %d", &time[0], &time[1], &time[2]);

            while (time[0] < 0 || time[0] >= 24 || time[1] < 0 || time[1] >= 60 || time[2] < 0 || time[2] >= 60)
            {
                printf("Invalid time entered! Please enter a valid time (HH MM SS): ");
                scanf("%d %d %d", &time[0], &time[1], &time[2]);
            }

            containers[containerIndex].dispenseTime[0] = time[0];
            containers[containerIndex].dispenseTime[1] = time[1];
            containers[containerIndex].dispenseTime[2] = time[2];
        }
        else
        {
            printf("Change Name Cancelled");
        }
        break;
    }
    case 3:
    {
        printf("Warning: All Information related to the container will be lost permanently\n");
        printf("Are you sure you want to change name of container %d (y/n): ", containerIndex + 1);
        scanf(" %c", &flag);
        if (flag == 'y' || flag == 'Y')
        {
            initializeContainers();
            printf("Container %d Reset\n", containerIndex + 1);
        }
        else
        {
            printf("Reset Container Information Cancelled");
        }
        break;
    }
    case 4:
    {
        break;
    }
    default:
    {
        printf("Enter Valid Input\n");
    }
    }
}

// Function to exit the system
void exitSystem()
{
    printf("Exiting system.\n");
    exit(0);
}
