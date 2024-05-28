#pragma once
#include<hashtable.cpp>
using namespace HashTable;
int main() {
    int tableSize = 10; 
    int a = 1;
    int b = 100; 

    HashTable::MyUnorderedMap<int, int> myMap(tableSize, a, b);
    std::cout << "Initial Map:" << std::endl;
    myMap.print(); 

    
    return 0;
}