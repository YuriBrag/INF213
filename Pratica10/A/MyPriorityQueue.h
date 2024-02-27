#ifndef MyPriorityQueue_H
#define MyPriorityQueue_H

#include "MyVecNewIterator.h"
#include <iostream>
using namespace std;

template<class T>
class MyPriorityQueue {
public:
	void pushMaior(const T&el);
	void pushMenor(const T&el);
	const T & top() const { return heap[ 0 ]; }
	void popMaior();
	void popMenor();

	int size() const { return heap.size(); }

	//para estudar o estado do heap...
	void print()  const ;
private:
	void moveUpMaior(int pos);
	void moveUpMenor(int pos);
	void moveDownMaior(int pos);
	void moveDownMenor(int pos);

	MyVec<T> heap;
};

template<class T>
void MyPriorityQueue<T>::moveDownMenor(int pos) { //refaz o heap da posicao "pos" em diante
	while(2*pos+1 < heap.size()) { //enquanto a posicao atual tiver pelo menos um filho...
		int maiorFilho = 2*pos+1;
		if(2*pos+2 < heap.size() && heap[2*pos+2] > heap[maiorFilho]){ //ha um segundo filho e ele eh maior do que o primeiro?
			maiorFilho = 2*pos+2;
		}
		if(heap[pos] > heap[maiorFilho]) {
			return; //nao precisamos continuar... por que?
		} else {
			swap(heap[pos],heap[maiorFilho]); //troque o atual com o maior filho 
			pos = maiorFilho; //repita o processo agora na posicao "maiorFilho"
		}
	}
}

template<class T>
void MyPriorityQueue<T>::moveDownMaior(int pos) { 
	while(2*pos+1 < heap.size()) { 
		int menorFilho = 2*pos+1;
		if(2*pos+2 < heap.size() && heap[2*pos+2] < heap[menorFilho])
			menorFilho = 2*pos+2;
		if(heap[pos] < heap[menorFilho]) {
			return; 
		} else {
			swap(heap[pos],heap[menorFilho]); 
			pos = menorFilho; 
		}
	}
}


//dado um novo elemento (na posicao pos, inicialmente no final) do heap, refaz as propriedades do heap "subindo-o" 
template<class T>
void MyPriorityQueue<T>::moveUpMaior(int pos) { 
	while(pos>=0) {
		int pai = (pos-1)/2; //pai da posicao i...
		if(heap[pos] < heap[pai]) {
			swap(heap[pos],heap[pai]);
			pos = pai;
		}
		else break;
	}	
}

template<class T>
void MyPriorityQueue<T>::moveUpMenor(int pos) { 
	while(pos>=0) {
		int pai = (pos-1)/2; //pai da posicao i...
		if(heap[pos] > heap[pai]) {
			swap(heap[pos],heap[pai]);
			pos = pai;
		}
		else break;
	}	
}


template<class T>
void MyPriorityQueue<T>::pushMaior(const T&elem) {
	//adicione o elemento no final do heap e use moveUp para restaurar as propriedades de heap
	heap.push_back(elem);
	moveUpMaior(heap.size()-1);
}

template<class T>
void MyPriorityQueue<T>::pushMenor(const T&elem) {
	//adicione o elemento no final do heap e use moveUp para restaurar as propriedades de heap
	heap.push_back(elem);
	moveUpMenor(heap.size()-1);
}

template<class T>
void MyPriorityQueue<T>::popMaior() {
	swap(heap[heap.size()-1],heap[0]); //pega o ultimo elemento do heap e coloca-o na primeira posicao
	heap.resize(heap.size()-1); //reduz o tamanho do heap
	moveDownMaior(0); //restaura as propriedades de heap a partir da posicao 0
}

template<class T>
void MyPriorityQueue<T>::popMenor() {
	swap(heap[heap.size()-1],heap[0]); //pega o ultimo elemento do heap e coloca-o na primeira posicao
	heap.resize(heap.size()-1); //reduz o tamanho do heap
	moveDownMenor(0); //restaura as propriedades de heap a partir da posicao 0
}

template<class T>
void MyPriorityQueue<T>::print() const {
	cout << heap << endl;
}


#endif