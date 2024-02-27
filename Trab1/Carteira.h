#ifndef Carteira_h
#define Carteira_h

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <string>

class Carteira {
private:
    std::string ticker;
    int quantidade;
    int valorTotal;
    int dividendos;
    
public:
    Carteira();
    Carteira(std::string ticker, int quantidade, int valorTotal, int dividendos);
    ~Carteira();

    //return atributos
    std::string rTicker() const;
    int rQuantidade() const;
    int rValor() const;
    int rDividendos() const;

    //atualiza valores da carteira para aporte
    void attQuantidade(int add);
    void attValorTotal(int valAdd);
};

#endif