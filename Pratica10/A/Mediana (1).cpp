#include <iostream>
#include "Mediana.h"
#include <algorithm>
using namespace std;


void Mediana::insere(int el) {
    if(menores.size() == 0){
        menores.pushMenor(el);
    }else if(maiores.size() == 0){
        if(el < menores.top()){
            maiores.pushMaior(menores.top());
            menores.popMenor();
            menores.pushMenor(el);
        }else{
            maiores.pushMaior(el);
        }
    }else if(menores.size() == maiores.size()){
        if(el > maiores.top()){
            menores.pushMenor(maiores.top());
            maiores.popMaior();
            maiores.pushMaior(el);
        }else{
            menores.pushMenor(el);
        }
    }else{
        if(el >= menores.top()){
            maiores.pushMaior(el);
        }else{
            maiores.pushMaior(menores.top());
            menores.popMenor();
            menores.pushMenor(el);
        }
    }
}

int Mediana::getMediana() {
	if(menores.size() > maiores.size()){
        return menores.top();
    }else{
        return (menores.top()+maiores.top())/2;
    }
}