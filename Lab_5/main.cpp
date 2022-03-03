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
    public:
        Student(void);
        Student(const Student &student);
        Student(int ID, const char* firstName, const char* lastName, float GPA);
        ~Student(void);
        void setID(int ID);
        int getID(void);
        void setGPA(float GPA);
        float getGPA(void);
        void setFirstName(const char *firstName);
        char* getFirstName(void);
        void setLastName(const char *lastName);
        char* getLastName(void);
};

Student::Student()
{
    ID = 1688;
    firstName = (char *)malloc(30);
    lastName = (char *)malloc(30);
    strcpy(firstName, "Bob");
    strcpy(lastName, "Smith");
    GPA = 2.0f;
}

Student::Student(int ID, const char* firstName, const char* lastName, float GPA)
{
    this->ID = ID;
    this->firstName = (char*)malloc(30);
    this->lastName = (char*)malloc(30);
    strcpy(this->firstName, firstName);
    strcpy(this->lastName, lastName);
    this->GPA = GPA;
}

Student::Student(const Student &student)
{
    ID = student.ID;
    firstName = (char*)malloc(30);
    lastName = (char*)malloc(30);
    strcpy(firstName, student.firstName);
    strcpy(lastName, student.lastName);
    GPA = student.GPA;
}

Student::~Student()
{
    printf("Destructor called!\n");
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

void Student::setFirstName(const char* firstName)
{
    strcpy(this->firstName, firstName);
}

char* Student::getFirstName()
{
    return this->firstName;
}

void Student::setLastName(const char* lastName)
{
    strcpy(this->lastName, lastName);
}

char* Student::getLastName()
{
    return this->lastName;
}

int main()
{
    Student student1;                                       //Default Constructor
    Student student2(345, "Alexander", "Graham", 3.4566);   //Parametrized constructor
    Student student3(student2);                             //Copy Constructor

    //Test of Set-Get of ID
    printf("The ID of student1 is %d\n", student1.getID());
    //Setting ID to new number
    student1.setID(1500);
    //Printing new ID
    printf("The new ID of student1 is %d\n", student1.getID());

    //Test of Set-Get of GPA
    printf("The GPA of student2 is %f\n", student2.getGPA());
    //Setting new GPA
    student2.setGPA(3.984);
    //Printing new GPA
    printf("The new GPA of student2 is %f\n", student2.getGPA());

    //Test of Set-Get of first name. Also shows that the copy constructor works
    printf("The first name of student3 is %s\n", student3.getFirstName());
    //Setting new first name
    student3.setFirstName("Alex");
    //Printing new name
    printf("The new first name of student3 is %s\n", student3.getFirstName());

    //Test of Set-Get of last name. Also shows that the copy constructor works
    printf("The last name of student3 is %s\n", student3.getLastName());
    //Setting new last name
    student3.setLastName("Smith");
    //Printing new name
    printf("The new last name of student3 is %s\n", student3.getLastName());

    //Each function tested works as expected and this can be seen in the terminal window as the program runs.
    //I know that there are no memory leaks as when I step through thru the program and the return 0 is called,
    //the cursor goes back up to student3 and calls its deconstructor which does indeed free up the variables
    //as I can see the memory addresses there stop representing the name and instead gets a default system value.
    //This occurs for all the objects so I am quite sure of not causing any memory leaks.

    return 0;
}