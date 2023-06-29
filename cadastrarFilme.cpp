#include <fstream>
#include <iostream>

using namespace std;

struct Filme {
  string nome;
  string genero1;
  string genero2;
  int ano_lancamento;
};

int main() {
  // nome do arquivo
  string fileName = "ListaFilmes.txt";

  // Leitura dos registros existentes
  string linha;

  // Adição dos novos filmes
  int n;
  cout << "Quantos filmes deseja adicionar ao arquivo?" << endl;
  cin >> n;

  ofstream filmesOut(fileName, ofstream::app);

  for (int i = 0; i < n; i++) {
    Filme filme;

    cout << "Digite o nome do filme: ";
    cin.ignore();
    getline(cin, filme.nome);

    cout << "Digite o ano de lançamento do filme: ";
    cin >> filme.ano_lancamento;
    
    cout << "Digite o gênero principal do filme: ";
    getline(cin, filme.genero1);

    cout << "Digite o gênero secundário do filme: ";
    getline(cin, filme.genero2);

  

    // muda a linha antes escrever
    filmesOut << endl;
    filmesOut << filme.nome << endl;
    filmesOut << filme.ano_lancamento << endl;
    filmesOut << filme.genero1 << endl;
    filmesOut << filme.genero2;

    cout << endl;
  }

  filmesOut.close();

  return 0;
}