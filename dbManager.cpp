#include "dbManager.hpp"



using namespace std;
using namespace rapidjson;

bool DbManager::DbManager::getContacts(){
    string contact;
    ifstream file_contacts("contacts.json");
    
    if(!file_contacts.is_open()){
        ofstream new_file_contacts("contacts.json");
        if(!new_file_contacts.is_open()) return false;
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

void DbManager::DbManager::sortContacts(){
    string list_name[contacts.size()];
    vector<Contact> con;
    int size_list = sizeof(list_name)/sizeof(list_name[0]);
    
    for(int i = 0; i< contacts.size(); i++){
        list_name[i] = contacts[i].name;
        con.push_back(contacts[i]);
    };

    sort(list_name, list_name + size_list);
    for(int i = 0; i< contacts.size(); i++){
        for(int y = 0; y< contacts.size(); y++){
            if( list_name[i] == con[y].name){
                contacts[i] = con[y];
                break;
            };
        };
    };
}


bool DbManager::DbManager::putContacts(){
    ofstream file_contacts("contacts.json");
    if(!file_contacts.is_open()) return false;
    sortContacts();
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
