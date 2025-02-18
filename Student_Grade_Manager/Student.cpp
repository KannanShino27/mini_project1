#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Student
{
private:
    string name;
    double score1, score2, score3;
    double average;
    char grade;

public:
    Student(string n, double s1, double s2, double s3)
    {
        name = n;
        score1 = s1;
        score2 = s2;
        score3 = s3;
        average = (score1 + score2 + score3) / 3;
        calculateGrade();
    }

    void calculateGrade()
    {
        if (average >= 90)
        {
            grade = 'A';
        }
        else if (average >= 80)
        {
            grade = 'B';
        }
        else if (average >= 70)
        {
            grade = 'C';
        }
        else if (average >= 60)
        {
            grade = 'D';
        }
        else
        {
            grade = 'F';
        }
    }

    void display() const
    {
        cout << "Name: " << name << endl;
        cout << "Scores: " << score1 << ", " << score2 << ", " << score3 << endl;
        cout << "Average: " << average << endl;
        cout << "Grade: " << grade << "\n\n";
    }

    void writeToFile(ofstream &outfile) const
    {
        outfile << name << " " << score1 << " " << score2 << " " << score3 << "\n";
    }

    const string& getName() const
    {
        return name;
    }
};

void readFromFile(const string &filename, vector<Student> &students)
{
    ifstream infile(filename);
    if (!infile)
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string name;
    double score1, score2, score3;

    while (infile >> name >> score1 >> score2 >> score3)
    {
        students.push_back(Student(name, score1, score2, score3));
    }

    infile.close();
}

void writeToFile(const string &filename, const vector<Student> &students)
{
    ofstream outfile(filename, ios::app);
    if (!outfile)
    {
        cerr << "Error occurs when the file is opened: " << filename << endl;
        return;
    }

    for (const auto &student : students)
    {
        student.writeToFile(outfile);
    }

    outfile.close();
}

void searchStudent(const vector<Student> &students, const string &searchName)
{
    for (const auto &student : students)
    {
        if (student.getName() == searchName)
        {
            student.display();
            return;
        }
    }
    cout << "Student not found." << endl;
}

void addStudent(vector<Student> &students)
{
    string name;
    double score1, score2, score3;

    cout << "Enter the name of the new student: ";
    cin >> name;

     for (const auto &student : students)
        {
        if (student.getName() == name)
            {
            cout << "This student already exists. Please enter a different name.\n";
            return;
            }
        }

    cout << "Enter scores for " << name<<"\n";
    cin>> score1 >> score2 >> score3;
    if(score1>100 || score2>100 || score3>100)
    {
         cout << "Scores cannot be greater than 100. Please enter valid scores.\n";
        return;
    }


    students.push_back(Student(name, score1, score2, score3));
    cout << "Student added successfully.\n";
}

int main()
{
    vector<Student> students;

    readFromFile("students.txt", students);

    while (true)
    {
        cout << "Options:" << endl;
        cout << "1. Display all students" << endl;
        cout << "2. Search for a student" << endl;
        cout << "3. Add a new student" << endl;
        cout << "4. Exit" << endl;

        int choice;
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            for (const auto &student : students)
            {
                student.display();
            }
            break;
        case 2:
        {
            string searchName;
            cout << "Enter the name of the student to search: ";
            cin >> searchName;
            searchStudent(students, searchName);
        }
        break;
        case 3:
            addStudent(students);
            break;
        case 4:
            writeToFile("updated_students.txt", students);
            return 0;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
        }
    }

    return 0;
}