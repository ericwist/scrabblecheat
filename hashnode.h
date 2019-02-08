// cribbed from github and changed to suit the needs of scrabble cheat
#pragma once
#include <cstddef>

// Hash node class template
template <typename K, typename V>
class HashNode {
public:
    HashNode(const K &key, const V &value) :
        m_key(key), m_value(value), m_next(nullptr) {
    }

    K getKey() const {
        return m_key;
    }
    
    V getValue() const {
        return m_value;
    }

    void setValue(V value) {
        m_value = value;
    }

    HashNode *getNext() const {
        return m_next;
    }

    void setNext(HashNode *next) {
        m_next = next;
    }

private:
    // key-value pair
    K m_key;
    V m_value;
    // next bucket with the same key
    HashNode *m_next;
    // disallow copy and assignment
    HashNode(const HashNode &);
    HashNode & operator=(const HashNode &);
};