#include "Paciente.h"

class TDI : public Paciente {
public:
    
  TDI(string nomeMedicoResponsavel, int idMedicoResponsavel);
  TDI(vector<string> atributos);
};