#include <iostream>
#include <string>
#include "Cotacoes.h"

Cotacoes::Cotacoes(){};

Cotacoes::Cotacoes(std::string data, std::string ticker) {
    this-> data = data;
    this-> ticker = ticker;
}

Cotacoes::~Cotacoes() {
}

std::string Cotacoes::rData() const {
    return this-> data;
}

std::string Cotacoes::rTicker() const {
    return this-> ticker;
}

bool Cotacoes::operator<(const Cotacoes &other) const {
    if (this->ticker == other.ticker)
    {
        return this->data < other.data;
    }
    return this->ticker < other.ticker;
}

bool Cotacoes::operator>(const Cotacoes &other) const {
    if (this->ticker == other.ticker)
    {
        return this->data > other.data;
    }
    return this->ticker > other.ticker;
}
