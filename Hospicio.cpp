#include "Hospicio.h"
#include "Esquizofrenico.h"
#include "Neurotico.h"
#include "TDI.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

Hospicio::Hospicio(string nome) {
  this->nome = nome;

  remedios.push_back(new Remedio("Haloperidol", 0));
  remedios.push_back(new Remedio("Alprazolam", 0));
  remedios.push_back(new Remedio("Risperidona", 0));
}

void Hospicio::showMenuInicial() {
  cout << "------------------------MENU------------------------\n\n";
  cout << "    Escolha uma das opções abaixo: \n\n";
  cout << "1 - Cadastrar médico" << endl;
  cout << "2 - Pesquisar médico" << endl;
  cout << "3 - Listar todos os médicos" << endl;
  cout << "4 - Gerenciar pacientes" << endl;
  cout << "5 - Ver estoque de remédios" << endl;
  cout << "6 - Realizar tratamento" << endl;
  cout << "7 - Ver relatorio (tratamentos realizados)" << endl;
  cout << "8 - Demitir medico" << endl;
  cout << "9 - Comprar remedios" << endl << endl;
  cout << "10 - Sair" << endl;
  cout << "---------------------------------------------------\n\n";
}

void Hospicio::showMenuPacientes() {
  cout << "---------------MENU PACIENTES---------------\n\n";
  cout << "      Escolha uma das opções abaixo: \n\n";
  cout << "1 - Cadastrar paciente" << endl;
  cout << "2 - Pesquisar paciente" << endl;
  cout << "3 - Listar pacientes" << endl;
  cout << "4 - Realocar pacientes pendentes" << endl;
  cout << "5 - Transferir paciente" << endl << endl;
  cout << "6 - Sair" << endl;
  cout << "--------------------------------------------\n\n";
}

void Hospicio::showMenuRemedio() {
  cout << "---------------LOJA DE REMEDIOS---------------\n\n";
  cout << "      Escolha uma das opções abaixo: \n\n";
  cout << "1 - Haloperidol" << endl;
  cout << "2 - Alprazolam" << endl;
  cout << "3 - Risperidona" << endl << endl;
  cout << "4 - Sair" << endl;
  cout << "----------------------------------------------\n\n";
}

////// MÉDICO //////
void Hospicio::cadastrarMedico(Medico *medico) { medicos.push_back(medico); }

string Hospicio::listarMedicos() {
  if (!medicos.size())
    throw "É necessário cadastrar médicos no hospício " + nome + "\n";
  string _medicos = "";
  for (int i = 0; i < medicos.size(); i++) {
    _medicos += medicos[i]->toString() + "\n\n";
  }

  return _medicos;
}

int Hospicio::getIndexMedico(int id) {
  int tamanho = medicos.size();

  for (int i = 0; i < tamanho; i++) {
    if (medicos[i]->getId() == id) {
      return i;
    }
  }
  throw "Médico ID( " + to_string(id) + ") não encontrado.\n";
}

string Hospicio::pesquisarMedicoByNome(string nome) {
  string medicosPesquisados = "";
  for (int i = 0; i < medicos.size(); i++) {
    if (medicos[i]->getNome().find(nome) != std::string::npos)
      medicosPesquisados += medicos[i]->toString();
  }

  if (medicosPesquisados == "")
    medicosPesquisados = "Não há medicos com este nome cadastrados.\n";

  return medicosPesquisados;
}

void Hospicio::demitirMedico(int idMedico) { // Demitir por id
  int indexMedico = getIndexMedico(idMedico);

  vector<Paciente *> pacientes = medicos[indexMedico]->getPacientes();
  int qntPacientes = pacientes.size();

  for (int i = 0; i < qntPacientes; i++) {
    pacientes[i]->setMedicoResponsavel("/", 0);
  }
  Medico::liberaId(medicos[indexMedico]->getId());

  medicos.erase(medicos.begin() + indexMedico);
  cout << "MÉDICO DEMITIDO\n";
}

