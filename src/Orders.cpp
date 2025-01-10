#include "../include/Orders.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <set>

using namespace std;

Order::Order(int orderNumber, string customerName){
    this->orderNumber = orderNumber;
    this->customerName = customerName;
}

void Order::addOrder(int orderNumber, string customerName, Product &product, int quantity, string ordersfile, string stockfile){
    products.emplace_back(product, quantity);

    ifstream stockFile(stockfile);
    if (!stockFile.is_open()){
        cout << "Could not open the file: " << stockfile << endl;
        return;
    }

    string line, productName;
    double productPrice = 0;
    bool productFound = false;
    vector<Product> stockItems;
    getline(stockFile, line);

    while (getline(stockFile, line)) {
        stringstream ss(line);
        string name;
        double cost, price;
        int stockQuantity;
        getline(ss, name, ',');
        ss >> cost;
        ss.ignore();
        ss >> price;
        ss.ignore();
        ss >> stockQuantity;

        if (name == product.getName()) {
            productPrice = price;
            stockQuantity -= quantity;
            productFound = true;
        }
        stockItems.emplace_back(name, cost, price, stockQuantity);
    }
    stockFile.close();

    if (!productFound) {
        cout << "Product not found in stock.\n";
        return;
    }

    ofstream stockOutput(stockfile);
    stockOutput << "Product,Cost,Price,Quantity\n";
    for (auto &item : stockItems){
        stockOutput << item.getName() << "," << item.getCost() << "," << item.getPrice() << "," << item.getQuantity() << endl;
    }
    stockOutput.close();

    ofstream ordersOutput(ordersfile, ios::app);
    if (!ordersOutput.is_open()){
        cout << "Could not open the file: " << ordersfile << endl;
        return;
    }

    if (ordersOutput.tellp() == 0){
        ordersOutput << "Order Number,Customer Name,Product,Quantity,Total\n";
    }

    ordersOutput << orderNumber << "," << customerName << "," << product.getName() << "," << quantity << "," << fixed << setprecision(2) << productPrice * quantity << endl;
    ordersOutput.close();

    cout << "Product " << product.getName() << " added to order " << orderNumber << endl;
}

double Order::calculateOrderTotal(string ordersFilename, string stockFilename, int orderNumber) {
    map<string, double> productPrices;
    ifstream stockFile(stockFilename);
    if (!stockFile.is_open()) {
        cout << "Could not open the file: " << stockFilename << endl;
        return 0;
    }

    string stockLine, productName;
    double productPrice;
    getline(stockFile, stockLine);

    while (getline(stockFile, stockLine)) {
        stringstream ss(stockLine);
        getline(ss, productName, ',');
        ss.ignore(256, ',');
        ss >> productPrice;
        productPrices[productName] = productPrice;
    }

    stockFile.close();

    ifstream ordersFile(ordersFilename);
    if (!ordersFile.is_open()) {
        cout << "Could not open the file: " << ordersFilename << endl;
        return 0;
    }

    map<string, int> customerOrderCount;
    string ordersLine;
    double total = 0;
    bool orderFound = false;

    while (getline(ordersFile, ordersLine)){
        stringstream ss(ordersLine);
        int fileOrderNumber;
        string customerName, productName;

        ss >> fileOrderNumber;
        ss.ignore();
        getline(ss, customerName, ',');
        getline(ss, productName, ',');
       
       customerOrderCount[customerName]++;
    }

    ordersFile.clear();
    ordersFile.seekg(0, ios::beg);
    getline(ordersFile, ordersLine);

    string customerNameforOrder;

    while (getline(ordersFile, ordersLine)){
        stringstream ss(ordersLine);
        int fileOrderNumber;
        string customerName, productName;
        int quantity;

        ss >> fileOrderNumber;
        ss.ignore();
        getline(ss, customerName, ',');
        getline(ss, productName, ',');
        ss >> quantity;
        ss.ignore();

        if (fileOrderNumber == orderNumber){
            orderFound = true;
            customerNameforOrder = customerName;

            if (productPrices.find(productName) != productPrices.end()){
                total += productPrices[productName] * quantity;
            } else {
                cout << "Product \"" << productName << "\" not found in stock.\n";
            }
        }
    }

    ordersFile.close();

    if (!orderFound){
        cout << "Order number " << orderNumber << " not found.\n";
        return 0;
    }

    if (customerOrderCount[customerNameforOrder] > 3){
        cout << "Applying 10% discount for customer " << customerNameforOrder << endl;
        total *= 0.9;
    }

    return total;
}

string Order::getCustomerName(){
    return customerName;
}

double Order::getTotal(){
    return total;
}

int Order::getOrderNumber(){
    return orderNumber;
}

double Order::calculateTotalAllOrders(string ordersFilename, string stockFilename) {
    ifstream ordersFile(ordersFilename);
    if (!ordersFile.is_open()) {
        cout << "Could not open the file: " << ordersFilename << endl;
        return 0;
    }

    set<int> uniqueOrderNumbers;
    string ordersLine;

    getline(ordersFile, ordersLine);
    while (getline(ordersFile, ordersLine)) {
        stringstream ss(ordersLine);
        int orderNumber;
        ss >> orderNumber;
        uniqueOrderNumbers.insert(orderNumber);
    }

    ordersFile.close();

    double totalRevenue = 0;
    for (int orderNumber : uniqueOrderNumbers) {
        totalRevenue += calculateOrderTotal(ordersFilename, stockFilename, orderNumber);
    }

    return totalRevenue;
}

void Order::displayOrder(string filename, int orderNumber){
   ifstream file(filename);
   if (!file.is_open()){
       cout << "Could not open the file: " << filename << endl;
       return;
   }

    string line;
    bool orderFound = false;
    cout << "Order Number: " << orderNumber << endl;

    while(getline(file, line)) {
        stringstream ss(line);
        int fileOrderNumber;
        string customerName, productName;
        int quantity;
        double price;

        ss >> fileOrderNumber;
        ss.ignore();
        getline(ss, customerName, ',');
        getline(ss, productName, ',');
        ss >> quantity;
        ss.ignore();
        ss >> price;

        if (fileOrderNumber == orderNumber){
            if (!orderFound){
                cout << "Customer Name: " << customerName << endl;
                cout << "Products:\n";
                orderFound = true;
            }
            cout << " - " << productName << " x" << quantity << " " << fixed << setprecision(2) << price << "RON\n";
        }
    }

    if (!orderFound) {
        cout << "Order not found.\n";
    }

    file.close();
}

