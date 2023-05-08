#include "Pessoa.h"
#include <iostream>

using namespace std;

Pessoa::Pessoa(){
  nome = "";
  idade = id = -1;
}

Pessoa::Pessoa(string n, int idade){
  this->nome = n;
  this->idade = idade;
}

void Pessoa::lerAtributos(){

  cout << "Nome: ";
  getline(cin, nome);
  while(nome == ""){
    cout << "Nome inválido, digite novamente\n";
    cout << "Nome: ";
    getline(cin, nome);
  }
 
  cout << "Idade: ";
  cin >> idade;
  while(idade < 0 || idade > 110){
    cout << "Idade inválida, digite novamente\n";
    cout << "Idade: ";
    cin >> idade;
  }
  cin.ignore();
}

string Pessoa::toString(){

  return "Nome: " + nome + '\n' +
        "Idade: " + to_string(idade) + '\n' +
        "ID: " + to_string(id) + '\n';
}

int Pessoa::getId(){return id;}
string Pessoa::getNome() { return nome; }
int Pessoa::getIdade(){return idade;}
void Pessoa::setNome(string nome){
  this->nome = nome;
}



