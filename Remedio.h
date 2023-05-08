#pragma once
#include <string>
#include <vector>

using namespace std;

class Remedio {
private:
  string nome;
  int comprimidos;

public:
  Remedio();
  Remedio(string nome, int comprimidos);
  Remedio(vector<string> atributos);
  int getComprimidos();
  void setComprimidos(int qntConsumida);
  void buyComprimidos(int qnt);
  string getNome();

  string toString();
  string toArchive();
};

