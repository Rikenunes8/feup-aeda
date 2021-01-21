#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):lotacao(lot),
numMaximoClientes(nMaxCli){
    vagas = lotacao;
}

unsigned int ParqueEstacionamento::getNumLugares() const {
  return lotacao;
}
unsigned int ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}
int ParqueEstacionamento::posicaoCliente(const string &nome) const {
    for (int i = 0; i < clientes.size(); i++ ){
        if (nome == clientes[i].nome)
            return i;
    }
    return -1;
}
bool ParqueEstacionamento::adicionaCliente(const string &nome) {
    if (clientes.size() < numMaximoClientes) {
        InfoCartao c;
        c.nome = nome;
        c.presente = false;
        clientes.push_back(c);
        return true;
    }
    return false;
}
bool ParqueEstacionamento::entrar(const string &nome) {
    if (vagas == 0)
        return false;
    int n = posicaoCliente(nome);
    if (n == -1 || clientes[n].presente)
        return false;
    else{
        vagas--;
        clientes.at(n).presente = true;
        return true;
    }
}
bool ParqueEstacionamento::retiraCliente(const string &nome) {
    int n = posicaoCliente(nome);
    if (n != -1)
        if (! clientes[n].presente) {
            clientes.erase(clientes.begin()+n);
            return true;
        }
    return false;
}
bool ParqueEstacionamento::sair(const string &nome) {
    int n = posicaoCliente(nome);
    if (n == -1 || !clientes[n].presente)
        return false;
    else {
        vagas++;
        clientes[n].presente = false;
        return true;
    }
}
unsigned ParqueEstacionamento::getNumLugaresOcupados() const {
    return lotacao-vagas;
}
unsigned ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}