#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

using namespace std;

struct student {
    string name;
    string ID;
    string gender;
    int age;
    string email;
    string Department;
    int year;

    // Year 1 courses
    float Calculus_I;
    float Management;
    float History;
    float Philosophy;
    float Mechanic_I;
    float Calculus_II;
    float Thermodynamic;
    float Marketing;
    float Environment;
    float Information;

    // Year 2 courses
    float Electricity;
    float Calculus_III;
    float Data_Structure_I;
    float Algebra;
    float Probability;
    float Differential_Equation;
    float Computer_Architecture;
    float Data_Structure_II;
};

struct Element {
    student info;
    Element *next;
    Element *previous;
};

struct List {
    int size;
    Element *head;
    Element *tail;
};

List* createEmptyList() {
    List *ls = new List();
    ls->size = 0;
    ls->head = nullptr;
    ls->tail = nullptr;
    return ls;
}

void addEnd(List *ls, const student newData) {
    Element *e = new Element();
    e->info = newData;
    e->next = nullptr;

    if (ls->size == 0) {
        ls->head = ls->tail = e;
        e->previous = nullptr;
    } else {
        ls->tail->next = e;
        e->previous = ls->tail;
        ls->tail = e;
    }
    ls->size++;
}


void inputStudent_information(List* l) {
    student s;

    cout << "Select Year (1 or 2): ";
    while (!(cin >> s.year) || (s.year != 1 && s.year != 2)) {
        cout << RED << "Invalid input! Please enter 1 or 2: " << RESET;
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Enter ID: ";
    getline(cin, s.ID);
    cout << "Enter Age: ";
    cin >> s.age;
    cout << "Enter Gender (M/F): ";
    cin >> s.gender;
    cout << "Enter Email: ";
    cin.ignore();
    getline(cin, s.email);
    cout << "Enter Department: ";
    getline(cin, s.Department);
    s.Calculus_I = s.Management = s.History = s.Philosophy = s.Mechanic_I =
    s.Calculus_II = s.Thermodynamic = s.Marketing = s.Environment = s.Information =
    s.Electricity = s.Calculus_III = s.Data_Structure_I = s.Algebra =
    s.Probability = s.Differential_Equation = s.Computer_Architecture = s.Data_Structure_II = 0;

    addEnd(l, s);
    cout << GREEN << "Student added successfully!" << RESET << endl;
}

void calculate_GPA(const student &s, float &average_score, int &total_credits, string &gpa) {
    if (s.year == 1) {
        average_score = (s.Calculus_I * 3 + s.Management * 3 +
                        s.History * 2 + s.Philosophy * 2 +
                        s.Mechanic_I * 3 + s.Calculus_II * 3 +
                        s.Thermodynamic * 3 + s.Marketing * 2 +
                        s.Environment * 2 + s.Information * 2) / 25.0;
        total_credits = 25;
    } else { // Year 2
        average_score = (s.Electricity * 3 + s.Calculus_III * 2 +
                        s.Data_Structure_I * 3 + s.Algebra * 2 +
                        s.Probability * 2 + s.Differential_Equation * 2 +
                        s.Computer_Architecture * 3 + s.Data_Structure_II * 3) / 20.0;
        total_credits = 20;
    }

    if (average_score >= 85) gpa = "4.0";
    else if (average_score >= 80) gpa = "3.5";
    else if (average_score >= 70) gpa = "3.0";
    else if (average_score >= 60) gpa = "2.5";
    else if (average_score >= 50) gpa = "2.0";
    else if (average_score >= 30) gpa = "1.5";
    else gpa = "1.0";
}

void display_student_info(const student &s) {
    float average_score;
    int total_credits;
    string gpa;

    calculate_GPA(s, average_score, total_credits, gpa);

    cout << YELLOW << "\n--------------------------------------------\n"<< RESET;
    cout << "Name: " << s.name << "\nGender: " << s.gender << "\nAge: " << s.age
         << "\nID: " << s.ID << "\nEmail: " << s.email << "\nDepartment: " << s.Department
         << "\nYear: " << s.year << "\n";

    if (s.year == 1) {
        cout << "Calculus I: " << s.Calculus_I << "\n"
             << "Management: " << s.Management << "\n"
             << "History: " << s.History << "\n"
             << "Philosophy: " << s.Philosophy << "\n"
             << "Mechanic I: " << s.Mechanic_I << "\n"
             << "Calculus II: " << s.Calculus_II << "\n"
             << "Thermodynamic: " << s.Thermodynamic << "\n"
             << "Marketing: " << s.Marketing << "\n"
             << "Environment: " << s.Environment << "\n"
             << "Information: " << s.Information << "\n";
    } else {
        cout << "Electricity: " << s.Electricity << "\n"
             << "Calculus III: " << s.Calculus_III << "\n"
             << "Data Structure I: " << s.Data_Structure_I << "\n"
             << "Algebra: " << s.Algebra << "\n"
             << "Probability: " << s.Probability << "\n"
             << "Differential Equation: " << s.Differential_Equation << "\n"
             << "Computer Architecture: " << s.Computer_Architecture << "\n"
             << "Data Structure II: " << s.Data_Structure_II << "\n";
    }

    cout << "Average Score: " << average_score << "\nGPA: " << gpa
         << "\nTotal Credits: " << total_credits
         << "\n--------------------------------------------\n";
}

void gpa_display(Element *e) {
    if (e != nullptr) {
        display_student_info(e->info);
    }
}
void storeToCSV(List* ls) {
    ofstream files[2]; // Only year 1 and 2
    for (int i = 0; i < 2; i++) {
        string filename = "students_year" + to_string(i+1) + ".csv";
        files[i].open(filename);
        if (!files[i].is_open()) {
            cout << "Error: Could not open file " << filename << " for writing!" << endl;
            return;
        }
        // Write header for each file
        if (i == 0) { // Year 1
            files[i] << "Name,ID,Age,Gender,Email,Department,Year,Calculus_I,Management,History,Philosophy,"
                    << "Mechanic_I,Calculus_II,Thermodynamic,Marketing,Environment,Information,Average,GPA\n";
        } else { // Year 2
            files[i] << "Name,ID,Age,Gender,Email,Department,Year,Electricity,Calculus_III,Data_Structure_I,Algebra,"
                    << "Probability,Differential_Equation,Computer_Architecture,Data_Structure_II,Average,GPA\n";
        }
    }

    Element* tmp = ls->head;
    while (tmp != nullptr) {
        float average_score;
        int total_credits;
        string gpa;

        // Use the existing calculate_GPA function
        calculate_GPA(tmp->info, average_score, total_credits, gpa);

        int yearIndex = tmp->info.year - 1;
        if (yearIndex < 2) { // Only process year 1 and 2
            files[yearIndex] << tmp->info.name << ","
                           << tmp->info.ID << ","
                           << tmp->info.age << ","
                           << tmp->info.gender << ","
                           << tmp->info.email << ","
                           << tmp->info.Department << ","
                           << tmp->info.year << ",";

            if (yearIndex == 0) { // Year 1
                files[yearIndex] << tmp->info.Calculus_I << ","
                               << tmp->info.Management << ","
                               << tmp->info.History << ","
                               << tmp->info.Philosophy << ","
                               << tmp->info.Mechanic_I << ","
                               << tmp->info.Calculus_II << ","
                               << tmp->info.Thermodynamic << ","
                               << tmp->info.Marketing << ","
                               << tmp->info.Environment << ","
                               << tmp->info.Information << ",";
            } else { // Year 2
                files[yearIndex] << tmp->info.Electricity << ","
                               << tmp->info.Calculus_III << ","
                               << tmp->info.Data_Structure_I << ","
                               << tmp->info.Algebra << ","
                               << tmp->info.Probability << ","
                               << tmp->info.Differential_Equation << ","
                               << tmp->info.Computer_Architecture << ","
                               << tmp->info.Data_Structure_II << ",";
            }

            files[yearIndex] << average_score << ","
                            << gpa << "\n";
        }

        tmp = tmp->next;
    }

    for (int i = 0; i < 2; i++) {
        files[i].close();
    }
    cout << GREEN << "Data has been successfully saved to year files" << RESET << endl;
}
void readFile(List* ls) {
    for (int year = 1; year <= 2; year++) {
        string filename = "students_year" + to_string(year) + ".csv";
        fstream file(filename, ios::in);

        if (!file.is_open()) {
            cout << "Note: Could not open file " << filename << " for reading (may not exist yet)" << endl;
            continue;
        }

        string line;
        getline(file, line); // Skip header line

        while (getline(file, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            student s_info;
            string Strage, StrYear;

            getline(ss, s_info.name, ',');
            getline(ss, s_info.ID, ',');
            getline(ss, Strage, ',');
            getline(ss, s_info.gender, ',');
            getline(ss, s_info.email, ',');
            getline(ss, s_info.Department, ',');
            getline(ss, StrYear, ',');

            if (Strage.empty() || StrYear.empty()) {
                continue;
            }

            s_info.age = stoi(Strage);
            s_info.year = stoi(StrYear);

            if (s_info.year == 1) {
                string scoreStr;
                getline(ss, scoreStr, ','); s_info.Calculus_I = stof(scoreStr);
                getline(ss, scoreStr, ','); s_info.Management = stof(scoreStr);
                getline(ss, scoreStr, ','); s_info.History = stof(scoreStr);
                getline(ss, scoreStr, ','); s_info.Philosophy = stof(scoreStr);
                getline(ss, scoreStr, ','); s_info.Mechanic_I = stof(scoreStr);
                getline(ss, scoreStr, ','); s_info.Calculus_II = stof(scoreStr);
                getline(ss, scoreStr, ','); s_info.Thermodynamic = stof(scoreStr);
                getline(ss, scoreStr, ','); s_info.Marketing = stof(scoreStr);
                getline(ss, scoreStr, ','); s_info.Environment = stof(scoreStr);
                getline(ss, scoreStr); s_info.Information = stof(scoreStr);
            } else {
                string scoreStr;
                getline(ss, scoreStr, ','); s_info.Electricity = stof(scoreStr);
                getline(ss, scoreStr, ','); s_info.Calculus_III = stof(scoreStr);
                getline(ss, scoreStr, ','); s_info.Data_Structure_I = stof(scoreStr);
                getline(ss, scoreStr, ','); s_info.Algebra = stof(scoreStr);
                getline(ss, scoreStr, ','); s_info.Probability = stof(scoreStr);
                getline(ss, scoreStr, ','); s_info.Differential_Equation = stof(scoreStr);
                getline(ss, scoreStr, ','); s_info.Computer_Architecture = stof(scoreStr);
                getline(ss, scoreStr); s_info.Data_Structure_II = stof(scoreStr);
            }

            addEnd(ls, s_info);
        }
        file.close();
    }
}




Element* searchByID(List* ls, const string& id) {
    Element* tmp = ls->head;
    while (tmp != nullptr) {
        if (tmp->info.ID == id) return tmp;
        tmp = tmp->next;
    }
    return nullptr;
}

void searchStudentInformation(List* ls, const string& id) {
    Element* student = searchByID(ls, id);
    if (student == nullptr) {
        cout << RED << "Student with ID " << id << " not found!" << RESET << endl;
        return;
    }
    cout << YELLOW << "\n--------------------------------------------\n" << RESET;
    cout << "Student Information for ID: " << id << "\n";
    gpa_display(student);
}

void deleteStudentByID(List* ls, const string& id) {
    Element* tmp = ls->head;
    while (tmp != nullptr) {
        if (tmp->info.ID == id) {
            if (tmp->previous != nullptr) tmp->previous->next = tmp->next;
            else ls->head = tmp->next;
            if (tmp->next != nullptr) tmp->next->previous = tmp->previous;
            else ls->tail = tmp->previous;

            delete tmp;
            ls->size--;
            cout << "Student with ID " << id << " has been deleted!" << endl;
            return;
        }
        tmp = tmp->next;
    }
    cout << "Student with ID " << id << " not found!" << endl;
}
void displayStudentsByYear(List* ls, int year) {
    if (ls->size == 0) {
        cout << RED << "No students in the list!" << RESET << endl;
        return;
    }

    Element* tmp = ls->head;
    bool found = false;
    bool headerPrinted = false;

    while (tmp != nullptr) {
        if (year == 0 || tmp->info.year == year) {
            if (!headerPrinted) {
                cout << YELLOW << "\n--------------------------------------------------------------------------------\n" << RESET;
                cout << "Name\tGender\tAge\tID\t\tEmail\t\tDepartment\tYear\n";
                cout << YELLOW << "--------------------------------------------------------------------------------\n" << RESET;
                headerPrinted = true;
            }

            cout << tmp->info.name << "\t"
                 << tmp->info.gender << "\t"
                 << tmp->info.age << "\t"
                 << tmp->info.ID << "\t"
                 << tmp->info.email << "\t"
                 << tmp->info.Department << "\t"
                 << tmp->info.year << "\n";

            found = true;
        }
        tmp = tmp->next;
    }

    if (found) {
        cout << YELLOW << "--------------------------------------------------------------------------------\n" << RESET;
    } else {
        cout << RED << "No students found for Year " << year << RESET << endl;
    }
}
void sortStudentsByGPA(List* ls, int year) {
    if (ls->size <= 1) {
        cout << "Not enough Year " << year << " students to sort.\n";
        return;
    }

    bool swapped;
    Element* current;
    Element* last = nullptr;

    do {
        swapped = false;
        current = ls->head;

        while (current != nullptr && current->next != nullptr && current->next != last) {
            if (current->info.year == year && current->next->info.year == year) {
                float avg_current, avg_next;
                int credits_current, credits_next;
                string gpa_current, gpa_next;

                calculate_GPA(current->info, avg_current, credits_current, gpa_current);
                calculate_GPA(current->next->info, avg_next, credits_next, gpa_next);

                if (avg_current < avg_next) {  // Changed to sort by average score
                    // Swap the data instead of nodes to keep the list structure intact
                    student temp = current->info;
                    current->info = current->next->info;
                    current->next->info = temp;
                    swapped = true;
                }
            }
            current = current->next;
        }
        last = current;
    } while (swapped);

    cout << "\nYear " << year << " Students Sorted by GPA (Highest to Lowest):\n";
    cout << YELLOW << "---------------------------------------------------------------\n" << RESET;
    cout << "No.\tName\t\tID\t\tGPA\tAverage Score\n";
    cout << YELLOW << "---------------------------------------------------------------\n" << RESET;

    Element* tmp = ls->head;
    int counter = 1;
    bool found = false;

    while (tmp != nullptr) {
        if (tmp->info.year == year) {
            float average_score;
            int total_credits;
            string gpa;
            calculate_GPA(tmp->info, average_score, total_credits, gpa);

            cout << counter++ << "\t"
                 << tmp->info.name << "\t\t"
                 << tmp->info.ID << "\t"
                 << gpa << "\t"
                 << average_score << "\n";

            found = true;
        }
        tmp = tmp->next;
    }

    if (found) {
        cout << YELLOW << "------------------------------------------------------------\n" << RESET;
    } else {
        cout << RED << "No students found for Year " << year << RESET << endl;
    }
}
void sortYear1StudentsByGPA(List* ls) {
    sortStudentsByGPA(ls, 1);
}

void sortYear2StudentsByGPA(List* ls) {
    sortStudentsByGPA(ls, 2);
}
void inputScoresForStudent(Element* student) {
    if (student == nullptr) {
        cout << RED << "Student not found!" << RESET << endl;
        return;
    }

    if (student->info.year == 1) {
        cout << "Enter scores for Year 1 courses:\n";

        cout << "Calculus I (3 credits): ";
        while (!(cin >> student->info.Calculus_I) || student->info.Calculus_I < 0 || student->info.Calculus_I > 100) {
            cout << RED << "Invalid input! Please enter a score between 0 and 100: " << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Management (3 credits): ";
        while (!(cin >> student->info.Management) || student->info.Management < 0 || student->info.Management > 100) {
            cout << RED << "Invalid input! Please enter a score between 0 and 100: " << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "History (2 credits): ";
        while (!(cin >> student->info.History) || student->info.History < 0 || student->info.History > 100) {
            cout << RED << "Invalid input! Please enter a score between 0 and 100: " << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Philosophy (2 credits): ";
        while (!(cin >> student->info.Philosophy) || student->info.Philosophy < 0 || student->info.Philosophy > 100) {
            cout << RED << "Invalid input! Please enter a score between 0 and 100: " << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Mechanic I (3 credits): ";
        while (!(cin >> student->info.Mechanic_I) || student->info.Mechanic_I < 0 || student->info.Mechanic_I > 100) {
            cout << RED << "Invalid input! Please enter a score between 0 and 100: " << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Calculus II (3 credits): ";
        while (!(cin >> student->info.Calculus_II) || student->info.Calculus_II < 0 || student->info.Calculus_II > 100) {
            cout << RED << "Invalid input! Please enter a score between 0 and 100: " << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }

        cout << "Thermodynamic (3 credits): ";
        while (!(cin >> student->info.Thermodynamic) || student->info.Thermodynamic < 0 || student->info.Thermodynamic > 100) {
            cout << RED << "Invalid input! Please enter a score between 0 and 100: " << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Marketing (2 credits): ";
        while (!(cin >> student->info.Marketing) || student->info.Marketing < 0 || student->info.Marketing > 100) {
            cout << RED << "Invalid input! Please enter a score between 0 and 100: " << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Environment (2 credits): ";
        while (!(cin >> student->info.Environment) || student->info.Environment < 0 || student->info.Environment > 100) {
            cout << RED << "Invalid input! Please enter a score between 0 and 100: " << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Information (2 credits): ";
        while (!(cin >> student->info.Information) || student->info.Information < 0 || student->info.Information > 100) {
            cout << RED << "Invalid input! Please enter a score between 0 and 100: " << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    } else {
        cout << "Enter scores for Year 2 courses:\n";

        cout << "Electricity (3 credits): ";
        while (!(cin >> student->info.Electricity) || student->info.Electricity < 0 || student->info.Electricity > 100) {
            cout << RED << "Invalid input! Please enter a score between 0 and 100: " << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Calculus III (2 credits): ";
        while (!(cin >> student->info.Calculus_III) || student->info.Calculus_III < 0 || student->info.Calculus_III > 100) {
            cout << RED << "Invalid input! Please enter a score between 0 and 100: " << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Data Structure I (3 credits): ";
        while (!(cin >> student->info.Data_Structure_I) || student->info.Data_Structure_I < 0 || student->info.Data_Structure_I > 100) {
            cout << RED << "Invalid input! Please enter a score between 0 and 100: " << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Algebra (2 credits): ";
        while (!(cin >> student->info.Algebra) || student->info.Algebra < 0 || student->info.Algebra > 100) {
            cout << RED << "Invalid input! Please enter a score between 0 and 100: " << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Probability (2 credits): ";
        while (!(cin >> student->info.Probability) || student->info.Probability < 0 || student->info.Probability > 100) {
            cout << RED << "Invalid input! Please enter a score between 0 and 100: " << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Differential Equation (2 credits): ";
        while (!(cin >> student->info.Differential_Equation) || student->info.Differential_Equation < 0 || student->info.Differential_Equation > 100) {
            cout << RED << "Invalid input! Please enter a score between 0 and 100: " << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Computer Architecture (3 credits): ";
        while (!(cin >> student->info.Computer_Architecture) || student->info.Computer_Architecture < 0 || student->info.Computer_Architecture > 100) {
            cout << RED << "Invalid input! Please enter a score between 0 and 100: " << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Data Structure II (3 credits): ";
        while (!(cin >> student->info.Data_Structure_II) || student->info.Data_Structure_II < 0 || student->info.Data_Structure_II > 100) {
            cout << RED << "Invalid input! Please enter a score between 0 and 100: " << RESET;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    cout << GREEN << "Scores updated successfully!" << RESET << endl;
}
void updateStudentInformationByID(List* ls) {
    if (ls->size == 0) {
        cout << RED << "No students in the list to update!" << RESET << endl;
        return;
    }
    string id;
    cout << "Enter student ID to update: ";
    cin.ignore();
    getline(cin, id);

    Element* student = searchByID(ls, id);
    if (student == nullptr) {
        cout << RED << "Student with ID " << id << " not found!" << RESET << endl;
        return;
    }
    while(1) {
        cout << CYAN << "\nCurrent student information:" << RESET << endl;
        display_student_info(student->info);

        cout << YELLOW << "\nSelect information to update:" << RESET << endl;
        cout << "1. Name\n";
        cout << "2. Age\n";
        cout << "3. Gender\n";
        cout << "4. Email\n";
        cout << "5. Department\n";
        cout << "6. Year\n";
        cout << "7. Course Scores\n";
        cout << "0. Exit Update Menu\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, student->info.name);
            cout << GREEN << "Name updated successfully!" << RESET << endl;
        }
        else if (choice == 2) {
            cout << "Enter new age: ";
            while (!(cin >> student->info.age) || student->info.age <= 0) {
                cout << RED << "Invalid input! Please enter a positive number: " << RESET;
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cout << GREEN << "Age updated successfully!" << RESET << endl;
        }
        else if (choice == 3) {
            cout << "Enter new gender (M/F): ";
            cin >> student->info.gender;
            while (student->info.gender != "M" && student->info.gender != "F") {
                cout << RED << "Invalid input! Please enter M or F: " << RESET;
                cin >> student->info.gender;
            }
            cout << GREEN << "Gender updated successfully!" << RESET << endl;
        }
        else if (choice == 4) {
            cout << "Enter new email: ";
            cin.ignore();
            getline(cin, student->info.email);
            cout << GREEN << "Email updated successfully!" << RESET << endl;
        }
        else if (choice == 5) {
            cout << "Enter new department: ";
            cin.ignore();
            getline(cin, student->info.Department);
            cout << GREEN << "Department updated successfully!" << RESET << endl;
        }
        else if (choice == 6) {
            cout << "Enter new year (1 or 2): ";
            while (!(cin >> student->info.year) || (student->info.year != 1 && student->info.year != 2)) {
                cout << RED << "Invalid input! Please enter 1 or 2: " << RESET;
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cout << GREEN << "Year updated successfully!" << RESET << endl;
        }
        else if (choice == 7) {
            inputScoresForStudent(student);
        }
        else if (choice == 0) {
            cout << "Exiting update menu...\n";
            return;
        }
        else {
            cout << RED << "Invalid choice! Please try again." << RESET << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        char cont;
        cout << "\nUpdate another field for this student? (y/n): ";
        cin >> cont;
        if (tolower(cont) != 'y') {
            break;
        }
    }
    cout << GREEN << "\nFinal updated student information:" << RESET << endl;
    display_student_info(student->info);
}
