#include "contact.hpp"

using namespace std;

Contact::Contact(string newName, string newLname, long long int newNumber, string newAddress="" ,string newEmail=""){
    name = newName;
    lname = newLname;
    number = newNumber;
    address = newAddress;
    email = newEmail;
}
