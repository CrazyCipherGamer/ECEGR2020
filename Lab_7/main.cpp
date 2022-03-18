#include <iostream>
#include <fstream>
#include "Person.h"
#include "Student.h"
#include "Employee.h"
#include "Professor.h"

using namespace std;

//Enum to switch between the three types of people
enum Type{STUD, EMPL, PROF};

//Variable to store number of individuals in the list
int numOfPeople;

//Head pointer to the list
Person* head = nullptr;

void ImportData(void);                                                               //Function to read and create the linked list
void SaveData(void);                                                                 //Function that writes out all data in linked list to the originial file.
void LinkedMenu(void);                                                                       //Function to utilise the menu
template<class T> void AddNode(T* node);                                                      //Templated function to add a node to the linked list at the end
void RemoveByID(int ID);                                                                    //Function to remove a student by searching for their ID in the linked list.
void UpdateByID(int ID);                                                                    //Function to find student by ID to update.
void PrintList(void);                                                                   //Prints all students in order of descending GPA as put in the linked list
void DeleteList(void);

int main()
{
    ImportData();
    LinkedMenu();
    DeleteList();
}

void LinkedMenu(void)
{
    int option = 0;
    while(option != 5)
    {
        cout << "1) List\n" << "2) Add\n" << "3) Remove (by ID)\n" << "4) Update (by ID)\n" << "5) Save and Quit\n\n\n";
        cin >> option;

        switch(option)
        {
            case 1:
            {
                PrintList();
                break;
            }
            case 2:
            {
                int typeOfPerson;
                int ID;
                string first, last;
                cout << "What kind of person do you want to add? (0 for Student, 1 for Employee, 2 for Professor): ";
                cin >> typeOfPerson;
                
                while(typeOfPerson < 0 || typeOfPerson > 2)
                {
                    cout << "What kind of person do you want to add? (0 for Student, 1 for Employee, 2 for Professor): ";
                    cin >> typeOfPerson;
                }
                
                switch((Type)typeOfPerson)
                {                    
                    case STUD:
                    {
                        float GPA;

                        cout << "Enter ID of new student: ";
                        cin >> ID;
                        cout << "Enter first name of new student: ";
                        cin >> first;
                        cout << "Enter last name of new student: ";
                        cin >> last;
                        cout << "Enter the GPA of new student: ";
                        cin >> GPA;
                        cout << endl << endl;

                        Student* insertStudent = new Student(ID, first, last, GPA);

                        AddNode(insertStudent);
                        break;
                    }
                    case EMPL:
                    {
                        float salary;

                        cout << "Enter ID of new employee: ";
                        cin >> ID;
                        cout << "Enter first name of new employee: ";
                        cin >> first;
                        cout << "Enter last name of new employee: ";
                        cin >> last;
                        cout << "Enter salary of new employee: ";
                        cin >> salary;
                        cout << endl << endl;

                        Employee* insertEmployee = new Employee(ID, first, last, salary);

                        AddNode(insertEmployee);
                        break;
                    }
                    case PROF:
                    {
                        float salary;
                        bool tenured;
                        int department;

                        cout << "Enter ID of new professor: ";
                        cin >> ID;
                        cout << "Enter first name of new professor: ";
                        cin >> first;
                        cout << "Enter last name of new professor: ";
                        cin >> last;
                        cout << "Enter salary of new professor: ";
                        cin >> salary;
                        cout << "Enter tenured status of new professor (0 for no, 1 for yes): ";
                        cin >> tenured;
                        cout << "Enter department of new professor (1 = Physics, 2 = Biology, 3 = Chemistry, 4 = Calculus, 5 = English): ";
                        cin >> department;
                        cout << endl << endl;

                        Professor* insertProfessor = new Professor(ID, first, last, salary, tenured, (Department)department);

                        AddNode(insertProfessor);
                        break;
                    }
                    default:
                    {
                        cerr << "Invalid choice\n";
                        cout << "What kind of person do you want to add? (0 for Student, 1 for Employee, 2 for Professor): ";
                        cin >> typeOfPerson;
                        break;
                    }
                }
                
                break;
            }
            case 3:
            {
                int ID;
                cout << "Enter ID of person to remove: ";
                cin >> ID;
                RemoveByID(ID);
                break;
            }
            case 4:
            {
                int ID;
                cout << "Enter ID of person to update: ";
                cin >> ID;
                UpdateByID(ID);
                break;
            }
            case 5:
            {
                SaveData();
                DeleteList();
                break;
            }
            default:
            {
                cerr << "Invalid input!\n\n";
                break;
            }
        }
    }
}

