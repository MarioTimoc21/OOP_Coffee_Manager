
#include "include/Menu.h"
#include "include/Template.h"
#include <iostream>

using namespace std;

int main() {

    printAnything<string>("\n == Welcome to the Coffee Shop Management System! == ");

    handleLocationMenu();

    return 0;
}