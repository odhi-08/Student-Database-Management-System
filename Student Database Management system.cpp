#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;

const int MAX_STUDENTS=100;
string admin_password="#IUBAT";
void save();
void load();

class Student
{
    string name,dept;
    int attendance;
    int grade,blueMarks,redMarks,blackMarks;
public:
    int id;
    float totalScore;
    Student();
    void addStudent();
    void updateStudent();
    void deleteStudent(int dId);
    void sortStudent();
    void assignMark();
    void generateReport(int searchId);
    void display();
    void saveToFile(ofstream &file);
    void loadFromFile(string line);
};

Student students[MAX_STUDENTS];
int studentCount=0;

Student:: Student()
{
    name="";
    dept="";
    id=0;
    grade='0';
    attendance=0;
    totalScore = 0;
    blueMarks = 0;
    redMarks = 0;
    blackMarks = 0;
}
void Student ::addStudent()
{
    if (studentCount<MAX_STUDENTS)
    {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter department: ";
        cin >> dept;
        cout << "Enter Grade: ";
        cin >> grade;
        cout << "Enter Attendance: ";
        cin >> attendance;
        studentCount++;
        save();
    }
    else
    {
        cout << "Maximum student limit reached!" << endl;
    }
}
void Student :: updateStudent()
{
    int choice;
    cout << "\nUpdate Options:\n";
    cout << "1. Update Department\n";
    cout << "2. Update Grade\n";
    cout << "3. Update Attendance\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
        case 1:
            cout << "Enter updated department: ";
            cin >> dept;
            break;
        case 2:
            cout << "Enter updated grade: ";
            cin >> grade;
            break;
        case 3:
            cout << "Enter updated attendance: ";
            cin >> attendance;
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
    save();

}
void Student :: deleteStudent(int dId)
{
    for(int i=0;i<studentCount;i++)
    {
        if(students[i].id==dId)
        {
            for(int j=i;j<studentCount-1;j++)
            {
                students[j]=students[j+1];
            }
            studentCount--;
            save();
            return;
        }

    }
    cout << "Student with ID " << dId << " not found.\n";

}
void searchStudent()
{
            int studentIDToSearch;
            cout << "Enter the ID of the student to search: ";
            cin >> studentIDToSearch;

            for(int i = 0;i < studentCount;i++)
            {
                if(students[i].id == studentIDToSearch)
                {
                    students[i].display();
                    return;
                }
            }

            cout << "Student not found" << endl;
}

void Student:: assignMark()
{
        char mark;
        cout<< "Enter grade(B/R/K): ";
        cin>>mark;
        switch (mark)
        {
            case 'B':
                blueMarks++;
                totalScore -= 5;
                break;
            case 'R':
                redMarks++;
                totalScore -= 10;
                break;
            case 'K':
                blackMarks++;
                totalScore -= 15;
                if (blackMarks >= 3)
                {
                    cout << name << " has been marked as a Bad Student.\n";
                }
                break;
            default:
                cout << "Invalid mark.\n";
                break;
        }

        save();
    }
void Student :: sortStudent()
{
    if (studentCount == 0)
    {
        cout << "No students to sort." << endl;
        return;
    }
    for (int i = 0; i < studentCount; i++)
    {
        for (int j = i+1; j < studentCount; j++)
        {
            if (students[i].grade < students[j].grade)
            {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    cout << "Students sorted by Grade:\n";
    for (int i = 0; i < studentCount; i++)
    {
        cout << "ID: " << students[i].id
             << ", Name: " << students[i].name
             << ", Grade: " << students[i].grade<<endl;
    }
    save();
}
void Student :: display()
{
    cout << "\nStudent Details:" << endl;
    cout << "Name: " << name <<endl;
    cout << "ID: " << id <<endl;
    cout << "Department: " << dept << endl;
    cout << "Grade: " << grade << endl;
}

void Student::generateReport(int searchId) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == searchId) {
            cout << "\nGenerating Report for Student ID: " << searchId << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Attendance: " << students[i].attendance << " days" << endl;
            cout << "Red Marks: " << students[i].redMarks << endl;
            cout << "Blue Marks: " << students[i].blueMarks << endl;
            cout << "Black Marks: " << students[i].blackMarks << endl;
            return;
        }
    }
    cout << "Student with ID " << searchId << " not found." << endl;
}

