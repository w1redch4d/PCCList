#include "../include/pcclist/pcclist.h"

int main() {
    PCCList::List L = {42, "hello", 3.14};

    // heterogeneous appends
    L.append(13.37);
    L.append(std::string("world"));
    L.append(42);

    // retrieve via operator[]
    int    a = L[0];              
    std::string b = L[1];          
    double c = L[2];               

    std::cout << "0: " << a << "\n"
                << "1: " << b << "\n"
              << "2: " << c << "\n"
              << "length: " << L.size() << "\n";

    for (auto v : L) {
        std::cout << "  - " << v << "\n";
    }

    // assign via operator[]
    L[0] = 100;                   
    L[1] = std::string("world");   

    std::cout << "After assignment:\n" << "0: " << L[0] << "\n"
              << "1: " << L[1] << "\n";

    try {
        auto x = L[5];             
    } catch (const std::out_of_range& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }

    return 0;
}