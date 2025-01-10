#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include <string>
#include <vector>

using namespace std;

// Constructori si destructori (cam la toate clasele)
// Incapsularea prin variabile protected accesate prin gettere si settere
class Employee{
    protected:
        string name, position;
        string startHour, endHour;
        double salary;
    public:
        Employee(string name, string position, string startH, string endH, double salary);
        string getName();
        string getPosition();
        string getStartHour();
        string getEndHour();
        double getSalary();

        void setstartHour(string startHour);
        void setendHour(string endHour);

        //metoda virtuala pura pentru polimorfism
        virtual void displayInfo();
        virtual ~Employee();
};

// Mostenire prin clase derivate
// Polimorfismul este utilizat tot in clasele derivate prin suprascrierea metodei displayInfo
class Manager : public Employee{
    public:
        Manager(string name, string startH, string endH, double salary);
        void displayInfo() override;
};

class Barista : public Employee{
    public:
        Barista(string name, string startH, string endH, double salary);
        void displayInfo() override;
};

class Waiter : public Employee{
    public:
        Waiter(string name, string startH, string endH, double salary);
        void displayInfo() override;
};

vector<Employee*> readEmployeesFromCSV(string filename);
void addEmployee(string filename, vector<Employee*>& employees, string name, string position, string startH, string endH, double salary);
bool deleteEmployees(string filename, vector<Employee*>& employees, string name);
bool editShift(string filename, vector<Employee*>& employees, string name, string startH, string endH);

#endif // EMPLOYEES_H