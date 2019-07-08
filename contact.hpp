#include <string>
using namespace std;
class Contact {
    public:
        string name, surname, address, email;
        long long int number;
        int birthday[2];
        
        Contact(string name_, string surname_, long long int number_, string address_, string email_);
        int edit(string type, string change);
        int edit (string type, long long int change);


};

