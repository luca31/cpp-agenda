#include <iostream>
#include <string>
#include "contact.hpp"

using namespace std;

Contact::Contact(string name_, string lname_, long long int number_, string address_ ,string email_){
    name = name_;
    lname = lname_;
    number = number_;
    address = address_;
    email = email_;
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