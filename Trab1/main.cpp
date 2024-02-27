#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <string>
#include "Cotacoes.h"
#include "Proventos.h"
#include "Carteira.h"

void imprimeCotacoesDia(std::string const &cabecalho, Cotacoes const *listaCotacoes, std::string const wData, int const n) { //funcao auxiliar chamada por "valor"
    int i = 0;
    
    if (cabecalho == "mostrarCabecalhos") {
        std::cout << "Data: " << wData << '\n';
        std::cout << "Ticker        Valor\n";
    }
    for (i = 0; i < n; i++) {
        if(listaCotacoes[i].rData() == wData) {
            std::cout <<  listaCotacoes[i].rTicker() << "          ";
            std::cout << listaCotacoes[i].rValor() << '\n';
        }
    } 
}

std::string inverteDataInt(std::string const &dataStr) { //funcao que utiliza substrings para retornar uma data no formato de aaaa/mm/dd para facilitar a comparação de datas posteriormente
    std::string ano, mes, dia;

    ano = dataStr.substr(6, 4);
    mes = dataStr.substr(3, 2);
    dia = dataStr.substr(0, 2);

    return ano + '/' + mes + '/' + dia;
}

void valor(std::string const &cabecalho, Carteira const *listaCarteira, Cotacoes const *listaCotacoes, std::string const &wData, const int nCarteira, const int nCotacoes) { //funcao chamada por "valor"
    int i = 0;
    int montante = 0;

    if (cabecalho == "mostrarCabecalhos") {
    
        std::cout << "Data: " << wData << '\n';
        std::cout << "Ticker" << std::right << std::setw(11) << "Quantidade" << std::right << std::setw(14) << "Compra" << std::right << std::setw(14) << "Dividendo" << std::right << std::setw(14) << "Valor" <<'\n';
    }

    if (cabecalho == "mostrarCabecalhos" || cabecalho == "naoMostrarCabecalhos") {
        for (i = 0; i < nCarteira; i++) {
            for (int j = 0; j < nCotacoes; j++) {
                if (listaCotacoes[j].rData() == wData && listaCotacoes[j].rTicker() == listaCarteira[i].rTicker()) { //if para imprimir apenas as acoes que tem ticker igual ao da carteira na busca sequencial
                    std::cout << std::left << std::setw(7) <<  listaCarteira[i].rTicker();
                    std::cout << std::right << std::setw(10) << listaCarteira[i].rQuantidade();
                    std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)listaCarteira[i].rValor()/100 ;
                    std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)listaCarteira[i].rDividendos()/100;
                    std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)((float)listaCarteira[i].rQuantidade() * (float)listaCotacoes[j].rValor()/100) << '\n';
                    montante += listaCarteira[i].rQuantidade() * listaCotacoes[j].rValor();
                }
            }
        }
        std::cout << "Valor total da carteira:" << std::right << std::setw(35)  <<  std::fixed << std::setprecision(2) << (float)montante/100 << '\n';
        
        if (cabecalho == "mostrarCabecalhos") {
            std::cout << '\n';
        }
    }
    else{
        for (i = 0; i < nCarteira; i++) {
            for (int j = 0; j < nCotacoes; j++) {
                if (listaCotacoes[j].rData() == wData && listaCotacoes[j].rTicker() == listaCarteira[i].rTicker()) {
                    montante += listaCarteira[i].rQuantidade() * listaCotacoes[j].rValor();
                }
            }
        }
        std::cout << std::fixed << std::setprecision(2) << std::fixed << std::setprecision(2) << (float)montante/100 << '\n';
    }
    
}

