#ifndef _MERCADO_H
#define _MERCADO_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "participante.h"
#include "produto.h"

using namespace std;


class Mercado
{
      vector<Participante> fornecedores;
      vector<Participante> clientes;
      static vector<Produto*> produtos;
public:
       void inicia(string nomeF);
       void imprime() const;
       Participante *precoMaisBaixo(int codProduto, int quant);
       void promocao();
       static Produto* getProduto(int codProduto);
};

#endif
