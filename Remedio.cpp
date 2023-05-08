#include "Remedio.h"
#include <vector>

using namespace std;

Remedio::Remedio() {
  nome = "";
  comprimidos = 0;
}
Remedio::Remedio(string nome, int comprimidos) {
  this->nome = nome;
  this->comprimidos = comprimidos;
}

Remedio::Remedio(vector<string> atributos){
  nome = atributos[0];
  comprimidos = stoi(atributos[1]);
}

int Remedio::getComprimidos() { return comprimidos; }
string Remedio::getNome() { return nome; }

void Remedio::setComprimidos(int qntConsumida) {
  comprimidos = comprimidos - qntConsumida < 0 ? 0 : comprimidos -= qntConsumida;
}

void Remedio::buyComprimidos(int qnt) {
  comprimidos += qnt;
}

string Remedio::toString(){

  return "Nome: " + nome + "\nQuantidade: " + to_string(comprimidos) + "\n";
}

string Remedio::toArchive(){
   return nome + "-" + to_string(comprimidos);
}