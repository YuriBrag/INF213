#ifndef Dividendos_h
#define Dividendos_h

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <string>

class Dividendos {
private:
    std::string data;
    std::string ticker;
    
public:
    Dividendos();
    Dividendos(std::string data, std::string ticker);
    ~Dividendos();

    //return atributos
    std::string rData() const;
    std::string rTicker() const;

    //funcoes de operacao
    bool operator>(const Dividendos &other) const;
    bool operator<(const Dividendos &other) const;
};

#endif