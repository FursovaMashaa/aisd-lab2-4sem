#pragma once
#include <iostream>
#include <vector>
#include <random>
using namespace std;

namespace HashTable{
    template <typename K, typename T>
    struct Pair {
        K key;
        T value;
        bool filled;
        Pair() : key(K()), value(T()), filled(false) {}
        Pair(K _key, T _value) : key(_key), value(_value), filled(false) {}
    };
    template <typename K, typename T>
    class MyUnorderedMap {
    private:
        int tableSize;
        vector<Pair<K, T>> table;

        int hashFunction(const K& key) {
            return key % tableSize;
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

        bool operator==(const MyUnorderedMap& other) const {
            if (tableSize != other.tableSize)
                return false;

            for (int i = 0; i < tableSize; i++) {
                if (table[i].filled != other.table[i].filled ||
                    table[i].key != other.table[i].key ||
                    table[i].value != other.table[i].value)
                    return false;
            }

            return true;
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
            table[index] = Pair<K, T>(key, value);
            table[index].filled = true;
        }

        void insert_or_assign(K key, T value) {
            int index = hashFunction(key);
            if (table[index].filled && table[index].key == key) {
                table[index].value = value;
            }
            else {
                if (!table[index].filled) {
                    table[index].filled = true;
                }
                table[index].key = key;
                table[index].value = value;
            }
        }
        T search(const K& key) {
            int index = hashFunction(key);
            while (table[index].filled) {
                if (table[index].key == key) {
                    return table[index].value;
                }
                index = (index + 1) % tableSize;
            }
            throw std::out_of_range("Key not found");
        }


        bool erase(const K& key) {
            int index = hashFunction(key);
            int originalIndex = index;
            while (table[index].filled) {
                if (table[index].key == key) {
                    table[index].filled = false;
                    return true;
                }
                index = (index + 1) % tableSize;
                if (index == originalIndex) {
                    break; 
                }
            }
            return false;
        }

        int count(const K& key) {
            int count = 0;
            for (const auto& element : table) {
                if (element.filled && element.key == key) {
                    count++;
                }
            }
            return count;
        }

        bool contains(T value) {
            for (int i = 0; i < tableSize; i++) {
                if (table[i].filled && table[i].value == value) {
                    return true;
                }
            }
            return false;
        }
        
    };
}
