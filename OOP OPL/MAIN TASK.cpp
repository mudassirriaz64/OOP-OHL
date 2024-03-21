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
class Student {
public:
    string studentID;
    string name;
    string email;
    string enrolledcourses;
    vector<Course*> coursesEnrolled;

    void enrollCourse(Course* course) {
        if (course->studentsEnrolled.size() < MAX_CAPACITY) {
            coursesEnrolled.push_back(course);
            course->addStudent(this);
        }
        else {
            cout << "Course " << course->courseName << " is full. Cannot enroll." << endl;
        }
    }

    void dropCourse(Course* course) {
        for (auto it = coursesEnrolled.begin(); it != coursesEnrolled.end(); ++it) {
            if (*it == course) {
                coursesEnrolled.erase(it);
                course->removeStudent(this);
                break;
            }
        }
    }

    void viewCourses()
    {
        cout << "Courses Enrolled by " << name << " (" << studentID << "):" << endl;
        if (coursesEnrolled.empty())
        {
            cout << "No courses enrolled." << endl;
        }
        else {
            for (auto course : coursesEnrolled) {
                cout << course->courseName << endl;
            }
        }
        system("pause");
    }

};

void Course::addStudent(Student* student)
{
    studentsEnrolled.push_back(student);
}

void Course::removeStudent(Student* student)
{
    for (auto it = studentsEnrolled.begin(); it != studentsEnrolled.end(); ++it) {
        if (*it == student) {
            studentsEnrolled.erase(it);
            break;
        }
    }
}
void Course::viewStudents()
{
    cout << "Students Enrolled in " << courseName << " (" << courseCode << "):" << endl;
    for (const Student* student : studentsEnrolled)
    {
        cout << student->name << endl;
    }
}

// Function prototypes
void saveAssignedCourses(const Teacher& teacher);
void loadAssignedCourses(Teacher& teacher, const string& assignedCoursesFile);
void loadEnrolledCourses(Student& student);
void saveEnrolledCourses(const Student& student);
void loadCourses(vector<Course>& courses);
void loadTeachers(vector<Teacher>& teachers);
void loadStudents(vector<Student>& students);
void saveData(const vector<Course>& courses, const vector<Teacher>& teachers, const vector<Student>& students);

const string COURSES_FILE = "courses.txt";
const string TEACHERS_FILE = "teachers.txt";
const string STUDENTS_FILE = "students.txt";// Maximum capacity for each course
   