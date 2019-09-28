#ifndef dbManager_hpp
#define dbManager_hpp

#include <stdio.h>
#include <vector>
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
    bool putContacts();
};

#endif
