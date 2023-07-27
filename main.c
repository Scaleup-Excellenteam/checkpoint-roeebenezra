#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NAME_LEN 32

#define NUM_COURSES 10
#define NUM_LEVELS 12
#define NUM_CLASSES 10

#define MAX_LINE_LENGTH 80
#define MAX_INP_LENGTH 50

struct Course {
    char _course_name[NAME_LEN];
    int _grade;
    bool _is_register;
};

struct Student {
    char _first_name[MAX_INP_LENGTH];
    char _last_name[MAX_INP_LENGTH];
    char _phone_number[11];
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


FILE *open_file();
void INITDB(FILE *);
void printDB();


static struct School school_system;

int main() {
    FILE *fptr = open_file();

    INITDB(fptr);
    printDB();

    fclose(fptr);

    return 0;
}


// Open file function
FILE *open_file() {
    // Open a file in read mode
    FILE *fptr = fopen("/Users/roeebenezra/CLionProjects/Checkpoint/students_with_class.txt", "r");
    if (fptr == NULL) {
        printf("file isn't opened");
        exit(EXIT_FAILURE);
    }
    return fptr;
}


// Init DB function
void INITDB(FILE *fptr){
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

        struct Student *stud = malloc(sizeof(struct Student));
        for (int i = 0, j = 5; i < NUM_COURSES; i++, j++) {
            int grade = atoi(student_data[j]);
            struct Course c = {"CourseName", grade, false};
            stud->_courses_list[i] = c;
        }

        strcpy(stud->_first_name, student_data[0]);
        strcpy(stud->_last_name, student_data[1]);
        strcpy(stud->_phone_number, student_data[2]);
        stud->_class_level = atoi(student_data[3]);
        stud->_class_number = atoi(student_data[4]);

        struct Student **class_head = &school_system._levels[stud->_class_level - 1]._classes[stud->_class_number -
                                                                                              1]._head_stud_list;
        struct Student **class_tail = &school_system._levels[stud->_class_level - 1]._classes[stud->_class_number -
                                                                                              1]._tail_stud_list;

        if (*class_head) {
            (*class_tail)->_next = stud;
            *class_tail = stud;
        } else {
            *class_head = stud;
            *class_tail = *class_head;
        }
    }
}

// print DB func
void printDB(){
    for (int i = 0; i < NUM_LEVELS ; i++) {
        for (int j = 0; j < NUM_CLASSES ; j++) {
            struct Student *s = school_system._levels[i]._classes[j]._head_stud_list;
            while (s) {
                printf("%s %s %s %d %d ", s->_first_name, s->_last_name, s->_phone_number, s->_class_level, s->_class_number);
                for(int k = 0 ; k < NUM_COURSES; k++)
                    printf("%d ", s->_courses_list[k]._grade);
                printf("\n");
                s = s->_next;
            }
        }
    }
}
