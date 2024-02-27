/*
TAD MyVec
- Representa uma lista implementada por contiguidade
- Interface similar a da classe Vector do STL
- Criado por Salles Magalhaes em 19/02/2018

*/

#ifndef MyVec_H__
#define MyVec_H__

#include <iostream>
#include <string>
#include <ostream>
#include <cassert>


//Excessao usada pela classe MyVec
class MyVecException {
private:
	std::string msg;
public:
	MyVecException (const std::string &msg0): msg(msg0) { }
	const std::string & what() const { return msg; }
};


template<class T>
class MyVec {
public:
	template<class T2>
	friend std::ostream& operator<<(std::ostream &, const MyVec<T2> &);

	//construtores/destrutures/etc
	MyVec();
	MyVec(int n, const T&init=T());

	//destrutor
	~MyVec() { destroy(); };

	//Construtor de copia
	MyVec(const MyVec &);
	MyVec & operator=(const MyVec &);

	//funcoes de acesso
	T &operator[](int pos) {return data[pos];}
	const T &operator[](int pos) const {return data[pos];}
	void push_back(const T&);
	void resize(int newSize);
	void insert(const T&,int pos);
	void clear();
	int eraseMatchingElements(const T&);
	void sortedInsert(const T&);

	void empty() const {return size() == 0;};
	int size() const {return dataSize;};
	

private:
	T *data; //declare o membro de dados data, que devera armazenar os elementos da lista
	int dataSize; //quantos elementos ha na lista?
	int dataCapacity; //quantos elementos atualmente cabem na lista? 

	void create();
	void destroy();
	void resizeCapacity(int newCapacity);
	
};

// template<class T>
// int MyVec<T>::eraseMatchingElements(const T&elem) {
// 	int cont = 0;
// 	if (dataSize == 0) {
// 		return 0;
// 	}
// 	for (int i = 0; i < size(); i++) {
// 		while (data[i] == elem) {
// 			data[i] = ' ';
// 			for (int j = i; j < (size() -1); j++) {
// 				swap(data[j], data[j++]);
// 			}
// 			cont++;
// 			i--;
// 		}
// 		dataSize -= cont;
// 	}
	
// 	return cont;
// }

template<class T>
void MyVec<T>::push_back(const T&elem) { //funcao que coloca um elemento na ultima pos
	// Implemente esta funcao! (nao reutilize a funcao "insere")
	if(size() == dataCapacity) { //se o vetor tiver cheio
		if(dataCapacity==0)
			resizeCapacity(1);
		else
			resizeCapacity(2*dataCapacity); //duplica o tamanho do vetor
	}
	data[size()] = elem; //bota o elemento na ultima pos
	dataSize++;
	// insert(elem, size());
}

template<class T>
void MyVec<T>::resize(int newSize) {
	//so aloca mais memoria se passar pra funcao um tamanho maior do que se tem disponivel
	if(newSize >= dataCapacity) { //primeiro temos que realocar o vector...
		resizeCapacity(newSize); //para o resize vamos usar o tamanho exato caso seja necessario realocar o vector..
	}
	for(int i=dataSize;i<newSize;i++) { //preencha a parte "extra" do vector com valores "em branco"
		data[i] = T();
	}
	dataSize = newSize;
}

//insere o elemento na posicao pos e move os elementos ja presentes no vetor
// pos pode ser:
//   uma posicao apos o final do vetor (para inserir na ultima posicao) 
//   ou uma posicao ja existente (nesse caso os elementos nessa posicao e apos ela serao movidos "para a frente")
template<class T>
void MyVec<T>::insert(const T&elem,int pos) {
	if(pos > dataSize || pos < 0) {
		throw MyVecException("Erro na funcao insert: posicao invalida");
	}

	if(dataSize == dataCapacity) { //preciso redimensionar?
		if(dataCapacity ==0) //Exercicio: Por que e' preciso testar isso?
			resizeCapacity(1);
		else
			resizeCapacity(dataCapacity*2);
	}	

	for(int i=dataSize;i>pos;i--)
		data[i] = data[i-1];
	data[pos] = elem;
	dataSize++;
}

template<class T>
void MyVec<T>::clear() {
	destroy();
	create();
}

