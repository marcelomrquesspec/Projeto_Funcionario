//Marcelo Marques Araujo CB3005631

#include <string>
#include <iomanip>
#include <iostream>


using namespace std;


#define SAIR 0
#define INCLUIR 1
#define EXCLUIR 2
#define PESQUISAR 3
#define LISTAR 4

struct Funcionario
{
    int prontuario;
    string nome;
    double salario;
    
};

struct ListaFuncionario
{
	Funcionario funcionario;
	ListaFuncionario* reference;
};

#pragma region metodos Lista
ListaFuncionario* init()
{
	return NULL;
}

int isEmpty(ListaFuncionario* lista)
{
	return (lista == NULL);
}

int count(ListaFuncionario* lista)
{
	int k = 0;
	ListaFuncionario* aux;
	aux = lista;

	while (aux != NULL)
	{
		++k;
		aux = aux->reference;
	}
	return k;
}

ListaFuncionario* insert(ListaFuncionario* lista, Funcionario newFuncionario)
{
	ListaFuncionario* novo = new ListaFuncionario();
	novo->funcionario = newFuncionario;
	novo->reference = lista;

	return novo;
}

ListaFuncionario* find(ListaFuncionario* lista, int prontuario)
{
	ListaFuncionario* aux;
	aux = lista;
	while (aux != NULL && aux->funcionario.prontuario != prontuario)
	{
		aux = aux->reference;
	}
	return aux;
}

ListaFuncionario* remove(ListaFuncionario* lista, int prontuario)
{
	ListaFuncionario *aux;
	
	ListaFuncionario *anterior = NULL;

	aux = lista;
	while (aux != NULL && aux->funcionario.prontuario != prontuario)
	{
		anterior = aux;
		aux = aux->reference;
	}
	
	if (aux == NULL)
	{
		return lista;
	}
	
    cout << "Prontuario: " << aux->funcionario.prontuario << endl;
	if (anterior == NULL)
	{
		lista = aux->reference; 
	}
	else
	{
   	    anterior->reference = aux->reference;
        lista = anterior;
	}
	free(aux);
	return lista;
}
#pragma endregion

#pragma region Funcoes genericas

void separador(){
    cout << endl << endl;
    for (int i = 0; i < 20; i++)
    {
        cout << "=";
    }
    cout << endl << endl;
    
}

int selecionarOpcaoMenu(){
    int opcao;

    cout << "Opções Menu" << endl << endl;


    cout << "0. Sair" << endl;
    cout << "1. Incluir" << endl;
    cout << "2. Excluir" << endl;
    cout << "3. Pesquisar" << endl;
    cout << "4. Listar" << endl;

    cout << endl << "opção: " ;
    cin >> opcao;

    return opcao;
}

void sairCadastro()
{
    cout << "Saiu do cadastro :)" << endl;
    cout << "Fim cadastro!!" << endl;
}

bool hasProntuario(ListaFuncionario* lista, int prontuario)
{
    ListaFuncionario* aux = find(lista, prontuario);
    return aux != NULL;
}

int inputProntuario(){
    int prontuario;

    do
    {
        cout << "Prontuário do Funcionario: ";
        cin >> prontuario;

        if(prontuario < 0){
            cout << endl << "Numero deve ser positivo"  << endl << endl;
        }

    } while (prontuario < 0);

    return prontuario;
}

#pragma region incluir funcionario

int inputProntuarioUnico(ListaFuncionario* lista)
{
    int prontuario;
    bool isPronuarioRepetido = false;

    do
    {
        prontuario = inputProntuario();
        isPronuarioRepetido = hasProntuario(lista, prontuario);

        if(isPronuarioRepetido){
            cout << endl << "Numero ja utilizado"  << endl << endl;
        }

    } while (isPronuarioRepetido);

    return prontuario;
}

string inputNome(){
    string nome;

    cout << "Nome Funcionario: ";
    cin >> nome;

    return nome;
}

double inputSalario(){
    double salario;

    do
    {
        cout << "Salario: ";
        cin >> salario;

        if(salario < 0){
            cout << endl << "Digite um salário valido"  << endl << endl;
        }

    } while (salario < 0);

    return salario;
}

ListaFuncionario* incluirFuncionario(ListaFuncionario* lista)
{
    Funcionario newFuncionario;

    cout << "Adicionar funcionario: " << endl << endl;

    newFuncionario.prontuario = inputProntuarioUnico(lista);
    newFuncionario.nome = inputNome();
    newFuncionario.salario = inputSalario();

    return insert(lista, newFuncionario);
}
#pragma endregion

ListaFuncionario* excluirFuncionario(ListaFuncionario* lista)
{
    int prontuario;
    ListaFuncionario* aux;
    cout << "Excluir funcionario: " << endl << endl;

    prontuario = inputProntuario();
    aux = remove(lista, prontuario);

    return aux;
}

void printFuncionario(Funcionario funcionario)
{
    cout << endl
         << "Prontuario: " << funcionario.prontuario << endl
         << "Nome: " << funcionario.nome << endl
         << "Salario: " << setprecision(2) << funcionario.salario << endl;
}

void pesquisarFuncionario(ListaFuncionario* lista)
{
    int prontuario;
    ListaFuncionario* aux;
    cout << "Pesquisar funcionario: " << endl << endl;

    prontuario = inputProntuario();
    aux = find(lista, prontuario);

    if(aux == NULL){
        cout << endl << "Não há funcionario com o prontuario " << prontuario << endl << endl;
        return;
    }

    printFuncionario(aux->funcionario);
}

void listarFuncionarios(ListaFuncionario* lista)
{
    ListaFuncionario *aux;
    double somaSalarios = 0;
    cout << "Lista de funcionarios: " << endl << endl;

	aux = lista;
	while (aux != NULL)
	{
        printFuncionario(aux->funcionario);
        somaSalarios += aux->funcionario.salario;

		aux = aux->reference;
	}

    cout << endl << "Total dos salários: "
         << setprecision(2) << somaSalarios << endl;
}
#pragma endregion

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "");
    
    int opcao;
    ListaFuncionario* funcionarios = init();

    cout << fixed;
    cout << "Cadastro funcionarios";
    separador();

    while (opcao != SAIR)
    {        
        opcao = selecionarOpcaoMenu();
        
        separador();
        switch (opcao)
        {
            case SAIR :
                sairCadastro();
            break;

            case INCLUIR:
                funcionarios = incluirFuncionario(funcionarios);
            break;

            case EXCLUIR:
                funcionarios = excluirFuncionario(funcionarios);
            break;

            case PESQUISAR:
                pesquisarFuncionario(funcionarios);
            break;

            case LISTAR:
                listarFuncionarios(funcionarios);
            break;
        
            default:
                cout << endl << "Digite um numero de 0 até 4" << endl << endl;
            break;
        }

        separador();

    }       

    return 0;
}