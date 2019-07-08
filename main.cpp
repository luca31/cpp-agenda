#include <iostream>
#include <string>
#include "interface.hpp"

using namespace std;

int main(){
    Interface::Interface interface;
    string command;
    
    while(true){
        cout << "\n\n\n\n\n";
        interface.Interface::list();
        
        cout << "\n\n\nScrivere 1 per aggiungere un contatto" << endl;
        cin >> command;
        cout << "\n\n\n\n\n";
        switch (stoi(command)) {
            case 1:
                interface.Interface::add();
                break;
                
            default:
                break;
        }
    }
    
    return 0;
}
