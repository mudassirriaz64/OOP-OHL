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

int main()
{
    for (auto& student : students)
    {
        loadEnrolledCourses(student);
    }
    loadCourses(courses);
    loadTeachers(teachers);
    loadStudents(students);


    int userType;

    // Main Menu Loop
    while (true)
    {
        system("cls");
        cout << "\nWelcome to the Course Management System!" << endl;
        cout << "1. Student Login" << endl;
        cout << "2. Teacher Login" << endl;
        cout << "3. Add Course" << endl;
        cout << "4. Remove Course" << endl;
        cout << "5. View Courses" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> userType;
        switch (userType)
        {
        case 1:
        {
            system("cls");
            string studentID;
            cout << "Enter your student ID: ";
            cin >> studentID;
            for (auto& student : students)
            {
                if (student.studentID == studentID)
                {
                    int studentChoice;
                    while (true)
                    {
                        system("cls");
                        cout << "Welcome " << student.name << "!" << endl;
                        cout << "1. Enroll in a course" << endl;
                        cout << "2. Drop a course" << endl;
                        cout << "3. View all courses" << endl;
                        cout << "4. View all enrolled courses" << endl;
                        cout << "5. Logout" << endl;
                        cout << "Enter your choice: ";
                        cin >> studentChoice;
                        switch (studentChoice)
                        {
                        case 1:
                        {
                            system("cls");
                            cout << "Available Courses:" << endl;
                            for (auto& course : courses)
                            {
                                cout << course.courseCode << " - " << course.courseName << endl;
                            }
                            string courseCode;
                            cout << "Enter the course code: ";
                            cin >> courseCode;
                            for (auto& course : courses)
                            {
                                if (course.courseCode == courseCode)
                                {
                                    student.enrollCourse(&course);
                                    break;
                                }
                            }
                            break;
                        }
                        case 2:
                        {
                            cout << "Enrolled Courses:" << endl;
                            for (auto& course : student.coursesEnrolled)
                            {
                                cout << course->courseCode << " - " << course->courseName << endl;
                            }
                            string courseCode;
                            cout << "Enter the course code: ";
                            cin >> courseCode;
                            for (auto& course : student.coursesEnrolled)
                            {
                                if (course->courseCode == courseCode)
                                {
                                    student.dropCourse(course);
                                    break;
                                }
                            }
                            break;
                        }
                        case 3:
                        {
                            system("cls");
                            cout << "Available Courses:" << endl;
                            for (auto& course : courses)
                            {
                                cout << course.courseCode << " - " << course.courseName << endl;
                            }
                            system("pause");
                            break;
                        }
                        case 4:
                        {
                            student.viewCourses();
                            break;
                        }
                        case 5:
                        {
                            saveEnrolledCourses(student);
                            return 0;
                        }
                        default:
                        {
                            cout << "Invalid choice. Please try again." << endl;
                            break;
                        }
                        }
                    }
                }
            }
        }
   