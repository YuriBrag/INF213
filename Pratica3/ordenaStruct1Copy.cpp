#include <algorithm>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

void insertionSort(int *v, int n)
{
	for (int i = 1; i < n; i++)
	{
		// o arranjo entre as posicoes [0,i) já está ordenado
		int elemInserir = v[i];
		int j = i - 1;
		while (j >= 0 && v[j] > elemInserir)
		{
			v[j + 1] = v[j];
			j--;
		}
		v[j + 1] = elemInserir;
	}
}

struct Pessoa
{
	string nome;
	int cpf;
	double altura;
};

void ordenaPessoasCPF(Pessoa *pessoas, int i, int j)
{
	if (pessoas[i].cpf < pessoas[j].cpf)
	{
		swap(pessoas[i], pessoas[j]);
	}
}

void ordenaPessoasNome(Pessoa *pessoas, int n)
{
	Pessoa aux;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (pessoas[i].nome < pessoas[j].nome) //em string ja se compara tamaho como ordem alfabética
			{
				// aux.nome = pessoas[i].nome;
				// aux.cpf = pessoas[i].cpf;
				// aux.altura = pessoas[i].altura;

				// pessoas[i].nome = pessoas[j].nome;
				// pessoas[i].cpf = pessoas[j].cpf;
				// pessoas[i].altura = pessoas[j].altura;

				// pessoas[j].nome = aux.nome;
				// pessoas[j].cpf = aux.cpf;
				// pessoas[j].altura = aux.altura;

				swap(pessoas[i], pessoas[j]);
			}
			if (pessoas[i].nome == pessoas[j].nome)
			{
				ordenaPessoasCPF(pessoas, i, j);
			}
		}
	}
}

void ordenaPessoas(Pessoa *pessoas, int n)
{
	ordenaPessoasNome(pessoas, n);
}

/*
Exemplo de entrada:
5
Dbc 123 1.8
Abc 194 1.7
Abc 125 1.9
Teste 100 1.1
Alto 300 3.2

Saida esperada:
Abc 125 1.9
Abc 194 1.7
Alto 300 3.2
Dbc 123 1.8
Teste 100 1.1
*/

//Não modifique nada daqui para baixo...
int main(int argc, char **argv)
{
	//O arquivo de entrada contém um numero n.
	//A seguir, há n linhas cada uma contendo o nome, cpf e altura de uma pessoa (separados por um espaço em branco)
	//O nome eh sempre composto de um unico token
	int n;
	cin >> n;
	Pessoa *pessoas = new Pessoa[n];
	for (int i = 0; i < n; i++)
	{
		cin >> pessoas[i].nome >> pessoas[i].cpf >> pessoas[i].altura;
	}

	ordenaPessoas(pessoas, n);

	//imprime a saída ordenada
	for (int i = 0; i < n; i++)
	{
		cout << pessoas[i].nome << " " << pessoas[i].cpf << " " << pessoas[i].altura << '\n';
	}

	delete[] pessoas;
	return 0;
}