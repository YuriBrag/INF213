#include <iostream>
#include <string>
#include "Cotacoes.h"

Cotacoes::Cotacoes(){};

Cotacoes::Cotacoes(std::string data, std::string ticker, int valor) {
    this-> data = data;
    this-> ticker = ticker;
    this-> valor = valor;
}

Cotacoes::~Cotacoes() {
}

std::string Cotacoes::rData() const {
    return this-> data;
}

std::string Cotacoes::rTicker() const {
    return this-> ticker;
}

int Cotacoes::rValor() const {
    return this-> valor;
}