#pragma once
#include "Paciente.h"
#include <vector>

using namespace std;

class Tratamento {
private:

  Paciente paciente;
  string nomeMedico;
  Remedio remedio;

public:

  Tratamento();
  Tratamento(Paciente p, string nomeMedico, Remedio remedio);
  Tratamento(vector<string> atributos);

  string toString();
  string toArchive();

  Paciente getPaciente();
  Remedio getRemedio();
  string getNomeMedico();
};