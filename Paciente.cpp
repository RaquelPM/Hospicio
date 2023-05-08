#include "Paciente.h"

vector<int> Paciente::idUtilizados = {};

Paciente::Paciente() : Pessoa() {
  nomeMedicoResponsavel = ala = remedio = "";
  tratamentoNecessario = tratamentosRealizados = 0;
}

Paciente::Paciente(string nome, int idade, int tratamentoNecessario, string nomeMedicoResponsavel, int idMedicoResponsavel)  : Pessoa(nome, idade){
  this->tratamentoNecessario = tratamentoNecessario;
  setMedicoResponsavel(nomeMedicoResponsavel, idMedicoResponsavel);
  tratamentosRealizados = 0;
  setId();
}

Paciente::Paciente(vector<string> atributos){
  nome = atributos[0];
  idade = stoi(atributos[1]);
  tratamentoNecessario = stoi(atributos[5]);
  tratamentosRealizados = stoi(atributos[6]);
  nomeMedicoResponsavel = atributos[7];
  idMedicoResponsavel = stoi(atributos[8]);
  id = stoi(atributos[2]);
  idUtilizados.push_back(id);
}

void Paciente::showAtributos(){
  cout << "Digite o nome, idade e quantidade de tratamento necessário para a cura, nesta ordem." << endl;
}

void Paciente::showDiagnosticos(){
  cout << "Digite qual diagnóstico o paciente possui:" << endl;
  cout << "1 - Esquizofrenia" << endl;
  cout << "2 - Neurose" << endl;
  cout << "3 - Transtorno de personalidade" << endl;
}

void Paciente::lerAtributos(){
  Pessoa::lerAtributos();

  cout << "Tratamento necessário: ";
  cin >> tratamentoNecessario;
  while(tratamentoNecessario < 0){
    cout << "Tratamento necessário inválido, digite novamente\n";
    cout << "Tratamento necessário: ";
    cin >> tratamentoNecessario;
  }
  setId();
  cin.ignore();
}

bool Paciente::realizarTratamento(Remedio* &remedioUtilizado) { //A quantidade do remedio tem que ser descontado do array do hospicio
  int t = tratamentoNecessario;
  tratamentoNecessario -= remedioUtilizado->getComprimidos();
  tratamentosRealizados++;
  remedioUtilizado->setComprimidos(t);
  
  if (tratamentoNecessario <= 0) 
    return true;
  return false;
}

string Paciente::getRemedio() { return remedio; }

string Paciente::toString() {
  
  return Pessoa::toString() + "Doença: " + ala + '\n' +
         "Tratavel com: " + remedio + '\n' +
         "Medico responsavel: " + nomeMedicoResponsavel + '\n' +
         "Tratamentos para cura: " + to_string(tratamentoNecessario) + '\n' +
         "Tratamentos realizados: " + to_string(tratamentosRealizados) + "\n\n";
}

string Paciente::toArchive(){

  int tipo;

  if(ala == "Esquizofrenia"){
    tipo = 1;
  }
  if(ala == "Neuróticos"){
    tipo = 2;
  }
  if(ala == "TDI"){
    tipo = 3;
  }

  return nome + "-" + to_string(idade) + "-" + to_string(id) + "-" + to_string(tipo) + "-" + remedio + "-" + to_string(tratamentoNecessario) + "-" + to_string(tratamentosRealizados) + "-" + nomeMedicoResponsavel + "-" + to_string(idMedicoResponsavel);
}

bool Paciente::checaId(int id){
  int qntIdUtilizados = idUtilizados.size();
  for(int i = 0; i < qntIdUtilizados; i++){
    if(idUtilizados[i] == id){
      return false;
    }
  }
  return true;
}

void Paciente::setId(){
  int idTeste;
  while(1){
    idTeste = rand() % 1000 + 1; //Criando ID do paciente entre 1 e 1000;
    if(checaId(idTeste)){ //Se o id gerado ainda não tiver sido utilizado
      id = idTeste;
      idUtilizados.push_back(id);
      break;
    } 
  }
}

void Paciente::liberaId(int id){
  int qntIdUtilizados = idUtilizados.size();
    for(int i = 0; i < qntIdUtilizados; i++){
      if(idUtilizados[i] == id){
       idUtilizados.erase(idUtilizados.begin() + i);
        break;
      }
    }
}

void Paciente::setMedicoResponsavel(string nomeMedicoResponsavel, int idMedicoResponsavel){
  this->nomeMedicoResponsavel =nomeMedicoResponsavel;
  this->idMedicoResponsavel = idMedicoResponsavel;
}

string Paciente::getMedicoResponsavel(){
  return nomeMedicoResponsavel; 
}

string Paciente::getAla(){return ala;}

int Paciente::getTratamentoNecessario(){return tratamentoNecessario;}

int Paciente::getTratamentoRealizados(){return tratamentosRealizados;}

int Paciente::getIdMedicoResponsavel(){return idMedicoResponsavel;}