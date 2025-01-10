#include "../include/Menu.h"
#include "../include/Employees.h"
#include "../include/Stock.h"
#include "../include/Product.h"
#include "../include/Orders.h"
#include "../include/Events.h"
#include "../include/Reports.h"
#include <iostream>
#include <limits>

using namespace std;

void handleEmployeeMenu(string csvFilename);
void handleStockMenu(string filename);
void handleOrderMenu(string filename, string stockFilename);
void handleEventMenu(string locationPrefix);

void displayLocationMenu(){
    cout << "\n  ~~ Select Location ~~\n";
    cout << "====================\n";
    cout << "1. Bucharest\n";
    cout << "2. Cluj-Napoca\n";
    cout << "3. Timisoara\n";
    cout << "4. Iasi\n";
    cout << "5. Brasov\n";
    cout << "6. Exit\n";
    cout << "====================\n";
}

string getLocationFilenamePrefix(int locationOption) {
    switch (locationOption) {
        case 1: return "Bucharest";
        case 2: return "Cluj";
        case 3: return "Timisoara";
        case 4: return "Iasi";
        case 5: return "Brasov";
        default: return "";
    }
}

void displayMenu(){
    cout << "\n     === Main Menu ===\n";
    cout << "====================\n";
    cout << "1. Handle Employees\n";
    cout << "2. Handle Products and Stock\n";
    cout << "3. Handle Orders\n";
    cout << "4. Handle Events\n";
    cout << "5. Get Report\n";
    cout << "6. Exit\n";
    cout << "====================\n";
}

void displayEmployeeMenu(){
    cout << "\n   === Employee Menu ===\n";
    cout << "====================\n";
    cout << "1. Display Employees\n";
    cout << "2. Add Employee\n";
    cout << "3. Delete Employee\n";
    cout << "4. Edit Shift\n";
    cout << "5. Exit\n";
    cout << "====================\n";
}

void displayStockMenu(){
    cout << "\n    === Stock Menu ===\n";
    cout << "====================\n";
    cout << "1. Display Stock\n";
    cout << "2. Add Product\n";
    cout << "3. Remove Product\n";
    cout << "4. Calculate Profit (based on stock)\n";
    cout << "5. Exit\n";
    cout << "====================\n";
}

void displayOrderMenu() {
    cout << "\n    === Orders Menu ===\n";
    cout << "====================\n";
    cout << "1. Add Order\n";
    cout << "2. Display Order\n";
    cout << "3. Calculate Total by Order Number\n";
    cout << "4. Exit\n";
    cout << "====================\n";
}

void displayEventMenu() {
    cout << "\n    === Events Menu ===\n";
    cout << "====================\n";
    cout << "1. Add Event\n";
    cout << "2. Display Events\n";
    cout << "3. Delete Event\n";
    cout << "4. Calculate Total Cost\n";
    cout << "5. Exit\n";
    cout << "====================\n";
}

