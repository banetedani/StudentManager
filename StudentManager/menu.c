#pragma warning(disable : 4996)

#include <stdio.h>
#include "menu.h"

Student* display_menu(Student* students, size_t* student_count) {
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Display students in alphabetical order\n");
        printf("2. Add student\n");
        printf("3. Delete student\n");
        printf("4. Edit student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please try again.\n");
            getchar(); // Clear invalid input
            continue;
        }
        getchar(); // Clear newline

        switch (choice) {
        case 1:
            sort_students(students, *student_count);
            display_students(students, *student_count);
            break;
        case 2: {
            /* Only save the students if the list has changed
               (all student data entered was valid). */
            Student* newStudents = add_student(students, student_count);
            if (newStudents != NULL) {
                students = newStudents;
                save_students("students.csv", students, *student_count);
            }
        }   break;
        case 3: {
            Student* newStudents = delete_student(students, student_count);
            /* Only save the students if the list has changed
               (the student was found and deleted). */
            if (newStudents != NULL) {
                students = newStudents;
                save_students("students.csv", students, *student_count);
            }
        }   break;
        case 4:
            edit_student(students, *student_count);
            save_students("students.csv", students, *student_count);
            break;
        case 5:
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return students;
}
