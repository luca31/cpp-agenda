#include <iostream>
#include <string>
#include "interface.hpp"

using namespace std;

Interface::Interface::Interface(void) {
    for(int x=0; x<10; x++){
        contacts.push_back(x);
    };
}

void Interface::Interface::list(){
    cout << "I tuoi contatti:\n" << endl;
    for(int x=0; x<contacts.size(); x++){
        cout << x << endl;
    }
}

void Interface::Interface::add(){
    string name, surname, number;
    cout << "Aggiungi un contatto\n" << endl;
    cout << "\nInserisci il nome: ";
    cin >> name;
    cout << "\n\nInserisci il cognome: ";
    cin >> surname;
    cout << "\n\nInserisci il numero di telefono: ";
    cin >> number;
    contacts.push_back(contacts.size());
}
