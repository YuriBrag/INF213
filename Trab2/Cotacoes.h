#ifndef Cotacoes_h
#define Cotacoes_h

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <string>

class Cotacoes {
private:
    std::string data;
    std::string ticker;
    
public:
    Cotacoes();
    Cotacoes(std::string data, std::string ticker);
    ~Cotacoes();

    //return atributos
    std::string rData() const;
    std::string rTicker() const;

    //funcao de operador
    bool operator<(const Cotacoes &other) const;
    bool operator>(const Cotacoes &other) const;
};

#endif