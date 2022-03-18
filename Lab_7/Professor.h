#include "Employee.h"

enum Department{Unknown, Physics, Biology, Chemistry, Calculus, English};

class Professor: public Employee
{
    private:
        bool tenured;
        enum Department department;
    public:
        Professor() : Employee()
        {
            tenured = false;
            department = Unknown;
        }
        Professor(int ID, string first, string last, float salary, bool tenured, Department department) : Employee(ID, first, last, salary)
        {
            this->tenured = tenured;
            this->department = department;
        }
        Professor(const Professor &obj) : Employee( dynamic_cast<const Employee &>(obj))
        {
            tenured = obj.tenured;
            department = obj.department;
        }
        bool getTenured()
        {
            return tenured;
        }
        Department getDepartment()
        {
            return department;
        }

        void setDepartment(Department department)
        {
            this->department = department;
        }

        void setTenured(bool tenured)
        {
            this->tenured = tenured;
        }
};