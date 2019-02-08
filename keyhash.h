// cribbed from stackoverflow.com
// https://stackoverflow.com/questions/8317508/hash-function-for-a-string
#pragma once
#include "defines.h"
#include <string>
// Default hash function class
template <typename K, size_t tableSize>
struct KeyHash {
    unsigned long operator()(const K &key) const
    {
        std::string s = reinterpret_cast<std::string>(key);
        unsigned long h = FIRSTH;
        while (*s) {
            h = (h * A) ^ (s[0] * B);
            ++s;
        }
        return h % tableSize;
    }
};