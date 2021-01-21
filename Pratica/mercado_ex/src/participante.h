#ifndef PARTICIPANTE_H_
#define PARTICIPANTE_H_

#include "produto.h"

#include <vector>
using namespace std;


class Participante{
      string codigo;
      vector<ProdutoMercado> produtos;
public:
       Participante(string cod);
       string getCodigo() const;
       float getPreco(int codProduto, int quant) const;
       void addProduto(ProdutoMercado &prod);
       void imprime() const;
       void promocao();
};


#endif /* PARTICIPANTE_H_ */
