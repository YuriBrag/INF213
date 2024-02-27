#include <iostream>
#include "Mediana.h"
#include <algorithm>
using namespace std;


void Mediana::insere(int el) {

    if(metadeMenor.size() == 0){
        metadeMenor.pushMenor(el);
    }
    else if(metadeMaior.size() == 0){
        if(el < metadeMenor.top()){
            metadeMaior.pushMaior(metadeMenor.top());
            metadeMenor.popMenor();
            metadeMenor.pushMenor(el);
        }
        else{
            metadeMaior.pushMaior(el);
        }
    }
    else if(metadeMenor.size() == metadeMaior.size()){
        if(el > metadeMaior.top()){
            metadeMenor.pushMenor(metadeMaior.top());
            metadeMaior.popMaior();
            metadeMaior.pushMaior(el);
        }
        else{
            metadeMenor.pushMenor(el);
        }
    }
    else{
        if(el >= metadeMenor.top()){
            metadeMaior.pushMaior(el);
        }
        else{
            metadeMaior.pushMaior(metadeMenor.top());
            metadeMenor.popMenor();
            metadeMenor.pushMenor(el);
        }
    }
}

int Mediana::getMediana() {
	if(metadeMenor.size() > metadeMaior.size()){
        return metadeMenor.top();
    }
    else{
        return (metadeMenor.top()+metadeMaior.top())/2;
    }
}