#include <iostream>
#include <sstream>
#include "Hospicio.h"
#include "Esquizofrenico.h"
#include "Neurotico.h"
#include "TDI.h"

int main()
{
  Hospicio *hospicio = new Hospicio("UFPB - Centro de informática");
  hospicio->abre();

  int option;
  Hospicio::showMenuInicial();
  cout << "Opção: ";
  cin >> option;
  cin.ignore();

  while (option != 10)
  {
    switch (option)
    {
    // cadastrar médico
    case 1:
    {
      Medico *m = new Medico();
      m->lerAtributos();
      hospicio->cadastrarMedico(m);

      // mensagem de sucesso
      cout << "Médico cadastrado com sucesso!" << endl;
      break;
    };
    // pesquisar médico
    case 2:
    {
      // pedindo o nome do médico
      string nome;
      cout << "Digite o nome do médico que deseja pesquisar:" << endl;
      getline(cin, nome);

      // pesquisando
      string medicos = hospicio->pesquisarMedicoByNome(nome);

      // mostrando resultados
      cout << "Resultados: " << endl
           << endl;
      cout << medicos << endl;
      break;
    };
    // Listar todos os medicos
    case 3:
    {
      string medicos;
      try
      {
        medicos = hospicio->listarMedicos();
      }
      catch (string e)
      {
        cout << e << endl;
        break;
      }
      cout << "Resultados: " << endl;
      cout << medicos;

      break;
    }
    // Gerenciar pacientes
    case 4:
    {
      int optionPaciente = 0;

      Hospicio::showMenuPacientes();
      cout << "Opção: ";
      cin >> optionPaciente;

      cin.ignore();
      while (optionPaciente != 6)
      {

        switch (optionPaciente)
        {
        // Cadastrar paciente
        case 1:
        {
          int idMedico;
          try
          {
            idMedico = hospicio->selecionarMedicoId();
          }
          catch (string e)
          {
            cout << e << endl;
            break;
          }

          Paciente *p;
          Medico *m = hospicio->pesquisarMedicoById(idMedico);

          int option;
          do
          {
            Paciente::showDiagnosticos();
            cin >> option;

            switch (option)
            {
            case 1:
              p = new Esquizofrenico(m->getNome(), m->getId());
              break;
            case 2:
              p = new Neurotico(m->getNome(), m->getId());
              break;
            case 3:
              p = new TDI(m->getNome(), m->getId());
              break;
            default:
              cout << "Opção inválida" << endl;
            }
          } while (option < 1 || option > 3);
          cin.ignore();

          p->lerAtributos();

          hospicio->cadastrarPaciente(idMedico, p);
          break;
        }
        // Pesquisar paciente
        case 2:
        {
          // pedindo o nome do paciente
          string nome;
          cout << "Digite o nome do paciente que deseja pesquisar:" << endl;
          getline(cin, nome);

          // pesquisando
          string pacientes = hospicio->pesquisarPaciente(nome);

          // mostrando resultados
          cout << "Resultados: " << endl;
          cout << pacientes << endl;
          break;
        }
        // listar paciente
        case 3:
        {
          string pacientes;
          try
          {
            pacientes = hospicio->listarPacientes();
          }
          catch (string e)
          {
            cout << e << endl;
            break;
          }
          cout << "Resultados: " << endl;
          cout << pacientes;

          break;
        }
        // Realocar paciente pendente
        case 4:
        {
          try
          {
            hospicio->realocaPacientePendente();
          }
          catch (string e)
          {
            cout << e << endl;
            break;
          }
          break;
        }
        // Transferir paciente
        case 5:
        {
          cout << "Escolha o paciente que deseja realocar: " << endl;
          int idPaciente;
          try
          {
            idPaciente = hospicio->selecionarPacienteId();
          }
          catch (string e)
          {
            cout << e << endl;
            break;
          }

          Paciente *p = hospicio->pesquisarPacienteById(idPaciente);
          Medico *m = hospicio->pesquisarMedicoById(p->getIdMedicoResponsavel());

          m->deletePaciente(idPaciente);

          cout << "Escolha o médico que vai ser o novo responsável pelo paciente: " << endl;

          int idMedico;
          try
          {
            idMedico = hospicio->selecionarMedicoId();
          }
          catch (string e)
          {
            cout << e << endl;
            break;
          }

          Medico *newM = hospicio->pesquisarMedicoById(idMedico);
          newM->addPaciente(p);

          cout << "Paciente realocado com sucesso!" << endl;

          break;
        }

          // Sair

        default:
          cout << "Opção inválida\n";
        }
        Hospicio::showMenuPacientes();
        cin >> optionPaciente;
        cin.ignore();
      }

      break;
    };
    // Ver estoque
    case 5:
    {

      hospicio->listaEstoque();
      break;
    }
    // realizar tratamento
    case 6:
    {
      try
      {
        hospicio->agendaTratamento();
      }
      catch (string e)
      {
        cout << e << endl;
      }

      break;
    };
    // ver relatorio
    case 7:
    {
      hospicio->showTratamentosRealizados();
      break;
    };
    // Demitir médico
    case 8:
    {
      int certeza;

      int idMedico = hospicio->selecionarMedicoId();
      if (idMedico == -1)
        break;

      cout << "AVISO: TODOS OS PACIENTES DO MÉDICO DEMITIDO FICARÃO SEM PROFISSIONAL RESPONSÁVEL\n";
      cout << "Deseja prosseguir?\n";
      cout << "1 - SIM\n";
      cout << "2 - NÃO\n";
      cin >> certeza;
      while (certeza < 1 || certeza > 2)
      {
        cout << "Opção inválida\n";
        cout << "1 - SIM\n";
        cout << "2 - NÃO\n";
        cin >> certeza;
      }
      cin.ignore();
      if (certeza == 1)
      {
        hospicio->demitirMedico(idMedico);
      }
      break;
    };
    // Comprar remedio
    case 9:
    {

      Hospicio::showMenuRemedio();
      int opcaoRemedio;
      cout << "Opção: ";
      cin >> opcaoRemedio;
      cin.ignore();
      while (opcaoRemedio != 4)
      {
        Remedio *r;
        switch (opcaoRemedio)
        {
          int qnt;

        // Haloperidol
        case 1:
        {

          cout << "Digite a quantidade: ";
          cin >> qnt;
          while (qnt < 0)
          {
            cout << "Quantidade inválida!\n";
            cout << "Digite novamente: ";
            cin >> qnt;
          }
          cin.ignore();
          cout << "A" << endl;
          r = new Remedio("Haloperidol", qnt);
          cout << "Qnt: " << qnt << endl;
          break;
        }
          cout << "B" << endl;
        // Alprazolam
        case 2:
        {

          cout << "Digite a quantidade: ";
          cin >> qnt;
          while (qnt < 0)
          {
            cout << "Quantidade inválida!\n";
            cout << "Digite novamente: ";
            cin >> qnt;
          }
          cin.ignore();

          r = new Remedio("Alprazolam", qnt);

          break;
        }

        case 3:
        {

          cout << "Digite a quantidade: ";
          cin >> qnt;
          while (qnt < 0)
          {
            cout << "Quantidade inválida!\n";
            cout << "Digite novamente: ";
            cin >> qnt;
          }
          cin.ignore();

          r = new Remedio("Risperidona", qnt);

          break;
        }

        default:
          cout << "Opção inválida!\n";
        }
        cout << "Remédio comprado com sucesso!\n";
        hospicio->adicionaRemedio(r);
        Hospicio::showMenuRemedio();
        cin >> opcaoRemedio;
        cin.ignore();
      }

      break;
    };

    default:
      cout << option << endl;
    }

    Hospicio::showMenuInicial();
    cin >> option;
    cin.ignore();
  }
  hospicio->fecha();
}
