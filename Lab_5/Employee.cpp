#include <string.h>
#include <stdlib.h>
#include <stdio.h>

class Employee
{
    private:
        int ID;
        char* firstName;
        char* lastName;
        float salary;
    public:
        Employee(void);
        Employee(const Employee &obj);
        Employee(int ID, const char* firstName, const char* lastName, float salary);
        ~Employee(void);
        void setID(int ID);
        int getID(void);
        void setFirstName(const char* firstName);
        char* getFirstName(void);
        void setLastName(const char* lastName);
        char* getLastName(void);
        void setSalary(float salary);
        float getSalary(void);
};

Employee::Employee()
{
    ID = 1688;
    firstName = (char *)malloc(30);
    lastName = (char *)malloc(30);
    strcpy(firstName, "Bob");
    strcpy(lastName, "Smith");
    salary = 3000.0f;
}

Employee::Employee(int ID, const char* firstName, const char* lastName, float salary)
{
    this->ID = ID;
    this->firstName = (char*)malloc(30);
    this->lastName = (char*)malloc(30);
    strcpy(this->firstName, firstName);
    strcpy(this->lastName, lastName);
    this->salary = salary;
}

Employee::Employee(const Employee &obj)
{
    ID = obj.ID;
    firstName = (char*)malloc(30);
    lastName = (char*)malloc(30);
    strcpy(firstName, obj.firstName);
    strcpy(lastName, obj.lastName);
    salary = obj.salary;
}

Employee::~Employee()
{
    free(firstName);
    free(lastName);
}

void Employee::setID(int ID)
{
    this->ID = ID;
}

int Employee::getID()
{
    return ID;
}

void Employee::setFirstName(const char* firstName)
{
    strcpy(this->firstName, firstName);
}

char* Employee::getFirstName()
{
    return firstName;
}

void Employee::setLastName(const char* lastName)
{
    strcpy(this->lastName, lastName);
}

char* Employee::getLastName()
{
    return lastName;
}

void Employee::setSalary(float salary)
{
    this->salary = salary;
}

float Employee::getSalary()
{
    return salary;
}