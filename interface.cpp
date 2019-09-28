#include "interface.hpp"

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

void Interface::Interface::askForValue(string name, long long int  &value){
    while (true){
        cout << "*" << name << ": ";
        cin >> value;
        if(cin.fail()) {
            cin.clear();
            cin.ignore(99999,'\n');
            cout << "  -> Il numero inserito non è corretto!" << endl;
        } else {
            cout << endl;
            break;
        }
    }
}

bool Interface::Interface::strEquals(const string& a, const string& b)
{
    return equal(a.begin(), a.end(),
        b.begin(), b.end(),
        [](char a, char b) {
            return tolower(a) == tolower(b);
        });
}

// PAGES

void Interface::Interface::list(){ // page 1
    int command;
    long size = db.contacts.size();
    
    cout << "I TUOI CONTATTI" << endl << endl;
    for(int x = 0; x < size; x++){
        cout<< x+1 << ": " << db.contacts[x].name << " " << db.contacts[x].lname << endl;
    }
    cout << "----------" << endl;
    cout << size+1 << ": Aggiungi contatto" << endl;
    cout << size+2 << ": Cerca contatto" << endl;
    cout << size+3 << ": Esci" << endl;
    
    cin >> command;
    if(cin.fail()) {
        cin.clear();
        cin.ignore(999,'\n');
        return;
    }

    for(int x = 0; x < size; x++){
        if(command-1 == x) {
            page = 3;
            actualContact = x;
            return;
        }
    }
    
    if(command == size+1) page = 2;
    else if(command == size+2) page = 6;
    else if(command == size+3) page = 0;
}

void Interface::Interface::add(){ // page 2
    string tmp, name, lname, address, email;
    long long int number;
    
    getline(cin,tmp);// non ho capito perche la usiamo 
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
    int command;
    
    Contact contact = db.contacts[actualContact];
    cout << "CONTATTO" << endl << endl;
    cout << "Nome: " << contact.name << endl << endl;
    cout << "Cognome: " << contact.lname << endl << endl;
    cout << "Numero di telefono: " << contact.number << endl << endl;
    if(contact.address != ""){
        cout << "Indirizzo di casa: " << contact.address << endl << endl;
    }
    if(contact.email != ""){
        cout << "Indirizzo email: " << contact.email << endl << endl;
    }
    cout << "----------" << endl;
    cout << "1: Indietro" << endl;
    cout << "2: Rimuovi" << endl;
    cout << "3: Modifica" << endl;
    
    cin >> command;
    if(cin.fail()) {
        cin.clear();
        cin.ignore(999,'\n');
        return;
    }
    
    if(command == 1) page = 1;
    else if(command == 2) page = 4;
    else if(command == 3) page = 5;
}

void Interface::Interface::remove(){ // page 4
    char command;
    
    cout << "Vuoi davvero eliminare " << db.contacts[actualContact].name << " " << db.contacts[actualContact].lname << "? (s/n) ";
    cin >> command;
    cin.clear();
    cin.ignore(255,'\n');
    if(tolower(command) == 's') {
        db.contacts.erase(db.contacts.begin()+actualContact);
        db.putContacts();
        page = 1;
    } else if(tolower(command) == 'n') page = 1;
}

void Interface::Interface::edit(){ // page 5
    int command;
    string tmp;
    
    cout << "MODIFICA" << endl << endl;
    
    cout << "Quale campo si desidera modificare? " << endl << endl;
    cout << "1: Nome (" << db.contacts[actualContact].name << ")" << endl;
    cout << "2: Cognome (" << db.contacts[actualContact].lname << ")" << endl;
    cout << "3: Numero di telefono (" << db.contacts[actualContact].number << ")" << endl;
    cout << "4: Indirizzo di casa (" << (db.contacts[actualContact].address.empty()?"non specificato":db.contacts[actualContact].address) << ")" << endl;
    cout << "5: Indirizzo email (" << (db.contacts[actualContact].email.empty()?"non specificato":db.contacts[actualContact].email) << ")" << endl;
    cout << "6: Indietro" << endl;
    
    cin >> command;
    if(cin.fail()) {
        cin.clear();
        cin.ignore(999,'\n');
        return;
    }
    
    if(command == 6){
        page = 1;
        return;
    }
    
    getline(cin,tmp);
    if(command == 1) askForValue("Nome", db.contacts[actualContact].name, true);
    else if(command == 2) askForValue("Cognome", db.contacts[actualContact].lname, true);
    else if(command == 3) askForValue("Numero di telefono", db.contacts[actualContact].number);
    else if(command == 4) askForValue("Indirizzo di casa", db.contacts[actualContact].address, false);
    else if(command == 5) askForValue("Indirizzo email", db.contacts[actualContact].email, false);
    else return;
    db.putContacts();
}

void Interface::Interface::search(){ // page 6
    int command;
    string value;
    vector<int> found;
    
    cout << "Inserisci la parola o il numero da ricercare: ";
    cin >> value;
    
    for(int x = 0; x < db.contacts.size(); x++){
        if(strEquals(db.contacts[x].name, value) || strEquals(db.contacts[x].lname, value) || value == to_string(db.contacts[x].number) || strEquals(db.contacts[x].address, value) || strEquals(db.contacts[x].email, value)){
            found.push_back(x);
        };
    };
    
    if(found.empty()) cout << endl << "Non è stata trovata alcuna corrispondenza" << endl;
    else {
        if(found.size()==1) {
            page = 3;
            actualContact = found[0];
            return;
        } else {
            cout << endl << found.size() << " contatti trovati" << endl << endl;
            for(int x = 0; x < found.size();  x++){
                cout << x+1 << ": " << db.contacts[found[x]].name << " " << db.contacts[found[x]].lname << endl;
            }
        }
    }
      
    cout << "----------" << endl;
    cout << found.size()+1 << ": Indietro" << endl;
    cin >> command;

    if(cin.fail()){
        cin.clear();
        cin.ignore(999,'\n');
        return;
    };

    if(command == found.size()+1){
        page = 1;
        return;
    }else{
       for(int x = 0; x < found.size(); x++){
            if(command-1 == x) {
                page = 3;
                actualContact = found[x];
                return;
            };
        };
    };
}
