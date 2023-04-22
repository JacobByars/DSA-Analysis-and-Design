
//============================================================================
// Name        : Project2.cpp
// Author      : Jacob Byars
// Version     : 1.0
// Description : Project 2 SNHU Courses
//============================================================================

//set includes for input output, vectors, and strings
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//declare namespace
using namespace std;

//setup course structure
struct Course {
    string courseNum; //store course number
    string courseName; //store course name
    vector<string> prerequisites; //store string vector list of prerequisites
};

//Function to split user string with a given delemeter
vector<string> splitUserStr(string userStr, string del = " ")
{
    //declare and intilize needed starting varaibles
    vector<string> stringArray;
    int start = 0;
    int end = userStr.find(del);

    //loop though user string until delementer not found
    while (end != -1) {
        //add each element to string array and update the start and end points 
        stringArray.push_back(userStr.substr(start, end - start));
        start = end + del.size();
        end = userStr.find(del, start);
    }

    //add last element to array and return array
    stringArray.push_back(userStr.substr(start, end - start));
    return stringArray;
}

//Function to Load data into data structure
vector<Course> loadDataStructure()
{
    //directions part 1 input
    //get file name from user
    string fileName;
    cout << "Please Enter the File Name: ";
    cin >> fileName;
    
    //open user file abcu.txt
    ifstream userFile(fileName, ios::in);

    //declare courselist and userLine variables
    vector<Course> courseList;
    string userLine;
    
    //check if file is open. 
    if (userFile.is_open()) {
        //directions part 3 loading Data Structure
        //if file is open then loop though file until getLine returns false meaning EOF
        while (getline(userFile, userLine)) {
            //make course varaiable and vector to store course info
            Course userCourse;
            vector<string> courseInfo = splitUserStr(userLine, ",");

            //check to see if course number and name are present on line
            if (courseInfo.size() > 1) {
                //If both are present then
                //add course number and name to user course
                userCourse.courseNum = courseInfo[0];
                userCourse.courseName = courseInfo[1];

                //check to see if prerequistes exist for the course
                if (courseInfo.size() > 2) {
                    // if prerequistes exist then loop though the remaining elements of courseInfo
                    // and add them to userCourse prerequisites list
                    for (int i = 2; i < courseInfo.size(); i++) {
                        userCourse.prerequisites.push_back(courseInfo[i]);
                    }
                }

                // add userCourse to courseList 
                courseList.push_back(userCourse);
            }
            else {
                //If both are not present then 
                // output error and continue to next line
                cout << "Not enough information for the course." << endl;
                continue;
            }
        }

        //close the user file
        userFile.close();
    }
    else {
        //if file was not open then output error
        cout << "Unable to open file!" << endl;
    }

    //return courseList
    return courseList;
}

//Function prints the information from passed course
void printCourse(Course course) {
    //get course number, name, and prerequistes list
    string courseNum = course.courseNum;
    string courseName = course.courseName;
    vector<string> prerequisites = course.prerequisites;

    // output seperator and info
    cout << "-------------------------------------------------" << endl;
    cout << "Course Number : " << courseNum << endl;
    cout << "Course Name   : " << courseName << endl;
    cout << "Prerequisites : ";
    
    //Check if prerequisites exist
    if (prerequisites.size() <= 0) {
        // output none if no prerequisites are required
        cout << "None" << endl;
    }
    else {
        // loop though and print prerequistes if they are required
        for (int i = 0; i < prerequisites.size(); i++) {
            if (i == 0) {
                cout << prerequisites[i] << endl;
            }
            else {
                cout << "                " << prerequisites[i] << endl;
            }
        }
    }
    
    //outupt two newlines
    cout << "\n\n";
}

//Function sorts passed course list by bubble sort
vector<Course> sortCourseList(vector<Course> courseList) {
    //directions part 4 Course List
    //get number of courses in list
    int numCourses = courseList.size();

    //outer loop though list
    for (int i = 0; i < numCourses - 1; i++) {
        //inner loop though list
        for (int j = 0; j < numCourses - i - 1; j++) {
            //swap if elements are not in correct order
            if (courseList[j].courseNum > courseList[j + 1].courseNum) {
                swap(courseList[j + 1], courseList[j]);
            }
        }
    }

    //return course list
    return courseList;
}

//Function prints sorted course list
void printSortedCourseList(vector<Course> courseList) {
    //directions part 4 course List
    //call to function to sort the list
    courseList = sortCourseList(courseList);

    //loop though list and print each couse info
    for (int i = 0; i < courseList.size(); i++) {
        printCourse(courseList[i]);
    }
}

//Function searches course list for user inputed course numberr
void seachCourseByNum(vector<Course> courseList) {
    //decalre userCourseNum and userNumFound Varables
    string userCourseNum;
    bool userNumFound = false;

    //get userCourseNum from user
    cout << "Enter Course Number: ";
    cin >> userCourseNum;

    //Loop though course list
    for (int i = 0; i < courseList.size(); i++) {
        // if found course then print the course 
        // set userNumFound to true and exit loop
        if (courseList[i].courseNum == userCourseNum) {
            userNumFound = true;
            printCourse(courseList[i]);
            break;
        }
    }

    //Check to see if course was not found and output not found message if needed
    if (!userNumFound) {
        cout << "Given course number not found in course list." << endl;
    }
}

//Function prints the main menu
void printMenu() {
    //Directions part 2 menu
    //output menu options and prompt for user to enter the number
    cout << "1) Load Data Structure" << endl;
    cout << "2) Print Course List" << endl;
    cout << "3) Print Course" << endl;
    cout << "4) Exit" << endl;
    cout << "Please enter the number of the option you wish to preform! ";
}

//main function that runs the program
int main()
{
    // make course list and set user choice to -1
    vector<Course> courseList;
    int userChoice = -1;

    //output welcome message
    cout << "Welcome to the course planner." << endl;

    //loop while userChoice < 1 or > 3
    while (userChoice < 1 || userChoice > 3) {
        // print main menu and get userChoice
        printMenu();
        cin >> userChoice;

        // if user does not enter and integer or thier choice is invalid then print error
        // and repromt them to select an option
        while (cin.fail() || userChoice < 1 || userChoice > 4) {
            cout << "\n\n";
            cout << "The option you entered is invalid!" << endl;
            printMenu();
            cin >> userChoice;
        }

        //switch statemet to handle the option they selected
        switch (userChoice) {
            case 1: // load data structure
                courseList = loadDataStructure();
                break;
            case 2: // print a sorted list by course number
                // check to see if data loaded into structure 
                if (courseList.size() <= 0) {
                    // if no data then print error
                    cout << "No courses are loaded in data structure. Please load the data structure before chosing this option." << endl;
                    break;
                }
                else {
                    // print the sorted course list
                    printSortedCourseList(courseList);
                    break;
                }
            case 3: // serach for course by course number and print it
                // check to see if data loaded into structure
                if (courseList.size() <= 0) {
                    // if no data then print error
                    cout << "No courses are loaded in data structure. Please load the data structure before chosing this option." << endl;
                    break;
                }
                else {
                    // call searchCourseByNum
                    seachCourseByNum(courseList);
                    break;
                }
            case 4: //Exit
                cout << "Exiting...Goodbye!" << endl;
        }

        //return 0
        return 0;
    }

}
