#include <iostream>
#include <iomanip>
#include <sstream>
#include <cassert>
#include <string>
#include "MyList2NewIterator.h"
#include "MyMap.h"
#include "Cotacoes.h"
#include "Dividendos.h"
#include "Carteira.h"

// void insertCotation() {

// }

std::string inverteData(std::string const &dataStr) { //funcao que utiliza substrings para retornar uma data no formato de aaaa/mm/dd para facilitar a comparação de datas posteriormente
    std::string ano, mes, dia;

    ano = dataStr.substr(6, 4);
    mes = dataStr.substr(3, 2);
    dia = dataStr.substr(0, 2);

    return ano + '/' + mes + '/' + dia;
}

int main() {
    std::string header;
    std::string lineTrash;
    std::string word;

    std::cin >> header;

    MyMap<Cotacoes, int> cotationsTree;

    MyMap<Dividendos, int> dividendosTree;

    MyList2<Carteira> listCarteira; // lista duplamente encadeada que armazena o objeto carteira;

    MyMap<string, MyList2<Carteira>::iterator> carteiraTreeTick; //arvore que armazena a carteira ordenada em relacao ao ticker, e facilita editar o objeto
    MyMap<int, MyList2<MyList2<Carteira>::iterator>> carteiraTreeDiv; //ordena em relacao ao dividendo
    MyMap<int, MyList2<MyList2<Carteira>::iterator>> carteiraTreeVal; //ordena em relacao ao valor
    MyMap<int, MyList2<MyList2<Carteira>::iterator>> carteiraTreeQt;  //ordena em relacao a quantidade


    while (cin >> word) {
        if (word[0] == '/' && word[1] == '/'){
            std::getline(cin, lineTrash); //usado para ignorar os comentarios da entrada
        }
        if (word == "IC") {
            std::string date;
            std::string refDate; //data refatorada
            std::string ticker;
            int value1;
            char dot;
            int cents;
            int value;

            std::cin >> date >> ticker >> value1 >> dot >> cents;

            refDate = inverteData(date);

            Cotacoes genericCotation(refDate, ticker);

            value = value1*100 + cents;

            cotationsTree[genericCotation] = value;

            // std::cout << genericCotation.rData() << " " << genericCotation.rTicker() << " " << cotationsTree[genericCotation] << '\n'; //imprime o que foi armazenado
        }
        if (word == "ID") {
            std::string date;
            std::string refDate; //data refatorada
            std::string ticker;
            int value1;
            char dot;
            int cents;
            int value;

            std::cin >> date >> ticker >> value1 >> dot >> cents;

            refDate = inverteData(date);

            Dividendos genericDividendo(refDate, ticker);

            value = value1*100 + cents;

            if (dividendosTree.count(genericDividendo) == 1) {
                value += dividendosTree[genericDividendo];
            }
            
            dividendosTree[genericDividendo] = value;

            // std::cout << genericDividendo.rData() << " " << genericDividendo.rTicker() << " " << dividendosTree[genericDividendo] << '\n'; //imprime o que foi armazenado
        }
        if (word == "IA") {
            std::string ticker;
            int qtd;
            int value1;
            char dot;
            int cents1;
            int value2;
            int cents2;
            int precoCompra;
            int dividendosRecebidos;

            std::cin >> ticker >> qtd >> value1 >> dot >> cents1 >> value2 >> dot >> cents2;

            precoCompra = value1*100 + cents1;

            dividendosRecebidos = value2*100 + cents2;

            Carteira genericCarteira(ticker, qtd, precoCompra, dividendosRecebidos); //cria o objeto carteira

            listCarteira.push_back(genericCarteira); //insere na lista duplamente enc. a carteira gerada (lista original)

            MyList2<Carteira>::iterator itList = listCarteira.end();
            itList--; //retorna para antes do NULL(ultimo elemento valido)

            carteiraTreeTick[ticker] = itList; //insere no map de carteira ordenado por ticker o iterador para o objeto

            carteiraTreeQt[qtd].push_back(itList); //da pushback na lista retornada pelo map de carteira na posicao do atributo
            carteiraTreeVal[precoCompra].push_back(itList);
            carteiraTreeDiv[dividendosRecebidos].push_back(itList);

            MyList2<MyList2<Carteira>::iterator>::iterator listQtdIt = carteiraTreeQt[qtd].end(); //cria o iterador para a lista de iteradores para guardar no objeto carteira
            MyList2<MyList2<Carteira>::iterator>::iterator listValIt = carteiraTreeVal[precoCompra].end();
            MyList2<MyList2<Carteira>::iterator>::iterator listDivIt = carteiraTreeDiv[dividendosRecebidos].end();

            listQtdIt--; //retorna para antes do NULL(ultimo elemento valido)
            listValIt--;
            listDivIt--;

            itList->setListQtd(listQtdIt); //guarda no objeto o ultimo iterador
            itList->setListVal(listValIt);
            itList->setListDiv(listDivIt);          

            // for (i = listCarteira.begin(); i != listCarteira.end(); i++) {
            //     std::cout << i->rTicker() << '\n';
            // }

            // for(MyMap<string, MyList2<Carteira>::iterator>::iterator it = carteiraTreeTick.begin();it!=carteiraTreeTick.end();it++) {
            //     std::cout << it->second->rTicker() << " ";
            // } std::cout << endl;
            
        }
        if(word == "DIV") {
            std::string begDate;
            std::string refBegDate;
            std::string finalDate;
            std::string refFinalDate;

            std::cin >> begDate >> finalDate;

            refBegDate = inverteData(begDate);

            refFinalDate = inverteData(finalDate);
            if (header == "mostrarCabecalhos" || header == "naoMostrarCabecalhos" || header == "ultimaColuna" || header == "compacta") {
                if (header == "mostrarCabecalhos") {
                    std::cout << "Dividendos no intervalo: " << begDate << " a " << finalDate << '\n';
                    std::cout << "Ticker" << std::right << std::setw(11) << "Quantidade" << std::right << std::setw(14) << "Compra" << std::right << std::setw(14) << "Dividendo" << std::right << std::setw(14) << "Div.inter." <<'\n';
                }
                
                MyList2<Carteira>::iterator i;
                int div = 0;
                int mont = 0;
                
                for (i = listCarteira.begin(); i != listCarteira.end(); i++) { //percorre a lista de carteira

                    for (MyMap<Dividendos, int>::iterator it = dividendosTree.begin(); it != dividendosTree.end(); it++) { //percorre o map de dividendos 
                        Dividendos aux = it->first;

                        if (aux.rData() >= refBegDate && aux.rData() <= refFinalDate && aux.rTicker() == i->rTicker()) { //se o ticker analisado da carteira e div bater e alem disso a data do div estiver no intervalo soma ao div
                            div += i->rQuantidade() * dividendosTree[aux];
                        }
                    }
                    // Dividendos aux (refBegDate, i->rTicker());
                    // MyMap<Dividendos, int>::iterator it = dividendosTree.upper_bound(aux);
                    // std::cout << dividendosTree[it->first] << '\n';

                    // while (it != dividendosTree.end() && finalDate >= it->first.rData() && it->first.rTicker() == i->rTicker()) {
                    //     std::cout << i->rQuantidade() << " " << it->second << '\n';
                    //     div += i->rQuantidade() * it->second;
                    //     it++;
                    // }

                    if (header == "mostrarCabecalhos" || header == "naoMostrarCabecalhos") {
                        std::cout << std::left << std::setw(7) << i->rTicker();
                        std::cout << std::right << std::setw(10) <<  i->rQuantidade(); 
                        std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)i->rValor()/100;
                        std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)i->rDividendos()/100;
                        std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)div/100 << '\n';
                        mont += div;
                        div = 0;
                    }
                    if (header == "ultimaColuna") {
                        std::cout << std::fixed << std::setprecision(2) << (float)div/100 << '\n';
                        mont += div;
                        div = 0;
                    }

                    if (header == "compacta") {
                        mont += div;
                        div = 0;
                    }
                }
                if (header == "mostrarCabecalhos" || header == "naoMostrarCabecalhos") {
                    std::cout << "Total de dividendos:" << std::right << std::setw(39) << (float)mont/100 << '\n';
                    mont = 0;
                    if (header == "mostrarCabecalhos") {
                        std::cout << '\n';
                    }
                }
                if (header == "compacta" || header == "ultimaColuna") {
                    std::cout << std::fixed << std::setprecision(2) << (float)mont/100 << '\n';
                    mont = 0;
                }
            }
            else {
                MyList2<Carteira>::iterator i;
                int div = 0;
                int mont = 0;
                
                for (i = listCarteira.begin(); i != listCarteira.end(); i++) {

                    for (MyMap<Dividendos, int>::iterator it = dividendosTree.begin(); it != dividendosTree.end(); it++) {
                        Dividendos aux = it->first;

                        if (aux.rData() >= refBegDate && aux.rData() <= refFinalDate && aux.rTicker() == i->rTicker()) {
                            div += i->rQuantidade() * dividendosTree[aux];
                        }
                    }
                    
                    std::cout << std::left << std::setw(7) << i->rTicker();
                    std::cout << std::right << std::setw(10) <<  i->rQuantidade(); 
                    std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)i->rValor()/100;
                    std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)i->rDividendos()/100;
                    std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)div/100 << '\n';
                    mont += div;
                    div = 0;
                    
                }
                std::cout << "Total de dividendos:" << std::right << std::setw(39) << (float)mont/100 << '\n';
                mont = 0;
            }
        }
        
        //funcao auxiliar p/ verificar o estado do map de dividendos
        if(word == "ImpDiv") {
            for(MyMap<Dividendos, int>::iterator it = dividendosTree.begin(); it != dividendosTree.end(); it++) {
                Dividendos div = it->first;
                int val = it->second;
                std::cout << div.rData() << " " << div.rTicker() << " " << val << '\n';
            } 
        }
        
        //funcao auxiliar p/ verificar o estado do map de cotacoes
        if(word == "ImpCot") {
            for(MyMap<Cotacoes, int>::iterator it = cotationsTree.begin(); it != cotationsTree.end(); it++) {
                Cotacoes div = it->first;
                int val = it->second;
                std::cout << div.rData() << " " << div.rTicker() << " " << val << '\n';
            } 
        }
        if (word == "ORD") {
            std::string op;
            std::cin >> op;
            
            int k;
            std::cin >> k;

            if (op == "ORIG") {
                int count = 0;
                std::string date;
                int val = 0;
                int mont = 0;

                std::cin >> date;
                if (header == "mostrarCabecalhos" || header == "naoMostrarCabecalhos" || header == "ultimaColuna" || header == "compacta") {
                    if (header == "mostrarCabecalhos") {
                        std::cout << "Data: " << date << '\n';
                        std::cout << "Ticker" << std::right << std::setw(11) << "Quantidade" << std::right << std::setw(14) << "Compra" << std::right << std::setw(14) << "Dividendo" << std::right << std::setw(14) << "Valor" <<'\n';
                    }
                    for (MyList2<Carteira>::iterator i = listCarteira.begin(); i != listCarteira.end(); i++) {
                        Cotacoes auxSearch(inverteData(date), i->rTicker()); //qual eh a cotacao que se busca

                        MyMap<Cotacoes, int>::iterator itSearch = cotationsTree.upper_bound(auxSearch); //funcao que retorna o iterador do primeiro maior que a chave passada caso ela nao esteja no map, se tiver mais de uma retorna a primeira
                        if (itSearch != cotationsTree.end()) { //se upper_bound retornar NULL acessaria uma posicao invalida do map de cotacoes
                            val += cotationsTree[itSearch->first] * i->rQuantidade();
                        }
                        else{
                            val = 0;
                        }
                    
                        if (header == "mostrarCabecalhos" || header == "naoMostrarCabecalhos") {
                            std::cout << std::left << std::setw(7) << i->rTicker();
                            std::cout << std::right << std::setw(10) <<  i->rQuantidade(); 
                            std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)i->rValor()/100;
                            std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)i->rDividendos()/100;
                            std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)val/100 << '\n';
                            mont += val;
                            val = 0;
                        }

                        if (header == "ultimaColuna") {
                            std::cout << std::fixed << std::setprecision(2) << (float)val/100 << '\n';
                            mont += val;
                            val = 0;
                        }

                        if (header == "compacta") {
                            mont += val;
                            val = 0;
                        }
                        
                        count++;
                        if (count == k) {
                            break;
                        }
                    }
                    count = 0;
                    if (header == "mostrarCabecalhos" || header == "naoMostrarCabecalhos") {
                        std::cout << "Valor total da carteira:" << std::right << std::setw(35) << (float)mont/100 << '\n';
                        mont = 0;
                        if (header == "mostrarCabecalhos") {
                            std::cout << '\n';
                        }
                    }
                    if (header == "compacta" || header == "ultimaColuna") {
                        std::cout << std::fixed << std::setprecision(2) << (float)mont/100 << '\n';
                        mont = 0;
                    }
                }
                else{
                    for (MyList2<Carteira>::iterator i = listCarteira.begin(); i != listCarteira.end(); i++) {
                        Cotacoes auxSearch(inverteData(date), i->rTicker()); //qual eh a cotacao que se busca

                        MyMap<Cotacoes, int>::iterator itSearch = cotationsTree.upper_bound(auxSearch); //funcao que retorna o iterador do primeiro maior que a chave passada caso ela nao esteja no map, se tiver mais de uma retorna a primeira
                        if (itSearch != cotationsTree.end()) {//se upper_bound retornar NULL acessaria uma posicao invalida do map de cotacoes
                            val += cotationsTree[itSearch->first] * i->rQuantidade();
                        }
                        else{
                            val = 0;
                        }
        
                        std::cout << std::left << std::setw(7) << i->rTicker();
                        std::cout << std::right << std::setw(10) <<  i->rQuantidade(); 
                        std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)i->rValor()/100;
                        std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)i->rDividendos()/100;
                        std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)val/100 << '\n';
                        mont += val;
                        val = 0;
                    }
                    std::cout << "Valor total da carteira:" << std::right << std::setw(35) << (float)mont/100 << '\n';
                    mont = 0;
                }
            }
                
            if (op == "TICK") {
                int count = 0;
                std::string date;
                int val = 0;
                int mont = 0;

                std::cin >> date;
                if (header == "mostrarCabecalhos" || header == "naoMostrarCabecalhos" || header == "ultimaColuna" || header == "compacta") {
                    if (header == "mostrarCabecalhos") {
                        std::cout << "Data: " << date << '\n';
                        std::cout << "Ticker" << std::right << std::setw(11) << "Quantidade" << std::right << std::setw(14) << "Compra" << std::right << std::setw(14) << "Dividendo" << std::right << std::setw(14) << "Valor" <<'\n';
                    }
                    for (MyMap<string, MyList2<Carteira>::iterator>::iterator  i = carteiraTreeTick.begin(); i != carteiraTreeTick.end(); i++) {
                        Cotacoes auxSearch(inverteData(date), i->first); //qual eh a cotacao que se busca

                        MyMap<Cotacoes, int>::iterator itSearch = cotationsTree.upper_bound(auxSearch); //funcao que retorna o iterador do primeiro maior que a chave passada caso ela nao esteja no map, se tiver mais de uma retorna a primeira
                        if (itSearch != cotationsTree.end()) { //se upper_bound retornar NULL acessaria uma posicao invalida do map de cotacoes
                            val += cotationsTree[itSearch->first] * i->second->rQuantidade();
                        }
                        else{
                            val = 0;
                        }
                    
                        if (header == "mostrarCabecalhos" || header == "naoMostrarCabecalhos") {
                            std::cout << std::left << std::setw(7) << i->second->rTicker();
                            std::cout << std::right << std::setw(10) <<  i->second->rQuantidade(); 
                            std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)i->second->rValor()/100;
                            std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)i->second->rDividendos()/100;
                            std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)val/100 << '\n';
                            mont += val;
                            val = 0;
                        }

                        if (header == "ultimaColuna") {
                            std::cout << std::fixed << std::setprecision(2) << (float)val/100 << '\n';
                            mont += val;
                            val = 0;
                        }

                        if (header == "compacta") {
                            mont += val;
                            val = 0;
                        }
                        
                        count++;
                        if (count == k) {
                            break;
                        }
                    }
                    count = 0;
                    if (header == "mostrarCabecalhos" || header == "naoMostrarCabecalhos") {
                        std::cout << "Valor total da carteira:" << std::right << std::setw(35) << (float)mont/100 << '\n';
                        mont = 0;
                        if (header == "mostrarCabecalhos") {
                            std::cout << '\n';
                        }
                    }
                    if (header == "compacta" || header == "ultimaColuna") {
                        std::cout << std::fixed << std::setprecision(2) << (float)mont/100 << '\n';
                        mont = 0;
                    }
                }
                else {
                    for (MyMap<string, MyList2<Carteira>::iterator>::iterator  i = carteiraTreeTick.begin(); i != carteiraTreeTick.end(); i++) {
                        Cotacoes auxSearch(inverteData(date), i->first); //qual eh a cotacao que se busca

                        MyMap<Cotacoes, int>::iterator itSearch = cotationsTree.upper_bound(auxSearch); //funcao que retorna o iterador do primeiro maior que a chave passada caso ela nao esteja no map, se tiver mais de uma retorna a primeira
                        if (itSearch != cotationsTree.end()) { //se upper_bound retornar NULL acessaria uma posicao invalida do map de cotacoes
                            val += cotationsTree[itSearch->first] * i->second->rQuantidade();
                        }
                        else{
                            val = 0;
                        }
                        
                        std::cout << std::left << std::setw(7) << i->second->rTicker();
                        std::cout << std::right << std::setw(10) <<  i->second->rQuantidade(); 
                        std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)i->second->rValor()/100;
                        std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)i->second->rDividendos()/100;
                        std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)val/100 << '\n';
                        mont += val;
                        val = 0;
                        
                        count++;
                        if (count == k) {
                            break;
                        }
                    }
                    std::cout << "Valor total da carteira:" << std::right << std::setw(35) << (float)mont/100 << '\n';
                    mont = 0;
                }
            }

            if (op == "DIV") {
                int count = 0;
                std::string date;
                int val = 0;
                int mont = 0;

                std::cin >> date;
                if (header == "mostrarCabecalhos" || header == "naoMostrarCabecalhos" || header == "ultimaColuna" || header == "compacta") {
                    if (header == "mostrarCabecalhos") {
                        std::cout << "Data: " << date << '\n';
                        std::cout << "Ticker" << std::right << std::setw(11) << "Quantidade" << std::right << std::setw(14) << "Compra" << std::right << std::setw(14) << "Dividendo" << std::right << std::setw(14) << "Valor" <<'\n';
                    }
                    for (MyMap<int, MyList2<MyList2<Carteira>::iterator>>::iterator  i = carteiraTreeDiv.begin(); i != carteiraTreeDiv.end(); i++) {//for que percorre cada valor int que guarda uma lista, ex: na pos [100]
                                                                                                                                                    //existe um iterador de lista que guarda uma lista de carteiras que sera acessada pelo outro for
                        for (MyList2<MyList2<Carteira>::iterator>::iterator j = (i->second).begin(); j != (i->second).end(); j++) { //for que percorrera dentro da lista aquelas carteiras com dividendos iguais
                            Cotacoes auxSearch(inverteData(date), (*j)->rTicker()); //qual eh a cotacao que se busca

                            MyMap<Cotacoes, int>::iterator itSearch = cotationsTree.upper_bound(auxSearch); //encontra o auxSearch no map de cotacoes, se nao tiver retorna o proximo
                            if (itSearch != cotationsTree.end()) { //se upper_bound retornar NULL acessaria uma posicao invalida do map de cotacoes
                                val += cotationsTree[itSearch->first] * (*j)->rQuantidade();
                            }
                            else{
                                val = 0;
                            }
                        
                            if (header == "mostrarCabecalhos" || header == "naoMostrarCabecalhos") {
                                std::cout << std::left << std::setw(7) << (*j)->rTicker();
                                std::cout << std::right << std::setw(10) <<  (*j)->rQuantidade(); 
                                std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)(*j)->rValor()/100;
                                std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)(*j)->rDividendos()/100;
                                std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)val/100 << '\n';
                                mont += val;
                                val = 0;
                            }

                            if (header == "ultimaColuna") {
                                std::cout << std::fixed << std::setprecision(2) << (float)val/100 << '\n';
                                mont += val;
                                val = 0;
                            }

                            if (header == "compacta") {
                                mont += val;
                                val = 0;
                            }
                            
                            count++;
                            if (count == k) {
                                break;
                            }
                        }
                        if (count == k) {
                            break;
                        }
                    }
                    count = 0;
                    if (header == "mostrarCabecalhos" || header == "naoMostrarCabecalhos") {
                        std::cout << "Valor total da carteira:" << std::right << std::setw(35) << (float)mont/100 << '\n';
                        mont = 0;
                        if (header == "mostrarCabecalhos") {
                            std::cout << '\n';
                        }
                    }
                    if (header == "compacta" || header == "ultimaColuna") {
                        std::cout << std::fixed << std::setprecision(2) << (float)mont/100 << '\n';
                        mont = 0;
                    }
                }
                else {
                    for (MyMap<int, MyList2<MyList2<Carteira>::iterator>>::iterator  i = carteiraTreeDiv.begin(); i != carteiraTreeDiv.end(); i++) {//for que percorre cada valor int que guarda uma lista, ex: na pos [100]
                                                                                                                                                    //existe um iterador de lista que guarda uma lista de carteiras que sera acessada pelo outro for
                        for (MyList2<MyList2<Carteira>::iterator>::iterator j = (i->second).begin(); j != (i->second).end(); j++) { //for que percorrera dentro da lista aquelas carteiras com dividendos iguais
                            Cotacoes auxSearch(inverteData(date), (*j)->rTicker()); //qual eh a cotacao que se busca

                            MyMap<Cotacoes, int>::iterator itSearch = cotationsTree.upper_bound(auxSearch); //encontra o auxSearch no map de cotacoes, se nao tiver retorna o proximo
                            if (itSearch != cotationsTree.end()) { //se upper_bound retornar NULL acessaria uma posicao invalida do map de cotacoes
                                val += cotationsTree[itSearch->first] * (*j)->rQuantidade();
                            }
                            else{
                                val = 0;
                            }
                        
                            
                            std::cout << std::left << std::setw(7) << (*j)->rTicker();
                            std::cout << std::right << std::setw(10) <<  (*j)->rQuantidade(); 
                            std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)(*j)->rValor()/100;
                            std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)(*j)->rDividendos()/100;
                            std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)val/100 << '\n';
                            mont += val;
                            val = 0;
                            
                            count++;
                            if (count == k) {
                                break;
                            }
                        }
                        if (count == k) {
                            break;
                        }
                    }
                    std::cout << "Valor total da carteira:" << std::right << std::setw(35) << (float)mont/100 << '\n';
                    mont = 0;
                }
            }   

            if (op == "VALOR") {
                int count = 0;
                std::string date;
                int val = 0;
                int mont = 0;

                std::cin >> date;
                if (header == "mostrarCabecalhos" || header == "naoMostrarCabecalhos" || header == "ultimaColuna" || header == "compacta") {
                    if (header == "mostrarCabecalhos") {
                        std::cout << "Data: " << date << '\n';
                        std::cout << "Ticker" << std::right << std::setw(11) << "Quantidade" << std::right << std::setw(14) << "Compra" << std::right << std::setw(14) << "Dividendo" << std::right << std::setw(14) << "Valor" <<'\n';
                    }
                    for (MyMap<int, MyList2<MyList2<Carteira>::iterator>>::iterator  i = carteiraTreeVal.begin(); i != carteiraTreeVal.end(); i++) {//for que percorre cada valor int que guarda uma lista, ex: na pos [100]
                                                                                                                                                    //existe um iterador de lista que guarda uma lista de carteiras que sera acessada pelo outro for
                        for (MyList2<MyList2<Carteira>::iterator>::iterator j = (i->second).begin(); j != (i->second).end(); j++) { //for que percorrera dentro da lista aquelas carteiras com dividendos iguais
                            Cotacoes auxSearch(inverteData(date), (*j)->rTicker()); //qual eh a cotacao que se busca

                            MyMap<Cotacoes, int>::iterator itSearch = cotationsTree.upper_bound(auxSearch); //encontra o auxSearch no map de cotacoes, se nao tiver retorna o proximo
                            if (itSearch != cotationsTree.end()) { //se upper_bound retornar NULL acessaria uma posicao invalida do map de cotacoes
                                val += cotationsTree[itSearch->first] * (*j)->rQuantidade();
                            }
                            else{
                                val = 0;
                            }
                        
                            if (header == "mostrarCabecalhos" || header == "naoMostrarCabecalhos") {
                                std::cout << std::left << std::setw(7) << (*j)->rTicker();
                                std::cout << std::right << std::setw(10) <<  (*j)->rQuantidade(); 
                                std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)(*j)->rValor()/100;
                                std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)(*j)->rDividendos()/100;
                                std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)val/100 << '\n';
                                mont += val;
                                val = 0;
                            }

                            if (header == "ultimaColuna") {
                                std::cout << std::fixed << std::setprecision(2) << (float)val/100 << '\n';
                                mont += val;
                                val = 0;
                            }

                            if (header == "compacta") {
                                mont += val;
                                val = 0;
                            }
                            
                            count++;
                            if (count == k) {
                                break;
                            }
                        }
                        if (count == k) {
                            break;
                        }
                    }
                    count = 0;
                    if (header == "mostrarCabecalhos" || header == "naoMostrarCabecalhos") {
                        std::cout << "Valor total da carteira:" << std::right << std::setw(35) << (float)mont/100 << '\n';
                        mont = 0;
                        if (header == "mostrarCabecalhos") {
                            std::cout << '\n';
                        }
                    }
                    if (header == "compacta" || header == "ultimaColuna") {
                        std::cout << std::fixed << std::setprecision(2) << (float)mont/100 << '\n';
                        mont = 0;
                    }
                }
                else{
                    for (MyMap<int, MyList2<MyList2<Carteira>::iterator>>::iterator  i = carteiraTreeVal.begin(); i != carteiraTreeVal.end(); i++) {//for que percorre cada valor int que guarda uma lista, ex: na pos [100]
                                                                                                                                                    //existe um iterador de lista que guarda uma lista de carteiras que sera acessada pelo outro for
                        for (MyList2<MyList2<Carteira>::iterator>::iterator j = (i->second).begin(); j != (i->second).end(); j++) { //for que percorrera dentro da lista aquelas carteiras com dividendos iguais
                            Cotacoes auxSearch(inverteData(date), (*j)->rTicker()); //qual eh a cotacao que se busca

                            MyMap<Cotacoes, int>::iterator itSearch = cotationsTree.upper_bound(auxSearch); //encontra o auxSearch no map de cotacoes, se nao tiver retorna o proximo
                            if (itSearch != cotationsTree.end()) { //se upper_bound retornar NULL acessaria uma posicao invalida do map de cotacoes
                                val += cotationsTree[itSearch->first] * (*j)->rQuantidade();
                            }
                            else{
                                val = 0;
                            }
                            
                            std::cout << std::left << std::setw(7) << (*j)->rTicker();
                            std::cout << std::right << std::setw(10) <<  (*j)->rQuantidade(); 
                            std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)(*j)->rValor()/100;
                            std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)(*j)->rDividendos()/100;
                            std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)val/100 << '\n';
                            mont += val;
                            val = 0;
                            
                            count++;
                            if (count == k) {
                                break;
                            }
                        }
                        if (count == k) {
                            break;
                        }
                    }
                    std::cout << "Valor total da carteira:" << std::right << std::setw(35) << (float)mont/100 << '\n';
                    mont = 0;
                }
            }   

            if (op == "QUANT") {
                int count = 0;
                std::string date;
                int val = 0;
                int mont = 0;

                std::cin >> date;
                if (header == "mostrarCabecalhos" || header == "naoMostrarCabecalhos" || header == "ultimaColuna" || header == "compacta") {
                    if (header == "mostrarCabecalhos") {
                        std::cout << "Data: " << date << '\n';
                        std::cout << "Ticker" << std::right << std::setw(11) << "Quantidade" << std::right << std::setw(14) << "Compra" << std::right << std::setw(14) << "Dividendo" << std::right << std::setw(14) << "Valor" <<'\n';
                    }
                    for (MyMap<int, MyList2<MyList2<Carteira>::iterator>>::iterator  i = carteiraTreeQt.begin(); i != carteiraTreeQt.end(); i++) {//for que percorre cada valor int que guarda uma lista, ex: na pos [100]
                                                                                                                                                    //existe um iterador de lista que guarda uma lista de carteiras que sera acessada pelo outro for
                        for (MyList2<MyList2<Carteira>::iterator>::iterator j = (i->second).begin(); j != (i->second).end(); j++) { //for que percorrera dentro da lista aquelas carteiras com dividendos iguais
                            Cotacoes auxSearch(inverteData(date), (*j)->rTicker()); //qual eh a cotacao que se busca

                            MyMap<Cotacoes, int>::iterator itSearch = cotationsTree.upper_bound(auxSearch); //encontra o auxSearch no map de cotacoes, se nao tiver retorna o proximo
                            if (itSearch != cotationsTree.end()) { //se upper_bound retornar NULL acessaria uma posicao invalida do map de cotacoes
                                val += cotationsTree[itSearch->first] * (*j)->rQuantidade();
                            }
                            else{
                                val = 0;
                            }
                        
                            if (header == "mostrarCabecalhos" || header == "naoMostrarCabecalhos") {
                                std::cout << std::left << std::setw(7) << (*j)->rTicker();
                                std::cout << std::right << std::setw(10) <<  (*j)->rQuantidade(); 
                                std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)(*j)->rValor()/100;
                                std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)(*j)->rDividendos()/100;
                                std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)val/100 << '\n';
                                mont += val;
                                val = 0;
                            }

                            if (header == "ultimaColuna") {
                                std::cout << std::fixed << std::setprecision(2) << (float)val/100 << '\n';
                                mont += val;
                                val = 0;
                            }

                            if (header == "compacta") {
                                mont += val;
                                val = 0;
                            }
                            
                            count++;
                            if (count == k) {
                                break;
                            }
                        }
                        if (count == k) {
                            break;
                        }
                    }
                    count = 0;
                    if (header == "mostrarCabecalhos" || header == "naoMostrarCabecalhos") {
                        std::cout << "Valor total da carteira:" << std::right << std::setw(35) << (float)mont/100 << '\n';
                        mont = 0;
                        if (header == "mostrarCabecalhos") {
                            std::cout << '\n';
                        }
                    }
                    if (header == "compacta" || header == "ultimaColuna") {
                        std::cout << std::fixed << std::setprecision(2) << (float)mont/100 << '\n';
                        mont = 0;
                    }
                }
                else {
                    for (MyMap<int, MyList2<MyList2<Carteira>::iterator>>::iterator  i = carteiraTreeQt.begin(); i != carteiraTreeQt.end(); i++) {//for que percorre cada valor int que guarda uma lista, ex: na pos [100]
                                                                                                                                                    //existe um iterador de lista que guarda uma lista de carteiras que sera acessada pelo outro for
                        for (MyList2<MyList2<Carteira>::iterator>::iterator j = (i->second).begin(); j != (i->second).end(); j++) { //for que percorrera dentro da lista aquelas carteiras com dividendos iguais
                            Cotacoes auxSearch(inverteData(date), (*j)->rTicker()); //qual eh a cotacao que se busca

                            MyMap<Cotacoes, int>::iterator itSearch = cotationsTree.upper_bound(auxSearch); //encontra o auxSearch no map de cotacoes, se nao tiver retorna o proximo
                            if (itSearch != cotationsTree.end()) { //se upper_bound retornar NULL acessaria uma posicao invalida do map de cotacoes
                                val += cotationsTree[itSearch->first] * (*j)->rQuantidade();
                            }
                            else{
                                val = 0;
                            }
                            
                        
                            std::cout << std::left << std::setw(7) << (*j)->rTicker();
                            std::cout << std::right << std::setw(10) <<  (*j)->rQuantidade(); 
                            std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)(*j)->rValor()/100;
                            std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)(*j)->rDividendos()/100;
                            std::cout << std::right << std::setw(14) << std::fixed << std::setprecision(2) << (float)val/100 << '\n';
                            mont += val;
                            val = 0;
                    
                            count++;
                            if (count == k) {
                                break;
                            }
                        }
                        if (count == k) {
                            break;
                        }
                    }
                    std::cout << "Valor total da carteira:" << std::right << std::setw(35) << (float)mont/100 << '\n';
                    mont = 0;
                }
            }   
        }
        if (word == "AC") {
            std::string op;
            std::cin >> op;

            std::string tick;
            std::cin >> tick;

            if (op == "REMOVE") {
                MyMap<string, MyList2<Carteira>::iterator>::iterator itErase = carteiraTreeTick.find(tick);
                MyList2<MyList2<Carteira>::iterator>::iterator itQtd = itErase->second->rListQtd(); //retorna o iterador para o atributo quantidade do objeto
                MyList2<MyList2<Carteira>::iterator>::iterator itVal = itErase->second->rListVal();
                MyList2<MyList2<Carteira>::iterator>::iterator itDiv = itErase->second->rListDiv();

                int qtObj = (*itQtd)->rQuantidade(); //pega o atributo do objeto para pesquisar no map
                int valObj = (*itVal)->rValor();
                int divObj = (*itDiv)->rDividendos();
                
                carteiraTreeQt[qtObj].erase(itQtd); //apaga o iterador para a quantidade do objeto
                carteiraTreeVal[valObj].erase(itVal);
                carteiraTreeDiv[divObj].erase(itDiv);

                listCarteira.erase(itErase->second); //apaga o iterador da carteira referente ao ticker passado
                carteiraTreeTick.erase(itErase); //apaga do map carteira o iterador referente ao ticker passado
            }

            if (op == "QUANTIDADE") {
                int newQtd;
                cin >> newQtd;
                MyMap<string, MyList2<Carteira>::iterator>::iterator itErase = carteiraTreeTick.find(tick);
                MyList2<MyList2<Carteira>::iterator>::iterator itQtd = itErase->second->rListQtd();

                int qtObj = (itErase->second)->rQuantidade(); //pega o atributo do objeto para pesquisar no map

                carteiraTreeQt[qtObj].erase(itQtd); //apaga o iterador para a quantidade do objeto

                (itErase->second)->atQuantidade(newQtd); //atualiza a quantidade apontada pelo iterador
                
                carteiraTreeQt[(itErase->second)->rQuantidade()].push_back(itErase->second); //atualiza o iterador 

                MyList2<MyList2<Carteira>::iterator>::iterator newIt = carteiraTreeQt[(itErase->second)->rQuantidade()].end(); //pega o novo iterador para mudalo no objeto
                newIt--;
                itErase->second->atItQtd(newIt);
            }

            if (op == "DIVIDENDO") {
                int value;
                char pt;
                int cents;
                
                cin >> value >> pt >> cents;

                int newDiv;

                newDiv = value*100 + cents;
                MyMap<string, MyList2<Carteira>::iterator>::iterator itErase = carteiraTreeTick.find(tick);
                MyList2<MyList2<Carteira>::iterator>::iterator itDiv = itErase->second->rListDiv();

                int divObj = (itErase->second)->rDividendos(); //pega o atributo do objeto para pesquisar no map

                carteiraTreeDiv[divObj].erase(itDiv); //apaga o iterador para o dividendos do objeto

                (itErase->second)->atDividendos(newDiv); //atualiza o dividendo apontado pelo iterador
                
                carteiraTreeDiv[(itErase->second)->rDividendos()].push_back(itErase->second); //atualiza o iterador 

                MyList2<MyList2<Carteira>::iterator>::iterator newIt = carteiraTreeDiv[(itErase->second)->rDividendos()].end();  //pega o novo iterador para mudalo no objeto
                newIt--;
                itErase->second->atItDiv(newIt);
            }

            if (op == "VALOR") {
                int value;
                char pt;
                int cents;
                
                cin >> value >> pt >> cents;

                int newVal;
                newVal = value*100 + cents;
                MyMap<string, MyList2<Carteira>::iterator>::iterator itErase = carteiraTreeTick.find(tick);
                MyList2<MyList2<Carteira>::iterator>::iterator itVal = itErase->second->rListVal();

                int valObj = (itErase->second)->rValor(); //pega o atributo do objeto para pesquisar no map

                carteiraTreeVal[valObj].erase(itVal); //apaga o iterador para o dividendos do objeto

                (itErase->second)->atValor(newVal); //atualiza o dividendo apontado pelo iterador
                
                carteiraTreeVal[(itErase->second)->rValor()].push_back(itErase->second); //atualiza o iterador 

                MyList2<MyList2<Carteira>::iterator>::iterator newIt = carteiraTreeVal[(itErase->second)->rValor()].end(); //pega o novo iterador para mudalo no objeto
                newIt--;
                itErase->second->atItVal(newIt);
            }
        }
        
    }

    return 0;
}