void merge(Cotacoes *v, int p, int q, int r, std::string const &fator) {
    int tam = r-p;
    Cotacoes *aux = new Cotacoes[tam];
    int i = p; //cursor 1
    int j = q; //cursor 2
    int k = 0; //cursor para aux
    while(i < q && j < r) {
        if (fator == "data") {
            if (inverteDataInt(v[i].rData()) <= inverteDataInt(v[j].rData())) {
                aux[k++] = v[i++];
            }
            else {
                aux[k++] = v[j++];
            }
        }

        if (fator == "ticker")
        {
            if (v[i].rTicker() <= v[j].rTicker()) {
                aux[k++] = v[i++];
            }
            else {
                aux[k++] = v[j++];
            }
        }
    }
    while(i < q)
        aux[k++] = v[i++];
    while(j < r)
        aux[k++] = v[j++];
    for(k = 0; k < tam; k++)
        v[p+k] = aux[k];    
    delete []aux;
}


void mergeSort(Cotacoes *v, int p, int r, std::string const &fator) {
    if (p < r-1) {
        int meio = (p+r) / 2;
        mergeSort(v, p, meio, fator);
        mergeSort(v, meio, r, fator);
        merge(v, p, meio, r, fator); 
    }
}


void mergeSort(Cotacoes *v, int n, std::string const &fator) { //merge para ordenar cotacoes recebe um fator de ordenação para comparar
    mergeSort(v, 0, n, fator);
}


int buscaBin(Cotacoes const *array, int begin, int end, std::string const &chave1, std::string const &chave2, int nCot) {
	
	int meio = (end - begin)/2 + begin;

    if (begin > end) { 
        return -1;
    }
    if (meio > nCot-1) { //tentando acessar pos invalida
        return -1;
    }
    

    if (inverteDataInt(array[meio].rData()) == chave2 && array[meio].rTicker() == chave1) { 
        return meio;
    }

    if (inverteDataInt(array[meio].rData()) < chave2) { 
        return buscaBin(array, meio + 1, end, chave1, chave2, nCot);
    }
    
    if (inverteDataInt(array[meio].rData()) > chave2) { 
        return buscaBin(array, begin, meio - 1, chave1, chave2, nCot);
    } 

    if (inverteDataInt(array[meio].rData()) == chave2) {
        if (array[meio].rTicker() < chave1) {
            return buscaBin(array, meio + 1, end, chave1, chave2, nCot);
        }
        else{
            return buscaBin(array, begin, meio - 1, chave1, chave2, nCot);
        }
    }
    return 0;
}

void valorFast(std::string const &cabecalho, Carteira const *listaCarteira, Cotacoes *listaCotacoes, std::string const &wData, const int nCarteira, const int nCotacoes) {
    
    int j;
    int montante = 0;

    if (cabecalho == "mostrarCabecalhos") {
        std::cout << "Data: " << wData << '\n';
        std::cout << "Ticker" << std::right << std::setw(11) << "Quantidade" << std::right << std::setw(14) << "Compra" << std::right << std::setw(14) << "Dividendo" << std::right << std::setw(14) << "Valor" <<'\n';
    }

    if (cabecalho == "mostrarCabecalhos" || cabecalho == "naoMostrarCabecalhos") {
        for (int i = 0; i < nCarteira; i++) {
            
            j = buscaBin(listaCotacoes, 0, nCotacoes - 1, listaCarteira[i].rTicker(), inverteDataInt(wData), nCotacoes); //faz uma busca binaria para cada ticker da carteira e data requisitada
            if (j != -1) { //imprime
                std::cout << std::left << std::setw(7) <<  listaCarteira[i].rTicker();
                std::cout << std::right << std::setw(10) << listaCarteira[i].rQuantidade();
                std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)listaCarteira[i].rValor()/100;
                std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)listaCarteira[i].rDividendos()/100;
                std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)((float)listaCarteira[i].rQuantidade() * (float)listaCotacoes[j].rValor()/100) << '\n';
                montante += listaCarteira[i].rQuantidade() * listaCotacoes[j].rValor(); //soma a variavel de valor total aquele valor total da acao
            }
        }
        std::cout << "Valor total da carteira:" << std::right << std::setw(35) << std::fixed << std::setprecision(2) << (float)montante/100 << '\n';
        
        if (cabecalho == "mostrarCabecalhos") { 
            std::cout << '\n';
        }
    }
    else { //se for o modo compacta
        for (int i = 0; i < nCarteira; i++) {
            for (int j = 0; j < nCotacoes; j++) {
                if (listaCotacoes[j].rData() == wData && listaCotacoes[j].rTicker() == listaCarteira[i].rTicker()) {
                    montante += listaCarteira[i].rQuantidade() * listaCotacoes[j].rValor();
                }
            }
        }
        std::cout << std::fixed << std::setprecision(2) << std::fixed << std::setprecision(2) << (float)montante/100 << '\n';
    }
}

