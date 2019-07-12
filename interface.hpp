#ifndef interface_hpp
#define interface_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "contact.hpp"
using namespace std;

namespace Interface{
    class Interface;
}

class Interface::Interface {
public:
    Interface(void);
    std::vector<Contact> contacts;
    int actualContact;
    short page;
    void list();
    void add();
    void view();
    void search();
    void edit();
    void remove();
    void askForValue(string name, string &value, bool needed);
    void askForValue(string name, long long int &value);

};

#endif
