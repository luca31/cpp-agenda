#include <iostream>  
#include <string>
#include "contact.hpp"
using namespace std;

Contact::Contact(string name_, string surname_, long long int number_, string address_ ,string email_, int birthday_[2]){
	name = name_;
    surname = surname_;
    number = number_;
    address = address_;
    email = email_;
    birthday[0] = birthday_[0];
    birthday[1] = birthday_[1];
}

int Contact::edit(string type){
    string change;
    if(type =="name"){
        cout <<"inserire modifica";
        cin >> change;
        name = change;
        return 0;
    }else if (type == "surname" ){
        cout <<"inserire modifica";
        cin >> change;
        surname = change;
        return 0;
    }else if (type == "address" ){
        cout <<"inserire modifica";
        cin >> change;
        address = change;
        return 0;
    }else if (type == "email" ){
        cout <<"inserire modifica";
        cin >> change;
        email = change;
        return 0;
    };           
		
}


int main() {
	return 0;

}
