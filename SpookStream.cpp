#include <iostream>
#include <cstring>
#include <fstream>
#include <locale.h>
using namespace std;

// Struct com as informacoes dos filmes
struct Filme{ 
	string nome; // Nome do filme
	int ano_lancamento; // Ano de lancamento do filme
	string genero1; // Genero principal do filme
	string genero2; // Genero secundario do filme
};

int main(){
	
	setlocale(LC_ALL, "portuguese");
	
	ifstream lista;
	string arq_lista = "ListaFilmes.txt";
	Filme filme[100];
	int quant = 0;

	lista.open(arq_lista.c_str(), ifstream::in);
	
	while(!lista.eof()){

		getline(lista, filme[quant].nome, '\n');
		lista >> filme[quant].ano_lancamento;
		lista.ignore();
		getline(lista, filme[quant].genero1, '\n');
		getline(lista, filme[quant].genero2, '\n');
		quant++; // Vê quantidade total de filmes

	}

	for(int i=0; i<quant; i++){

		cout << "Nome do " << i+1 << "º filme: " << filme[i].nome << endl;
		cout << "Ano de lancamento do " << i+1 << "º filme: " << filme[i].ano_lancamento << endl; 
		cout << "Genero principal do " << i+1 << "º filme: " << filme[i].genero1 << endl; 
		cout << "Genero secundario do " << i+1 << "º filme: " << filme[i].genero2 << endl << endl; 
		 
	}

	return 0;
}