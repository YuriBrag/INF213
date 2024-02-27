#include <iostream>
#include <string>
#include "Dividendos.h"

Dividendos::Dividendos(){};

Dividendos::Dividendos(std::string data, std::string ticker) {
    this-> data = data;
    this-> ticker = ticker;
}

Dividendos::~Dividendos() {
}

std::string Dividendos::rData() const {
    return this-> data;
}

std::string Dividendos::rTicker() const {
    return this-> ticker;
}

bool Dividendos::operator>(const Dividendos &other) const {
    if (this->ticker == other.ticker)
    {
        return this->data > other.data;
    }
    return this->ticker > other.ticker;
}

bool Dividendos::operator<(const Dividendos &other) const {
    if (this->ticker == other.ticker)
    {
        return this->data < other.data;
    }
    return this->ticker < other.ticker;
}