void merge(Carteira *v, int p, int q, int r, std::string const &fator) {
    int tam = r-p;
    Carteira *aux = new Carteira[tam];
    int i = p; 
    int j = q; 
    int k = 0; 
    while(i < q && j < r) {
        if (fator == "ticker") { //ordena em relacao ao ticker
            if (v[i].rTicker() <= v[j].rTicker()) {
                aux[k++] = v[i++];
            }
            else {
                aux[k++] = v[j++];
            }
        }

        if (fator == "preco") { //ordena em relacao ao preco
            if (v[i].rValor() > v[j].rValor()) {
                aux[k++] = v[i++];
            }
            else {
                aux[k++] = v[j++];
            }
        }

        if (fator == "quantidade") { //ordena em relacao a quantidade
            if (v[i].rQuantidade() > v[j].rQuantidade()) {
                aux[k++] = v[i++];
            }
            else {
                aux[k++] = v[j++];
            }
        }

        if (fator == "dividendo") { //ordena em relacao ao dividendo
            if (v[i].rDividendos() > v[j].rDividendos()) {
                aux[k++] = v[i++];
            }
            else {
                aux[k++] = v[j++];
            }
        }

        if (fator == "dividendoticker") { //ordena em relacao ao dividendo com criterio de desempate como sendo o ticker
            if (v[i].rDividendos() == v[j].rDividendos()) {
                if (v[i].rTicker() <= v[j].rTicker()) {
                    aux[k++] = v[i++];
                }
                else {
                    aux[k++] = v[j++];
                }
            }
            
            if (v[i].rDividendos() > v[j].rDividendos()) {
                aux[k++] = v[i++];
            }
            if (v[i].rDividendos() < v[j].rDividendos()) {
                aux[k++] = v[j++];
            }
        }
    }
    while(i < q){
        aux[k++] = v[i++];
    }
    while(j < r){
        aux[k++] = v[j++];
    }
    for(k = 0; k < tam; k++){
        v[p+k] = aux[k];
    }    
    delete []aux;
}


void mergeSort(Carteira *v, int p, int r, std::string const &fator) {
    if (p < r-1) {
        int meio = (p+r) / 2;
        mergeSort(v, p, meio, fator);
        mergeSort(v, meio, r, fator);
        merge(v, p, meio, r, fator); 
    }
}


void mergeSort(Carteira *v, int n, std::string const &fator) { //merge para ordenar carteira recebe um fator de ordenação para comparar
    mergeSort(v, 0, n, fator);
}


void ordena(Carteira *listaCarteira, int const nCarteira, std::string const &fator) {
    if (fator == "ticker") { //passa qual fator requisitado de ordenacao para o mergeSort 
        mergeSort(listaCarteira, nCarteira, fator);
    }
    if (fator == "preco") {
        mergeSort(listaCarteira, nCarteira, fator);
    }
    if (fator == "quantidade") {
        mergeSort(listaCarteira, nCarteira, fator);
    }
    if (fator == "dividendo") {
        mergeSort(listaCarteira, nCarteira, fator);
    }
    if (fator == "dividendoticker") {
        mergeSort(listaCarteira, nCarteira, fator);
    }
    
}

