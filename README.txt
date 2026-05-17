CS101 Student Grade Management System (C++)
1. This project is a beginner-friendly console application in one source file: main.cpp.
2. It stores up to 30 students using parallel arrays (no vector/list/map).
3. Open a terminal in the project folder.
4. Compile with: g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o grade_system
5. Run with: ./grade_system
6. Choose menu option 1 to enter student records (name, ID, Quiz, Mid-sem, Exam).
7. Scores are validated with these limits: Quiz 0-20, Mid-sem 0-30, Exam 0-50.
8. Choose option 2 to compute total score, grade, and pass/fail remark.
9. Option 3 shows the full class report in table form.
10. Option 4 shows class statistics (highest, lowest, average, pass count, fail count).
11. Option 5 searches and displays one student by ID.
12. Option 6 exits the application.
13. Limitation: Student IDs are not forced to be unique in this simple version.
14. Limitation: Data is kept in memory only and is lost when the program closes.
