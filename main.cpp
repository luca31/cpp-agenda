#include <iostream>
#include <string>
#include "interface.hpp"

using namespace std;

int main(){
    Interface::Interface interface;
    
    while(interface.page){
        switch(interface.page){
            case 1:
                interface.list();
                break;
            case 2:
                interface.add();
                break;
            case 3:
                interface.view();
                break;
            case 4:
                interface.remove();
                break;
            default:
                interface.page = 0;
                break;
        }
        cout << endl << endl << "~~~~~~~~~~" << endl << endl << endl;
    }
    
    return 0;
}
