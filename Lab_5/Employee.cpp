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
    printf("Destructor called!\n");
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

int main()
{
    Employee employee1;                                       //Default Constructor
    Employee employee2(345, "Alexander", "Graham", 3.4566);   //Parametrized constructor
    Employee employee3(employee2);                             //Copy Constructor

    //Test of Set-Get of ID
    printf("The ID of employee1 is %d\n", employee1.getID());
    //Setting ID to new number
    employee1.setID(1500);
    //Printing new ID
    printf("The new ID of employee1 is %d\n", employee1.getID());

    //Test of Set-Get of salary
    printf("The salary of employee2 is %f\n", employee2.getSalary());
    //Setting new salary
    employee2.setSalary(398.4);
    //Printing new salary
    printf("The new salary of employee2 is %f\n", employee2.getSalary());

    //Test of Set-Get of first name. Also shows that the copy constructor works
    printf("The first name of employee3 is %s\n", employee3.getFirstName());
    //Setting new first name
    employee3.setFirstName("Alex");
    //Printing new name
    printf("The new first name of employee3 is %s\n", employee3.getFirstName());

    //Test of Set-Get of last name. Also shows that the copy constructor works
    printf("The last name of employee3 is %s\n", employee3.getLastName());
    //Setting new last name
    employee3.setLastName("Smith");
    //Printing new name
    printf("The new last name of employee3 is %s\n", employee3.getLastName());

    //Each function tested works as expected and this can be seen in the terminal window as the program runs.
    //I know that there are no memory leaks as when I step through thru the program and the return 0 is called,
    //the cursor goes back up to employee3 and calls its deconstructor which does indeed free up the variables
    //as I can see the memory addresses there stop representing the name and instead gets a default system value.
    //This occurs for all the objects so I am quite sure of not causing any memory leaks.

    return 0;
}