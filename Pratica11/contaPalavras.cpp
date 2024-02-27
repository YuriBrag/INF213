#include <iostream>
#include <string>
#include "MyVecNewIterator.h"
#include "MySet.h"

bool repeate(const MyVec<string> list, std::string word) {
    for (int i = 0; i < list.size(); i++) {
        if (list[i] == word) {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    string tipo = argv[1];

    std::string word;
    int nWords = 0;

    if (tipo == "myvec") {
        MyVec<string> wordsList;

        while (cin >> word) {
            if (wordsList.empty()) {
                wordsList.push_back(word);
            }
            else {
                if (!repeate(wordsList, word)) {
                    wordsList.push_back(word);
                }
            }
            nWords++;
        }
        std::cout << nWords << " " << wordsList.size() << '\n';
    }

    if (tipo == "myset") {
        MySet<string> wordsList;

        while (cin >> word) {
            wordsList.insert(word);
            nWords++;
        }
        std::cout << nWords << " " << wordsList.size() << '\n';
    }
    
    return 0;
}