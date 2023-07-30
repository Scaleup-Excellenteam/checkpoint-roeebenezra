#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//#include <openssl/evp.h>
//#include <openssl/rand.h>

#define NAME_LEN 32

#define NUM_COURSES 10
#define NUM_LEVELS 12
#define NUM_CLASSES 10
#define NUM_TOP_STUDENTS 10
#define NUM_POTENTIAL_DROPOUTS 10

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

float calculateOverallAverage(const struct Student *student);

void topStudentsByLevel();

void potentialDropouts();

float calculateAveragePerCourse(int course_index);

void AverageOfCourses();

void exportToCSV(const char* filename);

void encryptAndSave(const char* filename);

void readAndDecrypt(const char* filename);


// static DB
static struct School school_system;


int main() {
    FILE *fptr = open_file();

    INITDB(fptr);
//    printDB();

    // Encrypt and save the school data
//    encryptAndSave("school_data.enc");

    // Clear the school data (optional)
//    memset(&school_system, 0, sizeof(struct School));

    // Read and decrypt the school data
//    readAndDecrypt("school_data.enc");

    menuDB();

    freePTRsDB();
    fclose(fptr);

    return 0;
}


//// Function to encrypt and save the school data to a file
//void encryptAndSave(const char* filename) {
//    FILE* file = fopen(filename, "wb");
//    if (file == NULL) {
//        printf("Error opening file for writing.\n");
//        return;
//    }
//
//    // Calculate the size of the data to be encrypted
//    size_t data_size = sizeof(struct School);
//
//    // Allocate memory to store the encrypted data
//    unsigned char* encrypted_data = (unsigned char*)malloc(data_size);
//
//    // Use a 256-bit key and 128-bit IV for AES-256 encryption
//    unsigned char key[32];
//    unsigned char iv[16];
//    RAND_bytes(key, sizeof(key));
//    RAND_bytes(iv, sizeof(iv));
//
//    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
//    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
//
//    // Allocate memory to store the encrypted data
//    unsigned char* encrypted_output = (unsigned char*)malloc(data_size);
//    int encrypted_output_size = 0;
//
//    // Encrypt the data and store it in the encrypted_output buffer
//    EVP_EncryptUpdate(ctx, encrypted_output, &encrypted_output_size, (const unsigned char*)school_system._levels, sizeof(struct School));
//
//    // Write the key and IV to the file
//    fwrite(key, sizeof(key), 1, file);
//    fwrite(iv, sizeof(iv), 1, file);
//
//    // Write the encrypted data to the file
//    fwrite(encrypted_output, encrypted_output_size, 1, file);
//
//    // Clean up
//    EVP_CIPHER_CTX_free(ctx);
//    free(encrypted_data);
//    free(encrypted_output);
//    fclose(file);
//
//    printf("Data encrypted and saved to %s successfully.\n", filename);
//}
//
//
//// Function to read and decrypt the school data from a file
//void readAndDecrypt(const char* filename) {
//    FILE* file = fopen(filename, "rb");
//    if (file == NULL) {
//        printf("Error opening file for reading.\n");
//        return;
//    }
//
//    // Calculate the size of the data to be read
//    fseek(file, 0, SEEK_END);
//    size_t data_size = ftell(file) - 32 - 16; // Subtract the size of the key and IV
//    fseek(file, 0, SEEK_SET);
//
//    // Allocate memory to store the encrypted data
//    unsigned char* encrypted_data = (unsigned char*)malloc(data_size);
//
//    // Read the key and IV from the file
//    unsigned char key[32];
//    unsigned char iv[16];
//    fread(key, sizeof(key), 1, file);
//    fread(iv, sizeof(iv), 1, file);
//
//    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
//    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
//
//    // Allocate memory to store the decrypted data
//    unsigned char* decrypted_data = (unsigned char*)malloc(data_size);
//
//    // Decrypt the data and store it in the decrypted_data buffer
//    int decrypted_data_size = 0;
//    EVP_DecryptUpdate(ctx, decrypted_data, &decrypted_data_size, encrypted_data, data_size);
//
//    // Copy the decrypted data back to the school structure
//    memcpy(school_system._levels, decrypted_data, decrypted_data_size);
//
//    // Clean up
//    EVP_CIPHER_CTX_free(ctx);
//    free(encrypted_data);
//    free(decrypted_data);
//    fclose(file);
//
//    printf("Data decrypted and loaded from %s successfully.\n", filename);
//}




