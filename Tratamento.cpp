#include "Tratamento.h"
#include "Esquizofrenico.h"
#include "TDI.h"
#include "Neurotico.h"
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

Tratamento::Tratamento() {}
Tratamento::Tratamento(Paciente paciente, string nomeMedico, Remedio remedio)
{
  this->paciente = paciente;
  this->nomeMedico = nomeMedico;
  this->remedio = remedio;
}

Tratamento::Tratamento(vector<string> atributos)
{

  int tipo = 1;

  Paciente *p;
  if (tipo == 1)
  {
    p = new Esquizofrenico(atributos[1], -1);
  }
  if (tipo == 2)
  {
    p = new Neurotico(atributos[1], -1);
  }
  if (tipo == 3)
  {
    p = new TDI(atributos[1], -1);
  }

  p->setNome(atributos[2]);
  paciente = *p;
  nomeMedico = atributos[1];
  remedio = Remedio(atributos[4], stoi(atributos[5]));
}

string Tratamento::toString()
{
  return "Tratamento realizado pelo médico " + nomeMedico + ".\nFeito no paciente " + paciente.getNome() + " que sofria de " + paciente.getAla() + ".\nTratamento realizado com uma dose de " + to_string(remedio.getComprimidos()) + " comprimidos de " + remedio.getNome() + ".\n\n";
}

string Tratamento::toArchive()
{

  int tipo;

  if (paciente.getAla() == "Esquizofrenia")
  {
    tipo = 1;
  }
  if (paciente.getAla() == "Neurótico")
  {
    tipo = 2;
  }
  if (paciente.getAla() == "TDI")
  {
    tipo = 3;
  }
  return nomeMedico + "-" + paciente.getNome() + "-" + to_string(tipo) + "-" + remedio.getNome() + "-" + to_string(remedio.getComprimidos());
}

Paciente Tratamento::getPaciente() { return paciente; }
Remedio Tratamento::getRemedio() { return remedio; }
string Tratamento::getNomeMedico() { return nomeMedico; }
