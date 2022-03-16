#include "StudentString.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

Student* head = nullptr;

int numStudents;

void ImportStudentData(void);                                                               //Function to read and create the linked list
void SaveStudentData(void);                                                                 //Function that writes out all data in linked list to the originial file.
void LinkedMenu(void);                                                                       //Function to utilise the menu
//Student* NewStudent(int ID, char firstName[30], char lastName[30], float GPA);              //Function to allocate and get user input for a new student node.
void AddStudent(Student* studentNode);                                                      //Function to add student node to the linked list at the end
void RemoveByID(int ID);                                                                    //Function to remove a student by searching for their ID in the linked list.
void UpdateByID(int ID);                                                                    //Function to find student by ID to update.
void InsertByGPA(Student* insertedStudent);                                                 //Inserts student by GPA in descending order in linked list. This avoids us having to resort the list as we enter the student right where they need to be.
void PrintStudents(void);                                                                   //Prints all students in order of descending GPA as put in the linked list
void DeleteList(void);                                                                      //Ensures all elements of the linked list are freed individually.

int main(void)
{
    ImportStudentData();
    LinkedMenu();
    DeleteList();
    return 0;
}

void ImportStudentData(void)
{
    ifstream studentFile("output.txt", ios::in);
    if(!studentFile.is_open())
    {
        cerr << "Cannot open file" << endl;
        return;
    }
    studentFile.seekg(0);
    studentFile >> numStudents;

    
    for(int i = 0; i < numStudents; ++i)
    {   
        
        int ID;
        string firstName;
        string lastName;
        float GPA;

        studentFile >> ID;
        studentFile >> firstName;
        studentFile >> lastName;
        studentFile >> GPA;

        Student* fileStudent = new Student(ID, firstName, lastName, GPA);

        if(fileStudent != nullptr)
        {
            AddStudent(fileStudent);
        }
    }
    studentFile.close();
}

void SaveStudentData()
{
    ofstream myfile("output.txt");

    myfile.seekp(0);

    myfile << numStudents << endl;

    //Wow, much cool checking and declaration
    for( Student *currentStudent = head; currentStudent != nullptr; currentStudent = currentStudent->getNext())
    {
        myfile << currentStudent->getID() << endl << currentStudent->getFirstName() << endl << currentStudent->getLastName() << endl
        << currentStudent->getGPA() << endl;
    }

    myfile.close();
}

void LinkedMenu()
{
    int option = 0;
    while(option != 5)
    {
        printf("1) List all Students\n");
        printf("2) Add Student\n");              //Student is inserted into the linked list in descending order of GPA. This avoids a full sort of the linked list entirely.
        printf("3) Remove Student (by ID)\n");   //Assuming that we remove student by their unique ID, a reasonable and realistic assumption.
        printf("4) Update Student (by ID)\n");   //Again, by using a sensible approach of ID.
        printf("5) Save and Quit\n\n\n");

        scanf("%d", &option);

        int ID;
        string firstName, lastName;
        float GPA;

        switch (option)
        {
        case 1:{
            PrintStudents();
            break;
        }
        case 2:{
            printf("Enter ID of new student: ");
            scanf("%d", &ID);
            printf("Enter the first name of new student: ");
            cin >> firstName;
            printf("Enter the last name of new student: ");
            cin >> lastName;
            printf("Enter the GPA of new student: ");
            scanf("%f", &GPA);
            printf("\n\n");
            
            Student *insertStudent = new Student(ID, firstName, lastName, GPA);

            InsertByGPA(insertStudent);
            break;
        }
        case 3:{
            printf("Enter ID of student to remove: ");
            scanf("%d", &ID);
            RemoveByID(ID);
            break;
        }
        case 4:{
            printf("Enter ID of student to update: ");
            scanf("%d", &ID);
            UpdateByID(ID);
            break;
        }
        case 5:{
            SaveStudentData();
            DeleteList();
            break;
        }
        default:{
            cerr << "Invalid input!\n\n";
            break;
        }
        }
    }
    
}

//Deprecated as new Student does the same thing
// Student* NewStudent(int ID, char firstName[30], char lastName[30], float GPA)
// {
//     //Create Student class node
//     return new Student(ID, firstName, lastName, GPA);
// }

void AddStudent(Student* studentNode)
{
    Student* currentStudent = head;
    
    //If list is empty, then make the input student as the head node.
    if(head == nullptr)
    {
        head = studentNode;
        return;
    }

    //Traverse list until the end and add the studentNode there if list had stuff.
    while(currentStudent->getNext() != nullptr)
    {
        currentStudent = currentStudent->getNext();
    }
    currentStudent->setNext(studentNode);
}

void RemoveByID(int ID)
{
    Student *prevStudent = head;
    Student *currentStudent = nullptr;
    if(prevStudent == nullptr)
    {
        cerr << "Error! Linked list empty!\n\n";
        return;
    }
    currentStudent = prevStudent->getNext();

    if(currentStudent == nullptr && prevStudent->getID() == ID)
    {
        delete prevStudent;
        cout << "List Cleared!" << endl;
        numStudents--;
        return;
    }

    while(currentStudent != NULL)
    {
        //Case when the student to be removed is the first student
        if(prevStudent->getID() == ID)
        {
            head = prevStudent->getNext();
            delete prevStudent;
            numStudents--;
            break;
        }
        //Case when the student to be removed is in the middle
        else if(currentStudent->getID() == ID)
        {
            prevStudent->setNext(currentStudent->getNext());
            delete currentStudent;
            numStudents--;
            break;
        }
        //Case when the student to be removed is at the end
        if(currentStudent->getID() == ID && currentStudent->getNext() == NULL)
        {
            prevStudent->setNext(nullptr);
            delete currentStudent;
            numStudents--;
            break;
        }
        prevStudent = currentStudent;
        currentStudent = currentStudent->getNext();
    }
}