void ImportData()
{
    ifstream directory("directory.txt");
    if(!directory.is_open())
    {
        cerr << "Cannot open file" << endl;
        return;
    }
    directory.seekg(0);
    directory >> numOfPeople;

    for(int i = 0; i < numOfPeople; ++i)
    {
        int temp;
        Type typeOfPerson;

        directory >> temp;
        typeOfPerson = (Type)temp;

        switch(typeOfPerson)
        {
            case STUD:{
                string first, last;
                int ID;
                float GPA;
                directory >> ID >> first >> last >> GPA;

                Student* tempStudent = new Student(ID, first, last, GPA);

                if(tempStudent != nullptr)
                {
                    AddNode(tempStudent);
                }
                break;
            }

            case EMPL:{
                string first, last;
                int ID;
                float salary;
                directory >> ID >> first >> last >> salary;

                Employee* tempEmployee = new Employee(ID, first, last, salary);

                if(tempEmployee != nullptr)
                {
                    AddNode(tempEmployee);
                }
                break;
            }

            case PROF:{
                string first, last;
                int ID;
                float salary;
                bool tenured;
                int tempDepartment;

                directory >> ID >> first >> last >> salary >> tenured >> tempDepartment;

                Professor* tempProfessor = new Professor(ID, first, last, salary, tenured, (Department)tempDepartment);

                if(tempProfessor != nullptr)
                {
                    AddNode(tempProfessor);
                }
                break;
            }
        }
    }
    directory.close();
}

void SaveData(void)
{
    ofstream myfile("directory.txt");

    myfile.seekp(0);

    myfile << numOfPeople << endl;

    for( Person *currentPerson = head; currentPerson != nullptr; currentPerson = currentPerson->getNext())
    {
        Student* tempStudent = dynamic_cast<Student*>(currentPerson);
        Professor* tempProffesor = dynamic_cast<Professor*>(currentPerson);
        Employee* tempEmployee = dynamic_cast<Employee*>(currentPerson);
        if(tempStudent != nullptr)
        {
            myfile << (int)STUD << endl;
            myfile << tempStudent->getID() << endl;
            myfile << tempStudent->getFirstName() << endl;
            myfile << tempStudent->getLastName() << endl;
            myfile << tempStudent->getGPA() << endl;
        }
        else if(tempProffesor != nullptr)
        {
            myfile << (int)PROF << endl;
            myfile << tempProffesor->getID() << endl;
            myfile << tempProffesor->getFirstName() << endl;
            myfile << tempProffesor->getLastName() << endl;
            myfile << tempProffesor->getSalary() << endl;
            myfile << (int)(tempProffesor->getTenured()) << endl;
            myfile << (int)(tempProffesor->getDepartment()) << endl;
        }
        else if(tempEmployee != nullptr)
        {
            myfile << (int)EMPL << endl;
            myfile << tempEmployee->getID() << endl;
            myfile << tempEmployee->getFirstName() << endl;
            myfile << tempEmployee->getLastName() << endl;
            myfile << tempEmployee->getSalary() << endl;
        }
        
    }

    myfile.close();
}

//Templated function that can add any derived class to the base class.
template<class T> void AddNode(T* node)
{
    Person* currentPerson = head;

    if(currentPerson == nullptr)
    {
        head = dynamic_cast<Person*>(node);
        return;
    }

    //Traverse list until the end and add the studentNode there if list had stuff.
    while(currentPerson->getNext() != nullptr)
    {
        currentPerson = currentPerson->getNext();
    }
    currentPerson->setNext(node);
}

void RemoveByID(int ID)
{
    Person *prevPerson = head;
    Person *currentPerson = nullptr;
    if(prevPerson == nullptr)
    {
        cerr << "Error! Linked list empty!\n\n";
        return;
    }
    currentPerson = prevPerson->getNext();

    if(currentPerson == nullptr && prevPerson->getID() == ID)
    {
        delete prevPerson;
        cout << "List Cleared!" << endl;
        numOfPeople--;
        return;
    }

    while(currentPerson != nullptr)
    {
        //Case when the person to be removed is the first person
        if(prevPerson->getID() == ID)
        {
            head = prevPerson->getNext();
            delete prevPerson;
            numOfPeople--;
            break;
        }
        //Case when the person to be removed is in the middle
        else if(currentPerson->getID() == ID)
        {
            prevPerson->setNext(currentPerson->getNext());
            delete currentPerson;
            numOfPeople--;
            break;
        }
        //Case when the person to be removed is at the end
        if(currentPerson->getID() == ID && currentPerson->getNext() == NULL)
        {
            prevPerson->setNext(nullptr);
            delete currentPerson;
            numOfPeople--;
            break;
        }
        prevPerson = currentPerson;
        currentPerson = currentPerson->getNext();
    }
}

