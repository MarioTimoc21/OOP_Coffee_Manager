#include "../include/Reports.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

void Reports::generateDailyReport(string ordersFilename, string stockFilename, string employeesFilename, string eventsFilename, string reportFilename) {
    // Exception handling
    try {
        vector<Order> orders;
        vector<Employee*> employees;
        vector<Event> events;

        employees = readEmployeesFromCSV(employeesFilename);
        loadEvent(events, eventsFilename);

        Order orderCalculator(0, "");
        double totalRevenue = orderCalculator.calculateTotalAllOrders(ordersFilename, stockFilename);

        double totalSalaries = 0;
        for (const auto& emp : employees) {
            totalSalaries += emp->getSalary() / 30;
        }

        double totalEventCost = calculateTotalCost(events);
        double totalStockCost = calculateStockCost(stockFilename);

        double totalCost = totalSalaries + totalEventCost + totalStockCost;
        double totalProfit = totalRevenue - totalCost;

        ofstream reportFile(reportFilename);
        if (!reportFile.is_open()) {
            throw runtime_error("Could not open the file: " + reportFilename);
        }

        reportFile << " ~~Daily Report~~\n";
        reportFile << "Total Revenue: " << fixed << setprecision(2) << totalRevenue << " RON\n";
        reportFile << "Total Stock Cost: " << fixed << setprecision(2) << totalStockCost << " RON\n";
        reportFile << "Total Salaries: " << fixed << setprecision(2) << totalSalaries << " RON\n";
        reportFile << "Total Event Cost: " << fixed << setprecision(2) << totalEventCost << " RON\n";
        reportFile << "-------------------\n";
        reportFile << "Net Profit: " << fixed << setprecision(2) << totalProfit << " RON\n";

        reportFile.close();

        cout << "Report generated successfully.\n";
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}