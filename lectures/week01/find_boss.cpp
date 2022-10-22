#include <string.h>

struct Employee
{
    char name[100];
    double salary;
    Employee* boss;

    Employee(char* name, double salary, Employee* boss)
    {
        strcpy(this->name, name);
        this->salary = salary;
        this->boss = boss;
    }
};

Employee* findBoss(Employee* e)
{
    if (e->boss == nullptr)
    {
        return e;
    }
    return findBoss(e->boss);
}

Employee* findBoss2(Employee* e)
{
    while (e->boss != nullptr)
    {
        e = e->boss;
    }
    return e;
}

int main()
{
    // Employee* e = new Employee;
    Employee ivan("Ivan", 200, new Employee("Petar", 500, nullptr));
    Employee stoyan("Stoyan", 100, &ivan);
}