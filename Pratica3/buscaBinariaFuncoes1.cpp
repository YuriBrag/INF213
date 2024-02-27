#include <algorithm>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

//Vamos usar variaveis globais nesse caso...
//Isso nao é uma boa pratica, mas vai facilitar no seu entendimento/implementacao da busca binaria
int taxaVideo,taxaDownload,tamanho;

//Essa funcao devera retornar true se for possível 
//assistir a um vídeo de "tamanho" segundos, que gasta taxaVideo bytes por segundo para ser assistido
//supondo que sua internet consegue baixar taxaDownload bytes por segundo.
//tempoCarregamento indica quanto tempo voce irá aguardar para começar assistir ao vídeo
//Implemente esta funcao

bool consigoAssistirSemPausas(int tempoCarregamento)
{
	int bytes = 0;
	bytes += taxaDownload * tempoCarregamento; //qtd de bytes necessarios para assistir o video

	for(int i = 0; i < tamanho; i++) //a cada segundo se carrega a taxa de download da internet(+) e se gasta uma parte para carregar o video(-)
	{
		bytes += taxaDownload;
		bytes -= taxaVideo;
	}

	if(bytes < 0) { //se bytes é negativo significa que teria que pausar em algum momento para carregar essa diferenca
		return false;
	}
	else {
		return true;
	}
}

int main() {
	cin >> taxaVideo >> taxaDownload >> tamanho;
	for(int i=0;i<20;i++) {
		bool resposta = consigoAssistirSemPausas(i);
		cout << i << ": " << resposta << "\n";		
	}
}