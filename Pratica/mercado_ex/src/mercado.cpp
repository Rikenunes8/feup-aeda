#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>

#include "mercado.h"

using namespace std;

vector<Produto*> Mercado::produtos;

Produto* Mercado::getProduto(int codProduto)
{
   for (unsigned int i=0; i<produtos.size();i++)
       if (produtos[i]->getCodigo()==codProduto) return produtos[i];
   return NULL;      
}

void Mercado::promocao()
{
       for (unsigned int i=0; i<fornecedores.size(); i++)
       {
           fornecedores[i].promocao();
       }
}

Participante *Mercado::precoMaisBaixo(int codProduto, int quant)
{
   float pmin=0;
   int indF=-1;
   ProdutoNaoDisp p1("produto inexistente",codProduto);
   for (unsigned int i=0; i<fornecedores.size(); i++)
   {
       try{
           float p=fornecedores[i].getPreco(codProduto,quant);
           if (pmin==0) { pmin=p; indF=i; }
           else if (p<pmin) { pmin=p; indF=i; }
       } catch(ProdutoNaoDisp &nd) { if (nd.getRazao()=="quantidade insuficiente") p1=nd; }
   }
   if (indF!=-1) return &fornecedores[indF];
   else throw p1; 
}

void Mercado::inicia(string nomeF)
{
     ifstream file(nomeF);
     if (!file.is_open()) {
         cout<<"Ficheiro nao encontrado";
         return;
     }
     string linha;
     Participante *p;
     while (!file.eof()) {
           file >> linha;
           int cod=atoi(linha.c_str());
           if (cod==0){ // linha contem uma string
              if (linha=="cliente") {
            	 file >> linha;
                 Participante p1(linha);
                 clientes.push_back(p1);
                 p=&clientes.back();
              }
              else if (linha=="fornecedor") {
            	   file >> linha;
            	   Participante p1(linha);
                   fornecedores.push_back(p1);
                   p=&fornecedores.back();
              }
              else if (linha=="produto") {
            	   file >> cod;
                   Produto *prod1= new Produto(cod);
                   produtos.push_back(prod1);
              }
              else if (linha=="produtoCons") {
                   int tempt, val;
                  file >> cod;
                  file >> tempt;
                  file >> val;
                   Produto *prod1;
                   prod1 = new ProdutoCons(cod,tempt,val);
                   produtos.push_back(prod1);
              }
           }
           else { // linha contem codigo produto
                int quant;
                float preco;
               file >> quant;
               file >> preco;
                Produto *prod1=Mercado::getProduto(cod);
                if (prod1!=NULL) {
                	ProdutoMercado prodM(prod1,quant,preco);
                	p->addProduto(prodM);
                }
           }
     }
    file.close();
}

void Mercado::imprime() const
{
     cout << "clientes:" << endl;
     for (unsigned int i=0; i<clientes.size(); i++)
         clientes[i].imprime();
     cout << endl << "fornecedores:" << endl;
     for (unsigned int i=0; i<fornecedores.size(); i++)
         fornecedores[i].imprime();
     cout << endl << "produtos:" << endl;
     for(unsigned int i=0; i<produtos.size();i++)
         produtos[i]->imprime();
     cout << endl;
}