//We find the student in the list and then update their info, connect the linked list as it should be and then just put the Student * for that student into InsertByGPA to put them in correctly in the list to never worry about resorting the entire linked list.
void UpdateByID(int ID)
{
    Student *currentStudent = head;
    Student *nextStudent = nullptr;
    if(currentStudent == nullptr)
    {
        cerr << "List empty!" << endl;
        return;
    }
    nextStudent = currentStudent->getNext();

    while(nextStudent != nullptr)
    {
        //Case when the first student is the student we need to update
        if(currentStudent->getID() == ID)
        {
            string firstName, lastName;
            cout << "Enter new ID: ";
            int tempID;
            cin >> tempID;
            currentStudent->setID(tempID);
            cout << "Enter new first name: ";
            cin >> firstName;
            currentStudent->setFirstName(firstName);
            cout << "Enter new last name: ";
            cin >> lastName;
            currentStudent->setLastName(lastName);
            cout << "Enter new GPA: ";
            float tempGPA;
            cin >> tempGPA;
            currentStudent->setGPA(tempGPA);

            //Remove the student node temporarily while connecting the linked list back up.
            head = nextStudent;
            currentStudent->setNext(nullptr);

            //Reinsert the student node
            InsertByGPA(currentStudent);
            break;
        }
        //Case when the student to be updated is in the middle. Note: currentStudent and nextStudent now refer to prevStudent and currentStudent here to ensure that all pointers are connected correctly.
        else if(nextStudent->getID() == ID && nextStudent->getNext() != nullptr)
        {
            string firstName, lastName;

            cout << "Enter new ID: ";
            int tempID;
            cin >> tempID;
            nextStudent->setID(tempID);
            cout << "Enter new first name: ";
            cin >> firstName;
            nextStudent->setFirstName(firstName);
            cout << "Enter new last name: ";
            cin >> lastName;
            nextStudent->setLastName(lastName);
            cout << "Enter new GPA: ";
            float tempGPA;
            cin >> tempGPA;
            nextStudent->setGPA(tempGPA);

            //Remove the student node temporarily while connecting the linked list back up
            currentStudent->setNext(nextStudent->getNext());
            nextStudent->setNext(nullptr);

            //Reinsert the student node
            InsertByGPA(nextStudent);
            break;
        }
        //Case for student at the end
        if(nextStudent->getID() == ID && nextStudent->getNext() == NULL)
        {
            string firstName, lastName;
            cout << "Enter new ID: ";
            int tempID;
            cin >> tempID;
            nextStudent->setID(tempID);
            cout << "Enter new first name: ";
            cin >> firstName;
            nextStudent->setFirstName(firstName);
            cout << "Enter new last name: ";
            cin >> lastName;
            nextStudent->setLastName(lastName);
            cout << "Enter new GPA: ";
            float tempGPA;
            cin >> tempGPA;
            nextStudent->setGPA(tempGPA);

            //Momentary disconnect
            currentStudent->setNext(nullptr);

            //Reinsert
            InsertByGPA(nextStudent);
            break;
        }
        currentStudent = nextStudent;
        nextStudent = nextStudent->getNext();
    }
    //Error-correction
    numStudents--;
}


//This function adds the student node at the correct point in the linked list by comparing GPAs ahead and behind in a loop
//This check ensures that the student is entered at the correct spot to ensure GPA is in descending order
//This method totally avoids the need to resort as long as the original data read in from the external file was in descending order.
void InsertByGPA(Student* insertedStudent)
{
    Student *currentStudent = head;
    Student *nextStudent = NULL;
    if(currentStudent == NULL)
    {
        cerr << "Error! Linked list empty!\n\n";
        return;
    }
    nextStudent = currentStudent->getNext();

    while(nextStudent != nullptr)
    {
        //Insertion at the beginning
        if(currentStudent->getGPA() < insertedStudent->getGPA())
        {
            insertedStudent->setNext(currentStudent);
            head = insertedStudent;
            numStudents++;
            break;
        }
        //Insertion at the middle
        else if(currentStudent->getGPA() > insertedStudent->getGPA() && nextStudent->getGPA() < insertedStudent->getGPA())
        {
            currentStudent->setNext(insertedStudent);
            insertedStudent->setNext(nextStudent);
            numStudents++;
            break;
        }
        //Insertion at the end
        if(nextStudent->getGPA() > insertedStudent->getGPA())
        {
            nextStudent->setNext(insertedStudent);
            numStudents++;
            break;
        }
        currentStudent = nextStudent;
        nextStudent = nextStudent->getNext();
    }
}

void PrintStudents(void)
{
    Student *currentStudent = head;

    if(numStudents == 0)
    {
        cerr << "List is empty!\n";
        return;
    }

    for (int pos = 0; currentStudent != nullptr; ++pos)
    {
        string firstName = currentStudent->getFirstName();
        string lastName = currentStudent->getLastName();
        cout << "The ID of student " << pos + 1 <<  " is: " << currentStudent->getID() << '\n';
        cout << "The first name of student " << pos + 1 <<  " is: " << firstName << '\n';
        cout << "The last name of student " << pos + 1 <<  " is: " << lastName << '\n';
        cout << "The GPA of student " << pos + 1 <<  " is: " << currentStudent->getGPA() << '\n';
    
        if(currentStudent->getNext() != nullptr)
        {
            currentStudent = currentStudent->getNext();
            continue;
        }
        break;
    }
}

void DeleteList(void)
{
    Student *prev = head;
    //This loop essentially cycles the nodes backwards to free them from memory.
    while(head)
    {
        head = head->getNext();
        delete prev;
        prev = head;
    }
}