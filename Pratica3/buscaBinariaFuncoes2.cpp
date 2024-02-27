#include <algorithm>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>

//Vamos usar variaveis globais nesse caso...
//Isso nao é uma boa pratica, mas vai facilitar no seu entendimento/implementacao da busca binaria
long long int taxaVideo, taxaDownload, tamanho;

//Essa funcao devera retornar true se for possível 
//assistir a um vídeo de "tamanho" segundos, que gasta taxaVideo bytes por segundo para ser assistido
//supondo que sua internet consegue baixar taxaDownload bytes por segundo.
//tempoCarregamento indica quanto tempo voce irá aguardar para começar assistir ao vídeo
//Implemente esta funcao

bool consigoAssistirSemPausas(long long int tempoCarregamento)
{
	long long int bytes = 0;
	bytes += taxaDownload * tempoCarregamento;

	for(long long int i = 0; i < tamanho; i++) {
		bytes += taxaDownload;
		bytes -= taxaVideo;
	}

	if(bytes >= 0) {
		return true;
	}
	else {
		return false;
	}
}

int buscaSeq(int begin,int end) {
	for (int i = begin; i <= end;i++) {
		if (consigoAssistirSemPausas(i)) {
			return i;
		}
	}
	return -1;
}


int main() 
{
	std::cin >> taxaVideo >> taxaDownload >> tamanho;
	std::cout << buscaSeq(0, 25000000) << std::endl;
}