Medico *Hospicio::pesquisarMedicoById(int id) {
  if (!medicos.size())
    throw "Nenhum médico cadastrado no hospício " + nome + "\n";
  for (int i = 0; i < medicos.size(); i++) {
    if (medicos[i]->getId() == id)
      return medicos[i];
  }
  throw "Nenhum médico com o id " + to_string(id) + "\n";
}

int Hospicio::selecionarMedicoId() {
  // listando médicos para o usuario selecionar
  string medicos;

  try {
    medicos = listarMedicos();
  } catch (string e) {
    // caso não tenha nenhum médico cadastrado
    throw e;
  }
  // exibindo médicos

  cout << "Médicos: \n\n";
  cout << medicos;

  // lendo e o id e checando se esta correto
  int id;
  while (1) {
    cout << "Digite o id do médico: " << endl;
    cin >> id;
    if (Medico::checaId(id)) {
      cout << "Id inválido" << endl;
      continue;
    }
    break;
  }
  cin.ignore();
  return id;
};

void Hospicio::agendaTratamento() {

  int idMedico;
  listaEstoque();
  try {
    idMedico = selecionarMedicoId();
  } catch (string e) {
    throw e;
  }
  Medico *m = pesquisarMedicoById(idMedico);

  int idPaciente;
  try {
    idPaciente = m->selecionarPacienteId();
  } catch (string e) {
    throw e;
  }

  bool curou = false;
  try {
    curou = m->tratar(idPaciente, remedios, tratamentosRealizados);
    Paciente *p = pesquisarPacienteById(idPaciente);
  } catch (string e) {
    throw e;
  }

  if (curou) {
    curePaciente(idPaciente);
  }
}

////////////////////////////////////// PACIENTE
////////////////////////////////////

int Hospicio::selecionarPacienteId() {
  // listando médicos para o usuario selecionar
  string pacientes;

  try {
    pacientes = listarPacientes();
  } catch (string e) {
    // caso não tenha nenhum paciente cadastrado
    throw e;
  }

  cout << "Pacientes: \n\n";
  cout << pacientes;

  // lendo e o id e checando se esta correto
  int id;
  while (1) {
    cout << "Digite o ID do paciente: " << endl;
    cin >> id;
    if (Paciente::checaId(id)) {
      cout << "ID inválido" << endl;
      continue;
    }
    break;
  }
  cin.ignore();
  return id;
};

void Hospicio::cadastrarPaciente(int idMedico, Paciente *paciente) {
  Medico *m = pesquisarMedicoById(idMedico);

  try {
    m->addPaciente(paciente);
    pacientes.push_back(paciente);
  } catch (string e) {
    cout << e << endl;
    return;
  }

  cout << "Paciente cadastrado com sucesso!\n" << endl;
}

string Hospicio::pesquisarPaciente(string nome) {
  string pacientesPesquisados = "";
  for (int i = 0; i < pacientes.size(); i++) {
    if (pacientes[i]->getNome().find(nome) != std::string::npos)
      pacientesPesquisados += pacientes[i]->toString();
  }

  if (pacientesPesquisados == "")
    pacientesPesquisados = "Não há pacientes com este nome cadastrados.\n";

  return pacientesPesquisados;
}

void Hospicio::listarPacientesPendentes() {
  vector<Paciente *> pendentes;

  if (!pacientes.size())
    throw "Não há pacientes no hospicio " + nome + "\n";
  for (int i = 0; i < pacientes.size(); i++) {
    if (pacientes[i]->getMedicoResponsavel() == "/") {
      pendentes.push_back(pacientes[i]);
    }
  }

  if (!pendentes.size())
    throw "Não há pacientes pendentes no hospicio " + nome + "\n";
  for (int i = 0; i < pendentes.size(); i++) {
    cout << pendentes[i]->toString() << endl;
  }
}

Paciente *Hospicio::pesquisarPacienteById(int id) {

  int qnt = pacientes.size();

  for (int i = 0; i < qnt; i++) {
    if (pacientes[i]->getId() == id) {
      return pacientes[i];
    }
  }

  throw "Nenhum paciente com o id " + to_string(id) + "\n";
}

