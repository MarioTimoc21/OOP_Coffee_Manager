#ifndef PRODUCT_H
#define PRODUCT_H

#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

// Incapsulare prin variabile private accesate prin gettere si settere
class Product{
    private:
        string name;
        double cost;
        double price;
        int quantity;

    public:
        Product(string name, double cost, double price, int quantity);
        //gettere
        string getName();
        double getCost();
        double getPrice();
        int getQuantity();
        //settere
        void setQuantity(int quantity);
        //afisare
        void displayInfo();
};

#endif // PRODUCT_H