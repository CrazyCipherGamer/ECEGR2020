#pragma once
#include <string>
#include "Person.h"

using namespace std;

class Employee: public Person
{
    private:
        float salary;
    public:

        Employee() : Person()
        {
            salary = 0.0f;
        }

        Employee(int ID, string firstName, string lastName, float salary) : Person(ID, firstName, lastName)
        {
            this->salary = salary;
        }

        Employee(const Employee &obj) : Person( static_cast<const Person &>(obj))
        {
            salary = obj.salary;
        }

        float getSalary()
        {
            return salary;
        }
        
        void setSalary(float salary)
        {
            this->salary = salary;
        }

};