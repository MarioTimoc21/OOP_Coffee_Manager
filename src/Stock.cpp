#include "../include/Stock.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>


using namespace std;

double calculateStockCost(string filename);

Stock::~Stock(){
    for (auto& prod : products){
        delete prod;
    }
    products.clear();
};

void Stock::addProduct(Product& product,string filename){
    ifstream inputFile(filename);
    vector<Product*> products;

    if (!inputFile.is_open()){
        cout << "Could not open the file.\n";
        return;
    }

    string line, name;
    double cost, price;
    int quantity;

    getline(inputFile, line);
    while(getline(inputFile, line)){
        stringstream ss(line);
        getline(ss, name, ',');
        ss >> cost;
        ss.ignore();
        ss >> price;
        ss.ignore();
        ss >> quantity;

        products.push_back(new Product(name, cost, price, quantity));
    }

    inputFile.close();

    bool found = false;
    for (auto& prod : products){
        if (prod->getName() == product.getName()){
            prod->setQuantity(prod->getQuantity() + product.getQuantity());
            found = true;
            break;
        }
    }

    if (!found){
        products.push_back(new Product(product.getName(), product.getCost(), product.getPrice(), product.getQuantity()));
        cout << "Product " << product.getName() << " added to stock.\n";
    } else {
        cout << "Updated quantity for product " << product.getName() << ".\n";
    }

    ofstream outputFile(filename);
    if (!outputFile.is_open()){
        cout << "Could not open the file.\n";
        return;
    }

    outputFile << "Name,Cost,Price,Quantity\n";
    for (const auto& prod : products){
        outputFile << prod->getName() << "," << prod->getCost() << "," << prod->getPrice() << "," << prod->getQuantity() << endl;
    }
    outputFile.close();

    for (auto& prod : products){
        delete prod;
    }
}

bool Stock::removeProduct(string name, int quantity, string filename){
    ifstream inputFile(filename);
    vector<Product*> products;

    if(!inputFile.is_open()){
        cout << "Could not open the file.\n";
        return false;
    }

    string line, prodName;
    double cost, price;
    int prodQuantity;

    getline(inputFile, line);
    while(getline(inputFile, line)){
        stringstream ss(line);
        getline(ss, prodName, ',');
        ss >> cost;
        ss.ignore();
        ss >> price;
        ss.ignore();
        ss >> prodQuantity;

        products.push_back(new Product(prodName, cost, price, prodQuantity));
    }
    inputFile.close();

    bool found = false;
    for(auto it = products.begin(); it != products.end(); ++it){
        if ((*it)->getName() == name){
            if ((*it)->getQuantity() > quantity){
                (*it)->setQuantity((*it)->getQuantity() - quantity);
                cout << "Removed " << quantity << " units of product " << name << " from stock.\n";
            } else {
                cout << "Removed all units of product " << name << ".\n";
                delete *it;
                products.erase(it);
            }
            found = true;
            break;
        }
    }

    if (!found){
        cout << "Product " << name << " not found in stock.\n";
        return false;
    }

    ofstream outputFile(filename);
    if (!outputFile.is_open()){
        cout << "Could not open the file: " << filename << endl;
        return false;
    }

    outputFile << "Name,Cost,Price,Quantity\n";
    for (const auto& prod : products){
        outputFile << prod->getName() << "," << prod->getCost() << "," << prod->getPrice() << "," << prod->getQuantity() << endl;
    }
    outputFile.close();

    for (auto& prod : products){
        delete prod;
    }

    return true;
}

void Stock::displayStock(string filename){
    ifstream inputFile(filename);

    if (!inputFile.is_open()){
        cout << "Could not open the file: " << filename << endl;
        return;
    }

    string line, name;
    double cost, price;
    int quantity;

    getline(inputFile, line);

    cout << "Stock:\n";
    while (getline(inputFile, line)){
        stringstream ss(line);
        getline(ss, name, ',');
        ss >> cost;
        ss.ignore();
        ss >> price;
        ss.ignore();
        ss >> quantity;

        cout << "Product: " << name << endl;
        cout << "Cost: " << cost << " RON\n";
        cout << "Price: " << price << " RON\n";
        cout << "Quantity: " << quantity << endl;
        cout << "-------------------\n";
    }
    
    inputFile.close();
}

double Stock::calculateStockProfit(string filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Could not open the file: " << filename << endl;
        return 0;
    }

    string line, name;
    double cost, price;
    int quantity;

    getline(inputFile, line);
    while (getline(inputFile, line)) {
        stringstream ss(line);
        getline(ss, name, ',');
        ss >> cost;
        ss.ignore();
        ss >> price;
        ss.ignore();
        ss >> quantity;

        products.push_back(new Product(name, cost, price, quantity));
    }

    inputFile.close();

    double profit = 0;
    for (const auto& prod : products) {
        profit += (prod->getPrice() - prod->getCost()) * prod->getQuantity();
    }

    return profit;
}

double calculateStockCost(string filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Could not open the file: " << filename << endl;
        return 0.0;
    }

    string line;
    getline(inputFile, line);

    double totalCost = 0;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string name;
        double cost, price;
        int quantity;

        getline(ss, name, ',');
        ss >> cost;
        ss.ignore();
        ss >> price;
        ss.ignore();
        ss >> quantity;

        totalCost += (cost * quantity);
    }

    inputFile.close();
    return totalCost;
}