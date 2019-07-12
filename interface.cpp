#include <iostream>
#include <string>
#include <fstream>
#include "interface.hpp"
#include "rapidjson/document.h"


using namespace std;
using namespace rapidjson;

Interface::Interface::Interface(void) {
    string contact;
    ifstream file_contacts("contacts.json");
    assert(file_contacts.is_open());
    
    while(getline(file_contacts,contact)){
        char line[contact.length() + 1];
        strcpy(line, contact.c_str()); 
        Document contacts_json;
        contacts_json.Parse(line);
        assert(contacts_json.IsObject());
        contacts.push_back(Contact(contacts_json["name"].GetString(),contacts_json["surname"].GetString(),stoll(contacts_json["number"].GetString()),contacts_json["address"].GetString(),contacts_json["email"].GetString()));
        

    }

    file_contacts.close();
    page=1;
    actualContact = 0;
}

void Interface::Interface::askForValue(string name, string &value, bool needed=false){
    while (true){
        cout << (needed?"*":"") << name << ": ";
        getline(cin, value);
        if(needed && value.empty()){
            cout << "  -> Questo campo è obbligatorio!" << endl;
        } else {
            cout << endl;
            break;
        }
    }
}

void Interface::Interface::askForValue(string name, long long int &value){
    while (true){
        cout << "*" << name << ": ";
        cin >> value;
        if(cin.fail()) {
            cin.clear();
            // qui mi dava errore numeric_limits<streamsize>::max() dunque l'ho cambiato in base a ciò che ho capiro del codice
            cin.ignore(100000000,'\n');
            cout << "  -> Il numero inserito non è corretto!" << endl;
        } else {
            cout << endl;
            break;
        }
    }
}

// PAGES

void Interface::Interface::list(){ // page 1
    string command;
    long size = contacts.size();
    
    cout << "I TUOI CONTATTI" << endl << endl;
    for(int x=0; x<size; x++){
        cout<< x+1 << ": " << contacts[x].name << " " << contacts[x].lname << endl;
    }
    cout << "----------" << endl;
    cout << size+1 << ": Aggiungi contatto" << endl;
    cout << size+2 << ": Esci" << endl;
    
    cin >> command;
    for(int x=0; x<size; x++){
        if(stoi(command)-1==x) {
            page=3;
            actualContact=x;
            return;
        }
    }
    if(stoi(command)==size+1) {
        page=2;
        return;
    } else if(stoi(command)==size+2) {
        page=0;
        return;
    }
}

void Interface::Interface::add(){ // page 2
    string tmp, name, lname, address, email;
    long long int number;
    
    getline(cin,tmp);
    cout << "AGGIUNGI CONTATTO" << endl << endl;
    askForValue("Nome", name, true);
    askForValue("Cognome", lname, true);
    askForValue("Numero di telefono", number);
    getline(cin,tmp);
    askForValue("Indirizzo di casa", address);
    askForValue("Indirizzo email", email);
    
    contacts.push_back(Contact(name, lname, number, address, email));
    
    /*ofstream file_contacts("contacts.json");
    assert(file_contacts.is_open());
    file_contacts << "{'name':"+ name +",'surname':" + lname +",'number':" + to_string(number) +",'address':" + address + ",'email':" + email + "}\n";
    file_contacts.close();*/
    page = 1;
}

void Interface::Interface::view(){ // page 3
    string command;
    Contact contact = contacts[actualContact];
    cout << "CONTATTO" << endl << endl;
    cout << "Nome: " << contact.name << endl << endl;
    cout << "Cognome: " << contact.lname << endl << endl;
    cout << "Numero di telefono: " << contact.number << endl << endl;
    if(contact.address!=""){
        cout << "Indirizzo di casa: " << contact.address << endl << endl;
    }
    if(contact.email!=""){
        cout << "Indirizzo email: " << contact.email << endl << endl;
    }
    cout << "----------" << endl;
    cout << "1: Indietro" << endl;
    cout << "2: Rimuovi" << endl;
    
    cin >> command;
    if(stoi(command)==1) {
        page=1;
        return;
    } else if(stoi(command)==2) {
        page=4;
        return;
    }
}

void Interface::Interface::remove(){ // page 4
    string command;
    
    cout << "Vuoi davvero eliminare " << contacts[actualContact].name << " " << contacts[actualContact].lname << "? (s/n) ";
    cin >> command;
    if(command=="s") {
        contacts.erase(contacts.begin()+actualContact);
        page=1;
        return;
    } else if(command=="n") {
        page=1;
        return;
    }
}