int buscaBinMimax(Cotacoes const *array, int begin, int end, std::string const &chave, int nCotacoes, std::string fator) { //busca binaria especifica para a funcao mimax, o vetor de cotacoes ja fora ordenado anteriormente
	if (begin > end){
		return -1;
    }

    if(begin == end ) { //quando begin == end significa que o elemento da pos meio é a mais proxima ou igual a chave procurada e meio = a begin, portanto:
        if (chave == inverteDataInt(array[begin].rData())) { //se o elemento begin é o procurado retorna sua posicao
            return begin;
        }
        
        if (begin < nCotacoes-1 && chave > inverteDataInt(array[begin].rData()) &&  fator == "min") { //se a data procurada for maior que a data da pos meio/begin e a prox posicao nao extrapolar o tam do vetor, retora a primaira data maior que a chave
            return begin + 1;
        }
        else if (begin > 0 && chave < inverteDataInt(array[begin].rData()) &&  fator == "max") { //de forma semelhante caso o fator seja "max" verifica se meio/begin nao é primeira pos do vetor e se a data da pos meio for maior que a procurada retorna a primeira data menor
            return begin - 1;
        }
        else {
            return begin;
        }
    }
    
	int meio = (end-begin)/2 + begin;

	if (inverteDataInt(array[meio].rData()) == chave && fator == "min"){
		while (meio >= 0 && chave == inverteDataInt(array[meio].rData())) { //a buscabin original nao retorna necessariamente a primeira chave encontrada, para isso, se encontrar uma é, necessario percorrer o vetor ate a primeira data valida
            meio--;
        }
        return meio + 1;
    }
    if (inverteDataInt(array[meio].rData()) == chave && fator == "max"){
		while (meio < nCotacoes && chave == inverteDataInt(array[meio].rData())) { //de forma semelhante ao fator "min", caso o fator seja "max" ira percorrer o vetor ate a ultima data procurada
            meio++;
        }
        return meio - 1;
    }
	if (inverteDataInt(array[meio].rData()) > chave){
		return buscaBinMimax(array,begin, meio-1, chave, nCotacoes, fator);
    }
	return buscaBinMimax(array,meio+1, end, chave, nCotacoes, fator); 	
}


void mimax(Cotacoes const *listaCotacoes, Carteira const *listaCarteira, std::string const &data1,  std::string const &data2, int const nCotacoes, int const nCarteira, std::string cabecalho){ //recebe a data na forma AAAAMMDD em int
    std::string dataValMin;
    std::string dataValMax;
    std::string currData;
    
    int posDatMin = 0;
    int posDatMax = 0;
    int montante = 0;

    posDatMin = buscaBinMimax(listaCotacoes, 0, nCotacoes-1, inverteDataInt(data1), nCotacoes, "min"); //acha a pos da primeira data do intervalo
    posDatMax = buscaBinMimax(listaCotacoes, 0, nCotacoes-1, inverteDataInt(data2), nCotacoes, "max"); //acha a pos da ultima data do intevalo
 
    int montanteMax = -1;
    int montanteMin = 100000001;

    for (int i = posDatMin; i < posDatMax; i++) {

        currData = listaCotacoes[i].rData(); //seta a data que vai ser analisada 

        if (i + 1 < nCotacoes && listaCotacoes[i].rData() != listaCotacoes[i+1].rData()) { //se a proxima data analisada for diferente da atual significa que é necessario fazer a analise do montante
            if (montante > montanteMax) { //se o montante dos valores das cotacoes naquela data for maior que o ate entao analisado atualiza o montante max e tambem atualiza a variavel que armazena em qual data foi aquele montante
                montanteMax = montante;
                dataValMax = currData;
            }
            if (montante < montanteMin) { //de forma semelhante faz-se para o montante min ate entao
                montanteMin = montante;
                dataValMin = currData;
            }
            montante = 0; //como sera analisado uma proxima data é necessario resetar o montante
        }
        
        for (int j = 0; j < nCarteira; j++) { 
            if (listaCotacoes[i].rTicker() == listaCarteira[j].rTicker()) { //acrescenta ao montante o valor total da acao de curr data
                montante = montante + (listaCotacoes[i].rValor() * listaCarteira[j].rQuantidade());
            }
        }
    }
    
    if (montante > montanteMax) { //é necessario verificar se a ultima data é a max ou a minima
        montanteMax = montante;
        dataValMax = currData;
    }
    if (montante < montanteMin) {
        montanteMin = montante;
        dataValMin = currData;
    }
    //imprime os minimos e maximos no intervalo
    if (cabecalho == "mostrarCabecalhos") {
       std::cout << "Minimos e maximos no intervalo: " << data1 << " a " << data2 << '\n';
    }
    
    if (cabecalho == "mostrarCabecalhos" || cabecalho == "naoMostrarCabecalhos") {
        std::cout << "Valor minimo no dia " << dataValMin << ":" << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float) montanteMin/100 <<'\n'; 
        std::cout << "Valor maximo no dia " << dataValMax << ":"<< std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float) montanteMax/100 << '\n';
        
        if (cabecalho == "mostrarCabecalhos") {
            std::cout << '\n';
        }
    }
    else {
        std::cout << std::fixed << std::setprecision(2) << (float) montanteMin/100 <<'\n'; 
        std::cout << std::fixed << std::setprecision(2) << (float) montanteMax/100 << '\n';
    }
    
    
}