// User actions in db
void menuDB() {
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add new student\n");
        printf("2. Delete student\n");
        printf("3. Update student information\n");
        printf("4. Search student\n");
        printf("5. Top students in each level\n");
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
                topStudentsByLevel();
                break;
            case 6:
                potentialDropouts();
                break;
            case 7:
                AverageOfCourses();
                break;
            case 8:
                exportToCSV("school_data.csv");
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
void addNewStudent() {
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
            struct Class *class = &(school_system._levels[i]._classes[j]);
            struct Student *curr_student = class->_head_stud_list;

            while (curr_student != NULL) {
                // Compare the first name and last name of the current student with the target names
                if (strcmp(curr_student->_first_name, first_name) == 0 &&
                    strcmp(curr_student->_last_name, last_name) == 0) {
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

// Function to search for a student in the school data structure
void searchStudent() {
    int i, j;
    bool student_found = false;

    char first_name[MAX_INP_LENGTH];
    char last_name[MAX_INP_LENGTH];

    printf("Enter the first name of the student to search: ");
    scanf("%s", first_name);

    printf("Enter the last name of the student to search: ");
    scanf("%s", last_name);

    // Traverse through all levels, classes, and students to find the student
    for (i = 0; i < NUM_LEVELS; i++) {
        for (j = 0; j < NUM_CLASSES; j++) {
            struct Class *class = &(school_system._levels[i]._classes[j]);
            struct Student *curr_student = class->_head_stud_list;

            while (curr_student != NULL) {
                // Compare the first name and last name of the current student with the target names
                if (strcmp(curr_student->_first_name, first_name) == 0 &&
                    strcmp(curr_student->_last_name, last_name) == 0) {
                    student_found = true;

                    // Display the student's information
                    printf("Student Found:\n");
                    printf("First Name: %s\n", curr_student->_first_name);
                    printf("Last Name: %s\n", curr_student->_last_name);
                    printf("Phone Number: %s\n", curr_student->_phone_number);
                    printf("Class Number: %d\n", curr_student->_class_number);
                    printf("Class Level: %d\n", curr_student->_class_level);
                    printf("\n");

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

// Function to calculate the overall average grade for a student
float calculateOverallAverage(const struct Student *student) {
    int total_grades = 0;
    int num_registered_courses = 0;

    for (int i = 0; i < NUM_COURSES; i++)
        total_grades += student->_courses_list[i]._grade;

    return (float) total_grades / NUM_COURSES;
}

// Function to find the top-performing students in each level
void topStudentsByLevel() {
    int i, j;

    // Traverse through all levels
    for (i = 0; i < NUM_LEVELS; i++) {
        printf("Top 10 students in Level %d:\n", i + 1);

        struct Student *top_students[NUM_TOP_STUDENTS] = {NULL};
        float top_student_averages[NUM_TOP_STUDENTS] = {0.0};

        // Traverse through all classes in the current level
        for (j = 0; j < NUM_CLASSES; j++) {
            struct Class *class = &(school_system._levels[i]._classes[j]);
            struct Student *curr_student = class->_head_stud_list;

            // Traverse all students in the class
            while (curr_student != NULL) {
                float avg = calculateOverallAverage(curr_student);

                // Compare the student's average with the current top students
                for (int k = 0; k < NUM_TOP_STUDENTS; k++) {
                    if (avg > top_student_averages[k]) {
                        // Shift the current top students to make space for the new student
                        for (int l = NUM_TOP_STUDENTS - 1; l > k; l--) {
                            top_students[l] = top_students[l - 1];
                            top_student_averages[l] = top_student_averages[l - 1];
                        }

                        // Insert the new student in the top list
                        top_students[k] = curr_student;
                        top_student_averages[k] = avg;

                        break;
                    }
                }

                curr_student = curr_student->_next;
            }
        }

        // Display the top students for the current level
        for (int k = 0; k < NUM_TOP_STUDENTS; k++) {
            if (top_students[k] != NULL) {
                printf("%d. %s %s (Average Grade: %.2f)\n", k + 1, top_students[k]->_first_name,
                       top_students[k]->_last_name, top_student_averages[k]);
            }
        }

        printf("\n");
    }
}

// Function to find the potential dropouts (lowest 10 students) in each level
void potentialDropouts() {
    int i, j;

    // Traverse through all levels
    for (i = 0; i < NUM_LEVELS; i++) {
        printf("Potential Dropouts in Level %d:\n", i + 1);

        struct Student *potential_dropouts[NUM_POTENTIAL_DROPOUTS] = {NULL};
        float potential_dropout_averages[NUM_POTENTIAL_DROPOUTS] = {
                100.0}; // Initialize with highest possible grade (100)

        // Traverse through all classes in the current level
        for (j = 0; j < NUM_CLASSES; j++) {
            struct Class *class = &(school_system._levels[i]._classes[j]);
            struct Student *curr_student = class->_head_stud_list;

            // Traverse all students in the class
            while (curr_student != NULL) {
                float avg = calculateOverallAverage(curr_student);

                // Compare the student's average with the current potential dropouts
                for (int k = 0; k < NUM_POTENTIAL_DROPOUTS; k++) {
                    if (avg < potential_dropout_averages[k]) {
                        // Shift the current potential dropouts to make space for the new student
                        for (int l = NUM_POTENTIAL_DROPOUTS - 1; l > k; l--) {
                            potential_dropouts[l] = potential_dropouts[l - 1];
                            potential_dropout_averages[l] = potential_dropout_averages[l - 1];
                        }

                        // Insert the new student in the potential dropouts list
                        potential_dropouts[k] = curr_student;
                        potential_dropout_averages[k] = avg;

                        break;
                    }
                }

                curr_student = curr_student->_next;
            }
        }

        // Display the potential dropouts for the current level
        for (int k = 0; k < NUM_POTENTIAL_DROPOUTS; k++) {
            if (potential_dropouts[k] != NULL) {
                printf("%d. %s %s (Average Grade: %.2f)\n", k + 1, potential_dropouts[k]->_first_name,
                       potential_dropouts[k]->_last_name, potential_dropout_averages[k]);
            }
        }

        printf("\n");
    }
}


// Function to calculate the average grade for a specific course across all students
float calculateAveragePerCourse(int course_index) {
    int total_grades = 0;
    int num_students = 0;

    // Traverse through all levels and classes
    for (int i = 0; i < NUM_LEVELS; i++) {
        for (int j = 0; j < NUM_CLASSES; j++) {
            struct Class *class = &(school_system._levels[i]._classes[j]);
            struct Student *curr_student = class->_head_stud_list;

            // Traverse all students in the class
            while (curr_student != NULL) {
                // Check if the student is registered for the specific course
                total_grades += curr_student->_courses_list[course_index]._grade;
                num_students++;

                curr_student = curr_student->_next;
            }
        }
    }

    return num_students > 0 ? (float) total_grades / num_students : 0.0;
}


// Calculate the average for each course
void AverageOfCourses() {
    printf("Average Grade for Each Course:\n");
    for (int i = 0; i < NUM_COURSES; i++) {
        printf("Course %d: %.2f\n", i + 1, calculateAveragePerCourse(i));
    }

}

// Function to export school data to a CSV file
void exportToCSV(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "First Name,Last Name,Phone Number,Class Number,Class Level");
    for (int i = 0; i < NUM_COURSES; i++) {
        fprintf(file, ",%s", school_system._levels[0]._classes[0]._head_stud_list->_courses_list[i]._course_name);
    }
    fprintf(file, "\n");

    // Traverse through all levels, classes, and students
    for (int i = 0; i < NUM_LEVELS; i++) {
        for (int j = 0; j < NUM_CLASSES; j++) {
            struct Class* class = &(school_system._levels[i]._classes[j]);
            struct Student* curr_student = class->_head_stud_list;

            // Traverse all students in the class
            while (curr_student != NULL) {
                // Write student information to the CSV file
                fprintf(file, "%s,%s,%s,%d,%d", curr_student->_first_name, curr_student->_last_name, curr_student->_phone_number,
                        curr_student->_class_number, curr_student->_class_level);

                // Write course grades for the student
                for (int k = 0; k < NUM_COURSES; k++) {
                    fprintf(file, ",%d", curr_student->_courses_list[k]._grade);
                }

                fprintf(file, "\n");
                curr_student = curr_student->_next;
            }
        }
    }

    fclose(file);
    printf("Data exported to %s successfully.\n", filename);
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
