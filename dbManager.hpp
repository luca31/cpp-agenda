#ifndef dbManager_hpp
#define dbManager_hpp

#include <stdio.h>
#include <vector>
#include <bits/stdc++.h> 
#include <fstream>
#include <string>
#include "contact.hpp"
#include "rapidjson/document.h"

namespace DbManager{
    class DbManager;
}

class DbManager::DbManager {
public:
    std::vector<Contact> contacts;
    bool getContacts();
    void sortContacts();
    bool putContacts();

};

#endif
