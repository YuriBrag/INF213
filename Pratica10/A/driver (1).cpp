#include <iostream>
#include "MyQueue.h"
#include "MyStack.h"
#include "Mediana.h"

using namespace std;


// Insira aqui o codigo para a etapa 1....

//Voce pode adicionar includes como o abaixo...
//#include "MyStack.h"


void etapa1() {
	MyStack<int> pilha;
	MyQueue<int> fila;
	int numero;
	for(int i = 0; i < 6; i++){
		cin >> numero;
		fila.push(numero);
		pilha.push(numero);
	}
	for(int i = 0; i < 6; i++){
		cout << pilha.top() << " ";
		pilha.pop();
	}
	cout << "\n";
	for(int i = 0; i < 6; i++){
		cout << fila.front() << " ";
		fila.pop();
	}
	cout << "\n";
	return;
}

//---------------------------------------

// Insira aqui o codigo para a etapa 2....

void etapa2() {
	MyStack<char> pilha;
	char c;
	pilha.push('=');
	while(cin >> c){
		if(c == '(' || c == '[' || c == '{'){
			pilha.push(c);
		} 
		if(c == ')'){
			if(pilha.top() == '('){
				pilha.pop();
			}else{
				cout << "Inconsistente\n";
				return;
			}
		}
		if(c == ']'){
			if(pilha.top() == '['){
				pilha.pop();
			}else{
				cout << "Inconsistente\n";
				return;
			}
		}
		if(c == '}'){
			if(pilha.top() == '{'){
				pilha.pop();
			}else{
				cout << "Inconsistente\n";
				return;
			}
		}
	}
	if(pilha.size() == 1){
		cout << "Consistente\n";
		return;
	}else{
		cout << "Inconsistente\n";
		return;
	}
}

//---------------------------------------

// Insira aqui o codigo para a etapa 3....

void etapa3() {
	Mediana mediana;

	int n,elem;	
	cin >> n;
	for(int i=0;i<n;i++) {
		cin >> elem;
		mediana.insere(elem);
		cout << mediana.getMediana() << " ";
	}
	
	cout << endl;
}

int main() {
	int etapa;
	cin >> etapa;
	switch(etapa) {
		case 1:
			cout << "Etapa 1" << endl;
			etapa1();
			break;
		case 2:
			cout << "Etapa 2" << endl;
			etapa2();
			break;
		case 3:
			cout << "Etapa 3" << endl;
			etapa3();
			break;
	}
}