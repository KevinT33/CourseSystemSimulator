#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "student.h"
#include "course.h"
#include "functions.h"


// Reads from a file and puts information in the given Course struct
void parseFile(istream& input, Course& course)
{
    input >> course.title >> course.number_of_students; // Gets and assigns a course title and quantity of students
                                                        // taking the course
    course.list = new Student[course.number_of_students];
    for (int i = 0; i < course.number_of_students; i++) // Adds student objects to the course struct
    {
        int currentId;
        string currentName;
        int currentScore;
        input >> currentId >> currentName >> currentScore;
        Student currentStudent(currentId, currentName, currentScore);
        course.list[i] = currentStudent;
    }
}

// Changes an array passed by reference to contain the numbers found in both of 2 arrays
// (gets the intersection)
int numsInCommon(int*& resultArr, int* firstArr, int firstArrSize,
                     int* secondArr, int secondArrSize)
{
    // Deep copies firstArr and secondArr
    int* oldFirstArr = firstArr;
    firstArr = new int[firstArrSize];
    for (int i = 0; i < firstArrSize; i++)
    {
        firstArr[i] = oldFirstArr[i];
    }
    int* oldSecondArr = secondArr;
    secondArr = new int[secondArrSize];
    for (int i = 0; i < secondArrSize; i++)
    {
        secondArr[i] = oldSecondArr[i];
    }
    // Nullifies oldFirstArr and oldSecondArr to prevent dangling pointers
    oldFirstArr = nullptr;
    oldSecondArr = nullptr;
    // Finds how many students firstArr and secondArr have in common, which will
    // be used to determine the size of resultArr
    int commonStudentCount = 0;
    for (int i = 0; i < firstArrSize; i++) // Iterates over student IDs of the first array
    {
        for (int j = 0; j < secondArrSize; j++) // Iterates over student IDs of the second array
        {
            if (firstArr[i] == secondArr[j])
            {
                commonStudentCount++;
                break;
            }
        }
    }
    // Clears out values in resultArr and adjusts the size
    int* oldArr = resultArr;
    resultArr = new int[commonStudentCount];
    delete[] oldArr; // Deletes the first parameter array to ensure no memory leak
    oldArr = nullptr;
    // Adds matching students to resultArr
    int resultArrIndex = 0;
    for (int i = 0; i < firstArrSize; i++)
    {
        for (int j = 0; j < secondArrSize; j++)
        {
            if (firstArr[i] == secondArr[j])
            {
                resultArr[resultArrIndex] = firstArr[i];
                resultArrIndex++;
                break;
            }
        }
    }
    // Deletes and nullifies deep copies of firstArr and secondArr
    delete[] firstArr;
    firstArr = nullptr;
    delete[] secondArr;
    secondArr = nullptr;
    
    return commonStudentCount;
}

// Prints lists of students in each course in ascending order based on ID number
void menuOne(Course theCourseArr[])
{
    for (int i = 0; i < M; i++) // Iterates through each course
    {
        Course currentCourse = theCourseArr[i];
        // Prints the course name header
        cout << "==========  " << currentCourse.title << "  ==========" << endl << endl;
        // Creates a dynamic array that will store the IDs of students in the current course in ascending order
        int* sortedStudentIds = new int[currentCourse.number_of_students];
        // Deep copies IDs from currentCourse to sortedStudentIds
        for (int j = 0; j < currentCourse.number_of_students; j++) // Iterates through the current course students
        {
            sortedStudentIds[j] = currentCourse.list[j].getId();
        }
        sort(sortedStudentIds, sortedStudentIds + currentCourse.number_of_students); // Sorts the student IDs
        // Prints the students in the course in sorted order
        for (int j = 0; j < currentCourse.number_of_students; j++) // Iterates through sorted student IDs
        {
            // Finds the student's name and score for the course
            string studentName = "";
            int courseScore = 0;
            for (int k = 0; k < currentCourse.number_of_students; k++) // Iterates through the current course students
            {
                if (sortedStudentIds[j] == currentCourse.list[k].getId()) // If the ID in the sorted list matches the ID in the 
                                                                          // course student list, records the name and score 
                                                                          // (for the current course) associated with the ID
                {
                    studentName = currentCourse.list[k].getName();
                    courseScore = currentCourse.list[k].getScore();
                    break;
                }
            }
            // Prints the student's information
            cout << setw(10) << sortedStudentIds[j] << setw(10) << studentName << setw(4) << courseScore << endl;
        }
        cout << endl;

        // Dellocates sortedStudents and nullifies pointer
        delete[] sortedStudentIds;
        sortedStudentIds = nullptr;
    }
}

