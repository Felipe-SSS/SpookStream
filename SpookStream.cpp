#include <iostream>
#include <cstring>
#include <fstream>
#include <locale.h>
using namespace std;

// Struct com as informacoes dos filmes
struct Filme
{
	string nome;		// Nome do filme
	int ano_lancamento; // Ano de lancamento do filme
	string genero1;		// Genero principal do filme
	string genero2;		// Genero secundario do filme
};

int main()
{

	// definir localidade para corrigir acentos e caracteres especiais
	// setlocale(LC_ALL, "portuguese");

	// carregando filmes a partir do arquivo
	ifstream r_lista; // variavel de leitura
	string arq_lista = "ListaFilmes.txt";
	Filme filme[100];
	int quant = 0; // quantidade de filmes cadastrados

	r_lista.open(arq_lista.c_str(), ifstream::in);

	while (!r_lista.eof())
	{

		getline(r_lista, filme[quant].nome, '\n');
		r_lista >> filme[quant].ano_lancamento;
		r_lista.ignore();
		getline(r_lista, filme[quant].genero1, '\n');
		getline(r_lista, filme[quant].genero2, '\n');
		quant++;
	}


	// cout << filme[0].nome << endl;
	for (int i = 0; i < quant; i++)
	{

		cout << "Nome do " << i + 1 << "º filme: " << filme[i].nome << endl;
		cout << "Ano de lancamento do " << i + 1 << "º filme: " << filme[i].ano_lancamento << endl;
		cout << "Genero principal do " << i + 1 << "º filme: " << filme[i].genero1 << endl;
		cout << "Genero secundario do " << i + 1 << "º filme: " << filme[i].genero2 << endl
			 << endl;
	}

	return 0;
}