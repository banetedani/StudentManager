#pragma warning(disable : 4996)

#include "student.h"
#include "validator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Student* load_students(const char* filename, size_t* student_count) {
    Student* students = NULL;
    FILE* file = fopen(filename, "r");

    if (!file) {
        perror("Could not open file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        students = (Student *)realloc(students, (*student_count + 1) * sizeof(Student)); 
        if (students == NULL) {
            perror("Failed to allocate memory");
            fclose(file);
            exit(EXIT_FAILURE);
        }

        if (sscanf(
                line,
                "%99[^,], %d, %c, %99[^,], %d",
                &students[*student_count].name,
                &students[*student_count].age,
                &students[*student_count].gender,
                &students[*student_count].specialization,
                &students[*student_count].studentYear
            ) != 5
        ) {
            fprintf(stderr, "Error parsing line: %s\n", line);
            continue;
        }

        if (!validate_student(students[*student_count])) {
            fprintf(stderr, "Invalid student data: %s\n", line);
            continue;
        }

        (*student_count)++;
    }

    fclose(file);

    return students;
}

void save_students(const char* filename, Student* students, size_t student_count) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Could not open file");
        return;
    }

    for (size_t i = 0; i < student_count; i++) {
        fprintf(file, "%s, %d, %c, %s, %d\n",
            students[i].name,
            students[i].age,
            students[i].gender,
            students[i].specialization,
            students[i].studentYear);
    }

    fclose(file);
}

void display_students(const Student* students, size_t student_count) {
    for (size_t i = 0; i < student_count; i++) {
        printf("Name: %s, Age: %d, Gender: %c, Specialization: %s, Student Year: %d\n",
            students[i].name, students[i].age, students[i].gender, students[i].specialization, students[i].studentYear);
    }
}

Student* add_student(Student* students, size_t* student_count) {
    Student studentToAdd;

    printf("Enter name: ");
    read_string(studentToAdd.name, sizeof(studentToAdd.name));

    printf("Enter age: ");
    if (scanf("%d", &studentToAdd.age) != 1) {
        printf("Invalid input for age.\n");
        getchar();
        return;
    }
    getchar();

    printf("Enter gender (M/F): ");
    if (scanf("%c", &studentToAdd.gender) != 1 ||
        (studentToAdd.gender != 'M' && studentToAdd.gender != 'F')) {
        printf("Invalid input for gender.\n");
        getchar();
        return;
    }
    getchar();

    printf("Enter specialization: ");
    read_string(studentToAdd.specialization, sizeof(studentToAdd.specialization));

    printf("Enter student year: ");
    if (scanf("%d", &studentToAdd.studentYear) != 1) {
        printf("Invalid input for student year.\n");
        getchar();
        return;
    }
    getchar();

    if (!validate_student(studentToAdd)) {
        printf("Invalid student data. Please try again.\n");
        return NULL;
    }

    // Reallocate memory only when the user has entered valid data
    Student* newStudents = (Student*)realloc(students, ((*student_count) + 1) * sizeof(Student));

    if (newStudents == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    newStudents[*student_count] = studentToAdd;
    (*student_count)++;

    return newStudents;
}

Student* delete_student(Student* students, size_t* student_count) {
    char name[MAX_NAME_LENGTH];
    printf("Enter name of student to delete: ");
    read_string(name, sizeof(name));

    size_t index = *student_count;
    for (size_t i = 0; i < *student_count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            index = i;
            break;
        }
    }

    if (index == *student_count) {
        printf("Student not found.\n");
        return NULL;
    }

    for (size_t i = index; i < *student_count - 1; i++) {
        students[i] = students[i + 1];
    }

    (*student_count)--;
    Student* newStudents = (Student*)realloc(students, (*student_count) * sizeof(Student));
    if (students == NULL && *student_count > 0) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    return newStudents;
}

void edit_student(Student* students, size_t student_count) {
    char name[MAX_NAME_LENGTH];
    printf("Enter name of student to edit: ");
    read_string(name, sizeof(name));

    size_t index = student_count;
    for (size_t i = 0; i < student_count; i++) {
        if (strcmp(students[i].name, name) == 0) {
            index = i;
            break;
        }
    }

    if (index == student_count) {
        printf("Student not found.\n");
        return;
    }

    printf("Enter new name: ");
    read_string(students[index].name, sizeof(students[index].name));

    printf("Enter new age: ");
    if (scanf("%d", &students[index].age) != 1) {
        printf("Invalid input for age.\n");
        getchar();
        return;
    }
    getchar();

    printf("Enter new gender (M/F): ");
    if (scanf("%c", &students[index].gender) != 1 ||
        (students[index].gender != 'M' && students[index].gender != 'F')) {
        printf("Invalid input for gender.\n");
        getchar();
        return;
    }
    getchar();

    printf("Enter new specialization: ");
    read_string(students[index].specialization, sizeof(students[index].specialization));

    printf("Enter new student year: ");
    if (scanf("%d", &students[index].studentYear) != 1) {
        printf("Invalid input for student year.\n");
        getchar();
        return;
    }
    getchar();

    if (!validate_student(students[index])) {
        printf("Invalid student data. Changes not saved.\n");
        return;
    }
}

void sort_students(Student* students, size_t student_count) {
    for (size_t i = 0; i < student_count - 1; i++) {
        for (size_t j = i + 1; j < student_count; j++) {
            if (strcmp(students[i].name, students[j].name) > 0) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}
