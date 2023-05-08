#pragma once

#include "Tratamento.h"
#include "Paciente.h"
#include "Pessoa.h"
#include <string>
#include <vector>

using namespace std;

class Medico : public Pessoa {
private:

  int maxPacientes;
  vector<Paciente *> pacientes;
  static vector<int> idUtilizados;

public:
  Medico();
  Medico(string nome, int idade, int maxPacientes);
  Medico(vector<string> atributos);
  static void showAtributos();
  void lerAtributos();

  void addPaciente(Paciente *paciente);
  void deletePaciente(int idPaciente);
  int getPacienteIndexById(int idPaciente);
  string listarPacientes();
  bool tratar(int idPaciente, vector<Remedio*> &remedios, vector<Tratamento*> &tratamentos);

  void setId();

  static bool checaId(int id);
  static void liberaId(int id);

  vector<Paciente*> getPacientes();
  int selecionarPacienteId();

  string toString();
  string toArchive();

  int getMaxPacientes();
};
