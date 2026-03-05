#pragma once
#include <vector>
#include <string>

struct Transaction {
    std::string date;
    std::string detail;
    double amount;
};

struct AppData {
    double totalIncome = 0.0;
    double totalExpense = 0.0;
    double taxToPay = 0.0;
    std::vector<Transaction> history;
};

extern AppData g_data;