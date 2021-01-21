#include <iostream>
using namespace std;

#include "mercado.h"

int main()
{
    Mercado m1;
    m1.inicia("mercado.txt");
    char op;
    do {
    	cout << "i - imprime informacao mercado" << endl;
    	cout << "f - pesquisa fornecedor mais barato" << endl;
    	cout << "p - promocao" << endl;
    	cout << "s - sair" << endl;
    	cin >>op;
    	switch (op) {
    	case 'f':
    		try {
    			int codP, qt;
    	        cout << "qual o codigo do produto? ";
    	        cin >> codP;
    	        cout << "qual a quantidade? ";
    	        cin >> qt;
    	        Participante *f1=m1.precoMaisBaixo(codP,qt);
    	        cout << "fornecedor com preco mais baixo para " << qt;
    	        cout << " unidades do artigo " << codP << " : " << f1->getCodigo() << endl;
    		}
    		catch (ProdutoNaoDisp &nd) { cout << nd ; }
    		break;
    	case 'i':  m1.imprime();
    		break;
    	case 'p': m1.promocao();
    		cout << endl << "promocao:" << endl << endl;
    	    m1.imprime();
    	    break;
    	}
    } while (op!='s');

    return 1;
}

