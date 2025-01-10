#include "../include/Employees.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Pentur template am folosit vectori de pointeri la clasa de baza Employee

Employee::Employee(string name, string position, string startH, string endH, double salary){
    this->name = name;
    this->position = position;
    this->startHour = startH;
    this->endHour = endH;
    this->salary = salary;
}

Employee::~Employee() {}

string Employee::getName(){
    return name;
}

string Employee::getPosition(){
    return position;
}

string Employee::getStartHour(){
    return startHour;
}

string Employee::getEndHour(){
    return endHour;
}

double Employee::getSalary(){
    return salary;
}

//Settere

void Employee::setstartHour(string startHour){
    this->startHour = startHour;
}

void Employee::setendHour(string endHour){
    this->endHour = endHour;
}

//Functii de afisare detalii

void Employee::displayInfo(){
    cout << "Name: " << name << endl;
    cout << "Position: " << position << endl;
    cout << "Shift: " << startHour << "-" << endHour << endl;
    cout << "Salary: " << salary << " RON" << endl;
}

Manager::Manager(string name, string startH, string endH, double salary) 
        : Employee(name, "Manager", startH, endH, salary) {}

// Suprascrierea metodei displayInfo
void Manager::displayInfo(){
    cout << "[Manager]";
    Employee::displayInfo();
}

Barista::Barista(string name, string startH, string endH, double salary) 
        : Employee(name, "Barista", startH, endH, salary) {}

void Barista::displayInfo(){
    cout << "[Barista]";
    Employee::displayInfo();
}

Waiter::Waiter(string name, string startH, string endH, double salary) 
        : Employee(name, "Waiter", startH, endH, salary) {}

void Waiter::displayInfo(){
    cout << "[Waiter]";
    Employee::displayInfo();
}

vector<Employee*> readEmployeesFromCSV(string filename){
    vector<Employee*> employees;
    ifstream file(filename);
    string line, name, position, start_shift, end_shift, salary_str;
    double salary;

    // Utilizare exceptii pentru a trata erorile
    if (!file.is_open()){
        throw runtime_error("Could not open the file: " + filename);
    }

    getline(file, line);

    while (getline(file, line)){
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, position, ',');
        getline(ss, start_shift, ',');
        getline(ss, end_shift, ',');
        getline(ss, salary_str, ',');
        salary = stod(salary_str);

        //cout << "Read line: " << name << ", " << position << ", " << start_shift << ", " << end_shift << ", " << salary << endl;

        if (position == "Manager"){
            employees.push_back(new Manager(name, start_shift, end_shift, salary));
        } else if (position == "Barista"){
            employees.push_back(new Barista(name, start_shift, end_shift, salary));
        } else if (position == "Waiter"){
            employees.push_back(new Waiter(name, start_shift, end_shift, salary));
        }
    }

    file.close();
    return employees;
}

void addEmployee(string filename, vector<Employee*>& employees, string name, string position, string startH, string endH, double salary){
    ifstream infile(filename);
    bool isEmpty = infile.peek() == ifstream::traits_type::eof();
    infile.close();

    ofstream file(filename, ios::app);

    if (file.is_open()){
        if (isEmpty) {
            file << "Name,Position,Start Hour,End Hour,Salary" << endl;
        }
        file << name << "," << position << "," << startH << "," << endH << "," << salary << endl;
        file.close();
    } else {
        cout << "Could not open the file: " << filename << endl;
        return;
    }

    //file << name << "," << position << "," << startH << "," << endH << "," << salary << endl;

    if (position == "Manager") {
        employees.push_back(new Manager(name, startH, endH, salary));
    } else if (position == "Barista") {
        employees.push_back(new Barista(name, startH, endH, salary));
    } else if (position == "Waiter") {
        employees.push_back(new Waiter(name, startH, endH, salary));
    } else {
        cout << "Invalid position: " << position << endl;
    }
}

bool deleteEmployees(string filename, vector<Employee*>& employees, string name){
    bool found = false;

    for (auto it = employees.begin(); it != employees.end(); ++it){
        if ((*it)->getName() == name){
            delete *it;
            employees.erase(it);
            cout << "Employee " << name << " deleted." << endl;
            found = true;
            break;
        }
    }

    ofstream file(filename);
    if (!file.is_open()){
        cout << "Could not open the file: " << filename << endl;
        return false;
    }

    file << "Name,Position,Start Shift,End Shift,Salary" << endl;
    for (const auto& emp : employees){
        file << emp->getName() << "," << emp->getPosition() << "," << emp->getStartHour() << "," << emp->getEndHour() << "," << emp->getSalary() << endl;
    }

    file.close();

    if (!found){
        cout << "Employee " << name << " not found." << endl;
    }

    return found;
}

bool editShift(string filename, vector<Employee*>& employees, string name, string startH, string endH) {
    bool updated = false;

    // Exception handling
    try {
        for (const auto& emp : employees) {
            if (emp->getName() == name) {
                emp->setstartHour(startH);
                emp->setendHour(endH);
                updated = true;
                break;
            }
        }

        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Could not open the file: " + filename);
        }

        file << "Name,Position,Start Shift,End Shift,Salary" << endl;
        for (const auto& emp : employees) {
            file << emp->getName() << "," << emp->getPosition() << "," << emp->getStartHour() << "," << emp->getEndHour() << "," << emp->getSalary() << endl;
        }

        file.close();

        if (!updated) {
            cout << "Employee " << name << " not found." << endl;
        } else {
            cout << "Shift updated for " << name << endl;
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return updated;
}