void Student::saveToFile(ofstream file)
{
    file << name << " " << dept << " " << id << " " <<  grade << " " << attendance << " " << totalScore << " " << redMarks << " " << blueMarks << " " << blackMarks << '\n';
}

void Student::loadFromFile(string line)
{
    istringstream iss(line);
    iss >> name >> dept >> id >> grade >> attendance >> totalScore >> redMarks >> blueMarks >> blackMarks;
}

void save()
{
    ofstream file("students.txt");
    for(int i = 0;i < studentCount;i++)
    {
        students[i].saveToFile(file);
    }
    file.close();
}

void load()
{
    ifstream file("students.txt");
    string line;
    if(file.is_open())
    {
        while(getline(file, line))
        {
            students[studentCount].loadFromFile(line);
            studentCount++;
        }
        file.close();
    }
}


int display()
{
    int choice;
    cout<< "\t\t\t\t\t\t\t\tStudent Database Management System "<<endl;
    cout<< "\t\t\t\t\t\t\t-------------------------------------------------"<<endl;
    cout<< "\n\t1.Add Student"<<endl;
    cout<< "\t2.Update Student"<<endl;
    cout<< "\t3.Delete Student"<<endl;
    cout<< "\t4.Search Student"<<endl;
    cout<< "\t5.Sort Student"<<endl;
    cout<< "\t6.Assign Mark"<<endl;
    cout<< "\t7.Generate Report"<<endl;
    cout<< "\t8.Exit"<<endl;

    cout<< "\nEnter your choice : ";
    cin>>choice;

    return choice;
}
int main()
{
    string temp_password;
    cout<< "Enter password : ";
    cin>>temp_password;
    if(temp_password==admin_password)
    {
        load();
    }
    Student s[MAX_STUDENTS];

    while(true)
    {
    int choice = display();

    switch(choice)
    {
    case 1:
        {
            int numStudents;
            cout << "How many students do you want to add? ";
            cin >> numStudents;

            if(numStudents<=MAX_STUDENTS)
            {
                    for (int i = 0; i < numStudents; i++)
                    {
                        cout << "\nAdding student " << studentCount + 1 << ":\n";
                        students[studentCount].addStudent();
                    }
            }
            else
            {
                cout<< "Student limit reached!"<<endl;
            }
        }
          break;
        case 2:
            {
                int studentIdToUpdate;
                cout << "Enter the ID of the student to update: ";
                cin >> studentIdToUpdate;
                for (int i = 0; i < studentCount; i++)
                {
                    if (students[i].id == studentIdToUpdate)
                    {
                        students[i].updateStudent();
                        break;
                    }
               }
              }
           break;
        case 3:
            int studentIdToDelete;
            cout << "Enter the ID of the student to delete: ";
            cin >> studentIdToDelete;

            for (int i = 0; i < studentCount; i++)
                {
                    if (students[i].id == studentIdToDelete)
                    {
                        students[i].deleteStudent(studentIdToDelete);
                        cout << "Student deleted successfully!" << endl;
                        break;
                    }
               }

            break;

        case 4:
            int studentIDToSearch;
            cout << "Enter the ID of the student to search: ";
            cin >> studentIDToSearch;

            for(int i = 0;i < studentCount;i++)
            {
                if(students[i].id == studentIDToSearch)
                {
                    students[i].display();
                }
            }

            break;
        case 5:
            students[0].sortStudent();
            break;
        case 6:
            int SId;
                cout << "Enter the ID of the student to assign marks: ";
                cin >> SId;
                for (int i = 0; i < studentCount; i++) {
                    if (students[i].id == SId) {
                        students[i].assignMark();
                        cout << "Mark assigned successfully!" << endl;
                        break;
                    }
                }
                break;
         case 7:
            int sid;
            cout << "Enter the ID of the student to generate report: ";
            cin >> sid;
            for (int i = 0; i < studentCount; i++)
                {
                    if (students[i].id == sid)
                    {
                        students[i].generateReport(sid);
                        break;
                    }
                }
                break;
        case 8:
                cout << "Exiting the program..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;


    }
    }
    return 0;
}
