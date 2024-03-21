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

    