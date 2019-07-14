#include <iostream>
#include <string>
#include "interface.hpp"
#include "rapidjson/document.h"

using namespace std;
using namespace rapidjson;

Interface::Interface::Interface(void) {
    if(!db.getContacts()) {
        cout << "Si è verificato un errore durante il caricamento dell'archivio" << endl << endl;
        exit(EXIT_FAILURE);
    }
    
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
            cin.ignore(99999999999,'\n');
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
    long size = db.contacts.size();
    
    cout << "I TUOI CONTATTI" << endl << endl;
    for(int x=0; x<size; x++){
        cout<< x+1 << ": " << db.contacts[x].name << " " << db.contacts[x].lname << endl;
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
    
    db.contacts.push_back(Contact(name, lname, number, address, email));
    
    db.putContacts();

    page = 1;
}

void Interface::Interface::view(){ // page 3
    string command;
    Contact contact = db.contacts[actualContact];
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
    
    cout << "Vuoi davvero eliminare " << db.contacts[actualContact].name << " " << db.contacts[actualContact].lname << "? (s/n) ";
    cin >> command;
    if(command=="s") {
        db.contacts.erase(db.contacts.begin()+actualContact);
        db.putContacts();
        page=1;
        return;
    } else if(command=="n") {
        page=1;
        return;
    }
}
