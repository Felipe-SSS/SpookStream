#include <iostream>
#include <locale.h>
#include <cstring>
#include <fstream>
#include <iomanip> // tabela

using namespace std;

// struct com os dados dos filmes
struct dados {
  string nome;         // nome do filme
  int ano_lancamento;  // ano de lançamento do filme
  string genero1;      // gênero principal do filme
  string genero2;      // gênero secundário do filme
  float probabilidade; // chance de recomendar o filme ao usuário
};

// função de início
// mostrar catalógo e ler filmes favoritos do usuário
void inicio(int quant, dados filmes[], dados *filmesSelecionados[]) {

  int cont = 1; // contador para ajudar no ajuste do catálogo em forma de tabela
  int numFilme; // numero que usuário escolherá na seleção de filmes

  cout << "\nSeja bem-vindo(a) ao SpookStream!" << endl;
  cout << "\nPara sua melhor experiência selecione o número correspondente ao seu filme favorito:\n" << endl;

  // mostrando nome do filmes em formato de tabela
  for (int i = 0; i < quant; i++) {

    // left - alinha conteúdo à esquerda
    // setw - witdh (largura) de cada célula
    cout << left << i + 1 << " - " << setw(30) << filmes[i].nome;

    if (cont == 3) {
      // adiciona quebra de linha a cada 3 filmes
      cout << endl;
      cont = 0;
    }

    cont++;
  }
  // quebra de linha final
  cout << endl;

  // lendo filmes selecionados
  for (int i = 0; i < 3; i ++) {
    cin >> numFilme;
    
    // se o filme não estiver no catálogo será pedido que digite novamente
    while (numFilme < 1 || numFilme >= quant) {
      cout << "Esse filme não está no catálogo. Digite outro número:" << endl;
      cin >> numFilme;
    }

    filmesSelecionados[i] = filmes[numFilme - 1];

    cout << "Filme escolhido: " << filmes[numFilme - 1].nome << endl;
    cout << "\nEscolha outro filme: " << endl;
  }

}

int main() {

  setlocale(LC_ALL, "portuguese");

  dados filmes[100];
  int quant = 0; // contador de filmes

  ifstream lista;
  string arq_lista = "ListaFilmes.txt";

  // filmes que o usuário irá escolher na tela inicial
  dados filmesSelecionados[3];

  // abrindo arquivo de texto
  lista.open(arq_lista.c_str(), ifstream::in);

  // lendo filmes do arquivo e guardando-os em uma variável
  while (!lista.eof()) {
    getline(lista, filmes[quant].nome, '\n');
    lista >> filmes[quant].ano_lancamento;
    lista.ignore();
    getline(lista, filmes[quant].genero1, '\n');
    getline(lista, filmes[quant].genero2, '\n');
    quant++; 
  }

  // chamando função de início
  inicio(quant, filmes, filmesSelecionados);

  // fechando arquivo de texto
  lista.close();

  return 0;
}