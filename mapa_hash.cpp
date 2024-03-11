#include <iostream>
#include "mapa.h"

int main() {

    map<int, int> myMap(10);

    std::cout << "Insert \n";

    myMap.insert(9, 1);
    myMap.insert(19, 2);
    myMap.insert(29,3);
    myMap.insert(39, 4);
    myMap.insert(49, 5);
    myMap.insert(59, 6);
    myMap.insert(69, 7);
    myMap.insert(79, 8);
    myMap.insert(89, 9);
    myMap.insert(99, 10);
    myMap.insert(109, 11);

 
    std::cout << "Operator [] \n";

    std::cout << myMap[109] << std::endl;
    std::cout << myMap[69] << std::endl;

    std::cout << "Iterator \n";

   map<int, int>::iterator it = myMap.begin();
   map<int, int>::iterator endit = myMap.end();

   while (++it != endit) {
        std::cout << it->klucz << " , " << it->wartosc << std::endl;
    };

    return 0;
}


