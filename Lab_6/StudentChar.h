#include <string.h>
#include <stdlib.h>
#include <stdio.h>

class Student
{
    private:
        int ID;
        char *firstName;
        char *lastName;
        float GPA;
        Student *next;
    public:
        Student(void);
        Student(const Student &student);
        Student(int ID, char* firstName, char* lastName, float GPA);
        ~Student(void);
        void setID(int ID);
        int getID(void);
        void setGPA(float GPA);
        float getGPA(void);
        void setFirstName(char *firstName);
        char* getFirstName(void);
        void setLastName(char *lastName);
        char* getLastName(void);
        Student* getNext(void);
        void setNext(Student* next_student);
};

Student::Student()
{
    ID = 0;
    firstName = nullptr;
    lastName = nullptr;
    GPA = 0.0f;
    next = nullptr;
}

Student::Student(int ID,  char* firstName,  char* lastName, float GPA)
{
    this->ID = ID;
    this->firstName = (char*)malloc(strlen(firstName) + 1);
    this->lastName = (char*)malloc(strlen(lastName) + 1);
    strcpy(this->firstName, firstName);
    strcpy(this->lastName, lastName);
    this->GPA = GPA;
    next = nullptr;
}

Student::Student(const Student &student)
{
    ID = student.ID;
    setFirstName(student.firstName);
    setLastName(student.lastName);
    GPA = student.GPA;
    next = student.next;
}

Student::~Student()
{
    //printf("Destructor called!\n");
    free(firstName);
    free(lastName);
}

void Student::setID(int ID)
{
    this->ID = ID;
}

int Student::getID()
{
    return ID;
}

void Student::setGPA(float GPA)
{
    this->GPA = GPA;
}

float Student::getGPA()
{
    return GPA;
}

void Student::setFirstName( char* firstName)
{
    if(this->firstName == nullptr)
    {
        this->firstName = (char*)malloc(strlen(firstName) + 1);
        strcpy(this->firstName, firstName);
    }
    else
    {
        free(this->firstName);
        this->firstName = (char*)malloc(strlen(firstName) + 1);
        strcpy(this->firstName, firstName);
    }
}

char* Student::getFirstName()
{
    return this->firstName;
}

void Student::setLastName( char* lastName)
{
    if(this->lastName == nullptr)
    {
        this->lastName = (char*)malloc(strlen(lastName) + 1);
        strcpy(this->lastName, lastName);
    }
    else
    {
        free(this->lastName);
        this->lastName = (char*)malloc(strlen(lastName) + 1);
        strcpy(this->lastName, lastName);
    }
}

char* Student::getLastName()
{
    return this->lastName;
}

Student* Student::getNext(void)
{
    return this->next;
}

void Student::setNext(Student* next_student)
{
    next = next_student;
}