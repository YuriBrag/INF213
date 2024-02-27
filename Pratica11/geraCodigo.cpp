#include <iostream>
#include <string>
#include "MyMap.h"

int main() {
    MyMap <string, int> list;
    std::string word;
    int ind = 0; //ou size

    while (cin >> word) {
        if (list.count(word) == 0) { //se fosse size teria q ser list[word] = list.size()-1, pois ao inserir a word no list aumenta o size antes e atribuiria ao indice 0 o numero 1, portanto
            list[word] = ind;
            ind++;
        }
        std::cout << word << " " << list[word] << '\n';
    }

    return 0;
}