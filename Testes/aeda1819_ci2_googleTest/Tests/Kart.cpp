#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <time.h>
#include <string>
#include "Kart.h"
#include <algorithm>
using namespace std;

//To help build better array
string itos(int i){
    stringstream s;
    s << i;
    return s.str();
}

void CGrupo::criaGrupo()
{
    float cilindradas[4]  = {134,250,450,600};
    bool avariados[3]  = {true,false,false};

    srand (1);   //Criar Pistas e Karts de Teste
    for(int i=1;i<=50;i++){
        vector<CKart> frota;
        for(int j=1;j<=50;j++){
            frota.push_back(CKart(avariados[rand()% 3],
                                  ("KART - "+itos(i))+itos(j),(i-1)*50+j,cilindradas[(rand() % 4)]));
        }
        adicionaPista(CPista("Pista - "+itos(i),frota));
    }
}


vector <CKart> CPista::getKartsAvariados()
{
    vector<CKart> aux;
    for (vector<CKart>::iterator it = frotaKartsPista.begin() ; it != frotaKartsPista.end(); ++it) {
        if ((it)->getAvariado()) aux.push_back((*it));
    }
    return aux;
}

bool cmpKarts(CKart k1, CKart k2) {
    return k1.getNumero()<k2.getNumero();
}

//Exercicio 1 a)     
vector<CKart> CGrupo::ordenaKarts()
{
    vector<CKart> frota;
    vector<CKart> frotaTotal;

	for (auto pista:pistasG) {
	    frota=pista.getFrotaActual();
	    for (auto kart:frota) {
	        frotaTotal.push_back(kart);
	    }
	}

	sort(frotaTotal.begin(), frotaTotal.end(), cmpKarts);
	return frotaTotal;
}

//Exercicio 1 b)  
int CGrupo::numAvariados(int cilind)
{
    vector<CKart> v;
    for (auto pista:pistasG) {
        for (auto kart:pista.getKartsAvariados()) {
            if (kart.getCilindrada() == cilind)
                v.push_back(kart);
        }
    }
    return v.size();
}

//Exercicio 1 c)   
bool CPista::prepararCorrida(int numeroKarts, int cilind)
{
    int i = 0;
    vector<CKart>::iterator it=frotaKartsPista.begin();
    while (i < numeroKarts) {
        if (it == frotaKartsPista.end())
            return false;
        if (!it->getAvariado() && it->getCilindrada() == cilind) {
            kartsLinhaPartida.push(*it);
            i++;
        }
        it++;
    }
    return true;
}

//Exercicio 1 d) 
int CPista::inicioCorrida()
{
    size_t n = kartsLinhaPartida.size();
    for (size_t _ = 0; _ < n; _++) {
        kartsEmProva.push_back(kartsLinhaPartida.front());
        kartsLinhaPartida.pop();
    }
    return kartsEmProva.size();
}

