#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "function.h"

using namespace std;

int main() {
    List* l = createEmptyList();
    readFile(l);

    int choice;
    string ID;

    cout << YELLOW << "\n==========================================================================\n";
    cout << WHITE << "\t        STUDENTS GRADE MANAGEMENT SYSTEM\n";
    cout << YELLOW << "==========================================================================";

    while (1) {
        cout << CYAN << "\n1." << WHITE << " Add student information\n";
        cout << CYAN << "2." << WHITE << " Display students information\n";
        cout << CYAN << "3." << WHITE << " Input student scores by ID\n";
        cout << CYAN << "4." << WHITE << " Delete student by ID\n";
        cout << CYAN << "5." << WHITE << " Search students by ID\n";
        cout << CYAN << "6." << WHITE << " Sort students by GPA\n";
        cout << CYAN << "7." << WHITE << " Save all records to files\n";
        cout << CYAN << "8." << WHITE << " Update student base on ID \n";
        cout << CYAN << "9." << WHITE << " Exit\n";
        cout << YELLOW << "==========================================================================\n";
        cout << YELLOW << "Enter Choice : " << CYAN;
        cin >> choice;
        cout << RESET;

        if (choice == 1) {
                inputStudent_information(l);
        }
        else if (choice == 2) {
                int yearChoice;
                cout << "\nDisplay students by:\n";
                cout << "1. Year 1 students\n";
                cout << "2. Year 2 students\n";
                cout << "Enter choice (1-2): ";
                cin >> yearChoice;
                    if (yearChoice == 1) {
                        cout << "\nYear 1 Students:\n";
                        displayStudentsByYear(l, 1);
                    }
                    else if (yearChoice == 2) {
                        cout << "\nYear 2 Students:\n";
                        displayStudentsByYear(l, 2);
                    }
                    else{
                        cout << RED << "Invalid choice!" << RESET << endl;
                    }
        }
        else if (choice == 3) {
                cout << "Enter student ID: ";
                cin >> ID;
                Element* student = searchByID(l, ID);
                inputScoresForStudent(student);

        }
        else if (choice == 4) {
                cout << "Enter student ID to delete: ";
                cin >> ID;
                deleteStudentByID(l, ID);
        }
        else if (choice == 5) {
                cout << "Enter student ID to search: ";
                cin >> ID;
                searchStudentInformation(l, ID);
        }
        else if (choice == 6) {
                int sortChoice;
                cout << "\nSort students by GPA:\n";
                cout << "1. Year 1 students\n";
                cout << "2. Year 2 students\n";
                cout << "Enter choice (1-2): ";
                cin >> sortChoice;

                    if (sortChoice == 1) {
                            sortYear1StudentsByGPA(l);
                    }
                    else if (sortChoice == 2) {
                            sortYear2StudentsByGPA(l);
                    }
                    else{
                            cout<<"Invalid choice. Please Enter again";   }
        }
        else if (choice == 7) {
            storeToCSV(l);
        }
        else if (choice == 8) {
            updateStudentInformationByID(l);
        }else if (choice == 9){
            break;
        }
         else {
            cout << RESET << "\n----------------------------------";
            cout << RED << "\nInvalid Input. " << GREEN << "Please Enter again! " << RESET;
            cout << "\n----------------------------------\n\n";
        }
    }

    return 0;
}
