#ifndef MENU_H
#define MENU_H

#include "Employees.h"
#include <vector>
#include <string>

using namespace std;

void displayMenu();
int readInteger(string prompt);
string readInput(string prompt);
void handleMenu(string locationPrefix, string location);
void handleLocationMenu();

#endif // MENU_H