void UpdateByID(int ID)
{
    Person *currentPerson = head;
    Person *nextPerson = nullptr;
    if(currentPerson == nullptr)
    {
        cerr << "List empty!" << endl;
        return;
    }
    nextPerson = currentPerson->getNext();

    while(nextPerson != nullptr)
    {
        //Case when the first person is the person we need to update
        if(currentPerson->getID() == ID)
        {
            Student* tempStudent = dynamic_cast<Student*>(currentPerson);
            Professor* tempProffesor = dynamic_cast<Professor*>(currentPerson);
            Employee* tempEmployee = dynamic_cast<Employee*>(currentPerson);
            string firstName, lastName;
            int tempID;
            cout << "Enter new ID: ";
            cin >> tempID;
            currentPerson->setID(tempID);
            cout << "Enter new first name: ";
            cin >> firstName;
            currentPerson->setFirstName(firstName);
            cout << "Enter new last name: ";
            cin >> lastName;
            currentPerson->setLastName(lastName);
            if(tempStudent != nullptr)
            {
                float tempGPA;
                cout << "Enter new GPA: ";
                cin >> tempGPA;
                tempStudent->setGPA(tempGPA);
            }
            else if(tempProffesor != nullptr)
            {
                float tempSalary;
                int tempTenured;
                int tempDepartment;

                cout << "Enter new salary: ";
                cin >> tempSalary;
                tempProffesor->setSalary(tempSalary);
                cout << "Enter tenured status (0 for no, 1 for yes): ";
                cin >> tempTenured;
                tempProffesor->setTenured(tempTenured);
                cout << "Enter department (1 = Physics, 2 = Biology, 3 = Chemistry, 4 = Calculus, 5 = English): ";
                cin >> tempDepartment;
                tempProffesor->setDepartment((Department)tempDepartment);
            }
            else if(tempEmployee != nullptr)
            {
                float tempSalary;
                cout << "Enter new salary: ";
                cin >> tempSalary;
                tempEmployee->setSalary(tempSalary);
            }

            break;
        }
        //Case when the student to be updated is in the middle. Note: currentStudent and nextStudent now refer to prevStudent and currentStudent here to ensure that all pointers are connected correctly.
        else if(nextPerson->getID() == ID && nextPerson->getNext() != nullptr)
        {
            string firstName, lastName;
            int tempID;
            Student* tempStudent = dynamic_cast<Student*>(nextPerson);
            Professor* tempProffesor = dynamic_cast<Professor*>(nextPerson);
            Employee* tempEmployee = dynamic_cast<Employee*>(nextPerson);

            cout << "Enter new ID: ";
            cin >> tempID;
            nextPerson->setID(tempID);
            cout << "Enter new first name: ";
            cin >> firstName;
            nextPerson->setFirstName(firstName);
            cout << "Enter new last name: ";
            cin >> lastName;
            nextPerson->setLastName(lastName);

            if(tempStudent != nullptr)
            {
                float tempGPA;
                cout << "Enter new GPA: ";
                cin >> tempGPA;
                tempStudent->setGPA(tempGPA);
            }

            else if(tempProffesor != nullptr)
            {
                float tempSalary;
                int tempTenured;
                int tempDepartment;

                cout << "Enter new salary: ";
                cin >> tempSalary;
                tempProffesor->setSalary(tempSalary);
                cout << "Enter tenured status (0 for no, 1 for yes): ";
                cin >> tempTenured;
                tempProffesor->setTenured(tempTenured);
                cout << "Enter department (1 = Physics, 2 = Biology, 3 = Chemistry, 4 = Calculus, 5 = English): ";
                cin >> tempDepartment;
                tempProffesor->setDepartment((Department)tempDepartment);
            }

            else if(tempEmployee != nullptr)
            {
                float tempSalary;
                cout << "Enter new salary: ";
                cin >> tempSalary;
                tempEmployee->setSalary(tempSalary);
            }
            

            break;
        }
        //Case for person at the end
        if(nextPerson->getID() == ID && nextPerson->getNext() == NULL)
        {
            string firstName, lastName;
            int tempID;
            Student* tempStudent = dynamic_cast<Student*>(nextPerson);
            Professor* tempProffesor = dynamic_cast<Professor*>(nextPerson);
            Employee* tempEmployee = dynamic_cast<Employee*>(nextPerson);

            cout << "Enter new ID: ";
            cin >> tempID;
            nextPerson->setID(tempID);
            cout << "Enter new first name: ";
            cin >> firstName;
            nextPerson->setFirstName(firstName);
            cout << "Enter new last name: ";
            cin >> lastName;
            nextPerson->setLastName(lastName);

            if(tempStudent != nullptr)
            {
                float tempGPA;
                cout << "Enter new GPA: ";
                cin >> tempGPA;
                tempStudent->setGPA(tempGPA);
            }

            else if(tempProffesor != nullptr)
            {
                float tempSalary;
                int tempTenured;
                int tempDepartment;

                cout << "Enter new salary: ";
                cin >> tempSalary;
                tempProffesor->setSalary(tempSalary);
                cout << "Enter tenured status (0 for no, 1 for yes): ";
                cin >> tempTenured;
                tempProffesor->setTenured(tempTenured);
                cout << "Enter department (1 = Physics, 2 = Biology, 3 = Chemistry, 4 = Calculus, 5 = English): ";
                cin >> tempDepartment;
                tempProffesor->setDepartment((Department)tempDepartment);
            }

            else if(tempEmployee != nullptr)
            {
                float tempSalary;
                cout << "Enter new salary: ";
                cin >> tempSalary;
                tempEmployee->setSalary(tempSalary);
            }
            

            break;
        }
        currentPerson = nextPerson;
        nextPerson = nextPerson->getNext();
    }
}

