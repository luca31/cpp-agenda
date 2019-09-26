#include <iostream>
#include <cstdlib>
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
            case 5:
                interface.edit();
                break;
            case 6 :
                interface.search();
                break;
            default:
                interface.page = 0;
                break;
        };
        if(getenv("windir") == NULL){
            system("clear");
        }else{
            system("cls");
        };
        
    }
    
    return 0;
}
