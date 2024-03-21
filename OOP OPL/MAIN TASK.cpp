#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>


using namespace std;

const int MAX_CAPACITY = 30;

// Forward declaration
class Teacher;
class Course;
class Student;


class Course
{
public:
    string courseCode;
    string courseName;
    Teacher* teacher;
    vector<Student*> studentsEnrolled;

    void addStudent(Student* student);
    void removeStudent(Student* student);
    void viewStudents();
};


// Global variables
vector<Course> courses;
vector<Student> students;
vector<Teacher> teachers;

// Class declarations
class Teacher {
public:
    string teacherID;
    string name;
    string email;
    vector<Course*> coursesTaught;

    void assignCourse(Course* course)
    {
        coursesTaught.push_back(course);
    }

    void removeCourse(Course* course) {
        for (auto it = coursesTaught.begin(); it != coursesTaught.end(); ++it) {
            if (*it == course) {
                coursesTaught.erase(it);
                break;
            }
        }
    }
    void viewCourses()
    {
        cout << "Courses Taught by " << name << " (" << teacherID << "):" << endl;
        for (auto course : coursesTaught) {
            cout << course->courseName << endl;
        }
        system("pause");
    }

    // Method to assign a course to this teacher
    void assignCourseToTeacher() {
        cout << "Available Courses:" << endl;
        for (auto& course : courses) {
            cout << course.courseCode << " - " << course.courseName << endl;
        }
        string courseCode;
        cout << "Enter the course code to assign: ";
        cin >> courseCode;
        Course* course = nullptr;
        for (auto& crs : courses) {
            if (crs.courseCode == courseCode) {
                course = &crs;
                break;
            }
        }
        if (course) {
            assignCourse(course);
            cout << "Course assigned successfully." << endl;
        }
        else {
            cout << "Course not found." << endl;
        }
    }

    // Method to remove a course assigned to this teacher
    void removeCourseFromTeacher() {
        cout << "Courses Taught by " << name << ":" << endl;
        for (auto& course : coursesTaught) {
            cout << course->courseCode << " - " << course->courseName << endl;
        }
        string courseCode;
        cout << "Enter the course code to remove: ";
        cin >> courseCode;
        Course* courseToRemove = nullptr;
        for (auto& course : coursesTaught) {
            if (course->courseCode == courseCode) {
                courseToRemove = course;
                break;
            }
        }
        if (courseToRemove) {
            removeCourse(courseToRemove);
            cout << "Course removed successfully." << endl;
        }
        else {
            cout << "Course not found in the courses taught by " << name << "." << endl;
        }
    }
};
   