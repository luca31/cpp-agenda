#include <fstream>
#include <vector>
#include <string>
#include "dbManager.hpp"
#include "rapidjson/document.h"

using namespace std;
using namespace rapidjson;

bool DbManager::DbManager::getContacts(){
    string contact;
    ifstream file_contacts("contacts.json");
    
    if(!file_contacts.is_open()){
        ofstream new_file_contacts("contacts.json");
        if(!new_file_contacts.is_open()) return false; // qui non ho capito, quindi me lo potresti spiegare
        new_file_contacts << "";
        new_file_contacts.close();
    } else {
        while(getline(file_contacts,contact)){
            char line[contact.length() + 1];
            strcpy(line, contact.c_str());
            Document contacts_json;
            contacts_json.Parse(line);
            if(contacts_json.IsObject()) {
                contacts.push_back(Contact(
                    contacts_json["name"].GetString(),
                    contacts_json["lname"].GetString(),
                    stoll(contacts_json["number"].GetString()),
                    contacts_json.HasMember("address")?contacts_json["address"].GetString():"",
                    contacts_json.HasMember("email")?contacts_json["email"].GetString():""
                ));
            }
        }
    }
    
    file_contacts.close();
    return true;
}

bool DbManager::DbManager::putContacts(){
    ofstream file_contacts("contacts.json");
    if(!file_contacts.is_open()) return false;
    for(int x = 0; x < contacts.size(); x++){
        Contact cnt = contacts[x];
        file_contacts << "{\"name\":\"" << cnt.name << "\",\"lname\":\"" << cnt.lname  << "\",\"number\":" << "\"" << cnt.number << "\"";
        if(!cnt.address.empty()) file_contacts << ",\"address\":\"" << cnt.address << "\"";
        if(!cnt.email.empty()) file_contacts << ",\"email\":\"" << cnt.email << "\"";
        file_contacts << "}\n";
    }
    
    file_contacts.close();
    return true;
}
