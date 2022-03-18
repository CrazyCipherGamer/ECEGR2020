#include "Person.h"
class Student: public Person
{
    private:
        float GPA;
    public:

        //Calls default parent constructor and also sets a default GPA
        Student() : Person()
        {
            GPA = 0.0f;
        }

        //Calls the parametrized parent constructor.
        Student(int ID, string firstName, string lastName, float GPA) : Person(ID, firstName, lastName)
        {
            this->GPA = GPA;
        }

        //Calls the parent copy constructor
        Student(const Student &obj) : Person( static_cast<const Person &>(obj) )
        {
            GPA = obj.GPA;
        }

        float getGPA()
        {
            return GPA;
        }

        void setGPA(float GPA)
        {
            this->GPA = GPA;
        }
};