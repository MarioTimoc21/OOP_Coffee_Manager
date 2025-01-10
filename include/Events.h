#ifndef EVENTS_H
#define EVENTS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Event{
    private:
        string name;
        string date;
        string type;
        double cost;

    public:
        Event(string name, string date, string type, double cost);

        string getName();
        string getDate();
        string getType();
        double getCost();

        void displayInfo();
};

void loadEvent(vector<Event>& events, string filename);
void saveEvent(vector<Event>& events, string filename);
void addEvent(vector<Event>& events, string filename);
void deleteEvent(vector<Event>& events, string filename);
void displayAllEvents(vector<Event>& events);
double calculateTotalCost(vector<Event>& events);

#endif // EVENTS_H