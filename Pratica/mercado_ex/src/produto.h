#ifndef PRODUTO_H_
#define PRODUTO_H_

#include <string>
using namespace std;


class ProdutoNaoDisp {
      string razao;
      int valor;
public:
      ProdutoNaoDisp(string rz,int v);
      string getRazao() const;
      friend ostream & operator << (ostream &out, const ProdutoNaoDisp &nd);
};


class Produto
{
      int codigo;
public:
      /**
       * @param cod codigo do produto
       */
       Produto(int cod);
       /**
        * metodo que indica o codigo do produto
        * @result codigo do produto
        */
       int getCodigo() const;
       /**
         * metodo virtual que calcula o valor da promocao a aplicar a um produto
         * @result valor da promocao em percentagem. Para um produto normal ee 2%
         */
        virtual int valorPromocao() const;
       /**
        * metodo virtual que imprime informacao sobre um produto. Para um produto normal imprime o codigo.
        * Para um produto com cuidados de conservacao imprime o codigo, a temperatura de conservacao e a validade
        */
       virtual void imprime() const;
       virtual ~Produto() {};
};

class ProdutoCons: public Produto
{
      int temptCons;
      int validade;
public:
       ProdutoCons(int cod, int tc, int val);
       int  valorPromocao() const;
       void imprime() const;
};

class ProdutoMercado
{
      Produto *produto;
      int quantidade;
      float preco;
public:
      ProdutoMercado(Produto *prod, int qt=0, float p=0);
      Produto *getProduto() const;
      int getQuantidade() const;
      float getPreco() const;
      void setPreco(float p);
      void imprime() const;
};


#endif /* PRODUTO_H_ */
