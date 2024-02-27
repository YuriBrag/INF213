#include <algorithm>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>

//Essa funcao devera retornar true se for possível 
//assistir a um vídeo de "tamanho" segundos, que gasta taxaVideo bytes por segundo para ser assistido
//supondo que sua internet consegue baixar taxaDownload bytes por segundo.
//tempoCarregamento indica quanto tempo voce irá aguardar para começar assistir ao vídeo
//Implemente esta funcao

long long int consigoAssistirSemPausas(long long int taxaVideo, long long int taxaDownload, long long int tamanho)
{
    long long int tempoCarregamento = 0;
    while(true)
    {
        long long int bytes = 0;
        bytes += taxaDownload * tempoCarregamento;

	    for(long long int j=0; j < tamanho; j++) {
		    bytes += taxaDownload;
		    bytes -= taxaVideo;
	    }

	    if(bytes >= 0) {
		    break;
        }
        else {
            tempoCarregamento++;
        }
    }
    return tempoCarregamento;
}

int main() 
{
    long long int taxaVideo, taxaDownload, tamanho;

	std::cin >> taxaVideo >> taxaDownload >> tamanho;
	std::cout << consigoAssistirSemPausas(taxaVideo, taxaDownload, tamanho) << std::endl;
}