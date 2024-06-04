#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <exception>
using namespace std;

namespace HashTable{
    template <typename K, typename T>
    class MyUnorderedMap {
    private:
        const int default_size = 15;
        enum State { empty = 0, exists = 1, deleted = 2 };

        template <typename K, typename T>
        struct Pair {
            K key;
            T value;
            State state;
            Pair() : key(K()), value(T()), state(empty) {}
            void print() const {
                if (state == exists)
                    cout << "Key: " << key << " | Value: " << value << endl;
            }
        };

        double loadFactor = 0.7;
        size_t tableSize;
        vector<Pair<K, T>> table;

        int hashFunction(K key)const {
            return key % table.size();

        }
        void rehash() {
            vector<Pair<K, T>> newTable;
            newTable.resize((int)(table.size() * 2 + 1));
            for (auto& c : table) insert(c.key, c.value);
            table = newTable;
        }

    public:
        MyUnorderedMap() : tableSize(0) {
            table.resize(default_size);
        }
        MyUnorderedMap(size_t size) : tableSize(0) {
            table.resize(size);
        }


        MyUnorderedMap(const MyUnorderedMap<K,T>& other):table(other.table), tableSize(other.tableSize){}

        ~MyUnorderedMap() {
            table.clear();
            tableSize = 0;
        }

        MyUnorderedMap<K, T>& operator=(const MyUnorderedMap<K, T>& other){
            if (this != other) {
                table = other.table;
                tableSize = other.tableSize;
            }
            return *this;
        }
        
        void print() const {
            for (auto& c: table){
                c.print();
            }
        }

        void insert(const K& key, const T& value) {
            size_t index = hashFunction(key);
            int i = 1;
            if (search(key) != nullptr) return;
            while (table[index].state != empty) {
                index = (index + i) % table.size();
                if (index == hashFunction(key)) return;
                i++;
            }
            table[index].key = key;
            table[index].value = value;
            table[index].state = exists;
            tableSize++;
            if (tableSize / table.size() >= loadFactor) rehash();
        }

        void insert_or_assign(K key, T value) {
            size_t index = hashFunction(key);
            if (table[index].state != exists) {
                table[index].state = exists;
                tableSize++;
                if (tableSize / table.size() >= 0.7) rehash();
            }
                table[index].key = key;
                table[index].value = value;
        }


        T* search(K key) {
            size_t index = hashFunction(key);
            if (table[index].key ==key) return &table[index].value;
            else{
                int i = 1;
                while(table[index].state != empty){
                    index = (index + 1) % tableSize;
                    if (index == hashFunction(key)) return nullptr;
                    if (table[index].key == key)return &table[index].value;
                    i++;
                }
            
            }
            return nullptr; 
        }


        bool erase(K key) {
			if (!search(key)) return false;
			size_t index = hashFunction(key);
			if (table[index].key == key) {
				table[index].state = deleted;
				table[index].key = K();
				table[index].value = T();
				tableSize--;
				return true;
			}
			else {
				int i = 1;
				while (true) {
					index = (index + i) % table.size();
					if (table[index].key == key) {
                        table[index].state = deleted;
                        table[index].key = K();
                        table[index].value = T();
						tableSize--;
						return true;
					}
					if (index == hashFunction(key)) return false;
				}
				i++;
			}
		}

        size_t count()const {
            return tableSize;
        }

        size_t size()const {
            return table.size();
        }

        bool contains(T value) {
            for (auto& c: table) {
                if (c.state==exists) {
                    if(c.value==value) return true;
                }
            }
            return false;
        }

        size_t count(K key) {
            size_t cnt = 0;
            for (auto& c : table) {
                if (c.state == exists) {
                    if (hashFuncion(c.key) == hashFunction(key)) cnt++;
                }
            }
            return cnt;
        }
        
    };
}

unsigned char Pearson_hash(string str) {
    static const unsigned char T[256] = {
            98,  6, 85,150, 36, 23,112,164,135,207,169,  5, 26, 64,165,219,
            61, 20, 68, 89,130, 63, 52,102, 24,229,132,245, 80,216,195,115,
            90,168,156,203,177,120,  2,190,188,  7,100,185,174,243,162, 10,
            237, 18,253,225,  8,208,172,244,255,126,101, 79,145,235,228,121,
            123,251, 67,250,161,  0,107, 97,241,111,181, 82,249, 33, 69, 55,
            59,153, 29,  9,213,167, 84, 93, 30, 46, 94, 75,151,114, 73,222,
            197, 96,210, 45, 16,227,248,202, 51,152,252,125, 81,206,215,186,
            39,158,178,187,131,136,  1, 49, 50, 17,141, 91, 47,129, 60, 99,
            154, 35, 86,171,105, 34, 38,200,147, 58, 77,118,173,246, 76,254,
            133,232,196,144,198,124, 53,  4,108, 74,223,234,134,230,157,139,
            189,205,199,128,176, 19,211,236,127,192,231, 70,233, 88,146, 44,
            183,201, 22, 83, 13,214,116,109,159, 32, 95,226,140,220, 57, 12,
            221, 31,209,182,143, 92,149,184,148, 62,113, 65, 37, 27,106,166,
            3, 14,204, 72, 21, 41, 56, 66, 28,193, 40,217, 25, 54,179,117,
            238, 87,240,155,180,170,242,212,191,163, 78,218,137,194,175,110,
            43,119,224, 71,122,142, 42,160,104, 48,247,103, 15, 11,138,239
    };
    unsigned char hash = 0;
    for (char c : str) {
        hash = T[hash ^ static_cast<unsigned char>(c)];
    }
    return hash;
}
bool hash_compare(string str, int hash) {
    int str_hash = Pearson_hash(str);
    if (str_hash == hash) {
        return true;
    }
    return false;
}