void merge(Proventos *v, int p, int q, int r, std::string const &fator) {
    int tam = r-p;
    Proventos *aux = new Proventos[tam];
    int i = p; //cursor 1
    int j = q; //cursor 2
    int k = 0; //cursor para aux
    while(i < q && j < r) {
        if (fator == "data") {
            if (inverteDataInt(v[i].rData()) <= inverteDataInt(v[j].rData())) {
                aux[k++] = v[i++];
            }
            else {
                aux[k++] = v[j++];
            }
        }

        if (fator == "ticker")
        {
            if (v[i].rTicker() <= v[j].rTicker()) {
                aux[k++] = v[i++];
            }
            else {
                aux[k++] = v[j++];
            }
        }
    }
    while(i < q)
        aux[k++] = v[i++];
    while(j < r)
        aux[k++] = v[j++];
    for(k = 0; k < tam; k++)
        v[p+k] = aux[k];    
    delete []aux;
}


void mergeSort(Proventos *v, int p, int r, std::string const &fator) {
    if (p < r-1) {
        int meio = (p+r) / 2;
        mergeSort(v, p, meio, fator);
        mergeSort(v, meio, r, fator);
        merge(v, p, meio, r, fator); 
    }
}


void mergeSort(Proventos *v, int n, std::string const &fator) { //merge para ordenar proventos recebe um fator de ordenação para comparar
    mergeSort(v, 0, n, fator);
}

int buscaBinDividendos(Proventos const *array, int begin, int end, std::string const &chave, int nProventos, std::string fator) {
	if (begin > end){
		return -1;
    }
    
	int meio = (end-begin)/2 + begin;

    if (meio > nProventos - 1) {
        return -1;
    }

	if (array[meio].rTicker() == chave && fator == "min"){
		while (meio >= 0 && chave == array[meio].rTicker()) {
            meio--;
        }
        return meio + 1;
    }

	if (array[meio].rTicker() > chave){
		return buscaBinDividendos(array,begin, meio-1, chave, nProventos, fator);
    }
	return buscaBinDividendos(array,meio+1, end, chave, nProventos, fator); 	
}