string readInput(string prompt){
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

int readInt(string prompt){
    int input;
    while (true){
        cout << prompt;
        cin >> input;

        if (cin.fail()){
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Invalid input. Please enter a number.\n";
        } else {
            cin.ignore(32767, '\n');
            return input;
        }
    }
}

void handleMenu(string locationPrefix, string location){
    int option;
    do {
        displayMenu();
        option = readInt("Enter your choice: ");

        switch (option){
            case 1: {
                handleEmployeeMenu(locationPrefix + "_employee.csv");
                break;
            }

            case 2: {
                handleStockMenu(locationPrefix + "_stock.csv");
                break;
            }

            case 3: {
                handleOrderMenu(locationPrefix + "_orders.csv", locationPrefix + "_stock.csv");
                break;
            }

            case 4: {
                handleEventMenu(locationPrefix);
                break;
            }

            case 5: {
                string reportFilename = "Reports/" + location + "_report.txt";
                Reports::getInstance().generateDailyReport(locationPrefix + "_orders.csv", locationPrefix + "_stock.csv", locationPrefix + "_employee.csv", locationPrefix + "_events.csv", reportFilename);
                break;
            }

            case 6: {
                cout << "Exiting Main Menu...\n";
                break;
            }

            default: {
                cout << "Invalid option. Please try again.\n";
                break;
            }
        }
    } while (option != 6);
}

void handleEmployeeMenu(string csvFilename) {
    int option;
    vector<Employee*> employees;
    employees = readEmployeesFromCSV(csvFilename);
    do {
        displayEmployeeMenu();
        option = readInt("Enter your choice: ");

        switch (option){
            case 1: {
                if (employees.empty()){
                    cout << "No employees found.\n";
                } else {
                    for (auto& emp : employees){
                        emp->displayInfo();
                        cout << "-------------------\n";
                    }
                }
                break;
            }

            case 2: {
                string name = readInput("Enter the name of the employee: ");
                string position = readInput("Enter the position of the employee (Manager, Barista, Waiter): ");
                string startH = readInput("Enter the start hour of the employee: ");
                string endH = readInput("Enter the end hour of the employee: ");
                double salary = stod(readInput("Enter the salary of the employee: "));

                addEmployee(csvFilename, employees, name, position, startH, endH, salary);
                cout << "Employee added.\n";
                break;
            }

            case 3: {
                string name = readInput("Enter the name of the employee you want to delete: ");
                if (!deleteEmployees(csvFilename, employees, name)){
                    cout << "Employee not found.\n";
                }
                break;
            }

            case 4: {
                string name = readInput("Enter the name of the employee you want to edit: ");
                string startH = readInput("Enter the new start hour: ");
                string endH = readInput("Enter the new end hour: ");
                if (!editShift(csvFilename, employees, name, startH, endH)){
                    cout << "Employee not found.\n";
                }
                break;
            }

            case 5: {
                cout << "Exiting Employee Menu...\n";
                break;
            }

            default: {
                cout << "Invalid option. Please try again.\n";
                break;
            }
        }
    } while (option != 5);
}

void handleStockMenu(string filename) {
    Stock stock;
    int option;

    do {
        displayStockMenu();
        option = readInt("Enter your choice: ");

        switch (option) {
            case 1: {
                stock.displayStock(filename);
                break;
            }
            
            case 2: {
                string name = readInput("Enter the name of the product: ");
                double cost = stod(readInput("Enter the cost of the product: "));
                double price = stod(readInput("Enter the price of the product: "));
                int quantity = readInt("Enter the quantity of the product: ");

                Product product(name, cost, price, quantity);
                stock.addProduct(product, filename);
                break;
            }

            case 3: {
                string name = readInput("Enter the name of the product you want to remove: ");
                int quantity = readInt("Enter the quantity you want to remove: ");
                
                if (!stock.removeProduct(name, quantity, filename)){
                    cout << "Product not found.\n";
                }
                break;
            }

            case 4: {
                double profit = stock.calculateStockProfit(filename);
                cout << "Total profit based on stock: " << profit << " RON\n";
                break;
            }

            case 5: {
                cout << "Exiting Stock Menu...\n";
                break;
            }

            default: {
                cout << "Invalid option. Please try again.\n";
                break;
            }
        }
    } while (option != 5);
}

void handleOrderMenu(string filename, string stockFilename) {
    vector<Order> orders;
    int option;

    do {
        displayOrderMenu();
        option = readInt("Enter your choice: ");

        switch (option) {
            case 1: {
                int orderNumber = readInt("Enter the order number: ");
                string customerName = readInput("Enter the customer name: ");
                Order order(orderNumber, customerName);

                while (true) {
                    string productName = readInput("Enter product name (or 'done' to finish): ");
                    if (productName == "done") {
                        break;
                    }

                    int quantity = readInt("Enter quantity: ");
                    Product product(productName, 0, 0, quantity);

                    order.addOrder(orderNumber, customerName, product, quantity, filename, stockFilename);
                }

                orders.push_back(order);
                cout << "Order added.\n";
                break;
            }

            case 2: {
                int orderNumber = readInt("Enter the order number: ");
                Order order(0, "");
                order.displayOrder(filename, orderNumber);
                break;
            }

            case 3: {
                int orderNumber = readInt("Enter the order number: ");
                Order order(0, "");
                double total = order.calculateOrderTotal(filename, stockFilename, orderNumber);
                cout << "Total for order " << orderNumber << ": " << total << " RON\n";
                break;
            }

            case 4: {
                cout << "Exiting Orders Menu...\n";
                break;
            }

            default: {
                cout << "Invalid option. Please try again.\n";
                break;
            }
        }
    } while (option != 4);
}

void handleEventMenu(string locationPrefix) {
    vector<Event> events;
    loadEvent(events, locationPrefix + "_events.csv");
    int option;

    do {
        displayEventMenu();
        option = readInt("Enter your choice: ");

        switch (option) {
            case 1: {
                addEvent(events, locationPrefix + "_events.csv");
                break;
            }

            case 2:{
                displayAllEvents(events);
                break;
            }

            case 3: {
                deleteEvent(events, locationPrefix + "_events.csv");
                break;
            }

            case 4: {
                double total = calculateTotalCost(events);
                cout << "Total cost of all events: " << total << " RON\n";
                break;
            }

            case 5: {
                cout << "Exiting Events Menu...\n";
                break;
            }

            default: {
                cout << "Invalid option. Please try again.\n";
                break;
            }
        }
    } while (option != 5);
}

void handleLocationMenu(){
    int locationOption;
    do {
        displayLocationMenu();
        locationOption = readInt("Enter your choice: ");
        string locationPrefix ="CSVs/" + getLocationFilenamePrefix(locationOption);
        string location = getLocationFilenamePrefix(locationOption);

        if (locationOption >= 1 && locationOption <= 5){
            handleMenu(locationPrefix, location);
        } else if (locationOption == 6) {
            cout << "Exiting Coffee-Manager...\n";
            break;
        } else {
            cout << "Invalid option. Please try again. (1 - 5)\n";
        }
    } while (locationOption != 6);
}