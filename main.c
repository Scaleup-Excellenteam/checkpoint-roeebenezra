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

int convertToInt(const char *str);

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

// User actions in db
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


// Function to convert a string to an integer using strtol
int convertToInt(const char *str) {
    char *endptr;
    long int num = strtol(str, &endptr, 10);

    if (*endptr != '\0') {
        return -1; // Conversion error
    }

    return (int) num;
}


// Function to add a new student to the school db
void addNewStudent(struct School *school) {
    char first_name[MAX_INP_LENGTH];
    char last_name[MAX_INP_LENGTH];
    char phone_number[11];
    char class_number_str[5];
    char class_level_str[5];

    // Input student details
    printf("Enter first name (without spaces): ");
    scanf("%s", first_name);

    printf("Enter last name (without spaces): ");
    scanf("%s", last_name);

    printf("Enter phone number: ");
    scanf("%s", phone_number);

    printf("Enter class number: ");
    scanf("%s", class_number_str);

    printf("Enter class level: ");
    scanf("%s", class_level_str);

    // Convert class number and level to integers
    int class_number = convertToInt(class_number_str);
    int class_level = convertToInt(class_level_str);

    // Check for conversion errors
    if (class_number == -1 || class_level == -1) {
        printf("Invalid class level or number.\n");
        return;
    }
    // Check for valid class level and number
    if (class_level < 1 || class_level > NUM_LEVELS || class_number < 1 || class_number > NUM_CLASSES) {
        printf("Invalid class level or number.\n");
        return;
    }

    // Create a new student
    struct Student *new_student = (struct Student *) malloc(sizeof(struct Student));
    strcpy(new_student->_first_name, first_name);
    strcpy(new_student->_last_name, last_name);
    strcpy(new_student->_phone_number, phone_number);
    new_student->_class_number = class_number;
    new_student->_class_level = class_level;
    new_student->_next = NULL;

    // Add the student to the appropriate class
    struct Student **class_head = &school_system._levels[new_student->_class_level - 1]._classes[
            new_student->_class_number - 1]._head_stud_list;
    struct Student **class_tail = &school_system._levels[new_student->_class_level - 1]._classes[
            new_student->_class_number - 1]._tail_stud_list;

    if (*class_head) {
        (*class_tail)->_next = new_student;
        *class_tail = new_student;
    } else {
        *class_head = new_student;
        *class_tail = *class_head;
    }

    printf("New student added successfully!\n");
}


// Function to delete a student to the school db
void deleteStudent() {
    // Test the deleteStudent function
    char first_name[MAX_INP_LENGTH];
    char last_name[MAX_INP_LENGTH];

    printf("Enter the first name of the student to delete: ");
    scanf("%s", first_name);

    printf("Enter the last name of the student to delete: ");
    scanf("%s", last_name);

    int i, j;
    bool student_found = false;

    // Traverse through all levels, classes, and students to find the student
    for (i = 0; i < NUM_LEVELS; i++) {
        for (j = 0; j < NUM_CLASSES; j++) {
            struct Class *class = &(school_system._levels[i]._classes[j]);
            struct Student *curr_student = class->_head_stud_list;
            struct Student *prev_student = NULL;

            while (curr_student != NULL) {
                // Compare the first name and last name of the current student with the target names
                if (strcmp(curr_student->_first_name, first_name) == 0 &&
                    strcmp(curr_student->_last_name, last_name) == 0) {
                    student_found = true;

                    // If the student is the head of the linked list
                    if (prev_student == NULL) {
                        class->_head_stud_list = curr_student->_next;
                    } else {
                        prev_student->_next = curr_student->_next;
                    }

                    // If the student is the tail of the linked list
                    if (curr_student == class->_tail_stud_list) {
                        class->_tail_stud_list = prev_student;
                    }

                    // Free memory allocated for the student
                    free(curr_student);
                    curr_student = NULL;

                    printf("Student deleted successfully!\n");
                    break;
                }

                prev_student = curr_student;
                curr_student = curr_student->_next;
            }

            if (student_found) {
                break;
            }
        }

        if (student_found) {
            break;
        }
    }

    if (!student_found) {
        printf("Student not found in the database.\n");
    }

}


// Function to update a student's information in the school data structure
void updateStudentInfo() {
    int i, j;
    bool student_found = false;

    char first_name[MAX_INP_LENGTH];
    char last_name[MAX_INP_LENGTH];

    printf("Enter the first name of the student to update: ");
    scanf("%s", first_name);

    printf("Enter the last name of the student to update: ");
    scanf("%s", last_name);


    // Traverse through all levels, classes, and students to find the student
    for (i = 0; i < NUM_LEVELS; i++) {
        for (j = 0; j < NUM_CLASSES; j++) {
            struct Class* class = &(school_system._levels[i]._classes[j]);
            struct Student* curr_student = class->_head_stud_list;

            while (curr_student != NULL) {
                // Compare the first name and last name of the current student with the target names
                if (strcmp(curr_student->_first_name, first_name) == 0 && strcmp(curr_student->_last_name, last_name) == 0) {
                    student_found = true;

                    // Prompt the user for the updated information
                    printf("Enter updated phone number: ");
                    scanf("%s", curr_student->_phone_number);

                    printf("Enter updated class number: ");
                    scanf("%d", &curr_student->_class_number);

                    printf("Enter updated class level: ");
                    scanf("%d", &curr_student->_class_level);

                    printf("Student information updated successfully!\n");
                    break;
                }

                curr_student = curr_student->_next;
            }

            if (student_found) {
                break;
            }
        }

        if (student_found) {
            break;
        }
    }

    if (!student_found) {
        printf("Student not found in the database.\n");
    }
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
        printf("file isn't opened\n");
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
