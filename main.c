#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NAME_LEN 32
#define PHONE_LEN 11

#define NUM_COURSES 20
#define NUM_LEVELS 12
#define NUM_CLASSES 10

#define MAX_LINE_LENGTH 80

struct Course {
    char _course_name[NAME_LEN];
    int _grade;
    bool is_register;
};

struct Student {
    char _name[NAME_LEN];
    char _phone_number[PHONE_LEN];
    struct Course _courses_list[NUM_COURSES];
    int class_number;
    int class_level;
    struct Student *_next;
    struct Student *_prev;
};

struct Class {
    int class_number;
    struct Student first_stud;
};

struct Level {
    int class_level;
    struct Class classes[NUM_CLASSES];
};

struct School {
    struct Level levels[NUM_LEVELS];
};

void open_file(FILE *fptr) {
    // Open a file in read mode
    fptr = fopen("/Users/roeebenezra/CLionProjects/Checkpoint/students_with_class.txt", "r");
    if (fptr == NULL) {
        printf("file isn't opened");
        exit(EXIT_FAILURE);
    }
}

static struct School school_system;

int main() {
    FILE *fptr = NULL;
    char line[MAX_LINE_LENGTH] = {0};

    open_file(fptr);

    while (fgets(line, MAX_LINE_LENGTH, fptr)) {
        printf("%s", line);
        char *filed = strtok(line, " ");

        // loop through the string to extract all others tokens
        while (filed != NULL) {
            printf(" %s\n", filed); //printing each token
            filed = strtok(NULL, " ");
        }
    }

    fclose(fptr);

    return 0;
}
