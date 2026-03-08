#include "Account.h"

Account::Account(const wxString& n, double b)
    : name(n), balance(b) 
{
}

void Account::add(double money)
{
    balance += money;
}

void Account::sub(double money)
{
    balance -= money;
}