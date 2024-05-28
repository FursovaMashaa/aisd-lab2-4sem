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

    MyUnorderedMap<int, std::string> map(10);

    map.insert(1, "one");
    map.insert(11, "eleven");
    map.insert(21, "twenty-one");
    map.insert(1, "one");
    map.insert(11, "eleven");
    map.insert(21, "twenty-one");

    std::cout << "Value for key 1: " << map.search(1) << std::endl;
    std::cout << "Value for key 11: " << map.search(11) << std::endl;
    std::cout << "Value for key 21: " << map.search(21) << std::endl;

    std::cout << "Count of elements with key 1: " << map.count(1) << std::endl;
    std::cout << "Count of elements with key 11: " << map.count(11) << std::endl;
    std::cout << "Count of elements with key 21: " << map.count(21) << std::endl;

    
    return 0;
}