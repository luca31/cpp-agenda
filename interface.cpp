#include <iostream>
#include <string>
#include "interface.hpp"
#include "contact.hpp"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;
Interface::Interface::Interface(void) {
    // caricare i contatti tramite un file json
    file_contacs >> contacts_json;
    for(auto contact : contacts_json){
        contacts.push_back(Contact(contact["name"],contact["surname"],contact["number"],contact["address"],contact["email"]));
    }
    
    page=1;
}

void Interface::Interface::askForValue(string name, string &value, bool needed=false){
    while (true){
        cout << name << ": ";
        cin >> value;
        cout << endl;
        break;
    }
}

void Interface::Interface::askForValue(string name, long long int &value){
    while (true){
        cout << name << ": ";
        cin >> value;
        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
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
    for(int x=1; x<size+1; x++){
        cout<< x << ": " << contacts[x-1].name << " " << contacts[x-1].lname << endl;
    }
    cout << "----------" << endl;
    cout << size+1 << ": Aggiungi contatto" << endl;
    cout << size+2 << ": Esci" << endl;
    
    cin >> command;
    if(stoi(command)==size+1) {
        page=2;
        return;
    } else if(stoi(command)==size+2) {
        page=0;
        return;
    }
}

void Interface::Interface::add(){ // page 2
    string name, lname;
    long long int number;
    
    askForValue("Nome", name);
    askForValue("Cognome", lname);
    askForValue("Numero di telefono", number);
    
    contacts.push_back(Contact(name, lname, number, "", ""));
    
    page = 1;
}