void PrintList(void)
{
    Person *currentPerson = head;

    if(numOfPeople == 0)
    {
        cerr << "List is empty!\n";
        return;
    }

    for (int pos = 0; currentPerson != nullptr; ++pos)
    {
        Student* tempStudent = dynamic_cast<Student*>(currentPerson);
        Professor* tempProffesor = dynamic_cast<Professor*>(currentPerson);
        Employee* tempEmployee = dynamic_cast<Employee*>(currentPerson);
        
        if(tempStudent != nullptr)
        {
            cout << "Student" << endl;
            cout << "ID: " << tempStudent->getID() << endl;
            cout << "First name: " << tempStudent->getFirstName() << endl;
            cout << "Last name: " << tempStudent->getLastName() << endl;
            cout << "GPA: " << tempStudent->getGPA() << endl << endl;
        }
        else if(tempProffesor != nullptr)
        {
            cout << "Professor" << endl;
            cout << "ID: " << tempProffesor->getID() << endl;
            cout << "First name: " << tempProffesor->getFirstName() << endl;
            cout << "Last name: " << tempProffesor->getLastName() << endl;
            cout << "Salary: " << tempProffesor->getSalary() << endl;
            if(tempProffesor->getTenured())
            {
                cout << "Tenured: YES" << endl;
            }
            else
            {
                cout << "Tenured: NO" << endl;
            }
            switch(tempProffesor->getDepartment())
            {
                case Physics:
                {
                    cout << "Department: Physics" << endl << endl;
                    break;
                }
                case Biology:
                {
                    cout << "Department: Biology" << endl << endl;
                    break;
                }
                case Chemistry:
                {
                    cout << "Department: Chemistry" << endl << endl;
                    break;
                }
                case Calculus:
                {
                    cout << "Department: Calculus" << endl << endl;
                    break;
                }
                case English:
                {
                    cout << "Department: English" << endl << endl;
                    break;
                }
                default:
                {
                    cout << "Department: Unknown" << endl << endl;
                    break;
                }
            }
        }
        else if(tempEmployee != nullptr)
        {
            cout << "Employee" << endl;
            cout << "ID: " << tempEmployee->getID() << endl;
            cout << "First name: " << tempEmployee->getFirstName() << endl;
            cout << "Last name: " << tempEmployee->getLastName() << endl;
            cout << "Salary: " << tempEmployee->getSalary() << endl << endl;
        }
    
        if(currentPerson->getNext() != nullptr)
        {
            currentPerson = currentPerson->getNext();
            continue;
        }
        break;
    }
}

void DeleteList(void)
{
    Person *prev = head;
    //This loop essentially cycles the nodes backwards to free them from memory.
    while(head)
    {
        head = head->getNext();
        delete prev;
        prev = head;
    }
}