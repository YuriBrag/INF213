#include <list>
#include <iostream>
using namespace std;

#include <string>
using namespace std;

class Functor1 {
public:
	void operator()() const { 
		cout << "Ola" << endl;
	}
};

class Functor2 {
public:
	void operator()(int x) const { 
		cout << x << endl;
	}
};

class FunctorCompara {
public:
	bool operator()(int a, int b) const { //retorna true sse a<b
		return a<b;
	}
};

class FunctorCompara2 {
public:
	bool operator()(int a, int b) const { //retorna true sse a>b
		return a>b;
	}
};

template <class Func>
void f(const int v1[], const int v2[], int n) {
	Func f; //cria o "objeto funcao"
	for(int i=0;i<n;i++) {
		cout << v1[i] << " " << v2[i] << " " << f(v1[i],v2[i]) << endl;
	}
	cout << endl;
}

template <class T, class Func>
void bubbleSort(T v[],int n, const Func &comparaMenor) {
	while(true) {
		bool trocou = false;
		for(int i=0;i<n-1;i++) {
			if(!comparaMenor(v[i],v[i+1])) {
				swap(v[i],v[i+1]);
				trocou = true;
			}
		}
		if(!trocou) return;
	}		
}

int main() {
	Functor1 f1;
	Functor2 f2;
	f1(); //imprime Ola
	f2(5); //imprime 5

	FunctorCompara menor;
	FunctorCompara2 maior;

	cout << menor(1,5) << endl;
	cout << maior(5,1) << endl;

	int v1[] = {1,5,10};
	int v2[] = {2,8,1};
	f<FunctorCompara>(v1,v2,3); //chama f passando o functor que verifica se o primeiro argumento eh menor do que o segundo...
	f<FunctorCompara2>(v1,v2,3);


	//usando um functor para prover uma funcao de comparacao customizada para um algoritmo de ordenacao...
	cout << "Ordenando em ordem crescente..." << endl;
	bubbleSort(v1,3,FunctorCompara());
	for(int i=0;i<3;i++)
		cout << v1[i] << " ";
	cout << endl;

	cout << "Ordenando em ordem decrescente..." << endl;
	bubbleSort(v1,3,FunctorCompara2());
	for(int i=0;i<3;i++)
		cout << v1[i] << " ";
	cout << endl;
}