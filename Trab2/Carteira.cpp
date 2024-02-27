#include <iostream>
#include <string>
#include "Carteira.h"

Carteira::Carteira(){};

Carteira::Carteira(std::string ticker, int quantidade, int valorTotal, int dividendos) {
    this-> ticker = ticker;
    this-> quantidade = quantidade;
    this-> valorTotal = valorTotal;
    this-> dividendos = dividendos;
}

Carteira::~Carteira() {
}

void Carteira::setListQtd(MyList2<MyList2<Carteira>::iterator>::iterator &listQtd){
    this->listQtd = listQtd;
}
void Carteira::setListVal(MyList2<MyList2<Carteira>::iterator>::iterator &listVal){
    this->listVal = listVal;
}
void Carteira::setListDiv(MyList2<MyList2<Carteira>::iterator>::iterator &listDiv){
    this->listDiv = listDiv;
}

std::string Carteira::rTicker() const {
    return this-> ticker;
}

int Carteira::rQuantidade() const {
    return this-> quantidade;
}

int Carteira::rValor() const {
    return this-> valorTotal;
}

int Carteira::rDividendos() const {
    return this-> dividendos;
}

MyList2<MyList2<Carteira>::iterator>::iterator Carteira::rListQtd() {
    return this->listQtd;
};

MyList2<MyList2<Carteira>::iterator>::iterator Carteira::rListVal() {
    return this->listVal;
};

MyList2<MyList2<Carteira>::iterator>::iterator Carteira::rListDiv() {
    return this->listDiv;
};

void Carteira::atQuantidade(int newQtd) {
    this-> quantidade = newQtd;
}

void Carteira::atItQtd(MyList2<MyList2<Carteira>::iterator>::iterator newItQtd) {
    this->listQtd = newItQtd;
}

void Carteira::atValor(int newVal) {
    this-> valorTotal =  newVal;
}

void Carteira::atItVal(MyList2<MyList2<Carteira>::iterator>::iterator newItVal) {
    this-> listVal = newItVal;
}

void Carteira::atDividendos(int newDiv) {
    this-> dividendos = newDiv;
}

void Carteira::atItDiv(MyList2<MyList2<Carteira>::iterator>::iterator newItDiv) {
    this->listQtd = newItDiv;
}