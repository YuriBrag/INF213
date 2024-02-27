#include "MyStack.h"
#include <iostream>
#include <string>

using namespace std;

bool validaEntrada() {
	MyStack<char> s;

	char c;
	while(cin >> c) {
		switch(c) {
			case '(':
			case '[':
			case '{':
				s.push(c);
				break;
			case ')':
				if(s.empty() || s.top()!='(')
					return false;
				s.pop();
				break;
			case ']':
				if(s.empty() || s.top()!='[')
					return false;
				s.pop();
				break;
			case '}':
				if(s.empty() || s.top()!='{')
					return false;
				s.pop();
				break;
		}
	}
	return s.empty();
}

int main() {
	if(validaEntrada()) cout << "OK\n";
	else cout << "nao ok\n";
}