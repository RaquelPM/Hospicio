#include "Medico.h"
#include <iostream>

using namespace std;

vector<int> Medico::idUtilizados = {};

Medico::Medico() : Pessoa("", -1) { maxPacientes = 0; };

Medico::Medico(string nome, int idade, int maxPacientes) : Pessoa(nome, idade)
{
  this->maxPacientes = maxPacientes;
  setId();
}

Medico::Medico(vector<string> atributos)
{
  nome = atributos[0];
  idade = stoi(atributos[1]);
  maxPacientes = stoi(atributos[3]);
  id = stoi(atributos[2]);
  idUtilizados.push_back(id);
}

void Medico::showAtributos()
{
  cout << "Digite o nome, a idade e o máximo de pacientes que o médico poderá "
          "atender, nesta ordem."
       << endl;
}

string Medico::toString()
{
  return Pessoa::toString() +
         "Responsável por: " + to_string(pacientes.size()) + "/" +
         to_string(maxPacientes) + " paciente(s)\n\n";
}

string Medico::toArchive()
{

  return nome + "-" + to_string(idade) + "-" + to_string(id) + "-" + to_string(maxPacientes);
}

void Medico::lerAtributos()
{
  Pessoa::lerAtributos();

  cout << "Max. pacientes: ";
  cin >> maxPacientes;

  while (maxPacientes < 0)
  {
    cout << "Número máximo de pacientes inválido, digite novamente\n";
    cout << "Max. pacientes: ";
    cin >> maxPacientes;
  }
  setId();
  cin.ignore();
}

void Medico::addPaciente(Paciente *paciente)
{
  if (pacientes.size() < maxPacientes)
  {
    pacientes.push_back(paciente);
    paciente->setMedicoResponsavel(nome, id);
    return;
  }
  throw "Médico " + nome + " não aceita mais pacientes";
}

void Medico::deletePaciente(int idPaciente)
{
  int index = getPacienteIndexById(idPaciente);
  pacientes.erase(pacientes.begin() + index);
}

string Medico::listarPacientes()
{
  if (!pacientes.size())
    throw "É necessário designar pacientes para o médico " + nome;
  string _pacientes = "";
  for (int i = 0; i < pacientes.size(); i++)
  {
    _pacientes += pacientes[i]->toString();
  }

  return _pacientes;
}

bool Medico::tratar(int idPaciente, vector<Remedio *> &remedios, vector<Tratamento *> &tratamentos)
{

  int posicaoPaciente;
  int posicaoRemedio;
  int qntPacientes = pacientes.size();
  int qntRemedios = remedios.size();
  int i = 0;

  posicaoPaciente = getPacienteIndexById(idPaciente);

  for (i = 0; i < qntRemedios; i++)
  {
    if (remedios[i]->getNome().find(pacientes[posicaoPaciente]->getRemedio()) !=
        string::npos)
    { // Achando o remedio do paciente no array
      posicaoRemedio = i;
    }
  }

  // tratar caso não tenha comprimido!!!!
  if (remedios[posicaoRemedio]->getComprimidos())
  {

    Remedio *remedioUtilizado = new Remedio(remedios[posicaoRemedio]->getNome(), min(pacientes[posicaoPaciente]->getTratamentoNecessario(), remedios[posicaoRemedio]->getComprimidos()));

    Tratamento *tratamentoRealizado = new Tratamento(*pacientes[posicaoPaciente], nome, *remedioUtilizado);
    tratamentos.push_back(tratamentoRealizado);

    if (pacientes[posicaoPaciente]->realizarTratamento(remedios[posicaoRemedio]))
    {
      pacientes.erase(pacientes.begin() + posicaoPaciente);
      pacientes[posicaoPaciente]->liberaId(pacientes[posicaoPaciente]->getId());
      cout << "Paciente curado!" << endl;
      return true;
    }
    cout << "Tratamento realizado!" << endl;

    return false;
  }

  throw "Não há estoque do remédio " + remedios[posicaoRemedio]->getNome() +
      '\n';
}

bool Medico::checaId(int id)
{
  int qntIdUtilizados = Medico::idUtilizados.size();
  for (int i = 0; i < qntIdUtilizados; i++)
  {
    if (Medico::idUtilizados[i] == id)
    {
      return false;
    }
  }
  return true;
}

void Medico::setId()
{
  int idTeste;
  while (1)
  {
    idTeste = rand() % 1000 + 1001; // Criando ID do paciente entre 1001 e 2000;
    if (checaId(idTeste))
    { // Se o id gerado ainda não tiver sido utilizado
      id = idTeste;
      Medico::idUtilizados.push_back(id);
      break;
    }
  }
}

void Medico::liberaId(int id)
{

  int qntIdUtilizados = Medico::idUtilizados.size();
  for (int i = 0; i < qntIdUtilizados; i++)
  {
    if (idUtilizados[i] == id)
    {
      Medico::idUtilizados.erase(idUtilizados.begin() + i);
      break;
    }
  }
}

vector<Paciente *> Medico::getPacientes() { return pacientes; }

int Medico::selecionarPacienteId()
{
  // listando médicos para o usuario selecionar
  string pacientes;

  try
  {
    pacientes = listarPacientes();
  }
  catch (string e)
  {
    // caso não tenha nenhum paciente cadastrado
    throw e;
  }
  // exibindo médicos

  cout << "Pacientes: \n\n";
  cout << pacientes;

  // lendo e o id e checando se esta correto
  int id;
  while (1)
  {
    cout << "Digite o ID do paciente: " << endl;
    cin >> id;
    if (Paciente::checaId(id))
    {
      cout << "ID inválido" << endl;
      continue;
    }
    break;
  }
  cin.ignore();
  return id;
};

int Medico::getMaxPacientes() { return maxPacientes; }

int Medico::getPacienteIndexById(int idPaciente)
{

  for (int i = 0; i < pacientes.size(); i++)
  {
    if (pacientes[i]->getId() == idPaciente)
    {
      return i;
    }
  }
  return -1;
}