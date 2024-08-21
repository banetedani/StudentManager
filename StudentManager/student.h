#ifndef STUDENT_H
#define STUDENT_H
#pragma warning(disable : 4996)

#include <stddef.h>

#define MAX_NAME_LENGTH 100
#define MAX_SPECIALIZATION_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int age;
    char gender;
    char specialization[MAX_SPECIALIZATION_LENGTH];
    int studentYear;
} Student;

Student* load_students(const char* filename, size_t* student_count);
void save_students(const char* filename, Student* students, size_t student_count);
void display_students(const Student* students, size_t student_count);
Student* add_student(Student* students, size_t* student_count);
Student* delete_student(Student* students, size_t* student_count);
void edit_student(Student* students, size_t student_count);
void sort_students(Student* students, size_t student_count);

#endif // STUDENT_H
