/* prog.c
 * A variant of structexample3.c from lab 5 with the following changes:
 *
 * 1. The student struct now contains a firstname, a lastname and a student ID
 *    instead of a name and an age.
 * 2. The input data file is again a CSV file but the fields are firstname,
 *    lastname and student ID (an int).
 *
 * Richard Lobb, August 2019.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 80      // The longest line this program will accept
#define MAX_NUM_STUDENTS 500    // The maximum number of students this program can handle
#define MAX_NAME_SIZE 50        // The maximum allowable name length

// The declaration of the student record (or struct). Note that
// the struct contains the first and last names as arrays of characters.

typedef struct student_s Student;

struct student_s {
    char firstname[MAX_NAME_SIZE];
    char lastname[MAX_NAME_SIZE];
    int studentId;
    Student* next;              // Pointer to next student in a list
};

// Create a pool of student records to be allocated on demand

Student studentPool[MAX_NUM_STUDENTS];  // The student pool
int firstFree = 0;

// Return a pointer to a new student record from the pool, after
// filling in the provided first and last name and student ID fields.
// Returns NULL if the student pool is exhausted.
Student* newStudent(const char* firstname, const char* lastname, int studentId)
{
    Student* student = NULL;
    if (firstFree < MAX_NUM_STUDENTS) {
        student = &studentPool[firstFree];
        firstFree += 1;
        strncpy(student->firstname, firstname, MAX_NAME_SIZE);
        student->firstname[MAX_NAME_SIZE - 1] = '\0';  // Make sure it's terminated
        strncpy(student->lastname, lastname, MAX_NAME_SIZE);
        student->lastname[MAX_NAME_SIZE - 1] = '\0';  // Make sure it's terminated
        student->studentId = studentId;
        student->next = NULL;
    }
    return student;
}

bool precedes(const Student* student1, const Student* student2)
{
    if (strcmp(student1->firstname, student2->firstname) < 0) {
        return true;
    } else if (strcmp(student1->firstname, student2->firstname) > 0) {
        return false;
    } else if (strcmp(student1->firstname, student2->firstname) == 0) {
        if (strcmp(student1->lastname, student2->lastname) < 0) {
            return true;
        } else if (strcmp(student1->lastname, student2->lastname) > 0) {
            return false;
        }
    }
    return true;
}

Student* insert(Student* student, Student* list)
{
    bool front = precedes(student, list);
    if (front == true) {
        student->next = list;
        list = student;
    } else {
        student->next = list->next;
        list->next = student;
        if (student->next != NULL) {
            Student* nexts = student->next;
            Student* previous = list;
            while (nexts != NULL) {
                if (precedes(student, nexts) == true) {
                    break;
                } else {
                    student->next = nexts->next;
                    previous->next = nexts;
                    nexts->next = student;
                    previous = nexts;
                    nexts = student->next;
                }
            }
        }
    }
    return list;
}

// Read a single student from a csv input file with student first name in first column,
// second name in the second column and studentId in the last (third) column.
// Returns: A pointer to a Student record, or NULL if EOF occurs or if
// a line with fewer than 2 commas is read.
Student* readOneStudent(FILE* file)
{
    Student* student = NULL;       // Pointer to a student record from the pool
    char buffer[MAX_LINE_LENGTH];
    char* line = fgets(buffer, MAX_LINE_LENGTH, file);
    if (line != NULL) {
        char* commaPos = strchr(buffer, ',');
        if (commaPos != NULL) {
            char* commaPos2 = strchr(commaPos + 1, ',');
            if ( commaPos2 != NULL) {
                *commaPos = '\0';
                *commaPos2 = '\0';
                int studentId = atoi(commaPos2 + 1);
                student = newStudent(buffer, commaPos + 1, studentId);
            }
        }
    }
    return student;
}

// Reads a list of students from a given file. Input stops when
// a blank line is read, or an EOF occurs, or an illegal input
// line is encountered.
// Returns a pointer to the first student in the list or NULL if no
// valid student records could be read.
Student* readStudents(FILE *file)
{
    Student* first = NULL;     // Pointer to the first student in the list
    Student* last = NULL;      // Pointer to the last student in the list
    Student* student = readOneStudent(file);
    while (student != NULL) {
        if (first == NULL) {
            first = last = student;   // Empty list case
        } else {
            first = insert(student, first);
        }
        student = readOneStudent(file);
    }
    return first;
}

// printOneStudent: prints a single student, passed by value
void printOneStudent(Student student)
{
    printf("%s %s (%d)\n", student.firstname, student.lastname, student.studentId);
}


// printStudents: print all students in a list of students, passed
// by reference
void printStudents(const Student* student)
{
    while (student != NULL) {
        printOneStudent(*student);
        student = student->next;
    }
}


// Main program. Read a linked list of students from a csv file, then display
// the contents of that list.
int main(int argc, char* argv[])
{
    if (argv[1] != NULL && argv[2] == NULL) {
        FILE* inputFile = fopen(argv[1], "r");
        if (inputFile == NULL) {
            fprintf(stderr, "File '%s' not found\n", argv[1]);
        } else {
            Student* studentList = readStudents(inputFile);
            printStudents(studentList);

            // The program could now do various things that make use of
            // the linked list, like deleting students and adding new ones,
            // but the program is already quite long enough!
        }
    } else {
        fprintf(stderr, "Usage: prog filename");
    }
}
