#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

struct Course {
    string name;
    float grade;
    int credit;
};

int main() {
    int numCourses;
    cout << "Enter number of courses: ";
    cin >> numCourses;

    vector<Course> courses(numCourses);
    float totalGradePoints = 0;
    int totalCredits = 0;

    for (int i = 0; i < numCourses; ++i) {
        cout << "\nCourse " << i + 1 << " name: ";
        cin >> ws; // clear newline
        getline(cin, courses[i].name);

        cout << "Grade (on 10.0 scale) for " << courses[i].name << ": ";
        cin >> courses[i].grade;

        cout << "Credit hours for " << courses[i].name << ": ";
        cin >> courses[i].credit;

        totalGradePoints += courses[i].grade * courses[i].credit;
        totalCredits += courses[i].credit;
    }

    cout << fixed << setprecision(2);
    cout << "\n---------------------------------------------\n";
    cout << "Course Summary:\n";

    for (const auto& course : courses) {
        cout << course.name << " | Grade: " << course.grade
             << " | Credits: " << course.credit << '\n';
    }

    float cgpa = totalGradePoints / totalCredits;
    cout << "---------------------------------------------\n";
    cout << "Total Credits: " << totalCredits << '\n';
    cout << "CGPA: " << cgpa << "\n";

    return 0;
}
