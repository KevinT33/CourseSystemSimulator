#include <iostream>
#include <string>
#include "student.h"

using namespace std;

Student::Student() // Default constructor
{
    id = 0;
    name = "";
    score = 0;
}
Student::Student(int id, string name, int score) // Second constructor
{
    this->id = id;
    this->name = name;
    this->score = score;
}
void Student::setId(int id) // Sets the student's id number
{
    this->id = id;
}
void Student::setName(string name) // Sets the student's name
{
    this->name = name;
}
void Student::setScore(int score) // Sets the student's score
{
    this->score = score;
}
int Student::getId() const // Gets the student's id number
{
    return id;
}
string Student::getName() const // Gets the student's name
{
    return name;
}
int Student::getScore() const // Gets the student's score
{
    return score;
}