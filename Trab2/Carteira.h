#ifndef Carteira_h
#define Carteira_h

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <string>
#include "MyList2NewIterator.h"

class Carteira {
private:
    std::string ticker;
    int quantidade;
    int valorTotal;
    int dividendos;
    
    //o objeto guardara um iterador para uma lista de iteradores para facilitar a edicao
    MyList2<MyList2<Carteira>::iterator>::iterator listQtd;
    MyList2<MyList2<Carteira>::iterator>::iterator listVal;
    MyList2<MyList2<Carteira>::iterator>::iterator listDiv;

public:
    Carteira();
    Carteira(std::string ticker, int quantidade, int valorTotal, int dividendos);
    ~Carteira();

    //return atributos (metodos gets)
    std::string rTicker() const;
    int rQuantidade() const;
    int rValor() const;
    int rDividendos() const;
    MyList2<MyList2<Carteira>::iterator>::iterator rListQtd();
    MyList2<MyList2<Carteira>::iterator>::iterator rListVal();
    MyList2<MyList2<Carteira>::iterator>::iterator rListDiv();


    //metodo sets
    void setListQtd(MyList2<MyList2<Carteira>::iterator>::iterator &listQtd);
    void setListVal(MyList2<MyList2<Carteira>::iterator>::iterator &listVal);
    void setListDiv(MyList2<MyList2<Carteira>::iterator>::iterator &listDiv);

    //atualiza valores da carteira para aporte
    void atQuantidade(int newQtd);
    void atItQtd(MyList2<MyList2<Carteira>::iterator>::iterator newListQtd);
    void atValor(int newVal);
    void atItVal(MyList2<MyList2<Carteira>::iterator>::iterator newListVal);
    void atDividendos(int newDiv);
    void atItDiv(MyList2<MyList2<Carteira>::iterator>::iterator newListDiv);
};

#endif