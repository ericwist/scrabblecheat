// scrabblecheat.cpp : Scrabble cheat app that uses a hashmap.
// @author: Eric Wistrand
// @date: 02/07/2019

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <locale>
#include <io.h>
#include "defines.h"
#include "hashmap.h"

using namespace std;

// stores the key temporarily before use
static char key_alpha[26] = { '1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1' };

static inline bool FileExists(const std::string& filename)
{

    if (_access(filename.c_str(), 0) != -1) {
        // file exists
        return true;
    }
    else {
        // file doesn't exist
        return false;
    }
}

static inline void remove_chars_if_not(string& s, const string& allowed) {
    s.erase(remove_if(s.begin(), s.end(), [&allowed](const char& c) {
        return allowed.find(c) == string::npos;
    }), s.end());
}

struct MyKeyHash {
    unsigned long operator()(const char* k) const
    {
        unsigned long h = FIRSTH;
        while (*k) {
            h = (h * A) ^ (k[0] * B);
            ++k;
        }
        return h % tableSize;
    }
};

int main()
{
    std::string filename = "scrabble.txt";
    if (!FileExists(filename))
    {
        std::cout << "The file " << filename << " was not found!\n";
    }

    std::ifstream file("scrabble.txt");
    std::string word;
    HashMap<string, string, tableSize, MyKeyHash> hmap;
    std::cout << "Please wait loading scrabble cheat database...\n";
    while (getline(file, word)) {
        // only allow lower case
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        // remove any characters not in the range we want...
        remove_chars_if_not(word, "abcdefghijklmnopqrstuvwxyz");
        // clear the array to all 1's (0x31)
        memset(&key_alpha, 0x31, 26);
        // build the key
        for (unsigned int i = 0; i < word.length(); ++i) {
            key_alpha[word[i]-97] += 1;
        }
        //add key pair
        hmap.put(key_alpha, word);
#if _DEBUG
        std::cout << word << "\n";
#endif
    }
    //todo: dump all the keys words in order when in _DEBUG
    std::cout << std::endl;

    string input;
    while (input != "stop")
    {
        cout << "Enter letters to find matching words.\nEnter 'stop' to stop the process:\n";
        cin >> input;
        {
            // change entry to all lower case
            transform(input.begin(), input.end(), input.begin(), ::tolower);
            // remove any characters not in the range we want...
            remove_chars_if_not(input, "abcdefghijklmnopqrstuvwxyz");
            // clear the array to all 1's (0x31)
            memset(&key_alpha, 0x31, 26);
            // build the key
            for (unsigned int i = 0; i < input.length(); ++i) {
                key_alpha[input[i] - 97] += 1;
            }
            // get the value from the key
            string valout;
            hmap.get(key_alpha,valout);
            cout << "KEY: " << key_alpha << " VALUE(S): " << valout << "\n";
            //now test the remove
            //hmap.remove(alpha);
        }

    }


}

//Here are some links to some hash map code / discussions:
#if 0
https://medium.com/@aozturk/simple-hash-map-hash-table-implementation-in-c-931965904250
https://github.com/Tessil/ordered-map
https://gist.github.com/aozturk/2368896
http://www.algolist.net/Data_structures/Hash_table/Simple_example
#endif