#include <stdlib.h>
#include <new>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <locale.h>

using namespace std;

//Variaveis de nome de usuario global
string nomeUsuario = " ";
int unidadeRedeGeral = NULL;

//Struct Funcionarios
struct loginFuncionario
{
    string nome;
    string usuario;
    string senha;
    string telefone;
    string rg;
    string cpf;
    int unidadeRede;
    bool ativo;
    struct loginFuncionario *proximo;
};
//Struct de agendamento
struct agendamento
{
    string tratamento;
    string cpfPaciente;
    string horario;
    string cpfMedico;
    double valor;
    int unidadeRede;
    bool ativo;
    struct agendamento *proximo;
};
//Struct de unidades da rede
struct unidade
{
    int unidadeRede;
    string nomeRede;
    bool ativo;
    struct unidade *proximo;
};
//Struct de feedback de pacientes
struct feedback
{
    string feedback;
    int tipoFeedback;
    string cpfPaciente;
    struct feedback *proximo;
};
//Struct de pacientes
struct paciente
{
    string nome;
    string telefone;
    string cpf;
    string rg;
    int unidadeRede;
    char genero;
    bool ativo;
    struct paciente *proximo;
};
//struct de medicos
struct medico
{
    string nome;
    string telefone;
    string cpf;
    string rg;
    string crm;
    char genero;
    bool ativo;
    struct medico *proximo;
};
//Struct para salvar os cadastros nos arquivos separados/ struct com as variaveis de todos eles para um salvamento mais rapido
struct salvarCadastro
{
    string nome;
    string usuario;
    string senha;
    string telefone;
    string rg;
    string cpf;
    string tratamento;
    string paciente;
    string horario;
    double valor;
    int idPaciente;
    int idUnidade;
    string cpfPaciente;
    string cpfMedico;
    int idMedico;
    string feedback;
    int tipoFeedback;
    char genero;
    string crm;
    bool ativo;
    struct salvarCadastro *proximo;
};
//Função para limpar tela
void limpaTela()
{
    system("cls");
}
//Referencia dos metodos
bool criarLoginFuncionario(loginFuncionario *&cadastros, string nome, string usuario, string senha, string telefone, string rg, string cpf, bool status, int unidadeRede, bool preCarregamento);

bool criarPaciente(paciente *&cadastros, string nome, char genero, string telefone, string rg, string cpf, bool status, int unidadeRede, bool preCarregamento);

bool criarAgendamento(agendamento *&cadastros, string tratamento, string cpfPaciente, string horario, string cpfMedico, bool status, double valor,int unidadadeRede, bool preCarregamento);

bool criarMedico(medico *&cadastros, string nome, char genero, string telefone, string rg, string cpf, bool status, string crm, bool preCarregamento);

