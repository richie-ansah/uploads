/*
Name: [Your Name Here]
Student ID: [Your Student ID Here]
Date: [YYYY-MM-DD]
Program: CS101 Level 100 Student Grade Management System.
Description: Console program that stores up to 30 student records,
computes totals/grades, and prints reports/statistics using arrays,
functions, and pointers.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

const int MAX_STUDENTS = 30;

// Purpose: Read a whole line safely after previous numeric input.
// Parameters: text - message shown to user.
// Return: The entered line as a string.
string readLineInput(const string& text) {
    cout << text;
    string value;
    getline(cin, value);
    return value;
}

// Purpose: Read and validate an integer value in a given range.
// Parameters: text - prompt, minValue - lower bound, maxValue - upper bound.
// Return: A valid integer within [minValue, maxValue].
int readIntInRange(const string& text, int minValue, int maxValue) {
    int value;
    while (true) {
        cout << text;
        if (cin >> value && value >= minValue && value <= maxValue) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Enter a value from " << minValue << " to " << maxValue << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Purpose: Read and validate a score in a given range.
// Parameters: text - prompt, minValue - lower bound, maxValue - upper bound.
// Return: A valid score within [minValue, maxValue].
float readScoreInRange(const string& text, float minValue, float maxValue) {
    float score;
    while (true) {
        cout << text;
        if (cin >> score && score >= minValue && score <= maxValue) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return score;
        }
        cout << "Invalid score. Enter a value from " << minValue << " to " << maxValue << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Purpose: Enter and validate records for a class.
// Parameters: names, ids, quiz, midSem, exam - parallel arrays; studentCount - output count.
// Return: None.
void inputStudents(string* names, int* ids, float* quiz, float* midSem, float* exam, int* studentCount) {
    int count = readIntInRange("How many students do you want to enter (1-30)? ", 1, MAX_STUDENTS);

    for (int i = 0; i < count; i++) {
        cout << "\nStudent " << (i + 1) << "\n";
        names[i] = readLineInput("Enter student name: ");
        ids[i] = readIntInRange("Enter student ID (positive number): ", 1, 99999999);
        quiz[i] = readScoreInRange("Enter Quiz score (0-20): ", 0.0f, 20.0f);
        midSem[i] = readScoreInRange("Enter Mid-sem score (0-30): ", 0.0f, 30.0f);
        exam[i] = readScoreInRange("Enter Exam score (0-50): ", 0.0f, 50.0f);
    }

    *studentCount = count;
    cout << "\nRecords entered successfully.\n";
}

// Purpose: Convert a total score into letter grade.
// Parameters: total - total score out of 100.
// Return: Grade letter A, B, C, D, or F.
char assignGrade(float total) {
    if (total >= 80.0f) return 'A';
    if (total >= 70.0f) return 'B';
    if (total >= 60.0f) return 'C';
    if (total >= 50.0f) return 'D';
    return 'F';
}

// Purpose: Convert a grade to a remark string.
// Parameters: grade - letter grade.
// Return: Pass/Fail remark text.
string assignRemark(char grade) {
    if (grade == 'F') {
        return "Fail";
    }
    return "Pass";
}

// Purpose: Compute total, grade, and remark for all students.
// Parameters: quiz, midSem, exam - input score arrays; totals, grades, remarks - output arrays; studentCount - number of students.
// Return: None.
void computeGrades(const float* quiz, const float* midSem, const float* exam, float* totals, char* grades, string* remarks, int studentCount) {
    const float* quizPtr = quiz;
    const float* midPtr = midSem;
    const float* examPtr = exam;
    float* totalPtr = totals;

    for (int i = 0; i < studentCount; i++) {
        *totalPtr = *quizPtr + *midPtr + *examPtr;
        grades[i] = assignGrade(*totalPtr);
        remarks[i] = assignRemark(grades[i]);

        quizPtr++;
        midPtr++;
        examPtr++;
        totalPtr++;
    }
}

// Purpose: Print all student records in a table format.
// Parameters: names, ids, quiz, midSem, exam, totals, grades, remarks - parallel arrays; studentCount - number of students.
// Return: None.
void displayReport(const string* names, const int* ids, const float* quiz, const float* midSem, const float* exam, const float* totals, const char* grades, const string* remarks, int studentCount) {
    if (studentCount == 0) {
        cout << "No student records found. Please enter records first.\n";
        return;
    }

    cout << "\n==================== FULL CLASS REPORT ====================\n";
    cout << left
         << setw(4) << "No"
         << setw(20) << "Name"
         << setw(12) << "Student ID"
         << setw(8) << "Quiz"
         << setw(10) << "MidSem"
         << setw(8) << "Exam"
         << setw(8) << "Total"
         << setw(8) << "Grade"
         << setw(8) << "Remark" << "\n";

    cout << string(86, '-') << "\n";

    for (int i = 0; i < studentCount; i++) {
        cout << left
             << setw(4) << (i + 1)
             << setw(20) << names[i]
             << setw(12) << ids[i]
             << setw(8) << fixed << setprecision(1) << quiz[i]
             << setw(10) << midSem[i]
             << setw(8) << exam[i]
             << setw(8) << totals[i]
             << setw(8) << grades[i]
             << setw(8) << remarks[i] << "\n";
    }
}

// Purpose: Calculate highest, lowest, average, and pass/fail counts.
// Parameters: totals, grades - input arrays; studentCount - number of students; highest, lowest, average, passCount, failCount - outputs via pointers.
// Return: None.
void calculateStatistics(const float* totals, const char* grades, int studentCount,
                         float* highest, float* lowest, float* average,
                         int* passCount, int* failCount) {
    if (studentCount == 0) {
        *highest = 0.0f;
        *lowest = 0.0f;
        *average = 0.0f;
        *passCount = 0;
        *failCount = 0;
        return;
    }

    *highest = totals[0];
    *lowest = totals[0];
    float sum = 0.0f;
    *passCount = 0;
    *failCount = 0;

    for (int i = 0; i < studentCount; i++) {
        if (totals[i] > *highest) *highest = totals[i];
        if (totals[i] < *lowest) *lowest = totals[i];
        sum += totals[i];

        if (grades[i] == 'F') {
            (*failCount)++;
        } else {
            (*passCount)++;
        }
    }

    *average = sum / studentCount;
}

// Purpose: Display class-level statistics.
// Parameters: totals, grades - input arrays; studentCount - number of students.
// Return: None.
void displayStatistics(const float* totals, const char* grades, int studentCount) {
    if (studentCount == 0) {
        cout << "No student records found. Please enter records first.\n";
        return;
    }

    float highest, lowest, average;
    int passCount, failCount;

    calculateStatistics(totals, grades, studentCount, &highest, &lowest, &average, &passCount, &failCount);

    cout << "\n==================== CLASS STATISTICS ====================\n";
    cout << "Highest Total Score: " << fixed << setprecision(1) << highest << "\n";
    cout << "Lowest Total Score : " << fixed << setprecision(1) << lowest << "\n";
    cout << "Class Average      : " << fixed << setprecision(2) << average << "\n";
    cout << "Pass Count         : " << passCount << "\n";
    cout << "Fail Count         : " << failCount << "\n";
}

// Purpose: Find a student index by ID.
// Parameters: ids - ID array; studentCount - number of students; targetId - ID to search.
// Return: Index if found, otherwise -1.
int searchByID(const int* ids, int studentCount, int targetId) {
    for (int i = 0; i < studentCount; i++) {
        if (ids[i] == targetId) {
            return i;
        }
    }
    return -1;
}

// Purpose: Display one student's computed result by ID.
// Parameters: names, ids, quiz, midSem, exam, totals, grades, remarks - parallel arrays; studentCount - number of students.
// Return: None.
void displaySearchResult(const string* names, const int* ids, const float* quiz, const float* midSem, const float* exam,
                         const float* totals, const char* grades, const string* remarks, int studentCount) {
    if (studentCount == 0) {
        cout << "No student records found. Please enter records first.\n";
        return;
    }

    int idToFind = readIntInRange("Enter student ID to search: ", 1, 99999999);
    int index = searchByID(ids, studentCount, idToFind);

    if (index == -1) {
        cout << "Student with ID " << idToFind << " not found.\n";
        return;
    }

    cout << "\nStudent Found:\n";
    cout << "Name    : " << names[index] << "\n";
    cout << "ID      : " << ids[index] << "\n";
    cout << "Quiz    : " << fixed << setprecision(1) << quiz[index] << "\n";
    cout << "Mid-sem : " << midSem[index] << "\n";
    cout << "Exam    : " << exam[index] << "\n";
    cout << "Total   : " << totals[index] << "\n";
    cout << "Grade   : " << grades[index] << "\n";
    cout << "Remark  : " << remarks[index] << "\n";
}

// Purpose: Show menu and read user's choice.
// Parameters: None.
// Return: Valid menu choice 1-6.
int displayMenu() {
    cout << "\n========== STUDENT GRADE MANAGEMENT SYSTEM ==========\n";
    cout << "1. Enter Student Records\n";
    cout << "2. Compute and Assign Grades\n";
    cout << "3. Display Full Class Report\n";
    cout << "4. Display Class Statistics\n";
    cout << "5. Search Student by ID\n";
    cout << "6. Exit\n";

    return readIntInRange("Enter your choice (1-6): ", 1, 6);
}

int main() {
    string names[MAX_STUDENTS];
    int ids[MAX_STUDENTS];
    float quiz[MAX_STUDENTS] = {0.0f};
    float midSem[MAX_STUDENTS] = {0.0f};
    float exam[MAX_STUDENTS] = {0.0f};
    float totals[MAX_STUDENTS] = {0.0f};
    char grades[MAX_STUDENTS];
    string remarks[MAX_STUDENTS];

    int studentCount = 0;
    bool gradesComputed = false;

    for (int i = 0; i < MAX_STUDENTS; i++) {
        grades[i] = 'F';
    }

    while (true) {
        int choice = displayMenu();

        if (choice == 1) {
            inputStudents(names, ids, quiz, midSem, exam, &studentCount);
            gradesComputed = false;
        } else if (choice == 2) {
            if (studentCount == 0) {
                cout << "Please enter student records first.\n";
            } else {
                computeGrades(quiz, midSem, exam, totals, grades, remarks, studentCount);
                gradesComputed = true;
                cout << "Grades computed successfully.\n";
            }
        } else if (choice == 3) {
            if (!gradesComputed && studentCount > 0) {
                cout << "Please compute grades first (Option 2).\n";
            } else {
                displayReport(names, ids, quiz, midSem, exam, totals, grades, remarks, studentCount);
            }
        } else if (choice == 4) {
            if (!gradesComputed && studentCount > 0) {
                cout << "Please compute grades first (Option 2).\n";
            } else {
                displayStatistics(totals, grades, studentCount);
            }
        } else if (choice == 5) {
            if (!gradesComputed && studentCount > 0) {
                cout << "Please compute grades first (Option 2).\n";
            } else {
                displaySearchResult(names, ids, quiz, midSem, exam, totals, grades, remarks, studentCount);
            }
        } else if (choice == 6) {
            cout << "Exiting program. Goodbye!\n";
            break;
        }
    }

    return 0;
}
