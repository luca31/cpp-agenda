#ifndef contact_hpp
#define contact_hpp

#include <stdio.h>
#include <string>

using namespace std;
class Contact {
    public:
        string name, lname, address, email;
        long long int number;
    
        Contact(string name_, string lname_, long long int number_, string address_, string email_);
        void edit(string type, string change);
        void edit(string type, long long int change);

};

#endif