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
};

struct Class {
    struct Student *_head_stud_list;
    struct Student *_tail_stud_list;
};

struct Level {
    struct Class _classes[NUM_CLASSES];
};

struct School {
    struct Level _levels[NUM_LEVELS];
};
// Function prototypes
FILE *open_file();
void INITDB(FILE *);
void printDB();
void menuDB();
void freePTRsDB();

void addNewStudent();
void deleteStudent();
void updateStudentInfo();
void searchStudent();
void topStudentsByCourse();
void potentialDropouts();
void calculateAveragePerCourse();
void exportToCSV();

// static DB
static struct School school_system;

int main() {
    FILE *fptr = open_file();

    INITDB(fptr);
    menuDB();
//    printDB();
    freePTRsDB();
    fclose(fptr);

    return 0;
}


void menuDB() {
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add new student\n");
        printf("2. Delete student\n");
        printf("3. Update student information\n");
        printf("4. Search student\n");
        printf("5. Top students by course\n");
        printf("6. Potential dropouts\n");
        printf("7. Calculate average per course\n");
        printf("8. Export to CSV\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addNewStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                updateStudentInfo();
                break;
            case 4:
                searchStudent();
                break;
            case 5:
                topStudentsByCourse();
                break;
            case 6:
                potentialDropouts();
                break;
            case 7:
                calculateAveragePerCourse();
                break;
            case 8:
                exportToCSV();
                break;
            case 9:
                printf("Exiting the program.\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void addNewStudent() {
    // Implement code to add a new student to the database
    printf("Adding a new student...\n");
}

void deleteStudent() {
    // Implement code to delete a student from the database
    printf("Deleting a student...\n");
}

void updateStudentInfo() {
    // Implement code to update student information
    printf("Updating student information...\n");
}

void searchStudent() {
    // Implement code to search for a student and display their information
    printf("Searching for a student...\n");
}

void topStudentsByCourse() {
    // Implement code to find the top students by course
    printf("Top students by course...\n");
}

void potentialDropouts() {
    // Implement code to find potential dropouts based on parameters
    printf("Potential dropouts...\n");
}

void calculateAveragePerCourse() {
    // Implement code to calculate the average per course
    printf("Calculating average per course...\n");
}

void exportToCSV() {
    // Implement code to export the database to a CSV file
    printf("Exporting to CSV...\n");
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
void INITDB(FILE *fptr) {
    char line[MAX_LINE_LENGTH] = {0};
    char *filed = NULL;
    struct Student *stud = NULL;
    char student_data[15][MAX_INP_LENGTH] = {{0}};

    while (fgets(line, MAX_LINE_LENGTH, fptr)) {
        filed = strtok(line, " ");
        // loop through the string to extract all others tokens

        for (int i = 0; filed != NULL; i++) {
            strcpy(student_data[i], filed);
            filed = strtok(NULL, " ");
        }

        stud = malloc(sizeof(struct Student));
        stud->_next = NULL;
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
void printDB() {
    struct Student *s = NULL;

    for (int i = 0; i < NUM_LEVELS; i++) {
        for (int j = 0; j < NUM_CLASSES; j++) {
            s = school_system._levels[i]._classes[j]._head_stud_list;
            while (s) {
                printf("%s %s %s %d %d ", s->_first_name, s->_last_name, s->_phone_number, s->_class_level,
                       s->_class_number);
                for (int k = 0; k < NUM_COURSES; k++)
                    printf("%d ", s->_courses_list[k]._grade);
                printf("\n");
                s = s->_next;
            }
        }
    }
}

// free memory in DB func
void freePTRsDB() {
    struct Student *s = NULL;
    struct Student *temp = NULL;

    for (int i = 0; i < NUM_LEVELS; i++) {
        for (int j = 0; j < NUM_CLASSES; j++) {
            s = school_system._levels[i]._classes[j]._head_stud_list;
            while (s) {
                temp = s;
                s = s->_next;
                free(temp);
            }
        }
    }
}