void dividendos(Proventos *listaProventos, Carteira *listaCarteira, std::string const &data1, std::string const &data2, int nProventos, int nCarteira, std::string cabecalho) {
    int j = 0;
    int montante = 0;
    int valorTotal = 0;
    
    if (cabecalho == "mostrarCabecalhos") {
        std::cout << "Dividendos no intervalo: " << data1 << " a " << data2 << '\n';
        std::cout << "Ticker Quantidade        Compra     Dividendo    Div.inter." << '\n';
    }
    if (cabecalho == "mostrarCabecalhos" || cabecalho == "naoMostrarCabecalhos") {
        for (int i = 0; i < nCarteira; i++) {
            j = buscaBinDividendos(listaProventos, 0, nProventos - 1, listaCarteira[i].rTicker(), nProventos, "min"); //busca a primeira acao de cada acao da carteira

            if(j != -1){
                while (listaCarteira[i].rTicker() == listaProventos[j].rTicker() && 
                inverteDataInt(listaProventos[j].rData()) <= inverteDataInt(data2) && 
                inverteDataInt(listaProventos[j].rData()) >= inverteDataInt(data1)) { //como a lista de proventos esta ordenada com tickers iguais em bloco e nesse bloco ordenado por data vamos somando ao montante 
                    montante += (listaCarteira[i].rQuantidade() * listaProventos[j].rValor()); //seus valores ate que a analise mude de acao ou a data saia do intervalo requisitado
                    j++;
                }
            }
        
        valorTotal += montante;
        
            
        std::cout << std::left << std::setw(7) << listaCarteira[i].rTicker();
        std::cout << std::right << std::setw(10) << listaCarteira[i].rQuantidade();
        std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)listaCarteira[i].rValor()/100;
        std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)listaCarteira[i].rDividendos()/100;
        std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)montante/100 << '\n';
        montante = 0;
        }
        std::cout << "Total de dividendos:" << std::right << std::setw(39) << (float)valorTotal/100 << '\n';
        
        if (cabecalho == "mostrarCabecalhos") {
            std::cout << '\n';
        }
    }
    else{
        for (int i = 0; i < nCarteira; i++) {
            j = buscaBinDividendos(listaProventos, 0, nProventos - 1, listaCarteira[i].rTicker(), nProventos, "min");
            if(j != -1){
                while (listaCarteira[i].rTicker() == listaProventos[j].rTicker() && inverteDataInt(listaProventos[j].rData()) <= inverteDataInt(data2) && inverteDataInt(listaProventos[j].rData()) >= inverteDataInt(data1)) {
                    montante += (listaCarteira[i].rQuantidade() * listaProventos[j].rValor());
                    j++;
                }
            }
        
        valorTotal += montante;
        montante = 0;
        }
        std::cout << std::fixed << std::setprecision(2) << (float)valorTotal/100 << '\n';
    }
}

