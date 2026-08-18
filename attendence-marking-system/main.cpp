#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

// ================= CONSTANTS =================
const int MAX_STUDENTS = 100;
const int MAX_DATES = 30;
const string ADMIN_PASS = "admin123";

// ================= STRUCTURES =================

struct Attendance {
    string date;
    bool isPresent;
};

struct Student {
    string name;
    Attendance records[MAX_DATES];
    int dateCount = 0;
};

// ================= GLOBAL VARIABLES =================

Student students[MAX_STUDENTS];
int studentCount = 0;

// ================= FUNCTION DECLARATIONS =================

bool adminLogin();

void adminMenu();
void studentMenu();

void addStudent();
void markAttendance();
void displayRecords();
void searchStudentMenu();
void deleteStudent();

void viewOwnAttendance();
void viewAttendancePercentage();
void displayStudentReport();
void displayDateWiseReport();

int searchStudent(int index, const string& query);
int findStudent(const string& name);

double calculatePercentage(int index);

void pauseScreen();


// =====================================================
//                     ADMIN LOGIN
// =====================================================

bool adminLogin() {

    string password;

    cout << "\n========================================\n";
    cout << "           ADMIN LOGIN\n";
    cout << "========================================\n";

    cout << "Enter Admin Password: ";
    getline(cin, password);

    if (password == ADMIN_PASS) {
        cout << "\nLogin Successful!\n";
        return true;
    }

    cout << "\nIncorrect Password!\n";
    return false;
}


// =====================================================
//                     ADD STUDENT
// =====================================================

void addStudent() {

    if (studentCount >= MAX_STUDENTS) {
        cout << "\nMaximum student limit reached.\n";
        return;
    }

    string name;

    cout << "\nEnter student name: ";
    getline(cin, name);

    if (name.empty()) {
        cout << "Student name cannot be empty.\n";
        return;
    }

    // Check duplicate student
    if (findStudent(name) != -1) {
        cout << "Student already exists.\n";
        return;
    }

    students[studentCount].name = name;
    students[studentCount].dateCount = 0;

    studentCount++;

    cout << "\nStudent added successfully!\n";
}


// =====================================================
//                  MARK ATTENDANCE
// =====================================================

void markAttendance() {

    if (studentCount == 0) {
        cout << "\nNo students available.\n";
        return;
    }

    string date;

    cout << "\nEnter date (dd-mm-yyyy): ";
    getline(cin, date);

    for (int i = 0; i < studentCount; i++) {

        if (students[i].dateCount >= MAX_DATES) {
            cout << "\nMaximum attendance records reached for "
                 << students[i].name << ".\n";
            continue;
        }

        char status;

        cout << "\nMark attendance for "
             << students[i].name
             << " (P/A): ";

        cin >> status;
        cin.ignore();

        status = toupper(status);

        if (status != 'P' && status != 'A') {
            cout << "Invalid input! Marked as Absent.\n";
            status = 'A';
        }

        students[i].records[students[i].dateCount].date = date;

        students[i].records[students[i].dateCount].isPresent =
            (status == 'P');

        students[i].dateCount++;
    }

    cout << "\nAttendance marked successfully for all students.\n";
}


// =====================================================
//                DISPLAY ALL RECORDS
// =====================================================

