#ifndef DATA_H
#define DATA_H

using namespace std;

// Class for student objects
class Student
{
private:
    int id; // Student ID
    string name; // Student name
    int score; // Student score
public:
    Student(); // Default constructor
    Student(int, string, int); // Second constructor
    void setId(int); // Sets the student's id number
    void setName(string); // Sets the student's name
    void setScore(int); // Sets the student's score
    int getId() const; // Gets the student's id number
    string getName() const; // Gets the student's name
    int getScore() const; // Gets the student's score
};

#endif