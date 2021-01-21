#include <iostream>
#include "produto.h"

using namespace std;

ostream & operator << (ostream &out, const ProdutoNaoDisp &nd) {
        out << nd.razao << " : " << nd.valor << endl;
        return out;
}

ProdutoNaoDisp::ProdutoNaoDisp(string rz, int codP): razao(rz), valor(codP)
{ }

string ProdutoNaoDisp::getRazao() const { return razao; }



// Produto
Produto::Produto(int cod): codigo(cod)  { }

int Produto::getCodigo() const {
	return codigo;
}

int Produto::valorPromocao() const {
	return 2;
}

void Produto::imprime() const {
	cout << codigo << endl;
}

//ProdutoCons
ProdutoCons::ProdutoCons(int cod, int tc, int val): Produto(cod), temptCons(tc), validade(val) { }

int  ProdutoCons::valorPromocao() const {
	if (validade<20) return 5;
	else return 2;
}

void ProdutoCons::imprime() const {
	cout << getCodigo() << " : temperatura=" << temptCons << ", validade=" << validade << endl;
}


//ProdutoMercado
ProdutoMercado::ProdutoMercado(Produto *prod, int qt, float p): produto(prod), quantidade(qt), preco(p)
{ }

Produto *ProdutoMercado::getProduto() const {
	return produto;
}
int ProdutoMercado::getQuantidade() const {
	return quantidade;
}
float ProdutoMercado::getPreco() const {
	return preco;
}
void ProdutoMercado::setPreco(float p) {
	preco=p;
}

void ProdutoMercado::imprime() const {
	cout << produto->getCodigo() << " : quant=" << quantidade << " , preco=" << preco << endl;
}

