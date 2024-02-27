#include <list>
#include <iostream>
#include "MyHashMap.h"
using namespace std;

#include <string>
using namespace std;

//functor que calcula o hash de um numero inteiro i
class MyIntHash {
public:
	unsigned operator()(unsigned i) const { //nesse exemplo, temos que hash(i) = i
		return i;
	}
};

int main() {
	MyHashMap<int,string,MyIntHash > map;
	map.set(1230, "Jose da Silva");
	map.set(1391, "Joaquim");
	map.set(9211, "Maria Silva");
	map.set(79, "Fernando Ferreira");
	map.set(98, "Arthur Bernardes");
	map.set(96, "Salles Magalhaes");
	map.set(6, "Abc da Silva");
	map.set(22, "Renata Gomes");
	map.set(123, "Patricia Sousa");
	map.set(1234, "Ligia Soares");
	map.imprime();

	cout << "Quantas pessoas com matricula 1234? " << map.count(1234) << endl;
	cout << "Quantas pessoas com matricula 1? " << map.count(1) << endl;
	cout << "Quem tem matricula 96? " << map.getValue(96) << endl;
	cout << "Quem tem matricula 6?" << map.getValue(6) << endl;
	cout << "Quem tem matricula 1230?" << map.getValue(1230) << endl;
}