void displayRecords() {

    if (studentCount == 0) {
        cout << "\nNo students available.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "          ALL ATTENDANCE RECORDS\n";
    cout << "========================================\n";

    for (int i = 0; i < studentCount; i++) {

        cout << "\nStudent: " << students[i].name << "\n";

        if (students[i].dateCount == 0) {
            cout << "  No attendance records.\n";
            continue;
        }

        for (int j = 0; j < students[i].dateCount; j++) {

            cout << "  Date: "
                 << students[i].records[j].date
                 << " | Status: "
                 << (students[i].records[j].isPresent
                     ? "Present"
                     : "Absent")
                 << "\n";
        }

        cout << "  Attendance Percentage: "
             << fixed << setprecision(2)
             << calculatePercentage(i)
             << "%\n";
    }
}


// =====================================================
//                RECURSIVE SEARCH
// =====================================================

int searchStudent(int index, const string& query) {

    if (index == studentCount) {
        return -1;
    }

    if (students[index].name == query) {
        return index;
    }

    return searchStudent(index + 1, query);
}


// =====================================================
//                  ITERATIVE SEARCH
// =====================================================

int findStudent(const string& name) {

    for (int i = 0; i < studentCount; i++) {

        if (students[i].name == name) {
            return i;
        }
    }

    return -1;
}


// =====================================================
//                 SEARCH STUDENT
// =====================================================

void searchStudentMenu() {

    string name;

    cout << "\nEnter student name to search: ";
    getline(cin, name);

    int index = searchStudent(0, name);

    if (index == -1) {
        cout << "\nStudent not found.\n";
        return;
    }

    cout << "\nStudent Found!\n";
    cout << "Name: " << students[index].name << "\n";

    cout << "Total Records: "
         << students[index].dateCount
         << "\n";

    cout << "Attendance Percentage: "
         << fixed << setprecision(2)
         << calculatePercentage(index)
         << "%\n";
}


// =====================================================
//             CALCULATE ATTENDANCE %
// =====================================================

double calculatePercentage(int index) {

    if (students[index].dateCount == 0) {
        return 0.0;
    }

    int presentCount = 0;

    for (int i = 0;
         i < students[index].dateCount;
         i++) {

        if (students[index].records[i].isPresent) {
            presentCount++;
        }
    }

    return (presentCount * 100.0) /
           students[index].dateCount;
}


// =====================================================
//             VIEW OWN ATTENDANCE
// =====================================================

void viewOwnAttendance() {

    string name;

    cout << "\nEnter your name: ";
    getline(cin, name);

    int index = searchStudent(0, name);

    if (index == -1) {
        cout << "\nStudent not found.\n";
        return;
    }

    if (students[index].dateCount == 0) {
        cout << "\nNo attendance records available.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "        YOUR ATTENDANCE RECORD\n";
    cout << "========================================\n";

    cout << "Student: "
         << students[index].name
         << "\n\n";

    for (int i = 0;
         i < students[index].dateCount;
         i++) {

        cout << "Date: "
             << students[index].records[i].date
             << " | Status: "
             << (students[index].records[i].isPresent
                 ? "Present"
                 : "Absent")
             << "\n";
    }

    cout << "\nAttendance Percentage: "
         << fixed << setprecision(2)
         << calculatePercentage(index)
         << "%\n";
}


// =====================================================
//             VIEW ATTENDANCE PERCENTAGE
// =====================================================

void viewAttendancePercentage() {

    if (studentCount == 0) {
        cout << "\nNo students available.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "       ATTENDANCE PERCENTAGE\n";
    cout << "========================================\n";

    cout << left
         << setw(25) << "Student"
         << setw(15) << "Records"
         << setw(15) << "Percentage"
         << "\n";

    cout << "----------------------------------------\n";

    for (int i = 0; i < studentCount; i++) {

        cout << left
             << setw(25) << students[i].name
             << setw(15) << students[i].dateCount
             << setw(15)
             << fixed << setprecision(2)
             << calculatePercentage(i)
             << "%\n";
    }
}


// =====================================================
//              STUDENT-WISE REPORT
// =====================================================

void displayStudentReport() {

    string name;

    cout << "\nEnter student name: ";
    getline(cin, name);

    int index = findStudent(name);

    if (index == -1) {
        cout << "\nStudent not found.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "          STUDENT REPORT\n";
    cout << "========================================\n";

    cout << "Student Name: "
         << students[index].name
         << "\n";

    cout << "Total Classes: "
         << students[index].dateCount
         << "\n";

    int present = 0;
    int absent = 0;

    for (int i = 0;
         i < students[index].dateCount;
         i++) {

        if (students[index].records[i].isPresent) {
            present++;
        } else {
            absent++;
        }
    }

    cout << "Present: " << present << "\n";
    cout << "Absent: " << absent << "\n";

    cout << "Attendance Percentage: "
         << fixed << setprecision(2)
         << calculatePercentage(index)
         << "%\n";

    cout << "\nAttendance Status: ";

    double percentage = calculatePercentage(index);

    if (percentage >= 75) {
        cout << "GOOD\n";
    } else {
        cout << "LOW - Below 75%\n";
    }
}


// =====================================================
//               DATE-WISE REPORT
// =====================================================

void displayDateWiseReport() {

    string date;

    cout << "\nEnter date (dd-mm-yyyy): ";
    getline(cin, date);

    bool found = false;

    cout << "\n========================================\n";
    cout << "          DATE-WISE REPORT\n";
    cout << "========================================\n";

    cout << "Date: " << date << "\n\n";

    int present = 0;
    int absent = 0;

    for (int i = 0; i < studentCount; i++) {

        for (int j = 0;
             j < students[i].dateCount;
             j++) {

            if (students[i].records[j].date == date) {

                found = true;

                cout << left
                     << setw(25)
                     << students[i].name
                     << (students[i].records[j].isPresent
                         ? "Present"
                         : "Absent")
                     << "\n";

                if (students[i].records[j].isPresent) {
                    present++;
                } else {
                    absent++;
                }

                break;
            }
        }
    }

    if (!found) {
        cout << "No attendance records found for this date.\n";
        return;
    }

    cout << "\nTotal Present: " << present << "\n";
    cout << "Total Absent: " << absent << "\n";
}


// =====================================================
//                  DELETE STUDENT
// =====================================================

void deleteStudent() {

    if (studentCount == 0) {
        cout << "\nNo students available.\n";
        return;
    }

    string name;

    cout << "\nEnter student name to delete: ";
    getline(cin, name);

    int index = findStudent(name);

    if (index == -1) {
        cout << "\nStudent not found.\n";
        return;
    }

    for (int i = index;
         i < studentCount - 1;
         i++) {

        students[i] = students[i + 1];
    }

    studentCount--;

    cout << "\nStudent deleted successfully.\n";
}


// =====================================================
//                    PAUSE SCREEN
// =====================================================

void pauseScreen() {

    cout << "\nPress ENTER to continue...";
    cin.get();
}


// =====================================================
//                    ADMIN MENU
// =====================================================

void adminMenu() {

    int choice;

    do {

        cout << "\n\n========================================\n";
        cout << "       STUDENT ATTENDANCE SYSTEM\n";
        cout << "             ADMIN PANEL\n";
        cout << "========================================\n";

        cout << "1. Add Student\n";
        cout << "2. Mark Attendance\n";
        cout << "3. Display All Records\n";
        cout << "4. Search Student\n";
        cout << "5. Attendance Percentage\n";
        cout << "6. Student Report\n";
        cout << "7. Date-Wise Report\n";
        cout << "8. Delete Student\n";
        cout << "9. Logout\n";

        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                markAttendance();
                break;

            case 3:
                displayRecords();
                break;

            case 4:
                searchStudentMenu();
                break;

            case 5:
                viewAttendancePercentage();
                break;

            case 6:
                displayStudentReport();
                break;

            case 7:
                displayDateWiseReport();
                break;

            case 8:
                deleteStudent();
                break;

            case 9:
                cout << "\nAdmin logged out successfully.\n";
                break;

            default:
                cout << "\nInvalid choice!\n";
        }

        if (choice != 9) {
            pauseScreen();
        }

    } while (choice != 9);
}


// =====================================================
//                    STUDENT MENU
// =====================================================

void studentMenu() {

    int choice;

    do {

        cout << "\n\n========================================\n";
        cout << "          STUDENT PANEL\n";
        cout << "========================================\n";

        cout << "1. View My Attendance\n";
        cout << "2. View My Percentage\n";
        cout << "3. Back to Main Menu\n";

        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {

            case 1:
                viewOwnAttendance();
                break;

            case 2: {
                string name;

                cout << "\nEnter your name: ";
                getline(cin, name);

                int index = findStudent(name);

                if (index == -1) {
                    cout << "\nStudent not found.\n";
                } else {
                    cout << "\nStudent: "
                         << students[index].name
                         << "\n";

                    cout << "Attendance Percentage: "
                         << fixed << setprecision(2)
                         << calculatePercentage(index)
                         << "%\n";
                }

                break;
            }

            case 3:
                cout << "\nReturning to main menu...\n";
                break;

            default:
                cout << "\nInvalid choice!\n";
        }

        if (choice != 3) {
            pauseScreen();
        }

    } while (choice != 3);
}


// =====================================================
//                     MAIN FUNCTION
// =====================================================

int main() {

    int choice;

    do {

        cout << "\n\n";
        cout << "========================================\n";
        cout << "    STUDENT ATTENDANCE MANAGEMENT\n";
        cout << "             SYSTEM\n";
        cout << "========================================\n";

        cout << "1. Admin Login\n";
        cout << "2. Student Panel\n";
        cout << "3. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {

            case 1:

                if (adminLogin()) {
                    pauseScreen();
                    adminMenu();
                } else {
                    pauseScreen();
                }

                break;

            case 2:
                studentMenu();
                break;

            case 3:
                cout << "\nThank you for using the system!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
                pauseScreen();
        }

    } while (choice != 3);

    return 0;
}