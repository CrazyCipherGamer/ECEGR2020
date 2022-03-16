#include <string>
#include <iostream>
#include <fstream>

class Student
{
    private:
        int ID;
        std::string firstName;
        std::string lastName;
        float GPA;
        class Student *next;
    public:
        Student(void);
        Student(const Student &student);
        Student(int ID, std::string firstName, std::string lastName, float GPA);
        ~Student(void);
        void setID(int ID);
        int getID(void);
        void setGPA(float GPA);
        float getGPA(void);
        void setFirstName(std::string firstName);
        std::string getFirstName(void);
        void setLastName(std::string lastName);
        std::string getLastName(void);
};

Student::Student()
{
    ID = 1688;
    firstName = (char *)malloc(30);
    lastName = (char *)malloc(30);
    firstName = "Bob";
    lastName = "Smith";
    GPA = 2.0f;
}

Student::Student(int ID, std::string firstName, std::string lastName, float GPA)
{
    this->ID = ID;
    this->firstName = firstName;
    this->lastName = lastName;
    this->GPA = GPA;
}

Student::Student(const Student &student)
{
    ID = student.ID;
    firstName = student.firstName;
    lastName = student.lastName;
    GPA = student.GPA;
}

Student::~Student()
{
    printf("Destructor called!\n");
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

void Student::setFirstName(std::string firstName)
{
    this->firstName = firstName;
}

std::string Student::getFirstName()
{
    return this->firstName;
}

void Student::setLastName(std::string lastName)
{
    this->lastName = lastName;
}

std::string Student::getLastName()
{
    return this->lastName;
}