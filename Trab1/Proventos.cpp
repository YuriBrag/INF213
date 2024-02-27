#include <iostream>
#include <string>
#include "Proventos.h"

Proventos::Proventos(){};

Proventos::Proventos(std::string data, std::string ticker, int valor) {
    this-> data = data;
    this-> ticker = ticker;
    this-> valor = valor;
}

Proventos::~Proventos() {
}

std::string Proventos::rData() const {
    return this-> data;
}

std::string Proventos::rTicker() const {
    return this-> ticker;
}

int Proventos::rValor() const {
    return this-> valor;
}