// Cribbed from github and changed to suit the needs of scrabble cheat
// 
// After my changes this is no longer a traditional HashMap.
//
// A traditional HashMap doesn't allow duplicate keys but allows duplicate values. 
// That means A single key can't contain more than 1 value but more 
// than 1 key can contain a single value. HashMap allows null key 
// also but only once and multiple null values.
// 
// My implementation, in order to suit the needs of scrabble cheat,
// searches the linked list to see if a HashNode already exists 
// with the given value. If found, it does nothing. If not, it adds 
// a new HashNode with the given key and value to the linked  list.
// -EJW 02/13/2019
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
        // no need to destroy table
    }

    void get(const K &key, V &value) {
        string skey = static_cast<string>(key);
        unsigned long hashValue = hashFunc(skey.c_str());
        HashNode<K, V> *entry = table[hashValue];

        while (entry != NULL) {
            if (entry->getKey() == skey) {
                //concatenate the values contain by this one key
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
        // This is where the difference is, I check against 
        // the Value instead of the Key.
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