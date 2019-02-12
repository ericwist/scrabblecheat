// cribbed from github and changed to suit the needs of scrabble cheat
#pragma once
#include "hashnode.h"
#include "defines.h"
#include <cstddef>
#include <string>

using namespace std;

// Hash map class template
template <typename K, typename V, size_t tableSize, typename F = KeyHash<K, tableSize> >
class HashMap {
public:
    HashMap() :
        table(),
        hashFunc()
    {
    }

    ~HashMap() {
        // destroy all buckets one by one
        for (int i = 0; i < tableSize; ++i) {
            HashNode<K, V> *entry = table[i];
            while (entry != nullptr) {
                HashNode<K, V> *prev = entry;
                entry = entry->getNext();
                SAFE_DELETE(prev);
            }
            table[i] = nullptr;
        }
        // table is declared static, no need to destroy it
    }

    void get(const K &key, V &value) {
        string skey = static_cast<string>(key);
        unsigned long hashValue = hashFunc(skey.c_str());
        HashNode<K, V> *entry = table[hashValue];

        while (entry != NULL) {
            if (entry->getKey() == skey) {
                if (value.length() > 0) {
                    value += (", " + entry->getValue());
                } else {
                    value = entry->getValue();
                }
            }
            entry = entry->getNext();
        }
    }

    void put(const K &key, const V &value) {
        string skey = static_cast<string>(key);
        unsigned long hashValue = hashFunc(skey.c_str());
        HashNode<K, V> *prev = nullptr;
        HashNode<K, V> *entry = table[hashValue];

        while (entry != nullptr && entry->getValue() != value) {
            prev = entry;
            entry = entry->getNext();
        }

        if (entry == nullptr) {
            entry = new HashNode<K, V>(skey, value);
            if (prev == nullptr) {
                // insert as first bucket
                table[hashValue] = entry;
            }
            else {
                prev->setNext(entry);
            }
        }
    }

    void remove(const K &key) {
        string skey = static_cast<string>(key);
        unsigned long hashValue = hashFunc(skey.c_str());
        HashNode<K, V> *entry = table[hashValue];

        while (entry != nullptr) {
            HashNode<K, V> *temp = entry->getNext();
            SAFE_DELETE(entry);
            entry = temp;
        }
        table[hashValue] = nullptr;
    }

private:
    // hash table
    HashNode<K, V> *table[tableSize];
    F hashFunc;
    // disallow copy and assignment
    HashMap(const HashMap & other);
    const HashMap & operator=(const HashMap & other);
};