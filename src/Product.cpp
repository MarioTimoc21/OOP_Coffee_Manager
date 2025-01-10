#include "../include/Product.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Product::Product(string name, double cost, double price, int quantity){
    this->name = name;
    this->cost = cost;
    this->price = price;
    this->quantity = quantity;
}

string Product::getName(){
    return name;
}

double Product::getCost(){
    return cost;
}

double Product::getPrice(){
    return price;
}

int Product::getQuantity(){
    return quantity;
}

void Product::setQuantity(int quantity){
    this->quantity = quantity;
}

void Product::displayInfo(){
    cout << "Product: " << name << endl;
    cout << "Cost: " << cost << " RON\n";
    cout << "Price: " << price << " RON\n";
    cout << "Quantity: " << quantity << endl;
}

