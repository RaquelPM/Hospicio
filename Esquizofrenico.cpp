#include "Esquizofrenico.h"

Esquizofrenico::Esquizofrenico(string nomeMedicoResponsavel, int idMedicoResponsavel):Paciente("", -1, -1, nomeMedicoResponsavel, idMedicoResponsavel){
  ala = "Esquizofrenia";
  remedio = "Risperidona";
}

Esquizofrenico::Esquizofrenico(vector<string> atributos):Paciente(atributos){
  ala = "Esquizofrenia";
  remedio = "Risperidona";
}