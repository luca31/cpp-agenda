#ifndef interface_hpp
#define interface_hpp

#include <iostream>
#include <stdio.h> 
#include <vector>
#include <string>
#include "contact.hpp"
#include "dbManager.hpp"

using namespace std;

namespace Interface{
    class Interface;
}

class Interface::Interface {
public:
    Interface(void);
    DbManager::DbManager db;
    int actualContact;
    short page;
    void askForValue(string name, string &value, bool needed);
    void askForValue(string name, long long int &value);
    bool strEquals(const string& a, const string& b);
    void list();
    void add();
    void view();
    void remove();
    void edit();
    void search();
};

#endif
