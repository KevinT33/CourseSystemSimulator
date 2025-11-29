#ifndef COURSE_H
#define COURSE_H
#include "student.h"

using namespace std;

// Data type for courses
struct Course
{
    string title;
    int number_of_students;
    Student* list;
};

#endif