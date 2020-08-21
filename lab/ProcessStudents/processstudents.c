/* processstudents.c: a program to process students read from a file.
 * In fact it does very little other then read the students and link
 * them into a list, which it then prints.
 * Written to demonstrate the use of structs, linked lists and separate
 * compilation for course ENCE260.
 *
 * Author: Richard Lobb
 * Date: August 2014.
 */

#include <stdio.h>
#include <string.h>
#include "student.h"
#include "studentlist.h"

int main(void)
{
    char name[MAX_NAME_SIZE] = {0};
    const Student* student = NULL;
    FILE* inputFile = fopen("studlist.txt", "r");
    if (inputFile == NULL) {
        fprintf(stderr, "File not found\n");
    } else { 
        Student* studentList = readStudents(inputFile);
        puts("Enter the name of a student");
        fgets(name, MAX_NAME_SIZE, stdin); // Reads a line from stdin. Trust me
        if (name[strlen(name) - 1] == '\n') {
            name[strlen(name) - 1] = '\0';
        }
        student = findStudent(studentList, name);
        if (student == NULL) {
            printf("'%s' not found\n", name);
        } else {
            printOneStudent(*student);
        }
    }
}
