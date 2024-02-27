#include "MyStack.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	MyStack<string> s;
	s.push("hello");
	s.push("abc");
	s.push("def");

	cout << "Tamanho: " << s.size() << endl;
	cout << "Acessando a pilha... " << endl;
	while(!s.empty()) {
		cout << s.top() << endl;
		s.pop();
	}
}