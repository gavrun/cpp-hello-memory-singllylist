// cpp-hello-memory-singllylist.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// singly list

#include <stdio.h>  // For using printf
#include <stdlib.h> // For using malloc and free
#include <string.h> // For working with strings

// Definition of the Student structure for each list element
struct Student {
    int id; // Field for storing the student's ID
    char name[50]; // Field for storing the student's name
    struct Student* next; // Pointer to the next element in the list
};

// Function to add a new student to the end of the linked list
void addStudent(struct Student** head, int new_id, const char* new_name) {
    // Allocate memory for the new student
    struct Student* new_student = (struct Student*)malloc(sizeof(struct Student));

    // Check if memory allocation was successful
    if (new_student == NULL) {
        printf("ERR: failed to allocate memory for a new student.\n");
        return; // Exit the function if memory allocation fails
    }

    // Fill in the fields of the new node (id and name)
    new_student->id = new_id; // Set the student's ID
    strcpy_s(new_student->name, sizeof(new_student->name), new_name); // Copy the student's name, with sting length check
    new_student->next = NULL; // Set the next element to NULL as this is the last element

    // If the list is empty (head points to NULL)
    if (*head == NULL) {
        *head = new_student; // The new element becomes the head of the list
    }
    else {
        // Otherwise, find the last element in the list
        struct Student* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next; // Move to the next element
        }
        // Attach the new element to the last element of the list
        temp->next = new_student;
    }
}

// Function to delete a student by ID
void deleteStudent(struct Student** head, int id) {
    struct Student* temp = *head;
    struct Student* prev = NULL;

    // If the first element itself is the student we want to delete
    if (temp != NULL && temp->id == id) {
        *head = temp->next; // Change the head of the list
        free(temp); // Free the memory
        return;
    }

    // Search for the student until we find or reach the end of the list
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    // If the student with the given ID is not found
    if (temp == NULL) {
        printf("Student with ID %d not found.\n", id);
        return;
    }

    // Unlink the student from the list
    prev->next = temp->next;
    free(temp); // Free the memory
}

// Function to print the list of students as a table (ID + Name)
void printStudents(struct Student* head) {
    struct Student* temp = head;
    printf("ID\tName\n");
    printf("-------------------------\n");
    while (temp != NULL) {
        printf("%d\t%s\n", temp->id, temp->name); // Print the student's ID and name
        temp = temp->next;
    }
}

// Main function of the program
int main() {
    struct Student* head = NULL; // Initialize the head pointer to NULL (the list is empty)

    // Print message the list of students is empty
    printf("Students list.\n\nStudents list is empty.\n");
    printStudents(head);

    // Add 3 students to the list with ID 101, 102 and 103
    addStudent(&head, 101, "Pedro");
    addStudent(&head, 102, "Maria");
    addStudent(&head, 103, "Alexey");

    // Print the list of students before deletion
    printf("\nStudents list before removal:\n");
    printStudents(head);

    // Delete the student with ID 102 example
    printf("\nRemoving student with ID 102...\n");
    deleteStudent(&head, 102);

    // Print the updated list of students
    printf("\nStudents list after removal:\n");
    printStudents(head);

    // Free the allocated memory at the end of the program (free all nodes)
    struct Student* current = head;
    struct Student* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0; // End the program
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
