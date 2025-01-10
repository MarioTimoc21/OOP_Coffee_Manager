#ifndef ORDERS_H
#define ORDERS_H

#include "Product.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Order {
    private:
        int orderNumber;
        string customerName;
        vector<pair<Product, int>> products;
        string product;
        int quantity;
        double total;
    
    public:
        Order(int orderNumber, string customerName);
        void addOrder(int orderNumber, string customerName, Product &product, int quantity, string ordersfile, string stockfile);
        void calculateTotal();
        void displayOrder(string filename, int orderNumber);
        double calculateOrderTotal(string ordersFilename, string stockFilename, int orderNumber);
        double calculateTotalAllOrders(string ordersFilename, string stockFilename);
        string getCustomerName();
        int getOrderNumber();
        double getTotal();
};


#endif // ORDERS_H