#include "../include/Events.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

Event::Event(string name, string date, string type, double cost){
    this->name = name;
    this->date = date;
    this->type = type;
    this->cost = cost;
}

void Event::displayInfo(){
    cout << "Name: " << name << endl;
    cout << "Date: " << date << endl;
    cout << "Type: " << type << endl;
    cout << "Cost: " << cost << " RON\n";
}

string Event::getName(){
    return name;
}

string Event::getDate(){
    return date;
}

string Event::getType(){
    return type;
}

double Event::getCost(){
    return cost;
}

void loadEvent(vector<Event>& events, string filename){
    ifstream file(filename);
    if (!file.is_open()){
        cout << "Could not open the file: " << filename << endl;
        return;
    }

    string line, name, date, type;
    double cost;

    getline(file, line);
    while (getline(file, line)){
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, date, ',');
        getline(ss, type, ',');
        ss >> cost;

        events.emplace_back(name, date, type, cost);
    }

    file.close();
}

void saveEvent(vector<Event>& events, string filename){
    ofstream file(filename);
    if (!file.is_open()){
        cout << "Could not open the file: " << filename << endl;
        return;
    }

    file << "Name,Date,Type,Cost\n";
    for (auto& event : events){
        file << event.getName() << "," << event.getDate() << "," << event.getType() << "," << event.getCost() << endl;
    }

    file.close();
}

void addEvent(vector<Event>& events, string filename){
    string name, date, type;
    double cost;
    cout << "Enter the name of the event: ";
    getline(cin, name);

    cout << "Enter the date of the event: ";
    getline(cin, date);

    cout << "Enter the type of the event: ";
    getline(cin, type);

    cout << "Enter the cost of the event: ";
    cin >> cost;
    cin.ignore();

    events.emplace_back(name, date, type, cost);
    saveEvent(events, filename);

    cout << "Event added.\n";
}

void deleteEvent(vector<Event>& events, string filename){
    string name;
    cout << "Enter the name of the event you want to delete: ";
    getline(cin, name);

    auto it = find_if(events.begin(), events.end(), [&name](Event& event){
        return event.getName() == name;
    });

    if (it != events.end()){
        events.erase(it);
        saveEvent(events, filename);
        cout << "Event deleted.\n";
    } else {
        cout << "Event not found.\n";
    }
}

void displayAllEvents(vector<Event>& events){
    if (events.empty()){
        cout << "No events to display.\n";
        return;
    }

    for (auto& event : events){
        event.displayInfo();
        cout << "-------------------\n";
    }
}

double calculateTotalCost(vector<Event>& events){
    double total = 0;
    for (auto& event : events){
        total += event.getCost();
    }

    return total;
}

