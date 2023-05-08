#include "Paciente.h"

class Esquizofrenico : public Paciente {
public:
  Esquizofrenico(string nomeMedicoResponsavel, int idMedicoResponsavel);
  Esquizofrenico(vector<string> atributos);
};