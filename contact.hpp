#ifndef contact_hpp
#define contact_hpp

#include <stdio.h>
#include <string>

using namespace std;
class Contact {
    public:
        string name, lname, address, email, number;
        Contact(string newName, string newLname, string newNumber, string newAddress, string newEmail);
};

#endif
