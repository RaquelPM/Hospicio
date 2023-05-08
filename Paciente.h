#pragma once
#include "Pessoa.h"
#include "Remedio.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Paciente : public Pessoa{

  protected:

    string ala, remedio;
    int tratamentoNecessario, tratamentosRealizados, idMedicoResponsavel;
    string nomeMedicoResponsavel;

   static vector<int> idUtilizados;

  public:

    Paciente();
    Paciente(string nome, int idade, int tratamentoNecessario, string nomeMedicoResponsavel, int idMedicoResponsavel);
    Paciente(vector<string> atributos);
    static void showAtributos();
    static void showDiagnosticos();
    void lerAtributos();
  
    bool realizarTratamento(Remedio* &remedioUtilizado);
    string getRemedio();
    string getAla();
    string toString();
    string toArchive();
    void setMedicoResponsavel(string nomeMedicoResponsavel, int idMedicoResponsavel);
    string getMedicoResponsavel();
    int getTratamentoNecessario();
    int getTratamentoRealizados();
    int getIdMedicoResponsavel();

    void setId();
    static bool checaId(int id);
    static void liberaId(int id);

};