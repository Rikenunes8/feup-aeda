
#include <iostream>
#include "participante.h"

Participante::Participante(string cod): codigo(cod)
{ }
string Participante::getCodigo() const {
	return codigo;
}

void Participante::promocao()
{
     for (unsigned int i=0; i<produtos.size(); i++)
     {
    	 Produto *prod=produtos[i].getProduto();
         int decPreco=prod->valorPromocao();
         float preco= produtos[i].getPreco()*(1.0-decPreco/100.0);
         produtos[i].setPreco(preco);
     }
}

void Participante::addProduto(ProdutoMercado &prod)
{
     produtos.push_back(prod);
}

float Participante::getPreco(int codProduto,int quant) const
{
      for (unsigned int i=0; i<produtos.size(); i++)
          if (produtos[i].getProduto()->getCodigo()==codProduto)
          {
             if (produtos[i].getQuantidade()>=quant)
                return produtos[i].getPreco();
             else throw ProdutoNaoDisp("quantidade insuficiente",quant);
          }
      throw ProdutoNaoDisp("nao existente",codProduto);
}

void Participante::imprime() const
{
     cout << "codigo: " << codigo << endl;
     cout << "Produtos: " << endl;
     for (unsigned int i=0; i<produtos.size(); i++) {
         cout << "    " ; produtos[i].imprime(); }
}