// Prints the students taking all courses
void menuTwo(Course theCourseArr[])
{
    // Deep copies the student ids from the first course to inAllCoursesIds
    int inAllCoursesCount = theCourseArr[0].number_of_students;
    int* inAllCoursesIds = new int[inAllCoursesCount];
    for (int i = 0; i < inAllCoursesCount; i++) // Iterates over each student ID in the first course
    {
        inAllCoursesIds[i] = theCourseArr[0].list[i].getId();
    }
    // Gets the IDs of students in all courses
    for (int i = 1; i < M; i++) // Iterates over every succeeding course
    {
        // Gets the student IDs of the course being compared
        int* courseIds = new int[theCourseArr[i].number_of_students];
        for (int j = 0; j < theCourseArr[i].number_of_students; j++) // Iterates over each student ID
        {
            courseIds[j] = theCourseArr[i].list[j].getId();
        }
        // Updates the intersection
        inAllCoursesCount = numsInCommon(inAllCoursesIds,
                                         inAllCoursesIds, inAllCoursesCount,
                                         courseIds, theCourseArr[i].number_of_students);
        // Deletes courseIds and nullifies pointer
        delete[] courseIds;
        courseIds = nullptr;
    }
    sort(inAllCoursesIds, inAllCoursesIds + inAllCoursesCount); // Sorts inAllCoursesIds
    // Prints how many students are in all courses (as well as their information if there
    // is at least one)
    if (inAllCoursesCount == 0)
    {
        if (M == 3) // Prints if there are no students taking all 3 courses (matches output specification)
        {
            cout << "    There are no students who take all three courses." << endl;
        }
        else // Prints if there are no students taking all courses (handles other cases)
        {
            cout << "    There are no students who take all courses." << endl;
        }
        cout << endl;
    }
    else
    {
        cout << "    There are " << inAllCoursesCount << " students who take "<< M << " courses" << endl;
        cout << "-------------------------------------------------" << endl;
        for (int i = 0; i < inAllCoursesCount; i++) // Iterates through the student IDs in all courses
        {
            // Finds the student's name and scores for each course
            string studentName = "";
            int* courseScores = new int[M];
            for (int j = 0; j < M; j++) // Iterates through each course
            {
                for (int k = 0; k < theCourseArr[j].number_of_students; k++) // Iterates through the students in each individual course
                {
                    // Looks up the associated name and course score for the given ID
                    if (inAllCoursesIds[i] == theCourseArr[j].list[k].getId())
                    {
                        studentName = theCourseArr[j].list[k].getName();
                        courseScores[j] = theCourseArr[j].list[k].getScore();
                        break;
                    }
                }
            }
            // Prints the student and their data
            cout << setw(8) << inAllCoursesIds[i] << setw(10) << studentName
                << " ";
            for (int j = 0; j < M; j++) // Iterates through the student's course grades
            {
                cout << theCourseArr[j].title << "(" << courseScores[j] << ")  ";
            }
            cout << endl;
            // Deletes courseScores and nullifies pointer
            delete[] courseScores;
            courseScores = nullptr;
        }
        cout << endl;
    }
    // Dellocates inAllCoursesIds and nullifies pointer
    delete[] inAllCoursesIds;
    inAllCoursesIds = nullptr;
}