void Hospicio::curePaciente(int id) {
  int index = -1;
  int qnt = pacientes.size();
  for (int i = 0; i < qnt; i++) {
    if (pacientes[i]->getId() == id) {
      index = i;
      break;
    }
  }

  if (index == -1)
    throw "Nenhum paciente com o id " + to_string(id) + "\n";
  pacientes.erase(pacientes.begin() + index);
}

void Hospicio::realocaPacientePendente() {
  int id;
  try {
    listarPacientesPendentes();
  } catch (string e) {
    throw e;
  }
  while (1) {
    cout << "Digite o ID do paciente a ser realocado: \n";
    cin >> id;

    if (Paciente::checaId(id)) {
      cout << "ID não existe!\n";
      continue;
    }
    break;
  }
  cout << "\nSelecione o médico que ficará responsável pelo paciente: \n";
  int idMedico;
  try {
    idMedico = selecionarMedicoId();
  } catch (string e) {
    throw e;
  }

  Paciente *p = pesquisarPacienteById(id);
  Medico *m = pesquisarMedicoById(idMedico);

  m->addPaciente(p);
  cout << "Paciente realocado com sucesso!\n";
}

string Hospicio::listarPacientes() {
  if (!pacientes.size())
    throw "É necessário cadastrar pacientes no hospício " + nome + "\n";
  string _pacientes = "";
  for (int i = 0; i < pacientes.size(); i++) {
    _pacientes += pacientes[i]->toString() + "\n";
  }

  return _pacientes;
}

/////////////////////////////////////////REMEDIO/////////////////////////////////////

vector<Remedio *> Hospicio::getRemedios() { return remedios; }

// void Hospicio::comprarRemedio(int index, int qnt) {
//   if (qnt < 0)
//     throw "Quantidade invalida para a compra de " + remedios[index]->getNome() +
//         "\n";
//   remedios[index]->buyComprimidos(qnt);
// }

void Hospicio::listaEstoque() {

  int qnt = remedios.size();
  cout << "------ESTOQUE------\n\n";
  for (int i = 0; i < qnt; i++) {
    cout << remedios[i]->toString();
  }
  cout << "-------------------\n\n";
  cout << endl;
}

void Hospicio::adicionaRemedio(Remedio *r) {

  for (int i = 0; i < 3; i++) {
    if (remedios[i]->getNome() == r->getNome()) {
      remedios[i]->buyComprimidos(r->getComprimidos());
    }
  }
}

// Relatorio

void Hospicio::showTratamentosRealizados() {

  int qnt = tratamentosRealizados.size();
  if (qnt == 0) {
    cout << "Nenhum tratamento realizado até o momento\n";
  }
  for (int i = 0; i < qnt; i++) {
    cout << "Tratamento nº " << i + 1 << endl;
    cout << tratamentosRealizados[i]->toString();
  }

  cout << "Total de médicos cadastrados: " << medicos.size() << endl;
  cout << "Total de pacientes cadastrados: " << pacientes.size() << endl << endl;
  listaEstoque();

  cout << endl;
}

vector<string> Hospicio::split(char dem, string linha) {

  stringstream ss(linha);
  string element;
  vector<string> elements;

  while (getline(ss, element, dem)) {
    element.erase(0, element.find_first_not_of(" \t\n\r\f\v"));
    element.erase(element.find_last_not_of(" \t\n\r\f\v") + 1);

    // cout << element << std::endl;
    elements.push_back(element);
  }

  return elements;
}

void Hospicio::abre() {
  carregaPacientes();
  carregaMedicos();
  carregaTratamento();
  carregaRemedio();
}

void Hospicio::carregaPacientes() {

  ifstream input("Arquivos/Pacientes.txt");
  // Check if the file was opened successfully
  if (!input.is_open()) {
    cout << "Não foi possível abrir o arquivo\n" << endl;
  }

  // Skip the first two lines
  string line;
  for (int i = 0; i < 2; i++) {
    getline(input, line);
  }

  // Read the data from the remaining lines
  while (getline(input, line)) {
    vector<string> atributos = split('-', line);
    Paciente *p;

    if (stoi(atributos[3]) == 1) {
      p = new Esquizofrenico(atributos);
    }
    if (stoi(atributos[3]) == 2) {
      p = new Neurotico(atributos);
    }
    if (stoi(atributos[3]) == 3) {
      p = new TDI(atributos);
    }

    pacientes.push_back(p);
  }

  // Close the file
  input.close();
}

