#include "Neurotico.h"

Neurotico::Neurotico(string nomeMedicoResponsavel, int idMedicoResponsavel):Paciente("", -1, -1, nomeMedicoResponsavel, idMedicoResponsavel){
  ala = "Neurótico";
  remedio = "Haloperidol";
}

Neurotico::Neurotico(vector<string> atributos):Paciente(atributos){
  ala = "Neurótico";
  remedio = "Haloperidol";
}