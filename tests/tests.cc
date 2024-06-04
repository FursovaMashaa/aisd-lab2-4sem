#pragma once
#include<hashtable.cpp>
using namespace HashTable;
int main() {
    MyUnorderedMap <char, int> a;
    a.insert('N', 15);
    a.print();
    cout << "--------------" << endl;
    MyUnorderedMap <int, int> b(10);
    b.insert(1, 15);
    b.insert(1, 9);
    b.print();
    cout << "--------------" << endl;
    MyUnorderedMap <char, int> c;
    c.insert('N', 15);
    c.insert('M', 1);
    c.insert_or_assign('X', 14);
    c.print();
    cout << "------------" << endl;
    MyUnorderedMap<char, int> k;
    k.insert('N', 15);
    k.insert('M', 14);
    k.insert('A', 1);
    bool result1 = k.contains(1);
    cout << "Contains 1: " << result1 << endl;
    cout << "------------" << endl;
    MyUnorderedMap<int, int> p(10);
    cout << p.size() << endl;
    cout << "------------" << endl;
    MyUnorderedMap<int, int> q;
    q.insert(1, 1);
    q.insert(2, 148);
    q.insert(3, -5);
    q.insert(4, 15);
    q.print();
    cout << boolalpha << "Result of erasing key 100: " << q.erase(100) << endl;
    cout << "------------" << endl;
    MyUnorderedMap<int, int> l(10);
    l.insert(1, 1);
    l.insert(2, 148);
    l.insert(41, 15);
    l.insert(4, -5);
    l.print();



    cout << "--------------" << endl;
    string str1 = "Hello";
    string str2 = "Hello";

    unsigned char hash_str1 = Pearson_hash(str1);
    cout << "Hash of str1: " << static_cast<int>(hash_str1) << endl;

    bool result = hash_compare(str2, hash_str1);
    if (result) {
        cout << "Hashes comparison result: true (hashes match)" << endl;
    }
    else {
        cout << "Hashes comparison result: false (hashes do not match)" << endl;
    }


    return 0;
}