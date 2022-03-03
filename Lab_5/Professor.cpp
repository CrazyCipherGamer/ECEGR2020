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
    printf("Destructor called!\n");
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

int main()
{
    Professor professor1;                                       //Default Constructor
    Professor professor2(345, "Alexander", "Graham", 3456.6, true, HUMANITIES);   //Parametrized constructor
    Professor professor3(professor2);                             //Copy Constructor

    //Test of Set-Get of ID
    printf("The ID of professor1 is %d\n", professor1.getID());
    //Setting ID to new number
    professor1.setID(1500);
    //Printing new ID
    printf("The new ID of professor1 is %d\n", professor1.getID());

    //Test of Set-Get of salary
    printf("The salary of professor2 is %f\n", professor2.getSalary());
    //Setting new salary
    professor2.setSalary(398.4);
    //Printing new GPA
    printf("The new salary of professor2 is %f\n", professor2.getSalary());

    //Test of Set-Get of first name. Also shows that the copy constructor works
    printf("The first name of professor3 is %s\n", professor3.getFirstName());
    //Setting new first name
    professor3.setFirstName("Alex");
    //Printing new name
    printf("The new first name of professor3 is %s\n", professor3.getFirstName());

    //Test of Set-Get of last name. Also shows that the copy constructor works
    printf("The last name of professor3 is %s\n", professor3.getLastName());
    //Setting new last name
    professor3.setLastName("Smith");
    //Printing new name
    printf("The new last name of professor3 is %s\n", professor3.getLastName());

    //Test of Set-Get of tenured status
    printf("The tenured status of professor2 is %d\n", professor2.getTenured());
    //Setting new tenured status
    professor2.setTenured(false);
    //Printing new tenured status
    printf("The new tenured status of professor2 is %d\n", professor2.getTenured());

    //Test of Set-Get of department
    printf("The department of professor2 is %d\n", professor2.getDepartment());
    //Setting new deapartment
    professor2.setDepartment(SCIENCE);
    //Printing new tenured status
    printf("The new department of professor2 is %d\n", professor2.getDepartment());

    //Each function tested works as expected and this can be seen in the terminal window as the program runs.
    //I know that there are no memory leaks as when I step through thru the program and the return 0 is called,
    //the cursor goes back up to professor3 and calls its deconstructor which does indeed free up the variables
    //as I can see the memory addresses there stop representing the name and instead gets a default system value.
    //This occurs for all the objects so I am quite sure of not causing any memory leaks.

    return 0;
}