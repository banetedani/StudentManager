#include "menu.h"
#include "student.h"
#include <stdlib.h>

int main() {
    Student* students = NULL;
    size_t student_count = 0;

    students = load_students("students.csv", &student_count);
    students = display_menu(students, &student_count);

    free(students);
    return 0;
}
