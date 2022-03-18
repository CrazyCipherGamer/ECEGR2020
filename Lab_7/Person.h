#pragma once
#include <string>

using namespace std;

class Person
{
    private:
        int ID;
        string firstName;
        string lastName;
        Person *next;
    
    public:
        Person()
        {
            ID = 0;
            firstName = "NULL";
            lastName = "NULL";
            next = nullptr;
        }

        Person(int ID, string firstName, string lastName)
        {
            this->ID = ID;
            this->firstName = firstName;
            this->lastName = lastName;
            this->next = nullptr;
        }

        Person(const Person &obj)
        {
            ID = obj.ID;
            firstName = obj.firstName;
            lastName = obj.lastName;
            next = obj.next;
        }

        virtual ~Person(){}

        //Get and set methods
        int getID()
        {
            return ID;
        }

        string getFirstName()
        {
            return firstName;
        }

        string getLastName()
        {
            return lastName;
        }

        Person* getNext()
        {
            return next;
        }

        void setID(int newID)
        {
            ID = newID;
        }

        void setFirstName(string newName)
        {
            firstName = newName;
        }

        void setLastName(string newName)
        {
            lastName = newName;
        }

        void setNext(Person* pNext)
        {
            next = pNext;
        }
};