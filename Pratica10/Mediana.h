#ifndef MEDIANA_H
#define MEDIANA_H

#include <iostream>
#include "MyPriorityQueue.h"
using namespace std;


class Mediana {
public:
	void insere(int el);
	int getMediana();

private:
	MyPriorityQueue<int> metadeMenor;
  	MyPriorityQueue<int> metadeMaior;
};

#endif