// Prints the students taking exactly 2 courses
void menuThree(Course theCourseArr[])
{
    // 2D dynamic array that will contain lists of IDs of students taking both of every combination of 2 courses (inclusive)
    int uniquePairs = M * (M - 1) / 2;
    int** inTwoCoursesIds = new int*[uniquePairs];
    int* inTwoCoursesCount = new int[uniquePairs];
    // Gets data for inTwoCoursesIds
    int twoCourseIndex = 0;
    for (int i = 0; i < M - 1; i++) // Iterates the first course in the pair
    {
        for (int j = i + 1; j < M; j++) // Iterates the second course in the pair
        {
            // Creates dynamic arrays containing IDs of students in the 2 courses being compared
            int* firstCourseIds = new int[theCourseArr[i].number_of_students];
            // Deep copies IDs from theCourseArr[i] to firstCourseIds
            for (int k = 0; k < theCourseArr[i].number_of_students; k++)
            {
                firstCourseIds[k] = theCourseArr[i].list[k].getId();
            }
            int* secondCourseIds = new int[theCourseArr[j].number_of_students];
            // Deep copies IDs from theCourseArr[j] to secondCourseIds
            for (int k = 0; k < theCourseArr[j].number_of_students; k++)
            {
                secondCourseIds[k] = theCourseArr[j].list[k].getId();
            }
            // Finds the common students
            inTwoCoursesIds[twoCourseIndex] = nullptr;
            inTwoCoursesCount[twoCourseIndex] = numsInCommon(inTwoCoursesIds[twoCourseIndex],
                                                firstCourseIds, theCourseArr[i].number_of_students,
                                                secondCourseIds, theCourseArr[j].number_of_students);
            // Deallocates firstCourseIds and secondCourseIds and nullifies pointers
            delete[] firstCourseIds;
            firstCourseIds = nullptr;
            delete[] secondCourseIds;
            secondCourseIds = nullptr;
            
            twoCourseIndex++;
        }
    }
    // Counts how many students are exclusively in the two courses
    twoCourseIndex = 0;
    int* inTwoCoursesExclusiveCount = new int[uniquePairs];
    for (int i = 0; i < M - 1; i++) // Iterates the first course in the pair
    {
        for (int j = i + 1; j < M; j++) // Iterates the second course in the pair
        {
            inTwoCoursesExclusiveCount[twoCourseIndex] = 0;
            for (int k = 0; k < inTwoCoursesCount[twoCourseIndex]; k++) // Iterates through students inclusively in the two courses
            {
                bool isExclusive = true;
                for (int l = 0; l < M; l++) // Iterates through each course
                {
                    // If the course is not one of the two paired courses, searches it
                    if (l != i && l != j)
                    {
                        for (int m = 0; m < theCourseArr[l].number_of_students; m++) // Iterates through the course students
                        {
                            if (inTwoCoursesIds[twoCourseIndex][k] == theCourseArr[l].list[m].getId())
                            {
                                isExclusive = false;
                                break;
                            }
                        }
                    }
                }
                if (isExclusive) // Counts how many exclusive students there are
                {
                    inTwoCoursesExclusiveCount[twoCourseIndex]++;
                }
            }
            twoCourseIndex++;
        }        
    }
    // Will stores IDs of students exclusively in 2 classes
    int** inTwoCoursesExclusiveIds = new int*[uniquePairs];
    for (int i = 0; i < uniquePairs; i++) // Iterates over two course combinations
    {
        inTwoCoursesExclusiveIds[i] = new int[inTwoCoursesExclusiveCount[i]];
    }
    twoCourseIndex = 0;
    for (int i = 0; i < M - 1; i++) // Iterates the first course in the pair
    {
        for (int j = i + 1; j < M; j++) // Iterates the second course in the pair
        {
            int twoCourseExclusiveStudentIndex = 0;
            for (int k = 0; k < inTwoCoursesCount[twoCourseIndex]; k++) // Iterates through students inclusively in the two courses
            {
                bool isExclusive = true;
                for (int l = 0; l < M; l++) // Iterates through each course
                {
                    // If the course is not one of the two paired courses, searches it
                    if (l != i && l != j)
                    {
                        for (int m = 0; m < theCourseArr[l].number_of_students; m++) // Iterates through the course students
                        {
                            if (inTwoCoursesIds[twoCourseIndex][k] == theCourseArr[l].list[m].getId())
                            {
                                isExclusive = false;
                                break;
                            }
                        }
                    }
                }
                if (isExclusive) // Adds exclusive students to inTwoCoursesExclusiveIds
                {
                    inTwoCoursesExclusiveIds[twoCourseIndex][twoCourseExclusiveStudentIndex] = inTwoCoursesIds[twoCourseIndex][k];
                    twoCourseExclusiveStudentIndex++;
                }
            }
            // Sorts the row
            sort(inTwoCoursesExclusiveIds[twoCourseIndex], inTwoCoursesExclusiveIds[twoCourseIndex] + inTwoCoursesExclusiveCount[twoCourseIndex]);
        
            twoCourseIndex++;
        }        
    }
    // Deletes inTwoCoursesIds and inTwoCoursesCount and nullifies pointers
    for (int i = 0; i < uniquePairs; i++)
    {
        delete[] inTwoCoursesIds[i];
        inTwoCoursesIds[i] = nullptr;
    }
    delete[] inTwoCoursesIds;
    inTwoCoursesIds = nullptr;
    delete[] inTwoCoursesCount;
    inTwoCoursesCount = nullptr;
    
    // Prints how many students are taking 2 courses (as well as their information
    // if there is at least one)
    twoCourseIndex = 0;
    for (int i = 0; i < M - 1; i++) // Iterates the first course in the pair
    {
        for (int j = i + 1; j < M; j++) // Iterates the second course in the pair
        {
            if (inTwoCoursesExclusiveCount[twoCourseIndex] == 0)
            {
                cout << "  There are no students who take " << theCourseArr[i].title << " and " << theCourseArr[j].title << "." << endl << endl;
            }
            else
            {
                cout << "  There are " << inTwoCoursesExclusiveCount[twoCourseIndex] <<
                    " students who take " << theCourseArr[i].title << " and " << theCourseArr[j].title << endl;
                cout << "-----------------------------------------------" << endl;
                for (int k = 0; k < inTwoCoursesExclusiveCount[twoCourseIndex]; k++) // Iterates through the students exclusively in two courses
                {
                    // Finds the student's name and scores for each course
                    string studentName = "";
                    int firstCourseScore = 0;
                    int secondCourseScore = 0;
                    // Gets the student's first score and name
                    for (int l = 0; l < theCourseArr[i].number_of_students; l++) // Iterates through theCourseArr[i] students
                    {
                        // If the student is found, gets their name and score
                        if (inTwoCoursesExclusiveIds[twoCourseIndex][k] == theCourseArr[i].list[l].getId())
                        {
                            studentName = theCourseArr[i].list[l].getName();
                            firstCourseScore = theCourseArr[i].list[l].getScore();
                            break;
                        }
                    }
                    // Gets the student's second score
                    for (int l = 0; l < theCourseArr[j].number_of_students; l++) // Iterates through theCourseArr[j] students
                    {
                        // If the student is found, gets their score
                        if (inTwoCoursesExclusiveIds[twoCourseIndex][k] == theCourseArr[j].list[l].getId())
                        {
                            secondCourseScore = theCourseArr[j].list[l].getScore();
                            break;
                        }
                    }
                    // Prints the student info
                    cout << " " << inTwoCoursesExclusiveIds[twoCourseIndex][k] << setw(10) <<
                        studentName << setw(8) << theCourseArr[i].title << "(" << firstCourseScore
                        << ")" << setw(8) << theCourseArr[j].title << "(" << secondCourseScore << ")" << endl;
                }
                cout << endl;
            }
            twoCourseIndex++;
        }
    }
    
    // Delocates arrays and nullifies pointers
    for (int i = 0; i < uniquePairs; i++)
    {
        delete[] inTwoCoursesExclusiveIds[i];
        inTwoCoursesExclusiveIds[i] = nullptr;
    }
    delete[] inTwoCoursesExclusiveIds;
    inTwoCoursesExclusiveIds = nullptr;
    delete[] inTwoCoursesExclusiveCount;
    inTwoCoursesExclusiveCount = nullptr;
}

