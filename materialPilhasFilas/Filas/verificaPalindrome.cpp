#include "MyQueue.h"
#include "MyStack.h"
#include <iostream>
using namespace std;


//Exemplo: verificar se uma string eh palindrome (ignorando espaco, newlines, etc)
//Obs: ha formas muito melhores de fazer isso (sem filas/pilhas)
int main() {
	MyQueue<char> q;
	MyStack<char> s;

	char c;
	while(cin >> c) {
		q.push(c);
		s.push(c);
	}

	while(!q.empty()) {
		if(q.front()!=s.top()) {
			//elementos diferentes...
			cout << "Nao e' uma palindrome..." << endl;
			return 0;
		}
		q.pop();
		s.pop();
 	}
 	cout << "Eh uma palindrome" << endl;
}