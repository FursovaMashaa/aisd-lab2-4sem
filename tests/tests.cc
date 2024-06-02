#pragma once
#include<hashtable.cpp>
using namespace HashTable;
int main() {
    MyUnorderedMap<int, int> myMap1(10, 5); 
    myMap1.print();

    cout << "--------------" << endl;
    MyUnorderedMap<int, int> myMap(10);

    myMap.insert(1, 10);
    myMap.insert(2, 20);
    myMap.insert(3, 30);
    myMap.insert(4, 40);

    myMap.print();

    MyUnorderedMap<int, int> myMap2 = myMap;

    if (myMap == myMap2) {
        cout << "Maps are equal" << endl;
    }
    else {
        cout << "Maps are not equal" << endl;
    }

    myMap2.insert_or_assign(3, 300);

    if (myMap == myMap2) {
        cout << "Maps are equal" << endl;
    }
    else {
        cout << "Maps are not equal" << endl;
    }

    cout << "--------------" << endl;
    return 0;

}