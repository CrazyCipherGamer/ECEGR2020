#include <string.h>
#include <stdlib.h>
#include <stdio.h>

enum Department{ENGINEERING, HUMANITIES, SCIENCE};

class Professor
{
    private:
        int ID;
        char* firstName;
        char* lastName;
        float salary;
        bool tenured;
        Department department;
    public:
        Professor(void);
        Professor(const Professor &obj);
        Professor(int ID, const char* firstName, const char* lastName, float salary, bool tenured, Department department);
        ~Professor(void);
        void setID(int ID);
        int getID(void);
        void setFirstName(const char* firstName);
        char* getFirstName(void);
        void setLastName(const char* lastName);
        char* getLastName(void);
        void setSalary(float salary);
        float getSalary(void);
        void setTenured(bool tenured);
        bool getTenured(void);
        void setDepartment(Department department);
        Department getDepartment(void); 
};

Professor::Professor()
{
    ID = 1688;
    firstName = (char *)malloc(30);
    lastName = (char *)malloc(30);
    strcpy(firstName, "Bob");
    strcpy(lastName, "Smith");
    salary = 3000.0f;
    tenured = false;
    department = ENGINEERING;
}

Professor::Professor(int ID, const char* firstName, const char* lastName, float salary, bool tenured, Department department)
{
    this->ID = ID;
    this->firstName = (char*)malloc(30);
    this->lastName = (char*)malloc(30);
    strcpy(this->firstName, firstName);
    strcpy(this->lastName, lastName);
    this->salary = salary;
    this->tenured = tenured;
    this->department = department;
}

Professor::Professor(const Professor &obj)
{
    ID = obj.ID;
    firstName = (char*)malloc(30);
    lastName = (char*)malloc(30);
    strcpy(firstName, obj.firstName);
    strcpy(lastName, obj.lastName);
    salary = obj.salary;
    tenured = obj.tenured;
    department = obj.department;
}

Professor::~Professor()
{
    free(firstName);
    free(lastName);
}

void Professor::setID(int ID)
{
    this->ID = ID;
}

int Professor::getID()
{
    return ID;
}

void Professor::setFirstName(const char* firstName)
{
    strcpy(this->firstName, firstName);
}

char* Professor::getFirstName()
{
    return firstName;
}

void Professor::setLastName(const char* lastName)
{
    strcpy(this->lastName, lastName);
}

char* Professor::getLastName()
{
    return lastName;
}

void Professor::setSalary(float salary)
{
    this->salary = salary;
}

float Professor::getSalary()
{
    return salary;
}

void Professor::setTenured(bool tenured)
{
    this->tenured = tenured;
}

bool Professor::getTenured()
{
    return tenured;
}

void Professor::setDepartment(Department department)
{
    this->department = department;
}

Department Professor::getDepartment()
{
    return department;
}