void Hospicio::carregaMedicos() {
  ifstream input("Arquivos/Medicos.txt");

  if (!input.is_open()) {
    cout << "Não foi possível abrir o arquivo\n" << endl;
  }

  // Skip the first two lines
  string line;
  for (int i = 0; i < 2; i++) {
    getline(input, line);
  }

  while (getline(input, line)) {
    vector<string> atributos = split('-', line);
    Medico *m = new Medico(atributos);

    for (int i = 0; i < pacientes.size(); i++) {
      if (pacientes[i]->getIdMedicoResponsavel() == m->getId())
        m->addPaciente(pacientes[i]);
    }

    medicos.push_back(m);
  }

  // Close the file
  input.close();
}

void Hospicio::carregaTratamento() {

  ifstream input("Arquivos/TratamentosRealizados.txt");

  // Check if the file was opened successfully
  if (!input.is_open()) {
    cout << "Não foi possível abrir o arquivo\n" << endl;
  }

  // Skip the first two lines
  string line;
  for (int i = 0; i < 2; i++) {
    getline(input, line);
  }

  // Read the data from the remaining lines
  while (getline(input, line)) {
    vector<string> atributos = split('-', line);
    Tratamento *t = new Tratamento(atributos);

    tratamentosRealizados.push_back(t);
  }

  // Close the file
  input.close();
}

void Hospicio::carregaRemedio() {

  ifstream input("Arquivos/Remedios.txt");

  if (!input.is_open()) {
    cout << "Não foi possível abrir o arquivo\n" << endl;
  }

  // Skip the first two lines
  string line;
  for (int i = 0; i < 2; i++) {
    getline(input, line);
  }

  while (getline(input, line)) {
    vector<string> atributos = split('-', line);
    Remedio *r = new Remedio(atributos);

    adicionaRemedio(r);
  }

  // Close the file
  input.close();
}

void Hospicio::fecha() {
  salvaRemedios();
  salvaTratamentos();
  salvaMedicos();
  salvaPacientes();
}

void Hospicio::salvaRemedios() {

  ofstream output("Arquivos/Remedios.txt");

  if (!output.is_open()) {
    cout << "Não foi possível de criar o arquivo\n";
  }

  int qntRemedios = remedios.size();

  output << "Nome remédio-Quantidade\n\n";
  for (int i = 0; i < qntRemedios; i++) {
    output << remedios[i]->toArchive() << "\n";
  }
  output.close();
}

void Hospicio::salvaTratamentos() {

  ofstream output("Arquivos/TratamentosRealizados.txt");

  if (!output.is_open()) {
    cout << "Não foi possível criar o arquivo\n";
  }

  int qntTratamentos = tratamentosRealizados.size();

  output << "N° tratamento-Médico-Paciente-Tipo da Doença-Remedio-Dosagem\n\n";
  for (int i = 0; i < qntTratamentos; i++) {
    output << i + 1 << "-" << tratamentosRealizados[i]->toArchive() << endl;
  }
  output.close();
}

void Hospicio::salvaMedicos() {

  ofstream output("Arquivos/Medicos.txt");
  if (!output.is_open()) {
    cout << "Não foi possível criar o arquivo\n";
  }

  int qntMedicos = medicos.size();

  output << "Nome-Idade-ID-Max.Pacientes\n\n";

  for (int i = 0; i < qntMedicos; i++) {
    output << medicos[i]->toArchive() << endl;
  }
}

void Hospicio::salvaPacientes() {

  ofstream output("Arquivos/Pacientes.txt");

  if (!output.is_open()) {
    cout << "Não foi possível criar o arquivo\n";
  }

  int qntPacientes = pacientes.size();

  output << "Nome-Idade-ID-Tipo da "
            "Doenca-Remédio-Tratamentonecessário-TratamentoRealizado-"
            "NomeMédicoresponsável-ID Médico responsável\n\n";

  for (int i = 0; i < qntPacientes; i++) {
    output << pacientes[i]->toArchive() << endl;
  }
}
