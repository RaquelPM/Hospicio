#include "Paciente.h"

class Neurotico : public Paciente {
public:
  Neurotico(string nomeMedicoResponsavel, int idMedicoResponsavel);
  Neurotico(vector<string> atributos);
};