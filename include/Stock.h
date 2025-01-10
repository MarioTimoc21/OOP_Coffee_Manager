#ifndef STOCK_H
#define STOCK_H

#include "Product.h"
#include <vector>
#include <string>

class Stock{
    private:
        vector<Product*> products;
    public:
        void addProduct(Product& product, string filename);
        bool removeProduct(string name, int quantity, string filename);
        void displayStock(string filename);
        double calculateStockProfit(string filename);
        ~Stock();
};

double calculateStockCost(string filename);

#endif // STOCK_H