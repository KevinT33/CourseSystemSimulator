/******************************************************************************
Project 1
Kevin Truong
4/13/2025
*******************************************************************************/
#include <iostream>
#include <fstream>
#include "course.h"
#include "student.h"
#include "functions.h"

int main()
{
    Course courseArr[M]; // Array that will contain course information
    
    // Obtains course data as text files from the user and adds them to courseArr
    // in the form of Course structs
    for (int i = 0; i < M; i++)
    {
        // Gets the file name from the user
        ifstream ifs;
        string filename;
        while (true) // Repeats until enough filenames are inputted
        {
            cout << "Enter filename #" << (i+1) << " : ";
            cin >> filename;
            ifs.open(filename); // connect ifstream and the file
            if (ifs.fail())
            {
                cout << "File Opening Failed, Try Again" << endl;
            }
            else
            {
                break;
            }
        }
        Course currentCourse; // Will contain course information
        parseFile(ifs, currentCourse); // Reads data from the file and puts
                                       // it in currentCourse
        courseArr[i] = currentCourse; // Adds the course information (struct) to courseArr
        
        ifs.close();
    }
    
    cout << endl << endl;
    // Gets the user's menu selection option (integer)
    int menuSelect = 0;
    while (menuSelect != 5)
    {
        // Displays the menu select screen
        cout << "=================  Menu  =====================" << endl;
        cout << "  1. Show all course lists (sorting)" << endl;
        cout << "  2. List of students who take all courses" << endl;
        cout << "  3. List of students who take two courses" << endl;
        cout << "  4. Print out top three scores for each course" << endl;
        cout << "  5. Exit" << endl;
        cout << "  ----> Select : ";
        cin >> menuSelect; // Has the user input a selection
        cout << endl;
        switch (menuSelect) // Prints a result based on the user's menu selection
                            // (1-5 being the valid options)
        {
            case 1: //  Menu 1 (Prints the students in each course in ascending order of ID)
                menuOne(courseArr);
                break;
            case 2: // Menu 2 (Prints the students taking all courses)
                menuTwo(courseArr);
                break;
            case 3: // Menu 3 (Prints the students taking exactly 2 courses)
                menuThree(courseArr);
                break;
            case 4: // Menu 4 (Prints the highest 3 scores in each course along
                           // with student info)
                menuFour(courseArr);
                break;
            case 5: // Prepares to end the program
                menuFive(courseArr);
                break;
            default: // Reprompts if the user enters an invalid number
                cout << "Invalid selection, try again" << endl << endl;
                break;
        }
    }
    
    return 0;
}