bool criarFeedback(feedback *&cadastros, string feedbackMsg, int tipoFeedback, string cpfPaciente, bool preCarregamento);
//Função de pausa para uma melhor user interface
void pausa()
{
    system("pause");
}
//puxa os dados do txt Cadastro funcionarios e coloca no struct global dos funcionarios
void retornaFuncionariosArquivo(loginFuncionario *&funcionarios)
{

    ifstream input("cadastroFuncionario.txt");
    //String para colocar linha por linha na string
    string textoLido;
    //quantidade de linhas no arquivo
    int qtdLinhas = 0;
    //for para puxar as linhas para string até não ter mais
    for (string line; getline(input, line);)
    {
        //adiciona a linha linda na string
        textoLido += line + "\n";
        //aumenta a quantidade de linhas a cada passada do for
        qtdLinhas++;
    }
    // as sub-strings separadas vão ser colocadas neste vetor
    vector<string> tokens;
    // stream de strings de input inicializado com a string a ser separada
    istringstream tokenizer{textoLido};
    // variável de trabalho
    string token;
    // separa as sub-strings por pipe e coloca no vetor destino
    while (getline(tokenizer, token, '|'))
    {
        tokens.push_back(token);
    }
    //variaveis de ajuda para o for jogar as variaveis corretamente nas devidas casas do struct
    int i = 1;
    //for para enviar as variaveis automaticamente
    for (int j = 0; j < qtdLinhas; j++)
    {
        string nome = tokens[i++];
        string usuario = tokens[i++];
        string senha = tokens[i++];
        string telefone = tokens[i++];
        string rg = tokens[i++];
        string cpf = tokens[i++];
        bool status = (std::stoi(tokens[i++]) == 1) ? true : false; // if ternario para uma melhor taxa de resposta
        int redeUsuario = std::stoi(tokens[i++]);                   //std::stoi função para converter int em string
        //reajuste da variavel para leitura da proxima linha do arquivo
        i++;
        //usamos a função para criar login artificialmente com a ultima casa especificando que é usando dados do txt
        //especificamos isso para não causar uma replicação de dados no arquivo após ele criar o login
        criarLoginFuncionario(funcionarios, nome, usuario, senha, telefone, rg, cpf, status, redeUsuario, true);
    }
    //codigo para excluir a primeira casa da struct para que o primeiro struct não fique vazio
    if (funcionarios->proximo == NULL)
    {
        //crio um novo struct
        loginFuncionario *novoValor = new loginFuncionario;
        novoValor->nome = "";
        novoValor->rg = "";
        novoValor->proximo = NULL;
        //Jogo a referencia do primeiro struct no struct atual
        funcionarios = novoValor;
    }
    else
    {
        //caso ja tenha feito o if acima todos os casos são jogados para a proxima casa da struct
        funcionarios = funcionarios->proximo;
    }
}
//puxa os dados do txt Cadastro pacientes e coloca no struct global dos pacientes
void retornaPacienteArquivo(paciente *&pacientes)
{

    ifstream input("cadastroPaciente.txt");
    //String para colocar linha por linha na string
    string textoLido;
    //quantidade de linhas no arquivo
    int qtdLinhas = 0;
    //for para puxar as linhas para string até não ter mais
    for (string line; getline(input, line);)
    {
        //adiciona a linha linda na string
        textoLido += line + "\n";
        //aumenta a quantidade de linhas a cada passada do for
        qtdLinhas++;
    }
    // as sub-strings separadas vão ser colocadas neste vetor
    vector<string> tokens;
    // stream de strings de input inicializado com a string a ser separada
    istringstream tokenizer{textoLido};
    // variável de trabalho
    string token;
    // separa as sub-strings por pipe e coloca no vetor destino
    while (getline(tokenizer, token, '|'))
    {
        tokens.push_back(token);
    }
    //variaveis de ajuda para o for jogar as variaveis corretamente nas devidas casas do struct
    int i = 1;
    //for para enviar as variaveis automaticamente
    for (int j = 0; j < qtdLinhas; j++)
    {
        string nome = tokens[i++];
        string telefone = tokens[i++];
        string cpf = tokens[i++];
        string rg = tokens[i++];
        char genero = tokens[i++][0];
        bool status = (std::stoi(tokens[i++]) == 1) ? true : false; // if ternario para uma melhor taxa de resposta
        int redeUsuario = std::stoi(tokens[i++]);                   //std::stoi função para converter int em string
        //reajuste da variavel para leitura da proxima linha do arquivo
        i++;
        //usamos a função para criar login artificialmente com a ultima casa especificando que é usando dados do txt
        //especificamos isso para não causar uma replicação de dados no arquivo após ele criar o de paciente
        criarPaciente(pacientes, nome, genero, telefone, rg, cpf, status, redeUsuario, true);
    }
    //codigo para excluir a primeira casa da struct para que o primeiro struct não fique vazio
    if (pacientes->proximo == NULL)
    {
        //crio um novo struct
        paciente *novoValor = new paciente;
        novoValor->nome = "";
        novoValor->rg = "";
        novoValor->proximo = NULL;
        //Jogo a referencia do primeiro struct no struct atual
        pacientes = novoValor;
    }
    else
    {
        //caso ja tenha feito o if acima todos os casos são jogados para a proxima casa da struct
        pacientes = pacientes->proximo;
    }
}
//puxa os dados do txt Cadastro medico e coloca no struct global dos pacientes
void retornaMedico(medico *&medicos)
{

    ifstream input("cadastroMedico.txt");
    //String para colocar linha por linha na string
    string textoLido;
    //quantidade de linhas no arquivo
    int qtdLinhas = 0;
    //for para puxar as linhas para string até não ter mais
    for (string line; getline(input, line);)
    {
        //adiciona a linha linda na string
        textoLido += line + "\n";
        //aumenta a quantidade de linhas a cada passada do for
        qtdLinhas++;
    }
    // as sub-strings separadas vão ser colocadas neste vetor
    vector<string> tokens;
    // stream de strings de input inicializado com a string a ser separada
    istringstream tokenizer{textoLido};
    // variável de trabalho
    string token;
    // separa as sub-strings por pipe e coloca no vetor destino
    while (getline(tokenizer, token, '|'))
    {
        tokens.push_back(token);
    }
    //variaveis de ajuda para o for jogar as variaveis corretamente nas devidas casas do struct
    int i = 1;
    //for para enviar as variaveis automaticamente
    for (int j = 0; j < qtdLinhas; j++)
    {
        string nome = tokens[i++];
        string telefone = tokens[i++];
        string cpf = tokens[i++];
        string rg = tokens[i++];
        string crm = tokens[i++];
        char genero = tokens[i++][0];
        bool status = (std::stoi(tokens[i++]) == 1) ? true : false; // if ternario para uma melhor taxa de resposta
                                                                    //std::stoi função para converter int em string
        i++;

        //reajuste da variavel para leitura da proxima linha do arquivo
        //usamos a função para criar login artificialmente com a ultima casa especificando que é usando dados do txt
        //especificamos isso para não causar uma replicação de dados no arquivo após ele criar o de paciente
        criarMedico(medicos, nome, genero, telefone, rg, cpf, status, crm, true);
    }
    //codigo para excluir a primeira casa da struct para que o primeiro struct não fique vazio
    if (medicos->proximo == NULL)
    {
        //crio um novo struct
        medico *novoValor = new medico;
        novoValor->nome = "";
        novoValor->rg = "";
        novoValor->proximo = NULL;
        //Jogo a referencia do primeiro struct no struct atual
        medicos = novoValor;
    }
    else
    {
        //caso ja tenha feito o if acima todos os casos são jogados para a proxima casa da struct
        medicos = medicos->proximo;
    }
}
//puxa os dados do txt Cadastro agendamento e coloca no struct global dos pacientes
void retornaAgendamento(agendamento *&agendamentos)
{

    ifstream input("cadastroAgendamento.txt");
    //String para colocar linha por linha na string
    string textoLido;
    //quantidade de linhas no arquivo
    int qtdLinhas = 0;
    //for para puxar as linhas para string até não ter mais
    for (string line; getline(input, line);)
    {
        //adiciona a linha linda na string
        textoLido += line + "\n";
        //aumenta a quantidade de linhas a cada passada do for
        qtdLinhas++;
    }
    // as sub-strings separadas vão ser colocadas neste vetor
    vector<string> tokens;
    // stream de strings de input inicializado com a string a ser separada
    istringstream tokenizer{textoLido};
    // variável de trabalho
    string token;
    // separa as sub-strings por pipe e coloca no vetor destino
    while (getline(tokenizer, token, '|'))
    {
        tokens.push_back(token);
    }
    //variaveis de ajuda para o for jogar as variaveis corretamente nas devidas casas do struct
    int i = 1;
    //for para enviar as variaveis automaticamente
    for (int j = 0; j < qtdLinhas; j++)
    {
        string tratamento = tokens[i++];
        string cpfPaciente = tokens[i++];
        string horario = tokens[i++];
        string cpfMedico = tokens[i++];
        double valor = std::stod(tokens[i++]);
        int redeUsuario = std::stoi(tokens[i++]);                   //std::stoi função para converter int em string
        bool status = (std::stoi(tokens[i++]) == 1) ? true : false; // if ternario para uma melhor taxa de resposta
        //reajuste da variavel para leitura da proxima linha do arquivo
        i++;
        //usamos a função para criar login artificialmente com a ultima casa especificando que é usando dados do txt
        //especificamos isso para não causar uma replicação de dados no arquivo após ele criar o de paciente
        criarAgendamento(agendamentos, tratamento, cpfPaciente, horario, cpfMedico, status, valor,redeUsuario, true);
    }
    //codigo para excluir a primeira casa da struct para que o primeiro struct não fique vazio
    if (agendamentos->proximo == NULL)
    {
        //crio um novo struct
        agendamento *novoValor = new agendamento;
        novoValor->tratamento = "";
        novoValor->cpfPaciente = "";
        novoValor->cpfMedico = "";
        novoValor->proximo = NULL;
        //Jogo a referencia do primeiro struct no struct atual
        agendamentos = novoValor;
    }
    else
    {
        //caso ja tenha feito o if acima todos os casos são jogados para a proxima casa da struct
        agendamentos = agendamentos->proximo;
    }
}
//puxa os dados do txt Cadastro feedback e coloca no struct global dos pacientes
void retornaFeedback(feedback *&feedbacks)
{

    ifstream input("cadastroFeedback.txt");
    //String para colocar linha por linha na string
    string textoLido;
    //quantidade de linhas no arquivo
    int qtdLinhas = 0;
    //for para puxar as linhas para string até não ter mais
    for (string line; getline(input, line);)
    {
        //adiciona a linha linda na string
        textoLido += line + "\n";
        //aumenta a quantidade de linhas a cada passada do for
        qtdLinhas++;
    }
    // as sub-strings separadas vão ser colocadas neste vetor
    vector<string> tokens;
    // stream de strings de input inicializado com a string a ser separada
    istringstream tokenizer{textoLido};
    // variável de trabalho
    string token;
    // separa as sub-strings por pipe e coloca no vetor destino
    while (getline(tokenizer, token, '|'))
    {
        tokens.push_back(token);
    }
    //variaveis de ajuda para o for jogar as variaveis corretamente nas devidas casas do struct
    int i = 1;
    //for para enviar as variaveis automaticamente
    for (int j = 0; j < qtdLinhas; j++)
    {
        string feedback = tokens[i++];
        int tipoFeedback = std::stoi(tokens[i++]);
        string cpfPaciente = tokens[i++];
        //reajuste da variavel para leitura da proxima linha do arquivo
        i++;
        //usamos a função para criar login artificialmente com a ultima casa especificando que é usando dados do txt
        //especificamos isso para não causar uma replicação de dados no arquivo após ele criar o de paciente
        criarFeedback(feedbacks, feedback, tipoFeedback, cpfPaciente, true);
    }
    //codigo para excluir a primeira casa da struct para que o primeiro struct não fique vazio
    if (feedbacks->proximo == NULL)
    {
        //crio um novo struct
        feedback *novoValor = new feedback;
        novoValor->feedback = "";
        novoValor->cpfPaciente = "";
        novoValor->tipoFeedback = NULL;
        novoValor->proximo = NULL;
        //Jogo a referencia do primeiro struct no struct atual
        feedbacks = novoValor;
    }
    else
    {
        //caso ja tenha feito o if acima todos os casos são jogados para a proxima casa da struct
        feedbacks = feedbacks->proximo;
    }
}
//Função de salvar arquivos
void salvarArquivo(salvarCadastro *&dadosSalvar, char tipoCadastro)
{
    string titulo = " ";
    string descricao = " ";
    switch (tipoCadastro)
    {
    case 'f':
        titulo = "cadastroFuncionario.txt";
        descricao = "|" + dadosSalvar->nome + "|" + dadosSalvar->usuario + "|" + dadosSalvar->senha + "|" + dadosSalvar->telefone + "|" + dadosSalvar->rg + "|" + dadosSalvar->cpf + "|" + to_string(dadosSalvar->ativo) + "|" + to_string(dadosSalvar->idUnidade) + "|" + "\n";
        break;

    case 'a':
        titulo = "cadastroAgendamento.txt";
        descricao = "|" + dadosSalvar->tratamento + "|" + dadosSalvar->cpfPaciente + "|" + dadosSalvar->horario + "|" + dadosSalvar->cpfMedico + "|" + to_string(dadosSalvar->valor) + "|" + to_string(dadosSalvar->idUnidade) + "|" + to_string(dadosSalvar->ativo) + "|" + "\n";
        break;

    case 'u':
        titulo = "cadastroUnidade.txt";
        descricao = "|" + dadosSalvar->nome + "|" + to_string(dadosSalvar->idUnidade) + "|" + "\n";
        break;

    case 'm':
        titulo = "cadastroMedico.txt";
        descricao = "|" + dadosSalvar->nome + "|" + dadosSalvar->telefone + "|" + dadosSalvar->cpf + "|" + dadosSalvar->rg + "|" + dadosSalvar->crm + "|" + dadosSalvar->genero + "|" + to_string(dadosSalvar->ativo) + "|" + "\n";
        break;

    case 'p':
        titulo = "cadastroPaciente.txt";
        descricao = "|" + dadosSalvar->nome + "|" + dadosSalvar->telefone + "|" + dadosSalvar->cpf + "|" + dadosSalvar->rg + "|" + dadosSalvar->genero + "|" + to_string(dadosSalvar->ativo) + "|" + to_string(dadosSalvar->idUnidade) + "|" + "\n";
        break;

    case 'x':
        titulo = "cadastroFeedback.txt";
        descricao = "|" + dadosSalvar->feedback + "|" + to_string(dadosSalvar->tipoFeedback) + "|" + dadosSalvar->cpfPaciente + "|" + "\n";
        break;
    }
    //Cria o objeto do arquivo
    ofstream arquivoDeSaida;

    //Abre o arquivo
    arquivoDeSaida.open(titulo, std::ios_base::app);

    //Escreve algo
    arquivoDeSaida << descricao;

    //Fecha arquivo
    arquivoDeSaida.close();
}
//função para criar uma nova casa no struct de funcionarios
bool criarLoginFuncionario(loginFuncionario *&cadastros, string nome, string usuario, string senha, string telefone, string rg, string cpf, bool status, int unidadeRede, bool preCarregamento)
{
    loginFuncionario *novoCadastro = new loginFuncionario;
    novoCadastro->nome = nome;
    novoCadastro->usuario = usuario;
    novoCadastro->senha = senha;
    novoCadastro->telefone = telefone;
    novoCadastro->rg = rg;
    novoCadastro->cpf = cpf;
    novoCadastro->unidadeRede = unidadeRede;
    novoCadastro->ativo = status;
    novoCadastro->proximo = NULL;

    loginFuncionario *cd = cadastros;

    //Quando chega no ultimo elemento faz apontar para o novo valor
    while (cd != NULL)
    {
        if (cd->proximo == NULL)
        {
            if (cd->usuario == usuario)
            {
                return false;
            }
            cd->proximo = novoCadastro;
            if (preCarregamento == false)
            {
                salvarCadastro *cadastros = new salvarCadastro;
                cadastros->nome = novoCadastro->nome;
                cadastros->usuario = novoCadastro->usuario;
                cadastros->senha = novoCadastro->senha;
                cadastros->telefone = novoCadastro->telefone;
                cadastros->rg = novoCadastro->rg;
                cadastros->cpf = novoCadastro->cpf;
                cadastros->idUnidade = novoCadastro->unidadeRede;
                cadastros->ativo = novoCadastro->ativo;
                salvarArquivo(cadastros, 'f');
            }
            //Criar um cadastro sempre a frente no vetor
            return true;
        }
        cd = cd->proximo;
    }
}
//função para criar uma nova casa no struct de pacientes
bool criarPaciente(paciente *&cadastros, string nome, char genero, string telefone, string rg, string cpf, bool status, int unidadeRede, bool preCarregamento)
{
    paciente *novoCadastro = new paciente;
    novoCadastro->nome = nome;
    novoCadastro->genero = genero;
    novoCadastro->telefone = telefone;
    novoCadastro->rg = rg;
    novoCadastro->cpf = cpf;
    novoCadastro->unidadeRede = unidadeRede;
    novoCadastro->ativo = status;
    novoCadastro->proximo = NULL;
    paciente *cd = cadastros;

    //Quando chega no ultimo elemento faz apontar para o novo valor
    while (cd != NULL)
    {
        if (cd->proximo == NULL)
        {
            cd->proximo = novoCadastro;
            if (preCarregamento == false)
            {
                salvarCadastro *cadastros = new salvarCadastro;
                cadastros->nome = novoCadastro->nome;
                cadastros->genero = novoCadastro->genero;
                cadastros->telefone = novoCadastro->telefone;
                cadastros->rg = novoCadastro->rg;
                cadastros->cpf = novoCadastro->cpf;
                cadastros->idUnidade = novoCadastro->unidadeRede;
                cadastros->ativo = novoCadastro->ativo;
                salvarArquivo(cadastros, 'f');
            }
            //Criar um cadastro sempre a frente no vetor
            return true;
        }
        cd = cd->proximo;
    }
}
//função para criar uma nova casa no struct de medicos
bool criarMedico(medico *&cadastros, string nome, char genero, string telefone, string rg, string cpf, bool status, string crm, bool preCarregamento)
{
    medico *novoCadastro = new medico;
    novoCadastro->nome = nome;
    novoCadastro->genero = genero;
    novoCadastro->telefone = telefone;
    novoCadastro->rg = rg;
    novoCadastro->cpf = cpf;
    novoCadastro->crm = crm;
    novoCadastro->ativo = true;
    novoCadastro->proximo = NULL;
    medico *cd = cadastros;

    //Quando chega no ultimo elemento faz apontar para o novo valor
    while (cd != NULL)
    {
        if (cd->proximo == NULL)
        {
            cd->proximo = novoCadastro;
            if (preCarregamento == false)
            {
                salvarCadastro *cadastros = new salvarCadastro;
                cadastros->nome = novoCadastro->nome;
                cadastros->telefone = novoCadastro->telefone;
                cadastros->cpf = novoCadastro->cpf;
                cadastros->rg = novoCadastro->rg;
                cadastros->crm = novoCadastro->crm;
                cadastros->genero = novoCadastro->genero;
                cadastros->ativo = novoCadastro->ativo;
                salvarArquivo(cadastros, 'm');
            }
            //Criar um cadastro sempre a frente no vetor
            return true;
        }
        cd = cd->proximo;
    }
}
//função para criar uma nova casa no struct de unidades
bool criarUnidade(unidade *&cadastros, string nome, int idUnidade)
{
    unidade *novoCadastro = new unidade;
    novoCadastro->nomeRede = nome;
    novoCadastro->unidadeRede = idUnidade;
    novoCadastro->ativo = true;
    novoCadastro->proximo = NULL;
    unidade *cd = cadastros;

    //Quando chega no ultimo elemento faz apontar para o novo valor
    while (cd != NULL)
    {
        if (cd->proximo == NULL)
        {
            cd->proximo = novoCadastro;
            salvarCadastro *cadastros = new salvarCadastro;
            cadastros->nome = novoCadastro->nomeRede;
            cadastros->idUnidade = novoCadastro->unidadeRede;
            cadastros->ativo = novoCadastro->ativo;
            salvarArquivo(cadastros, 'u');
            //Criar um cadastro sempre a frente no vetor
            return true;
        }
        cd = cd->proximo;
    }
}
//função para criar uma nova casa no struct de agendamentos
bool criarAgendamento(agendamento *&cadastros, string tratamento, string cpfPaciente, string horario, string cpfMedico, bool status, double valor,int unidadadeRede, bool preCarregamento)
{
    agendamento *novoCadastro = new agendamento;
    novoCadastro->tratamento = tratamento;
    novoCadastro->cpfPaciente = cpfPaciente;
    novoCadastro->horario = horario;
    novoCadastro->cpfMedico = cpfMedico;
    novoCadastro->unidadeRede = unidadadeRede;
    novoCadastro->valor = valor;
    novoCadastro->ativo = true;
    novoCadastro->proximo = NULL;
    agendamento *cd = cadastros;

    //Quando chega no ultimo elemento faz apontar para o novo valor
    while (cd != NULL)
    {
        if (cd->proximo == NULL)
        {
            cd->proximo = novoCadastro;
            if (preCarregamento == false)
            {
                salvarCadastro *cadastros = new salvarCadastro;
                cadastros->tratamento = novoCadastro->tratamento;
                cadastros->cpfPaciente = novoCadastro->cpfPaciente;
                cadastros->cpfMedico = novoCadastro->cpfMedico;
                cadastros->horario = novoCadastro->horario;
                cadastros->idUnidade = novoCadastro->unidadeRede;
                cadastros->valor = novoCadastro->valor;
                cadastros->ativo = novoCadastro->ativo;
                salvarArquivo(cadastros, 'a');
            }
            //Criar um cadastro sempre a frente no vetor
            return true;
        }
        cd = cd->proximo;
    }
}
//função para criar uma nova casa no struct de feedback
bool criarFeedback(feedback *&cadastros, string feedbackMsg, int tipoFeedback, string cpfPaciente, bool preCarregamento)
{
    feedback *novoCadastro = new feedback;
    novoCadastro->feedback = feedbackMsg;
    novoCadastro->cpfPaciente = cpfPaciente;
    novoCadastro->tipoFeedback = tipoFeedback;
    novoCadastro->proximo = NULL;
    feedback *cd = cadastros;

    //Quando chega no ultimo elemento faz apontar para o novo valor
    while (cd != NULL)
    {
        if (cd->proximo == NULL)
        {
            cd->proximo = novoCadastro;
            if (preCarregamento == false)
            {
                salvarCadastro *cadastros = new salvarCadastro;
                cadastros->feedback = novoCadastro->feedback;
                cadastros->cpfPaciente = novoCadastro->cpfPaciente;
                cadastros->tipoFeedback = novoCadastro->tipoFeedback;
                salvarArquivo(cadastros, 'x');
            }
            //Criar um cadastro sempre a frente no vetor
            return true;
        }
        cd = cd->proximo;
    }
}
//Função de cancelar o agendamento
bool cancelarAgendamento(agendamento *&cadastros, string cpfPaciente, string cpfMedico)
{
    agendamento *p = cadastros;
    if (p->cpfMedico == cpfMedico && p->cpfPaciente == cpfPaciente)
    {
        //codigo para excluir a primeira casa da struct para que o primeiro struct não fique vazio
        if (cadastros->proximo == NULL)
        {
            //crio um novo struct
            agendamento *novoValor = new agendamento;
            novoValor->tratamento = "";
            novoValor->valor = 0;
            novoValor->proximo = NULL;
            //Jogo a referencia do primeiro struct no struct atual
            cadastros = novoValor;
        }
        else
        {
            //caso ja tenha feito o if acima todos os casos são jogados para a proxima casa da struct
            cadastros = cadastros->proximo;
        }
        return true;
    }
    else
    {
        while (p->proximo != NULL)
        {
            if (p->cpfPaciente == cpfPaciente && p->cpfMedico == cpfMedico)
            {
                //Cria um auxiliar
                agendamento *aux = new agendamento;
                //Auxiliar Recebe
                aux = p->proximo;
                //Faz com que o proximo pule um elemento
                p->proximo = aux->proximo;

                free(aux);
                return true;
            }
            //Passa o cursor para o proximo
            p = p->proximo;
        }
    }
    return false;
}
//verifico se o login realmente existe
bool verificarLogin(loginFuncionario *&cadastros, string usuario, string senha)
{
    loginFuncionario *vc = cadastros;

    while (vc != NULL)
    {
        if (vc->usuario == usuario && vc->senha == senha)
        {
            nomeUsuario = vc->nome;
            unidadeRedeGeral = vc->unidadeRede;
            return true;
        }
        vc = vc->proximo;
    }
    return false;
}
//função de relatorio que retorna a lista de pacientes por unidades
void verificarPacienteUnidade(paciente *cadastros, int unidadeRede)
{

    paciente *p = cadastros;
    string genero = ((tolower(p->genero) == 'm') ? "Masculino" : "Feminino");
    string statusCadastro = (p->ativo == 0) ? "Inativo" : "Ativo";
    cout << "\n";

    while (p != NULL && p->unidadeRede == unidadeRede)
    {
        cout << "|Nome: " << p->nome << " RG: " << p->rg << " CPF: " << p->cpf << " Sexo: " << genero << " Telefone: " << p->telefone << " Status do cadastro: " << statusCadastro << "|\n";
        p = p->proximo;
    }
    cout << "\n";
}
//função para retornar as listas de struct inteira
void verificarPaciente(paciente *cadastros)
{
    paciente *p = cadastros;
    string statusCadastro = " ";
    string genero = " ";
    while (p != NULL)
    {
        genero = (toupper(p->genero) == 'M') ? "Masculino" : "Feminino";
        statusCadastro = (p->ativo == 0) ? "Inativo" : "Ativo";
        cout << "|Nome: " << p->nome << " Sexo: " << genero << " RG: " << p->rg << " CPF: " << p->cpf << " Telefone: " << p->telefone << " Status do cadastro: " << statusCadastro << "|\n";
        p = p->proximo;
    }
    cout << "\n";
}
//função para retornar as listas de struct inteira
void verificarMedico(medico *cadastros)
{
    medico *m = cadastros;
    string statusCadastro = " ";
    string genero = " ";
    while (m != NULL)
    {
        genero = (toupper(m->genero) == 'M') ? "Masculino" : "Feminino";
        statusCadastro = (m->ativo == 0) ? "Inativo" : "Ativo";
        cout << "|Nome: " << m->nome << " Sexo: " << genero << " CPF: " << m->cpf << " Telefone: " << m->telefone << " Status do cadastro: " << statusCadastro << " CRM: " << m->crm << "|\n";
        m = m->proximo;
    }
    cout << "\n";
}
//função para retornar as listas de struct inteira
void verificarAgendamento(agendamento *cadastros)
{
    agendamento *a = cadastros;
    string statusCadastro = " ";
    while (a != NULL)
    {
        a->valor = (a->valor > 90000000000) ? a->valor = 0 : a->valor = a->valor;
        statusCadastro = (a->ativo == 0) ? "Inativo" : "Ativo";
        cout << "|Tratamento: " << a->tratamento << " Horario: " << a->horario << " Unidade da rede: " << a->unidadeRede << " Valor: " << to_string(a->valor) << " CPF medico: " << a->cpfMedico << " CPF paciente: " << a->cpfPaciente << " Status do cadastro: " << statusCadastro << "|\n";
        a = a->proximo;
    }
    cout << "\n";
}
//função para retornar as listas de struct inteira
void verificarFeedback(feedback *cadastros)
{
    feedback *x = cadastros;
    string tipoFeedback = " ";
    while (x != NULL)
    {
        tipoFeedback = x->tipoFeedback > 0 ? "Elogio" : "Reclamacao";
        cout << "|Tipo: " << tipoFeedback << " Mensagem: " << x->feedback << " CPF paciente: " << x->cpfPaciente << "|\n";
        x = x->proximo;
    }
    cout << "\n";
}
//função para verificar qual unidade mais atende
void verificarUnidadeMaisAtende(agendamento *cadastros)
{
    agendamento *a = cadastros;
    string unidades = "";
    int qtdUnidades = 0;
    while (a != NULL)
    {
        if (unidades.find(std::to_string(a->unidadeRede)) == std::string::npos)
        {
            unidades = unidades + "|" + to_string(a->unidadeRede);
            qtdUnidades++;
        }

        a = a->proximo;
    }

    unidades = unidades.substr(1, unidades.length());
    a = cadastros;

    // as sub-strings separadas vão ser colocadas neste vetor
    vector<string> tokens;
    // stream de strings de input inicializado com a string a ser separada
    istringstream tokenizer{unidades};
    // variável de trabalho
    string token;
    // separa as sub-strings por pipe e coloca no vetor destino
    while (getline(tokenizer, token, '|'))
    {
        tokens.push_back(token);
    }

    // Variáveis de apoio
    int quantidadeConsultasMax = 0;
    int unidadeMaisConsultas = 0;

    //Passa em cada unidade
    for (int i = 0; i < qtdUnidades; i++)
    {
        //Quantidade de consultas da unidade atual do FOR
        int qtdConsultasAtual = 0;
        int unidadeAtual = std::stoi(tokens[i++]);
        //Passa por todos os agendamentos
        while (a != NULL)
        {
            //Se for a unidade atual
            if (a->unidadeRede == unidadeAtual)
            {
                //Adiciona um a quantidade de consultas da unidade atual
                qtdConsultasAtual++;
            }

            //Passa para o próximo agendamento
            a = a->proximo;
        }

        //Se no final a quantidade de consultas desta unidade for maior do que o máximo até agora então refaz a quantidade máxima
        if (quantidadeConsultasMax < qtdConsultasAtual)
        {
            quantidadeConsultasMax = qtdConsultasAtual;
            unidadeMaisConsultas = unidadeAtual;
        }

        //Feito para passar por todos os agendamentos novamente
        a = cadastros;
    }
    cout << "\nA unidade com mais consultas e a unidade " << to_string(unidadeMaisConsultas) << "  com " << to_string(quantidadeConsultasMax) << " consultas.\n";
}
//função para retornar as listas de struct inteira
void verificarPacientePorCpf(paciente *cadastros, string cpfPaciente)
{
    cout << cpfPaciente;
    paciente *p = cadastros;
    string statusCadastro = " ";
    string genero = " ";
    bool exibiu = false;
    while (p != NULL)
    {
        if (p->cpf == cpfPaciente)
        {
            genero = (toupper(p->genero) == 'M') ? "Masculino" : "Feminino";
            statusCadastro = (p->ativo == 0) ? "Inativo" : "Ativo";
            cout << "|Nome: " << p->nome << " Sexo: " << genero << " RG: " << p->rg << " CPF: " << p->cpf << " Telefone: " << p->telefone << " Status do cadastro: " << statusCadastro << "|\n";
            p = p->proximo;
            exibiu = true;
        }
    }
    if (!exibiu)
    {
        cout << "Paciente nao localizado";
    }

    cout << "\n";
}
//função para verificar o paciente que mais veio
void verificarPacienteMaisVeio(agendamento *cadastros, paciente *cadastroPaciente)
{
    agendamento *a = cadastros;
    string pacientes = "";
    int qtdPacientes = 0;
    while (a != NULL)
    {
        if (pacientes.find(a->cpfPaciente) == std::string::npos)
        {
            pacientes = pacientes + "|" + a->cpfPaciente;
            qtdPacientes++;
        }

        a = a->proximo;
    }

    pacientes = pacientes.substr(1, pacientes.length());
    a = cadastros;

    // as sub-strings separadas vão ser colocadas neste vetor
    vector<string> tokens;
    // stream de strings de input inicializado com a string a ser separada
    istringstream tokenizer{pacientes};
    // variável de trabalho
    string token;
    // separa as sub-strings por pipe e coloca no vetor destino
    while (getline(tokenizer, token, '|'))
    {
        tokens.push_back(token);
    }

    // Variáveis de apoio
    int quantidadeConsultasMax = 0;
    string pacienteMaisConsultas = " ";
    //Passa em cada paciente
    for (int i = 0; i < qtdPacientes; i++)
    {
         string cpfPaciente = tokens[i++];

        //Quantidade de consultas da unidade atual do FOR
        int qtdConsultasAtual = 0;
        //Passa por todos os agendamentos
        while (a != NULL)
        {
            //Se for a unidade atual
            if (a->cpfPaciente == cpfPaciente)
            {
                //Adiciona um a quantidade de consultas da unidade atual
                qtdConsultasAtual++;
            }

            //Passa para o próximo agendamento
            a = a->proximo;
        }

        //Se no final a quantidade de consultas deste paciente for maior do que o máximo até agora então refaz a quantidade máxima
        if (quantidadeConsultasMax < qtdConsultasAtual)
        {
            quantidadeConsultasMax = qtdConsultasAtual;
            pacienteMaisConsultas = cpfPaciente;
        }

        //Feito para passar por todos os agendamentos novamente
        a = cadastros;
    }

    cout << "com " << to_string(quantidadeConsultasMax) << " consultas, o paciente que mais veio e:\n";
    verificarPacientePorCpf(cadastroPaciente, pacienteMaisConsultas);
}
//função para retornar as listas de struct inteira
void verificarMedicoPorCpf(medico *cadastros, string cpfMedico)
{
    medico *m = cadastros;
    string statusCadastro = " ";
    string genero = " ";
    bool exibiu = false;
    while (m != NULL)
    {
        if (m->cpf == cpfMedico)
        {
            genero = (toupper(m->genero) == 'M') ? "Masculino" : "Feminino";
            statusCadastro = (m->ativo == 0) ? "Inativo" : "Ativo";
            cout << "|Nome: " << m->nome << " Sexo: " << genero << " RG: " << m->rg << " CPF: " << m->cpf << " Telefone: " << m->telefone << " Status do cadastro: " << statusCadastro << " CRM: " << m->crm << "|\n";
            m = m->proximo;
            exibiu = true;
        }
    }
    if (!exibiu)
    {
        cout << "Medico nao localizado";
    }
    cout << "\n";
}
//função para verificar o medico que mais atendeu
void verificarMedicoMaisAtendeu(agendamento *cadastros, medico *cadastroMedico)
{
    agendamento *a = cadastros;
    string medicos = "";
    int qtdMedicos = 0;
    while (a != NULL)
    {
        if (medicos.find(a->cpfPaciente) == std::string::npos)
        {
            medicos = medicos + "|" + a->cpfMedico;
            qtdMedicos++;
        }

        a = a->proximo;
    }

    medicos = medicos.substr(1, medicos.length());
    a = cadastros;

    // as sub-strings separadas vão ser colocadas neste vetor
    vector<string> tokens;
    // stream de strings de input inicializado com a string a ser separada
    istringstream tokenizer{medicos};
    // variável de trabalho
    string token;
    // separa as sub-strings por pipe e coloca no vetor destino
    while (getline(tokenizer, token, '|'))
    {
        tokens.push_back(token);
    }

    // Variáveis de apoio
    int quantidadeConsultasMax = 0;
    string medicoMaisConsultas = " ";
    //Passa em cada médico
    for (int i = 0; i < qtdMedicos; i++)
    {
        string cpfMedico = tokens[i++];
        //Quantidade de consultas da unidade atual do FOR
        int qtdConsultasAtual = 0;
        //Passa por todos os agendamentos
        while (a != NULL)
        {
            //Se for a unidade atual
            if (a->cpfMedico == cpfMedico)
            {
                //Adiciona um a quantidade de consultas da unidade atual
                qtdConsultasAtual++;
            }

            //Passa para o próximo agendamento
            a = a->proximo;
        }

        //Se no final a quantidade de consultas deste médico for maior do que o máximo até agora então refaz a quantidade máxima
        if (quantidadeConsultasMax < qtdConsultasAtual)
        {
            quantidadeConsultasMax = qtdConsultasAtual;
            medicoMaisConsultas = cpfMedico;
        }

        //Feito para passar por todos os agendamentos novamente
        a = cadastros;
    }

    cout << " com " << to_string(quantidadeConsultasMax) << " consultas, o medico que mais atendeu foi:\n";
    verificarMedicoPorCpf(cadastroMedico, medicoMaisConsultas);
}
//Retorna struct de funcionarios atuais
void verificaFuncionarios(loginFuncionario *funcionarios)
{
    loginFuncionario *f = funcionarios;
    string statusCadastro = " ";

    while (f != NULL)
    {
        statusCadastro = (f->ativo == 0) ? "Inativo" : "Ativo";
        cout << "|Nome: " << f->nome << "| RG: " << f->rg << "| CPF: " << f->cpf << "| Telefone: " << f->telefone << "| Status do cadastro: " << statusCadastro << "| Unidade da rede: " << f->unidadeRede << "|"
             << "\n";
        f = f->proximo;
    }
    cout << "\n";
}
//função de login com switch cases/whiles e funções acima/ função obrigatória para acessar o menu
//caso a função login não retorne um valor true o menu não ira aparecer
bool Login()
{
    // system("color 01");
    //Cria o Inicio da Lista Encadeada
    loginFuncionario *cadastros = new loginFuncionario;
    cadastros->proximo = NULL;

    //Le arquivo
    retornaFuncionariosArquivo(cadastros);
    //Variaveis de Cadastro de Funcionarios e de Login

    int menu = 0;
    string nome;
    string usuario;
    string senha;
    string telefone;
    string cpf;
    string rg;
    int unidadeRede;
    bool ativo;

    while (menu <= 0 || menu >= 4)
    { // While de opçao
        //limpaTela();
        cout << "------------------------------------------ \n";
        cout << "| Sistemas de Gerenciamento de Clinicas  | \n";
        cout << "------------------------------------------ \n";
        cout << "| 1 - Cadastro | 2 - Login | 3 - Sair    | \n";
        cout << "------------------------------------------ \n";
        cout << "Escolha uma opcao acima\n";
        cin >> menu;
    }

    bool opSucesso = false;
    switch (menu)
    {
    case 1:
        while (opSucesso == false)
        {
            cout << "---------------------------------------------- \n";
            cout << "| Cadastro  no Sistema de Funcionarios       | \n";
            cout << "---------------------------------------------- \n";
            cout << "Nome: ";
            cin >> nome;
            cout << "Usuario(Maior de 3 Digitos): ";
            cin >> usuario;
            cout << "Senha(Maior de 5 Digitos): ";
            cin >> senha;
            cout << "Telefone(Com DD|Sem o Traço): ";
            cin >> telefone;
            cout << "RG: ";
            cin >> rg;
            cout << "CPF: ";
            cin >> cpf;
            cout << "Unidade de rede que trabalha: ";
            cin >> unidadeRede;

            if ((usuario.length() >= 3 && senha.length() >= 5 && nome.length() <= 15 && telefone.length() == 11 && rg.length() == 9 && cpf.length() == 11) && criarLoginFuncionario(cadastros, nome, usuario, senha, telefone, rg, cpf, true, unidadeRede, false) == true)
            {
                limpaTela();
                cout << "Cadastrado com Sucesso\n";
                pausa();
                opSucesso = true;
            }
            else
            {
                limpaTela();
                cout << "Dados incorretos\n";
                pausa();
            }
        }
    case 2:
        opSucesso = false;
        while (opSucesso != true)
        {
            limpaTela();
            cout << "--------------------------------------- \n";
            cout << "|                Login                | \n";
            cout << "---------------------------------------\n";

            cout << "--------------------------------------- \n";
            cout << "|               Usuario               | \n";
            cout << "--------------------------------------- \n";
            cout << "Usuario: ";
            cin >> usuario;
            cout << "--------------------------------------- \n";
            cout << "|                Senha                | \n";
            cout << "--------------------------------------- \n";
            cout << "Senha: ";
            cin >> senha;

            if ((usuario.length() >= 3 && senha.length() >= 5) && verificarLogin(cadastros, usuario, senha) == true)
            {
                limpaTela();
                cout << "Logado com Sucesso\n";
                pausa();
                return true;
            }
            else
            {
                limpaTela();
                cout << "Dados Incorretos\n";
                pausa();
            }
        }
        break;
    }
}
//menu para acesso de todas as funções/ com switch cases / whiles e tratamento de erros
void Menu()
{
    //system("color 01");
    setlocale(LC_ALL, "Portuguese_Brasil");
    loginFuncionario *cadastrosMenu = new loginFuncionario;
    cadastrosMenu->nome = " ";
    cadastrosMenu->usuario = " ";
    cadastrosMenu->senha = " ";
    cadastrosMenu->telefone = " ";
    cadastrosMenu->rg = " ";
    cadastrosMenu->cpf = " ";
    cadastrosMenu->unidadeRede = NULL;
    cadastrosMenu->ativo = NULL;
    cadastrosMenu->proximo = NULL;

    retornaFuncionariosArquivo(cadastrosMenu);

    paciente *cadastroPaciente = new paciente;
    cadastroPaciente->nome = " ";
    cadastroPaciente->rg = " ";
    cadastroPaciente->cpf = " ";
    cadastroPaciente->telefone = " ";
    cadastroPaciente->unidadeRede = NULL;
    cadastroPaciente->genero = ' ';
    cadastroPaciente->ativo = NULL;
    cadastroPaciente->proximo = NULL;

    retornaPacienteArquivo(cadastroPaciente);

    medico *cadastroMedico = new medico;
    cadastroMedico->nome = " ";
    cadastroMedico->rg = " ";
    cadastroMedico->cpf = " ";
    cadastroMedico->telefone = " ";
    cadastroMedico->crm = "";
    cadastroMedico->genero = ' ';
    cadastroMedico->ativo = NULL;
    cadastroMedico->proximo = NULL;

    retornaMedico(cadastroMedico);

    agendamento *cadastroAgendamento = new agendamento;
    cadastroAgendamento->tratamento = " ";
    cadastroAgendamento->unidadeRede = NULL;
    cadastroAgendamento->valor = NULL;
    cadastroAgendamento->cpfMedico = " ";
    cadastroAgendamento->cpfPaciente = " ";
    cadastroAgendamento->horario = " ";
    cadastroAgendamento->ativo = NULL;
    cadastroAgendamento->proximo = NULL;

    retornaAgendamento(cadastroAgendamento);

    feedback *cadastroFeedback = new feedback;
    cadastroFeedback->feedback = " ";
    cadastroFeedback->cpfPaciente = " ";
    cadastroFeedback->tipoFeedback = NULL;
    cadastroFeedback->proximo = NULL;
    retornaFeedback(cadastroFeedback);

    unidade *cadastroUnidade = new unidade;
    cadastroUnidade->nomeRede = " ";
    cadastroUnidade->unidadeRede = NULL;
    cadastroUnidade->ativo = NULL;
    cadastroUnidade->proximo = NULL;

    string nome = " ";
    string usuario = " ";
    string senha = " ";
    string telefone = " ";
    string rg = " ";
    string cpf = " ";
    char resp = ' ';
    char genero = ' ';
    string crm = " ";
    int unidadeRede = NULL;
    int menu = 0;
    string tratamento = " ";
    string cpfMedico = " ";
    string cpfPaciente = " ";
    string horario = " ";
    double valor = NULL;
    string feedback = " ";
    int tipoFeedback = NULL;
    bool opSucesso = false;

    while (menu <= 0 || menu >= 4)
    {

        limpaTela();
        printf("----------------------------------------------- \n");
        printf("|                  Tela Inicial               | \n");
        printf("|                  Bem Vindo(a)               | \n");
        printf("----------------------------------------------- \n");
        cout << "Nome: " << nomeUsuario << " Unidade: " << unidadeRedeGeral << "\n";
        printf("----------------------------------------------- \n");
        printf("| 1 - Operacional | 2 - Relatorios | 3 - Sair | \n");
        printf("----------------------------------------------- \n");

        printf("Digite a opcao valida:");
        scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            menu = 0;
            while (menu < 1 || menu > 3)
            {
                limpaTela();
                printf("-------------------------------------------- \n");
                printf("|                Operacional               | \n");
                printf("-------------------------------------------- \n");
                printf("| 1 - Cadastrar | 2 - Consultar | 3 - Sair | \n");
                printf("-------------------------------------------- \n");
                cin >> menu;
            }
            switch (menu)
            {
            case 1:
                menu = 0;
                while (menu <= 0 || menu > 7)
                {
                    limpaTela();
                    printf("-------------------------------------------------------------------------------------------------------------\n");
                    printf("|                                                  Cadastrar                                                |\n");
                    printf("-------------------------------------------------------------------------------------------------------------\n");
                    printf("| 1 - Funcionario | 2 - Paciente | 3 - Medico  | 4 - Agendamento | 5 - Reclamacoes | 6 - Elogios | 7 - Sair |\n");
                    printf("-------------------------------------------------------------------------------------------------------------\n");
                    printf("Digite a opcao:");
                    scanf("%d", &menu);

                    switch (menu)
                    {
                    case 1:
                        while (opSucesso == false)
                        {
                            cout << "---------------------------------------------- \n";
                            cout << "| Cadastro  no Sistema de Funcionarios       | \n";
                            cout << "---------------------------------------------- \n";
                            cout << "Nome: ";
                            cin >> nome;
                            cout << "Usuario(Maior de 3 Digitos): ";
                            cin >> usuario;
                            cout << "Senha(Maior de 5 Digitos): ";
                            cin >> senha;
                            cout << "Telefone(Com DD|Sem o Traço): ";
                            cin >> telefone;
                            cout << "RG: ";
                            cin >> rg;
                            cout << "CPF: ";
                            cin >> cpf;
                            cout << "Unidade de rede que trabalha: ";
                            cin >> unidadeRede;

                            if ((usuario.length() >= 3 && senha.length() >= 5 && nome.length() <= 15 && telefone.length() == 11 && rg.length() == 9 && cpf.length() == 11) && criarLoginFuncionario(cadastrosMenu, nome, usuario, senha, telefone, rg, cpf, true, unidadeRede, false) == true)
                            {
                                limpaTela();
                                cout << "Cadastrado com Sucesso\n";
                                opSucesso = true;
                            }
                            else
                            {
                                limpaTela();
                                cout << "Dados incorretos\n";
                            }
                        }
                        pausa();
                        break;
                    case 2:
                        while (opSucesso == false)
                        {
                            cout << "---------------------------------------------- \n";
                            cout << "|           Cadastro de Pacientes            | \n";
                            cout << "---------------------------------------------- \n";
                            cout << "Nome do paciente: ";
                            cin >> nome;
                            cout << "Telefone: ";
                            cin >> telefone;
                            cout << "RG: ";
                            cin >> rg;
                            cout << "CPF: ";
                            cin >> cpf;
                            cout << "Genero (M) ou (F): ";
                            cin >> genero;

                            if ((nome.length() <= 15 && telefone.length() == 11 && rg.length() == 9 && cpf.length() == 11 && (tolower(genero) == 'm' || tolower(genero) == 'f')) && criarPaciente(cadastroPaciente, nome, genero, telefone, rg, cpf, true, unidadeRedeGeral, false) == true)
                            {
                                limpaTela();
                                cout << "Paciente Cadastrado com Sucesso\n";
                                opSucesso = true;
                            }
                            else
                            {
                                limpaTela();
                                cout << "Dados incorretos\n";
                            }
                        }
                        pausa();
                        break;
                    case 3:
                        while (opSucesso == false)
                        {
                            cout << "-----------------------------------------------\n";
                            cout << "|             Cadastro de medicos             |\n";
                            cout << "-----------------------------------------------\n";
                            cout << "Nome do medico(a): ";
                            cin >> nome;
                            cout << "Telefone: ";
                            cin >> telefone;
                            cout << "RG: ";
                            cin >> rg;
                            cout << "CPF: ";
                            cin >> cpf;
                            cout << "Genero (M) ou (F): ";
                            cin >> genero;
                            cout << "CRM: ";
                            cin >> crm;

                            if ((nome.length() <= 15 && telefone.length() == 11 && rg.length() == 9 && cpf.length() == 11 && (tolower(genero) == 'm' || tolower(genero) == 'f') && crm.length() >= 6) && criarMedico(cadastroMedico, nome, genero, telefone, rg, cpf, true, crm, false) == true)
                            {
                                limpaTela();
                                cout << "Medico Cadastrado com Sucesso\n";
                                opSucesso = true;
                            }
                            else
                            {
                                limpaTela();
                                cout << "Dados incorretos\n";
                            }
                        }
                        break;
                    case 4:
                        while (opSucesso == false)
                        {
                            cout << "-----------------------------------------------\n";
                            cout << "|           Cadastro de agendamento           |\n";
                            cout << "-----------------------------------------------\n";
                            cout << "Tratamento: ";
                            cin >> tratamento;

                            cout << "Cpf do medico: ";
                            cin >> cpfMedico;

                            cout << "Cpf do paciente: ";
                            cin >> cpfPaciente;

                            cout << "Horario: ";
                            cin >> horario;

                            cout << "Valor: ";
                            cin >> valor;

                            cout << "Unidade da rede: ";
                            cin >> unidadeRede;

                            if ((tratamento.length() <= 30 && horario.length() > 10 && cpfPaciente.length() == 11 && cpfMedico.length() == 11 && valor > 0 && unidadeRede > 0) && criarAgendamento(cadastroAgendamento, tratamento, cpfPaciente, horario, cpfMedico, true, valor,unidadeRede, false) == true)
                            {
                                limpaTela();
                                cout << "Agendamento cadastrado com Sucesso\n";
                                opSucesso = true;
                                pausa();
                            }
                            else
                            {
                                limpaTela();
                                cout << "Dados incorretos\n";
                                pausa();
                            }
                        }
                        break;
                    case 5:
                    {
                        cout << "------------------------------------------------\n";
                        cout << "|           Cadastro de reclamacoes            |\n";
                        cout << "------------------------------------------------\n";
                        cout << "Reclamacao: ";
                        cin >> feedback;
                        cout << "Cpf do paciente: ";
                        cin >> cpfPaciente;

                        if ((feedback.length() <= 60 && cpfPaciente.length() == 11) && criarFeedback(cadastroFeedback, feedback, 0, cpfPaciente, false) == true)
                        {
                            limpaTela();
                            cout << "Reclamacao cadastrado com Sucesso\n";
                            opSucesso = true;
                        }
                        else
                        {
                            limpaTela();
                            cout << "Dados incorretos\n";
                        }
                    }
                    break;
                    case 6:
                        while (opSucesso == false)
                        {
                            cout << "--------------------------------------------\n";
                            cout << "|           Cadastro de elogios            |\n";
                            cout << "--------------------------------------------\n";
                            cout << "Elogio: ";
                            cin >> feedback;
                            cout << "Cpf do paciente: ";
                            cin >> cpfPaciente;

                            if ((feedback.length() <= 60 && cpfPaciente.length() == 11) && criarFeedback(cadastroFeedback, feedback, 1, cpfPaciente, false) == true)
                            {
                                limpaTela();
                                cout << "Elogio cadastrado com Sucesso\n";
                                opSucesso = true;
                            }
                            else
                            {
                                limpaTela();
                                cout << "Dados incorretos\n";
                            }
                        }
                        break;
                    case 7:

                        break;
                    }
                    opSucesso = false;
                    break;
                    menu = 0;
                }

            case 2:
                menu = 0;
                while (menu < 1 || menu > 7)
                {
                    limpaTela();
                    printf("--------------------------------------------------------------------------------------------------------------------\n");
                    printf("|                                                  Consultar                                                       |\n");
                    printf("--------------------------------------------------------------------------------------------------------------------\n");
                    printf("| 1 - Funcionario | 2 - Paciente | 3 - Medico  | 4 - Agendamento | 5 - Feedback (reclamacoes e elogios) | 6 - Sair |\n");
                    printf("--------------------------------------------------------------------------------------------------------------------\n");
                    printf("Digite a opcao:");
                    scanf("%d", &menu);
                    switch (menu)
                    {
                    case 1:
                        verificaFuncionarios(cadastrosMenu);
                        pausa();
                        break;
                    case 2:
                        verificarPaciente(cadastroPaciente);
                        pausa();
                        break;
                    case 3:
                        verificarMedico(cadastroMedico);
                        pausa();
                        break;
                    case 4:
                        verificarAgendamento(cadastroAgendamento);
                        pausa();
                        cout << "Gostaria de cancelar algum agendamento? (S ou N)";
                        cin >> resp;
                        if (tolower(resp) == 's')
                        {
                            cout << "CPF do Medico: ";
                            cin >> cpfMedico;
                            cout << "CPF do Paciente: ";
                            cin >> cpfPaciente;
                            if (cancelarAgendamento(cadastroAgendamento, cpfMedico, cpfPaciente) == true && (cpfMedico.length() == 11 && cpfPaciente.length() == 11))
                            {
                                cout << "Cancelado com sucesso\n";
                            }
                            else
                            {
                                cout << "Dados incorretos ou agendamento nao existe\n";
                            }
                            pausa();
                        }
                        break;
                    case 5:
                        verificarFeedback(cadastroFeedback);
                        pausa();
                        break;
                    }
                    if (menu != 6)
                    {
                        menu = 0;
                    }
                }
                menu = 0;
                break;
            }
            break;

        case 2:
            menu = 0;
            while (menu < 1 || menu > 7)
            {
                limpaTela();
                printf("------------------------------------------------------------------------------- \n");
                printf("|                                   Relatorios                                | \n");
                printf("------------------------------------------------------------------------------- \n");
                printf("| 1 - pacientes por unidade da rede                                           | \n");
                printf("| 2 - unidade da rede que mais atende                                         | \n");
                printf("| 3 - Paciente que mais veio                                                  |\n");
                printf("| 4 - Medico que mais atendeu                                                 |\n");
                printf("| 5 - totalizacao diario do faturamento por unidade de rede e total da rede   |\n");
                printf("| 6 - totalizacao mensal do faturamento por unidade de rede e total da rede   |\n");
                printf("| 7 - Sair                                                                    |\n");
                printf("---------------------------------------------------------------------------- \n");
                cin >> menu;
                int unidadeRede = 0;
                switch (menu)
                {
                case 1:
                    cout << "Unidade da rede que deseja consultar: ";
                    cin >> unidadeRede;
                    verificarPacienteUnidade(cadastroPaciente, unidadeRede);
                    break;

                case 2:
                    cout << "Unidade da rede que mais atende ";
                    verificarUnidadeMaisAtende(cadastroAgendamento);
                    break;

                case 3:
                    cout << "Paciente que mais veio ";
                    verificarPacienteMaisVeio(cadastroAgendamento, cadastroPaciente);
                    break;

                case 4:
                    cout << "Medico que mais atendeu";
                    verificarMedicoMaisAtendeu(cadastroAgendamento, cadastroMedico);
                    break;

                case 5:
                    cout << "Nao ha registros suficientes para puxar este relatorio\n";
                    break;
                case 6:
                    cout << "Nao ha registros suficientes para puxar este relatorio\n";
                    break;
                case 7:
                    opSucesso = true;
                    break;
                }
                if (menu > 0 && menu < 8)
                {
                    pausa();
                    limpaTela();
                }
            }
        }
    }
}
//Classe main
int main()
{
    if (Login() == true)
    {
        Menu();
    }
    limpaTela();
    cout << "Ate Breve\n";
    return 0;
}