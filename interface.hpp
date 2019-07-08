#ifndef interface_hpp
#define interface_hpp

#include <stdio.h>
#include <vector>

namespace Interface{
    class Interface;
}
class Interface::Interface {
public:
    Interface(void);
    std::vector<int> contacts;
    short int page;
    void list();
    void search();
    void edit();
    void add();
    void remove();
};

#endif
