#ifndef FUNCTIONS_H
#define FUNCTIONS_H

using namespace std;

const int M = 3; // Number of courses (adjustable)

// Reads from a file and puts information in the given Course struct
void parseFile(istream&, Course&);
// Changes an array passed by reference to contain the numbers found in both of 2 arrays
// (gets the intersection)
int numsInCommon(Student*&, Student*, int, Student*, int);
// Prints lists of students in each course in ascending order based on ID number
void menuOne(Course[]);
// Prints the students taking all courses
void menuTwo(Course[]);
// Prints the students taking two courses
void menuThree(Course[]);
// Prints the top 3 scores of each course along with the students who received
// those scores
void menuFour(Course[]);
// Clears the heap when the user decides to exit the program
void menuFive(Course[]);

#endif