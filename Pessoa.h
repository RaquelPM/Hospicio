#pragma once
#include <string>

using namespace std;

class Pessoa{

  protected:
    string nome;
    int idade, id = -1;

  public:
    Pessoa();
    Pessoa(string n, int idade);

    virtual void lerAtributos();

    virtual string toString();
    virtual void setId() = 0;
    void setNome(string nome);
    string getNome();
    int getIdade();

    int getId();
};