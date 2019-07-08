#include <iostream>  
#include <string>
#include "contact.hpp"
using namespace std;

Contact::Contact(string name_, string surname_, long long int number_, string address_ ,string email_){
	name = name_;
    surname = surname_;
    number = number_;
    address = address_;
    email = email_;
    birthday[0] = birthday_[0];
    birthday[1] = birthday_[1];
}

int Contact::edit(string type, string change){
    if(type =="name"){
        name = change;
    }else if (type == "surname" ){
        surname = change;
	}else if (type == "address" ){
        address = change;
    }else if (type == "email" ){
        email = change;
    };       
	return 0;
		
}


int Contact::edit(string type, long long int change){
		number = change;
}





int main() {
	return 0;

}
