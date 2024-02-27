#ifndef Proventos_h
#define Proventos_h

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <string>

class Proventos {
private:
    std::string data;
    std::string ticker;
    int valor;
    
public:
    Proventos();
    Proventos(std::string data, std::string ticker, int valor);
    ~Proventos();

    //return atributos
    std::string rData() const;
    std::string rTicker() const;
    int rValor() const;
};

#endif