void aporte(std::string const &cabecalho, Carteira *listaCarteira, Cotacoes const *listaCotacoes, std::string const &wData, const int nCarteira, const int nCotacoes, int valAporte) {
    int j;
    int posAcaoValMin = -1;
    int menorValDasAcoes = 100000001; //acao de menor valor totao de cotacao
    int valUniAcao = valAporte; //valor de unidade de acao da acao com menor valor total de cotacao
    int valEfetAport = 0;

    int qtdCart[nCarteira]; //variavel para salvar a quantidade de tickers da carteira antes do aporte

    for (int i = 0; i < nCarteira; i++){
        qtdCart[i] = listaCarteira[i].rQuantidade();
    }

    Cotacoes *listaAuxCot = new Cotacoes[nCarteira]; //cria um vetor auxiliar de cotaçoes para guardar apenas as cotaçoes necessarias das acoes da carteira na data requisitada
    
    for (int i = 0; i < nCarteira; i++) { //insere numa lista de cotacoes apenas as necessarias para a operacao
        j = buscaBin(listaCotacoes, 0, nCotacoes, listaCarteira[i].rTicker(), inverteDataInt(wData), nCotacoes);

        if (j == -1) { //se nao encontra acao da carteira insere uma nula no auxiliar, para nao deixar espaco de memoria vazio
            Cotacoes auxCot("null", "null", 0);
            listaAuxCot[i] = auxCot;
        }
        else { //copia para o vetor auxiliar a cotacao necessaria
            Cotacoes auxCot = listaCotacoes[j];
            listaAuxCot[i] = auxCot;
        }
    }

    while (true) {

        for (int i = 0; i < nCarteira; i++) {
            if (listaAuxCot[i].rTicker() != "null") {
                if ((listaAuxCot[i].rValor() * listaCarteira[i].rQuantidade()) < menorValDasAcoes) {
                    menorValDasAcoes = listaAuxCot[i].rValor() * listaCarteira[i].rQuantidade();
                    valUniAcao = listaAuxCot[i].rValor();
                    posAcaoValMin = i;
                }
            }
        }
        if (valAporte < valUniAcao) { //se nao tiver mais dinheiro de aporte para comprar a acao mais barata para
            break;
        }
        else {
            valAporte -= valUniAcao; 
            listaCarteira[posAcaoValMin].attQuantidade(1); //metodo que atualiza o valor da acao da carteira
            listaCarteira[posAcaoValMin].attValorTotal(valUniAcao); //metodo que acrescenta 1 unidade a acao 
            valEfetAport += valUniAcao; //adiciona a compra ao valor efetivamente aportado
            menorValDasAcoes += valUniAcao; //valor menor antigo é acrescido da compra
        }
    }
    
    //imprime os dados de aporte
    if (cabecalho == "mostrarCabecalhos") {
        std::cout << "Dados do aporte:" << '\n';
        std::cout << "Ticker Quantidade         Valor" << '\n';
    }
    if (cabecalho == "mostrarCabecalhos" || cabecalho == "naoMostrarCabecalhos") {
        for (int i = 0; i < nCarteira; i++) {
            if (listaAuxCot[i].rTicker() != "null" && (listaCarteira[i].rQuantidade() - qtdCart[i]) > 0) {
                int qtdAcoes = listaCarteira[i].rQuantidade() - qtdCart[i];
                std::cout << std::left << std::setw(7)<< listaAuxCot[i].rTicker();
                std::cout << std::right << std::setw(10) << qtdAcoes;
                std::cout << std::right << std::setw(14) <<  (float)(listaAuxCot[i].rValor() * qtdAcoes)/100 << '\n';
            }
        }
        std::cout << "Total aportado:" << std::setw(16) << std::fixed << std::setprecision(2) << (float)valEfetAport/100 << '\n';
        if (cabecalho == "mostrarCabecalhos") {
            std::cout << '\n';
        }
    }
    else {
        std::cout << std::fixed << std::setprecision(2) << (float)valEfetAport/100 << '\n';
    }

    delete [] listaAuxCot;
         
}


