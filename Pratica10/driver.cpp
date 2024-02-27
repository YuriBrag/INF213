#include <iostream>
#include "MyQueue.h"
#include "MyStack.h"

using namespace std;

// Insira aqui o codigo para a etapa 1....

//Voce pode adicionar includes como o abaixo...
//#include "MyStack.h"

void etapa1()
{
	MyQueue<int> queue;
	MyStack<int> stack;
	int n;

	for (int i = 0; i < 6; i++)
	{
		cin >> n;
		queue.push(n);
		stack.push(n);
	}

	while (!stack.empty())
	{
		cout << stack.top() << " ";
		stack.pop();
	}
	cout << '\n';

	while (!queue.empty())
	{
		cout << queue.front() << " ";
		queue.pop();
	}
	cout << '\n';
}

//---------------------------------------

// Insira aqui o codigo para a etapa 2....

void etapa2()
{
	MyStack<char> stack;
	char c;

	while (cin >> c)
	{
		if (c == '(' || c == '[' || c == '{')
		{
			stack.push(c);
		}
		if (c == ')')
		{
			if (stack.size() >= 1 && stack.top() == '(')
			{
				stack.pop();
			}
			else
			{
				cout << "Inconsistente" << '\n';
				return;
			}
		}
		if (c == ']')
		{
			if (stack.size() >= 1 && stack.top() == '[')
			{
				stack.pop();
			}
			else
			{
				cout << "Inconsistente" << '\n';
				return;
			}
		}
		if (c == '}')
		{
			if (stack.size() >= 1 && stack.top() == '{')
			{
				stack.pop();
			}
			else
			{
				cout << "Inconsistente" << '\n';
				return;
			}
		}
	}
	if (stack.empty())
	{
		cout << "Consistente" << '\n';
	}
	else
	{
		cout << "Inconsistente" << '\n';
	}
}

//---------------------------------------

// Insira aqui o codigo para a etapa 3....

// #include "MedianaLenta.h" //use essa implementacao para fazer os primeiros testes (com o calculo lento da mediana...)
#include "Mediana.h" //descomente esta linha para utilizar sua classe mais eficiente!
void etapa3()
{
	//descomente o codigo abaixo ao fazer a etapa 3
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

//---------------------------------------

int main()
{
	int etapa;
	cin >> etapa;
	switch (etapa)
	{
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