#ifndef REPORTS_H
#define REPORTS_H

#include "Orders.h"
#include "Stock.h"
#include "Employees.h"
#include "Events.h"

// Implementarea pattern-ului Singleton pentru clasa Reports
class Reports {
private:
    Reports() {}
    Reports(const Reports&) = delete;
    Reports& operator=(const Reports&) = delete;

public:
    static Reports& getInstance() {
        static Reports instance;
        return instance;
    }

    void generateDailyReport(string ordersFilename, string stockFilename, string employeesFilename, string eventsFilename, string reportFilename);
};

#endif // REPORTS_H