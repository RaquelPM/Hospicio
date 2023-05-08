#include "TDI.h"

TDI::TDI(string nomeMedicoResponsavel, int idMedicoResponsavel):Paciente("", -1, -1, nomeMedicoResponsavel, idMedicoResponsavel){
  ala = "TDI";
  remedio = "Alprazolam";
}

TDI::TDI(vector<string> atributos):Paciente(atributos){
  ala = "TDI";
  remedio = "Alprazolam";
}