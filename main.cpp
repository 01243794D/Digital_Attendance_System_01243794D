// C++ Midsemester Project: Digital Attendance System
// Developed by: [Amezah Emmanuel] - [01243794D]

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// --------------------- STUDENT CLASS --------------------- 
class Student {
private:
    string indexNumber;
    string name;
    string program;

public:
    Student() {}

    Student(string idx, string nm, string prog) {
        indexNumber = idx;
        name = nm;
        program = prog;
    }

    void inputStudent() {
        cout << "Enter Index Number: ";
        cin >> indexNumber;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Program: ";
        getline(cin, program);
    }

    void displayStudent() const {
        cout << "Index: " << indexNumber
             << " | Name: " << name
             << " | Program: " << program << endl;
    }

    string getIndex() const {
        return indexNumber;
    }

    string toFileString() const {
        return indexNumber + "," + name + "," + program;
    }

    static Student fromFileString(string line) {
        stringstream ss(line);
        string idx, nm, prog;

        getline(ss, idx, ',');
        getline(ss, nm, ',');
        getline(ss, prog, ',');

        return Student(idx, nm, prog);
    }
};

// --------------------- FILE FUNCTIONS ---------------------

void saveStudentToFile(const Student& s) {
    ofstream file("students.txt", ios::app);
    file << s.toFileString() << endl;
    file.close();
}

vector<Student> loadStudents() {
    vector<Student> students;
    ifstream file("students.txt");
    string line;

    while (getline(file, line)) {
        if (!line.empty()) {
            students.push_back(Student::fromFileString(line));
        }
    }

    file.close();
    return students;
}

// --------------------- SEARCH FUNCTION ---------------------

void searchStudent() {
    vector<Student> students = loadStudents();
    string searchIndex;

    cout << "Enter index number to search: ";
    cin >> searchIndex;

    bool found = false;

    for (const Student& s : students) {
        if (s.getIndex() == searchIndex) {
            s.displayStudent();
            found = true;
        }
    }

    if (!found) {
        cout << "Student not found.\n";
    }
}

// =--------------------- SESSION CREATION ---------------------

void createSession() {
    string courseCode, date, startTime;
    int duration;

    cout << "Enter Course Code: ";
    cin >> courseCode;

    cout << "Enter Date (YYYY_MM_DD): ";
    cin >> date;

    cout << "Enter Start Time (HH:MM): ";
    cin >> startTime;

    cout << "Enter Duration (hours): ";
    cin >> duration;

    string filename = "session_" + courseCode + "_" + date + ".txt";

    ofstream file(filename);
    file << "Course: " << courseCode << endl;
    file << "Date: " << date << endl;
    file << "Start Time: " << startTime << endl;
    file << "Duration: " << duration << " hours" << endl;
    file << "-----------------------------------" << endl;
    file.close();

    cout << "Session created successfully.\n";
}

// --------------------- MARK ATTENDANCE ---------------------

void markAttendance() {
    string filename;
    cout << "Enter session file name: ";
    cin >> filename;

    vector<Student> students = loadStudents();

    ofstream file(filename, ios::app);

    for (const Student& s : students) {
        s.displayStudent();

        int status;

        do {
            cout << "1=Present  2=Absent  3=Late : ";
            cin >> status;
        } while (status < 1 || status > 3);

        string result;

        if (status == 1)
            result = "Present";
        else if (status == 2)
            result = "Absent";
        else
            result = "Late";

        file << s.getIndex() << "," << result << endl;
    }

    file.close();
    cout << "Attendance recorded successfully.\n";
}

// --------------------- VIEW REPORT ---------------------

void viewReport() {
    string filename;
    cout << "Enter session file name: ";
    cin >> filename;

    ifstream file(filename);
    string line;

    int present = 0, absent = 0, late = 0;

    while (getline(file, line)) {
        cout << line << endl;

        if (line.find("Present") != string::npos)
            present++;
        else if (line.find("Absent") != string::npos)
            absent++;
        else if (line.find("Late") != string::npos)
            late++;
    }

    file.close();

    cout << "\n========== SUMMARY ==========\n";
    cout << "Present: " << present << endl;
    cout << "Absent : " << absent << endl;
    cout << "Late   : " << late << endl;
    cout << "=============================\n";
}

// --------------------- MAIN MENU ---------------------

int main() {
    int choice;

    do {
        cout << "\n===== DIGITAL ATTENDANCE SYSTEM =====\n";
        cout << "1. Register Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Create Session\n";
        cout << "5. Mark Attendance\n";
        cout << "6. View Report\n";
        cout << "7. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Student s;
                s.inputStudent();
                saveStudentToFile(s);
                break;
            }
            case 2: {
                vector<Student> students = loadStudents();
                for (const Student& s : students)
                    s.displayStudent();
                break;
            }
            case 3:
                searchStudent();
                break;
            case 4:
                createSession();
                break;
            case 5:
                markAttendance();
                break;
            case 6:
                viewReport();
                break;
            case 7:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid option.\n";
        }

    } while (choice != 7);

    return 0;
}