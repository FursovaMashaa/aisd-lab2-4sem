#pragma once
#include <iostream>
#include <vector>
#include <random>
using namespace std;
namespace HashTable{
    template <typename K, typename T>
    struct Element {
        K key;
        T value;
        bool filled;
        Element() : key(K()), value(T()), filled(false) {}
        Element(K _key, T _value) : key(_key), value(_value), filled(false) {}
    };
    template <typename K, typename T>
    class MyUnorderedMap {
    private:
        int tableSize;
        vector<Element<K, T>> table;

        int hashFunction(const K& key) {
            return std::hash<K>{}(key) % tableSize;
        }

    public:
        MyUnorderedMap(int size) : tableSize(size) {
            table.resize(tableSize);
        }
        MyUnorderedMap(int size, int a, int b) : tableSize(size) {
            table.resize(tableSize);
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> distribution(a, b);
            for (int i = 0; i < size; i++) {
                insert(i, distribution(gen));
            }
        }
        MyUnorderedMap(const MyUnorderedMap& other) {
            tableSize = other.tableSize;
            table = other.table;
        }
        ~MyUnorderedMap() {
            table.clear();
            tableSize = 0;
        }
        
        void print() {
            for (int i = 0; i < tableSize; ++i) {
                if (table[i].filled) {
                    std::cout << "Key: " << table[i].key << ", Value: " << table[i].value << std::endl;
                }
            }
        }
        void insert(const K& key, const T& value) {
            int index = hashFunction(key);
            while (table[index].filled) {
                index = (index + 1) % tableSize;
            }
            table[index] = HashElement<K, T>(key, value);
            table[index].filled = true;
        }

        
    };
}