template<class T>
void MyVec<T>::sortedInsert(const T&elem){
	int posInsert = 0;
	int i;

	//[a, c, d, e], quer inserir o 'b'
	//faz b é menor que a? nao, prox pos
	//b é menor que c? sim. salva a pos do c
	//se o elem que se quer inserir for maior que todos na lista o i seria igual ao dataSize, entao se insere o elem na pos dataSize
	//joga na func insert o elem na posInsert caso nao seja o maior da lista

	for(i = 0; i < dataSize; i++) {
		if(data[i] > elem){ //guarda a ultima pos em que o elem é menor que aquele analisado da lista
			posInsert = i;
			break;
		}
	}
	if (i == dataSize) {
		insert(elem, i);
	}
	else {
		insert(elem, posInsert);
	}
}

template<class T> 
int MyVec<T>::eraseMatchingElements(const T&elem) { //Complexidade: O(n), sendo n a quantidade de elementos de data[]. A alocação extra de memoria poderia ajudar a copiar os elemento de data, para um auxiliar, retidando aquele que se quer
	int cont = 0;
	int j = 0;

	if (size() == 0) {
		return 0;
	}

	//[a, b, c, d, e], quer retirar o 'b'
	//a == b? nao, j é diferente de i? nao, entao j++(j = 1) e i++(i = 1)
	//b == b? sim, entao cont++ e i++(i = 2)
	//c == b? nao, j é diferente de i? sim entao copia o elm pos2 para o pos1, j++(j = 2) e i++(i = 3)...

	for(int i = 0; i < dataSize; i++){
		if(data[i] == elem) { //se acha o elem atrasa o j uma pos em relacao ao i, ja que nao entra no else 
			cont++;
		}
		else { 
			if(i != j) { //se ja passou do elemento 1 pos significa que o j esta atrasado em relacao ao i 1 pos ou seja pegara o o elem da prox pos pra colocar na pos anterior
				data[j] = data[i];
			}
			j++;
		}
	}
	dataSize = dataSize - cont; //teoricamente os elementos continuam no final da lista, mas como se diminui dataSize 
	return cont;
}

template<class T>
void MyVec<T>::resizeCapacity(int newCapacity) {
	//implemente esta funcao
	//Ela deve redimensionar o vetor de modo que ele tenha capacidade newCapacity
	//Se newCapacity for menor do que a capacidade atual voce devera ignorar a chamada a esta funcao (i.e., nunca reduziremos a capacidade do vetor)
	//Nao se esqueca de liberar (deletar) a memoria que nao for mais necessaria (para evitar vazamentos de memoria)
	//Exemplo de execucao:
	//data=[1,2,3,,], dataSize=3, dataCapacity=5 (vetor de capacidade 5, com 3 elementos ocupados)
	//se chamarmos resizeCapacity(10), os membros de dados deverao ter os seguintes valores:
	//data=[1,2,3,,,,,,,], dataSize=3, dataCapacity=10

	if (newCapacity > dataCapacity) {
		T* dataAux = data;
		delete []data;
		data = new T[newCapacity];

		for (int i = 0; i < dataSize; i++) {
			data[i] = dataAux[i];
		}
		delete []dataAux;
		dataCapacity = newCapacity;
 	}
	else {
		return;
	}
}

template<class T>
void MyVec<T>::destroy() {
	delete []data;
	dataSize = dataCapacity = 0;
}

template<class T>
void MyVec<T>::create() {
	data = NULL;
	dataSize = dataCapacity = 0;
}

template<class T>
MyVec<T>::MyVec() {
	create();
}

template<class T>
MyVec<T>::MyVec(int n, const T&init) {
	//Implemente esta funcao:
	//Cria um vetor de tamanho e capacidade n, onde todos os n elementos valem "init"
	dataCapacity = n;
	dataSize = n;
	data = new T[n];

	for (int i = 0; i < n; i++) {
		data[i] = init;
	}	
}


//Construtor de copia
template<class T>
MyVec<T>::MyVec(const MyVec &other) {
	//Implemente esta funcao
	//Dica: nao duplique codigo! (esta funcao deve ser escrita utilizando apenas 2 linhas de codigo!)
	create();
	*this = other;
}

template<class T>
MyVec<T> & MyVec<T>::operator=(const MyVec &other) {
	if(this==&other) return *this; 
	destroy(); //Exercicio: por que precisamos disso?
	dataCapacity = other.dataCapacity;
	dataSize = other.dataSize;
	//data = other.data; //por que nao podemos fazer isso?
	data = new T[dataCapacity];
	for(int i=0;i<dataSize;i++) data[i] = other.data[i];
	return *this;
}

template<class T2>
std::ostream& operator<<(std::ostream &out, const MyVec<T2> &v) {
	out << "Size: " << v.size() << "\n";
	out << "Capacity: " << v.dataCapacity << "\n";
	for(int i=0;i<v.size();i++) out << v.data[i] << " ";
	out << "\n";
	return out;
}

#endif