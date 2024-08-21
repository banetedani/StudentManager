#include "validator.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MIN_AGE 18
#define MAX_AGE 100
#define MIN_YEAR 1
#define MAX_YEAR 6

int validate_student(const Student student) {
    if (strlen(student.name) == 0) {
        printf("Invalid name. Name cannot be empty.\n");
        return 0;
    }

    for (size_t i = 0; i < strlen(student.name); i++) {
        if (!isalpha(student.name[i]) && student.name[i] != ' ') {
            printf("Invalid name. Name can only contain alphabetic characters and spaces.\n");
            return 0;
        }
    }

    if (student.age < MIN_AGE || student.age > MAX_AGE) {
        printf("Invalid age. Age must be between %d and %d.\n", MIN_AGE, MAX_AGE);
        return 0;
    }

    if (student.gender != 'M' && student.gender != 'F') {
        printf("Invalid gender. Gender must be 'M' or 'F'.\n");
        return 0;
    }

    if (strlen(student.specialization) == 0) {
        printf("Invalid specialization. Specialization cannot be empty.\n");
        return 0;
    }

    if (student.studentYear < MIN_YEAR || student.studentYear > MAX_YEAR) {
        printf("Invalid student year. Year must be between %d and %d.\n", MIN_YEAR, MAX_YEAR);
        return 0;
    }

    return 1;
}

void read_string(char* buffer, size_t size) {
    if (fgets(buffer, size, stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}
