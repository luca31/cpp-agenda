#include <iostream>
#include <string>
#include "contact.hpp"

using namespace std;

Contact::Contact(string newName, string newLname, long long int newNumber, string newAddress="" ,string newEmail=""){
    name = newName;
    lname = newLname;
    number = newNumber;
    address = newAddress;
    email = newEmail;
}

void Contact::edit(string type, string change){
    if(type=="name") {
        name = change;
    } else if (type == "surname" ){
        lname = change;
    } else if (type == "address" ){
        address = change;
    } else if (type == "email" ){
        email = change;
    };
}

void Contact::edit(string type, long long int change){
    number = change;
}
