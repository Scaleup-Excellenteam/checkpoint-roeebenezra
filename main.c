#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NAME_LEN 32
#define PHONE_LEN 24

#define NUM_COURSES 10
#define NUM_LEVELS 12
#define NUM_CLASSES 10

#define MAX_LINE_LENGTH 80

struct Course {
    char _course_name[NAME_LEN];
    int _grade;
    bool _is_register;
};

struct Student {
    char *_first_name;
    char *_last_name;
    char *_phone_number;
    struct Course _courses_list[NUM_COURSES];
    int _class_number;
    int _class_level;
    struct Student *_next;
//    struct Student *_prev;
};

struct Class {
    int _class_number;
    struct Student *_head_stud_list;
    struct Student *_tail_stud_list;
};

struct Level {
    int _class_level;
    struct Class _classes[NUM_CLASSES];
};

struct School {
    struct Level _levels[NUM_LEVELS];
};


FILE *open_file() {
    // Open a file in read mode
    FILE *fptr = fopen("/Users/roeebenezra/CLionProjects/Checkpoint/students_with_class.txt", "r");
    if (fptr == NULL) {
        printf("file isn't opened");
        exit(EXIT_FAILURE);
    }
    return fptr;
}


static struct School school_system;

int main() {
    FILE *fptr = open_file();
    char line[MAX_LINE_LENGTH];


    while (fgets(line, MAX_LINE_LENGTH, fptr)) {
        char *student_data[15];
        char *filed = strtok(line, " ");
        // loop through the string to extract all others tokens

        for (int i = 0; filed != NULL; i++) {
            student_data[i] = malloc(strlen(filed) + 1);
            student_data[i] = filed;
            filed = strtok(NULL, " ");
        }

        struct Student stud;
        for (int i = 0, j = 4; i < NUM_COURSES; i++, j++) {
            int grade = atoi(student_data[j]);
            struct Course c = {"CourseName", grade, false};
            stud._courses_list[i] = c;
        }

        stud._first_name = malloc(strlen(student_data[0]));
        strcpy(stud._first_name, student_data[0]);
        stud._last_name = malloc(strlen(student_data[1]));
        strcpy(stud._last_name, student_data[1]);
        stud._phone_number = malloc(strlen(student_data[2]));
        strcpy(stud._phone_number, student_data[2]);

    }

    fclose(fptr);

    return 0;
}