// Prints the top 3 scores of each course along with the students who received
// those scores
void menuFour(Course theCourseArr[])
{
    for (int i = 0; i < M; i++) // Iterates through each course
    {
        int topScoreSize = 3;
        int* topScores = new int[topScoreSize];
        for (int j = 0; j < topScoreSize; j++) // Iterates through dynamic array that
                                               // will store the largest scores for the course
        {
            topScores[j] = -1;
        }
        // Gets the top 3 scores in the course
        for (int j = 0; j < theCourseArr[i].number_of_students; j++) // Iterates through
                                                                     // students in the course
        {
            for (int k = 0; k < topScoreSize; k++) // Iterates through the list of top scores
            {
                // Checks if a new higher score was reached
                if (theCourseArr[i].list[j].getScore() > topScores[k])
                {
                    for (int l = topScoreSize - 1; l > k; l--) // Iterates through the prior
                                                               // high scores  
                    {
                        topScores[l] = topScores[l - 1];
                    }
                    topScores[k] = theCourseArr[i].list[j].getScore();
                    break;
                }
                // Skips if the score is already one of the max scores
                else if (theCourseArr[i].list[j].getScore() == topScores[k])
                {
                    break;
                }
            }
        }
        // Prints the top scores and the students with those scores
        cout << "[ " << theCourseArr[i].title << " Top Three Scores ]" << endl;
        // Prints the students with the given top score
        for (int j = 0; j < topScoreSize; j++) // Iterates through the top scores
        {
            // Makes sure nothing extra is printed when there is fewer than 3 top scores
            if (topScores[j] == -1)
            {
                continue;
            }
            // Prints the score 
            cout << (j+1) << ". " << topScores[j] << endl;
            // Counts how many students got the given top score
            int topScoreCount = 0;
            for (int k = 0; k < theCourseArr[i].number_of_students; k++) // Iterates through
                                                                         // students in the given course
            {
                // Checks if the student has the given top score
                if (theCourseArr[i].list[k].getScore() == topScores[j])
                {
                    topScoreCount++;
                }
            }
            int* topScoreIds = new int[topScoreCount]; // Will store the IDs of students with the given top score
            int topScoreIndex = 0;
            for (int k = 0; k < theCourseArr[i].number_of_students; k++) // Iterates through
                                                                        // students in the course
            {
                // Checks if the student has the given top score
                if (theCourseArr[i].list[k].getScore() == topScores[j])
                {
                    topScoreIds[topScoreIndex] = theCourseArr[i].list[k].getId();
                    topScoreIndex++;
                }
            }
            sort(topScoreIds, topScoreIds + topScoreCount);
            for (int k = 0; k < topScoreCount; k++) // Iterates through the ids of students
                                                    // who got the given top score
            {
                string name = "";
                for (int l = 0; l < theCourseArr[i].number_of_students; l++) // Iterates through the students in the current course
                {
                    // Finds the name associated with the ID
                    if (topScoreIds[k] == theCourseArr[i].list[l].getId())
                    {
                        name = theCourseArr[i].list[l].getName();
                        break;
                    }
                }
                cout << "   " << topScoreIds[k] << setw(10) << name << endl;
            }
            delete[] topScoreIds;
            topScoreIds = nullptr;
        }
        cout << endl;
        
        delete[] topScores;
        topScores = nullptr;
    }
}

// Clears the heap when the user decides to exit the program
void menuFive(Course theCourseArr[])
{
    cout << "Exiting....";
    // Deletes theCourseArr dynamic arrays in heap 
    for (int i = 0; i < M; i++) // iterates through each course
    {
        delete[] theCourseArr[i].list;
        theCourseArr[i].list = nullptr;
    }
}