int main() {
    int nCotacoes;
    std::string cabecalho;

    std::cin >> nCotacoes;

    Cotacoes *listaCotacoes = new Cotacoes[nCotacoes]; //alocacao dinamica para lista de cotacoes

    for (int i = 0; i < nCotacoes; i++) { //le as cotacoes
        std::string data;
        std::string ticker;
        int valor1;
        int cents;
        char pt;
        int valor;
        std::cin >> data >> ticker >> valor1 >> pt >> cents;

        valor = valor1 * 100 + cents;
        
        Cotacoes aux(data, ticker, valor);

        listaCotacoes[i] = aux;

    }

    int nProventos;

    std::cin >> nProventos;

    Proventos *listaProventos = new Proventos[nProventos]; //alocacao dinamica para lista de cotacoes

    for (int i = 0; i < nProventos; i++) { //le os dividendos/proventos
        std::string data;
        std::string ticker;
        int valor1;
        int cents;
        char pt;
        int valor;
        std::cin >> data >> ticker >> valor1 >> pt >> cents;

        valor = valor1 * 100 + cents;
        
        Proventos aux(data, ticker, valor);

        listaProventos[i] = aux;
    }

    int nCarteira;

    std::cin >> nCarteira;

    Carteira *listaCarteira = new Carteira[nCarteira]; //alocacao dinamica para lista de cotacoes

    for (int i = 0; i < nCarteira; i++) { //le conteudo da carteira
        std::string ticker;
        int valor1;
        int cents1;
        int valor2;
        int cents2;
        char pt1;
        char pt2;
        int quantidade;
        int valorTotal;
        int dividendos;

        std::cin >> ticker >> quantidade >> valor1 >> pt1 >> cents1 >> valor2 >> pt2 >> cents2;
       
        valorTotal = valor1 * 100 + cents1; //transforma o char em int
        dividendos = valor2 * 100 + cents2;
        Carteira aux(ticker, quantidade, valorTotal, dividendos);

        listaCarteira[i] = aux;
    }
    
    std::cin >> cabecalho;

    std::string func; //que funcao é requisitada

    mergeSort(listaCotacoes, nCotacoes, "ticker"); //ordena a lista de cotacoes em blocos de data e nesses blocos ordenados por ordem alfabetica de ticker
    mergeSort(listaCotacoes, nCotacoes, "data");

    mergeSort(listaProventos, nProventos, "data"); //ordena os proventos em blocos de mesmo ticker e nesses blocos é ordenado por data
    mergeSort(listaProventos, nProventos, "ticker");

    // for (int i = 0; i < nCotacoes; i++) {
    //     std::cout << listaCotacoes[i].rData() << " " << listaCotacoes[i].rTicker() << " " << listaCotacoes[i].rValor() << '\n';
    // }

    // for (int i = 0; i < nCarteira; i++) {
    //     std::cout << listaCarteira[i].rTicker() << " " << listaCarteira[i].rQuantidade() << " " << listaCarteira[i].rValor() << " "<< listaCarteira[i].rDividendos() <<  '\n';
    // }

    // for (int i = 0; i < nProventos; i++) {
    //     std::cout << listaProventos[i].rData() << " " << listaProventos[i].rTicker() << " " << listaProventos[i].rValor() <<  '\n';
    // }


    while (std::cin >> func) {
        //chamada das funcoes
        if (func == "valor") {
            std::string wData; //which data
            std::cin >> wData;
            valor(cabecalho, listaCarteira, listaCotacoes, wData, nCarteira, nCotacoes);
        }
        if (func == "valorFast") {
            std::string wData; //which data
            std::cin >> wData;
            valorFast(cabecalho, listaCarteira, listaCotacoes, wData, nCarteira, nCotacoes);
        }
        if (func == "ordenar") {
            std::string fator;
            std::cin >> fator;
            ordena(listaCarteira, nCarteira, fator);
        }

        if (func == "mimax") {
            std::string data1;
            std::string data2;
            std::cin >> data1 >> data2;

            mimax(listaCotacoes, listaCarteira, data1, data2, nCotacoes, nCarteira, cabecalho);
        }

        if (func == "dividendo") {
            std::string data1;
            std::string data2;

            std::cin >> data1 >> data2;

            dividendos(listaProventos, listaCarteira, data1, data2, nProventos, nCarteira, cabecalho);
        }

        if (func == "aporte") {
            std::string wData;
            int valor;
            int valAporte;
            char pt;
            int cents;
            std::cin >> wData >> valor>> pt >> cents;

            valAporte = valor * 100 + cents;

            aporte(cabecalho, listaCarteira,listaCotacoes, wData,  nCarteira,  nCotacoes, valAporte);
        } 
    }
    
    //deleta os vetores alocados dinamicamente
    delete [] listaCotacoes;
    delete [] listaCarteira;
    delete [] listaProventos;
    return 0;
}