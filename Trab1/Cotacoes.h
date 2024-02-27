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
    int valor;
    
public:
    Cotacoes();
    Cotacoes(std::string data, std::string ticker, int valor);
    ~Cotacoes();

    //return atributos
    std::string rData() const;
    std::string rTicker() const;
    int rValor() const;
};

#endif