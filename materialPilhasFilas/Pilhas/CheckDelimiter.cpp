#include "MyStack.h"
#include <iostream>
#include <string>

using namespace std;

/*
Exemplo de aplicacao de pilhas: verificar se os delimitadores "(", ")", "[", "]", "{" e "}"
estao consistentes em uma string (para cada delimitador aberto ha um delimitador fechando
)

Exemplos de entrada consistente: 
8*(a+b+[c+2])
(9+{[][][]() (()) })
(5=1*5)
1+2=100000

Exemplos de entrada inconsistente:
))((
(9+2+(1+1)

*/

bool checkDelim(const string &st) {
	MyStack<char> s;
	for(char c:st) {
		switch(c) {
			case '(':
				s.push(c);
				break;
			case '[':
				s.push(c);
				break;
			case '{':
				s.push(c);
				break;
			case ')':
				if(s.empty() || s.top()!='(') return false;
				s.pop();
				break;
			case ']':
				if(s.empty() || s.top()!='[') return false;
				s.pop();
				break;
			case '}':
				if(s.empty() || s.top()!='{') return false;
				s.pop();
				break;
		}
	}

	return s.empty();
}

int main() {
	string st;
	getline(cin,st);
	if(checkDelim(st)) {
		cout << "Delimitadores ok" << endl;
	} else {
		cout << "Erro nos delimitadores" << endl;
	}
}