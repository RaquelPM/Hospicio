#include "Medico.h"
#include "Paciente.h"
#include "Remedio.h"
#include "Tratamento.h"
#include <vector>

class Hospicio {
private:
  string nome;
  vector<Remedio *> remedios;
  vector<Medico *> medicos;
  vector<Paciente *> pacientes;
  vector<Tratamento *> tratamentosRealizados;

  int getIndexMedico(int id);
public:
  Hospicio(string nome);
  // void comprarRemedio(int index, int qnt);
  string relatorioGeral();
  static void showMenuInicial();
  static void showMenuPacientes();
  static void showMenuRemedio();
  
   //Médico
  void cadastrarMedico(Medico *medico);
  void demitirMedico(int idMedico);
  Medico* pesquisarMedicoById(int id);
  string listarMedicos();
  string pesquisarMedicoByNome(string nome);
  int selecionarMedicoId();
  void agendaTratamento();
  //Paciente
  void cadastrarPaciente(int idMedico, Paciente *paciente);
  string pesquisarPaciente(string nome);
  string listarPacientes();
  void listarPacientesPendentes();
  int selecionarPacienteId();
  void realocaPacientePendente();
  Paciente* pesquisarPacienteById(int id);
  void curePaciente(int id);
  

  //Remedio
  vector<Remedio*> getRemedios();
  void listaEstoque();
  void adicionaRemedio(Remedio *r);
  

  //Relatorio

  vector<string> split(char dem, string linha);
  void showTratamentosRealizados();
  void abre(); //
  void fecha();
  
  void carregaTratamento();
  void carregaRemedio();
  void carregaPacientes();
  void carregaMedicos();


  void salvaRemedios();
  void salvaTratamentos();
  void salvaMedicos();
  void salvaPacientes();

};