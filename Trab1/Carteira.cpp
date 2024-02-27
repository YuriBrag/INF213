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

void Carteira::attQuantidade(int add) {
    this-> quantidade += add;
}

void Carteira::attValorTotal(int valAdd) {
    this-> valorTotal +=  valAdd;
}