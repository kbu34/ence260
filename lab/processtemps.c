#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 500 // defines the maximum length of a line


// Finds the nth occurance of a specified character.
// Returns a pointer to the nth occurance.
// Returns null if not found.
char* strchrn(char* s, int c, int n)
{
    char* ptr = NULL;
    int found = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == c) {
            found++;
            if (found == n) {
                ptr = &s[i];
            }
        }
    }
    return ptr;
}


// Looks through the header of the file and extracts the site name.
// Prints the name of the site if found.
void processsite(FILE *file, double thres)
{
    char buffer[MAX_LINE_LENGTH];
    char* siteline = fgets(buffer, MAX_LINE_LENGTH, file);
    if (siteline != NULL) {
        siteline = fgets(buffer, MAX_LINE_LENGTH, file);
        siteline = fgets(buffer, MAX_LINE_LENGTH, file);
        char* commaPos = strchrn(buffer, ',', 1);
        if (commaPos != NULL) {
            *commaPos = '\0';
            printf("Dates when %.1lf C was reached at %s\n\n", thres, siteline);
        }
    }
}

// Looks through the main data of the file and finds the date that the
// temperature goes through the threshold.
// Prints the date and temperature if the temperature is equal to or 
// higher than the threshold.
void processdata(FILE *file, double thres)
{
    char buffer[MAX_LINE_LENGTH];
    char* dataline = fgets(buffer, MAX_LINE_LENGTH, file);
    if (dataline != NULL) {
        for (int i = 0; i < 6; i++) {
            dataline = fgets(buffer, MAX_LINE_LENGTH, file);
        }
    }
    while (*dataline != '\n') {
        char* date = strchrn(dataline, ',', 1);
        char* dateend = strchrn(dataline, ':', 1);
        char* mid = strchrn(dataline, ',', 2);
        double temperature = atof(mid + 1);
        if (temperature >= thres) {
            *dateend = '\0';
            char yearstr[5];
            char monthstr[3];
            char daystr[3];
            strncpy(yearstr, date + 1, 4);
            strncpy(monthstr, date + 5, 2);
            strncpy(daystr, date + 7, 2);
            yearstr[4] = monthstr[2] = daystr[2] = '\0';
            int year = atoi(yearstr);
            int month = atoi(monthstr);
            int day = atoi(daystr);
            printf("%02d/%02d/%d%9.1lf C\n", day, month, year, temperature);
        }
        dataline = fgets(buffer, MAX_LINE_LENGTH, file);
    }
}


// Main program. Reads the file and calls the other functions.
// Prints error messages if the file is not found or parameters are
// not correct.
int main(int argc, char* argv[])
{
    if (argv[1] != NULL && argc == 3) {
        FILE* inputFile = fopen(argv[1], "r");
        if (inputFile == NULL) {
            fprintf(stderr, "File '%s' not found\n", argv[1]);
        } else {
            double thres = atof(argv[2]);
            processsite(inputFile, thres);
            printf("   Date       MaxTemp\n");
            processdata(inputFile, thres);
        }
    } else {
        fprintf(stderr, "Usage: processtemps filename threshold");
    }
}
