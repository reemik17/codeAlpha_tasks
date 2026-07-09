#include <iostream>
using namespace std;

int main() {
    cout << "WELCOME TO THE CGPA CALCULATOR PAGE" << endl;

    int numberOfCourses;

    cout << "Enter the number of courses: ";
    cin >> numberOfCourses;

    if (numberOfCourses <= 0) {
        cout << "Invalid number of courses." << endl;
        return 0;
    }

    float* grades = new float[numberOfCourses];
    float* credits = new float[numberOfCourses];

    float totalPoints = 0;
    float totalCredits = 0;

    // Input course details
    for (int i = 0; i < numberOfCourses; i++) {
        cout << "Course " << i + 1 << endl;

        // Keep asking until a valid grade is entered
        do {
            cout << "Enter Grade Points (0 - 4): ";
            cin >> grades[i];

            if (grades[i] < 0 || grades[i] > 4) {
                cout << "Invalid grade! Please enter a value between 0 and 4." << endl;
            }

        } while (grades[i] < 0 || grades[i] > 4);

        cout << "Enter Credit Hours: ";
        cin >> credits[i];

        // Validate credit hours
        if (credits[i] <= 0) {
            cout << "Invalid credit hours. Setting it to 1." << endl;
            credits[i] = 1;
        }

        totalPoints += grades[i] * credits[i];
        totalCredits += credits[i];
    }

    // Prevent division by zero
    if (totalCredits == 0) {
        cout << "Error: Total credits cannot be zero." << endl;
        delete[] grades;
        delete[] credits;
        return 0;
    }

    // GPA calculation
    float GPA = totalPoints / totalCredits;

    // Previous academic record
    float previousPoints = 0;
    float previousCredits = 0;

    cout << "Enter previous total grade points (0 if first semester): ";
    cin >> previousPoints;

    cout << "Enter previous total credits (0 if first semester): ";
    cin >> previousCredits;

    float CGPA;

    // CGPA calculation
    if (previousCredits == 0) {
        CGPA = GPA;
    }
    else {
        CGPA = (previousPoints + totalPoints) /
               (previousCredits + totalCredits);
    }

    // Display results
    cout << "========== RESULT ==========" << endl;
    cout << "Total Credits: " << totalCredits << endl;
    cout << "Total Grade Points: " << totalPoints << endl;
    cout << "Semester GPA: " << GPA << endl;
    cout << "Overall CGPA: " << CGPA << endl;

    cout << "==== INDIVIDUAL COURSES ====" << endl;

    for (int i = 0; i < numberOfCourses; i++) {
        cout << "Course " << i + 1
             << " | Grade: " << grades[i]
             << " | Credits: " << credits[i]
             << " | Grade Points: " << grades[i] * credits[i]
             << endl;
    }

    // Free memory
    delete[] grades;
    delete[] credits;

    return 0;
}
