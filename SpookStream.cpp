#include <cstring>
#include <fstream>
#include <iomanip> // tabela
#include <iostream>
#include <locale.h>

using namespace std;

// struct com os Filme dos filmes
struct Filme
{
  string nome;         // nome do filme
  int ano_lancamento;  // ano de lançamento do filme
  string genero1;      // gênero principal do filme
  string genero2;      // gênero secundário do filme
  float probabilidade; // chance de recomendar o filme ao usuário
};

struct indices
{
  string genero; // genero do filme
  int indice;    // indice do filme na matriz de similaridade
};

// matriz que contém as similaridades entre os gêneros dos filmes
// consulte o README
float matrizSimilaridade[11][11] = {{1, 0.8, 0.35, 0.3, 0.6, 0.7, 0.75, 0.4, 0.1, 0.55},
                                    {0.8, 1, 0.3, 0.25, 0.4, 0.5, 0.6, 0.3, 0.15, 0.5},
                                    {0.35, 0.3, 1, 0.8, 0.2, 0.25, 0.35, 0.15, 0.05, 0.3},
                                    {0.3, 0.25, 0.8, 1, 0.3, 0.2, 0.3, 0.1, 0.05, 0.25},
                                    {0.6, 0.4, 0.2, 0.3, 1, 0.35, 0.45, 0.3, 0.3, 0.4},
                                    {0.7, 0.5, 0.25, 0.2, 0.35, 1, 0.8, 0.6, 0.05, 0.45},
                                    {0.75, 0.6, 0.35, 0.3, 0.45, 0.8, 1, 0.65, 0.05, 0.55},
                                    {0.4, 0.3, 0.15, 0.1, 0.3, 0.6, 0.65, 1, 0.05, 0.5},
                                    {0.1, 0.15, 0.05, 0.05, 0.3, 0.05, 0.05, 0.05, 1, 0.2},
                                    {0.55, 0.5, 0.3, 0.25, 0.4, 0.45, 0.55, 0.5, 0.2, 1}};

// vetor com os generos e seus indices
indices generos[11] = {{"Ação", 0},
                       {"Aventura", 1},
                       {"Drama", 2},
                       {"Romance", 3},
                       {"Comédia", 4},
                       {"Crime", 5},
                       {"Suspense", 6},
                       {"Horror", 7},
                       {"Animação", 8},
                       {"Fantasia", 9},
                       {"Ficção Científica", 10}};

// função boas vindas
void welcome()
{

  cout << "\nSeja bem-vindo(a) ao SpookStream!" << endl;
  cout << "\nPara sua melhor experiência selecione o número correspondente ao seu filme favorito:\n"
       << endl;
}

void mostrarCatalogo(int nFilmes, Filme filmes[])
{
  // escolher n filmes aleatorios
  int n = 6;
  Filme filmes_aleatorios[n];
  int c = 0;
  while (c <= n)
  {
    int r = rand() % nFilmes; // filme aleatorio

    filmes_aleatorios[c] = filmes[r];
    c++;
  }
  
  

  int cont = 1; // contador para ajudar no ajuste do catálogo em forma de tabela
  // mostrando nome do filmes em formato de tabela
  for (int i = 0; i < n; i++)
  {

    // left - alinha conteúdo à esquerda
    // setw - witdh (largura) de cada célula
    cout << left << i + 1 << " - " << setw(30) << filmes_aleatorios[i].nome;

    if (cont == 3)
    {
      // adiciona quebra de linha a cada 3 filmes
      cout << endl;
      cont = 0;
    }

    cont++;
  }
  // quebra de linha final
  cout << endl;

    
}

// mostrar catalógo de filmes
void mostrarCatalogoOld(int nFilmes, Filme filmes[])
{
  int cont = 1; // contador para ajudar no ajuste do catálogo em forma de tabela

  // mostrando nome do filmes em formato de tabela
  for (int i = 0; i < nFilmes; i++)
  {

    // left - alinha conteúdo à esquerda
    // setw - witdh (largura) de cada célula
    cout << left << i + 1 << " - " << setw(30) << filmes[i].nome;

    if (cont == 3)
    {
      // adiciona quebra de linha a cada 3 filmes
      cout << endl;
      cont = 0;
    }

    cont++;
  }
  // quebra de linha final
  cout << endl;
}

// ler filmes favoritos do usuário
void selecionarFilmes(int nFilmes, Filme filmes[], Filme filmesSelecionados[])
{

  int opc; // opcao escolhida

  for (int i = 0; i < 3; i++)
  {
    cin >> opc;

    // se o filme não estiver no catálogo será pedido que digite novamente
    while (opc < 1 || opc > nFilmes)
    {
      cout << "Esse filme não está no catálogo. Digite outro número:" << endl;
      cin >> opc;
    }

    filmesSelecionados[i] = filmes[opc - 1];

    cout << "\nFilme escolhido: " << filmes[opc - 1].nome << endl;

    if (i < 2)
    {
      cout << "\nEscolha outro filme: ";
    }

    else
    {
      cout << "\nDe acordo com suas opções, segue abaixo algumas recomendações de filmes:\n\n";
    }
  }
}

// função que busca os filmes na matriz e retorna a similaridade
float consultarMatrizSimilaridade(string generoFilmeSelecionado, string generoFilme)
{

  float similaridade;
  int linha = -1, coluna = -1;

  for (int i = 0; i < 11; i++)
  {

    if (generos[i].genero.compare(generoFilme) == 0)
    {
      linha = i;
    }
    if (generos[i].genero.compare(generoFilmeSelecionado) == 0)
    {
      coluna = i;
    }

    if (linha != -1 && coluna != -1)
    {
      similaridade = matrizSimilaridade[linha][coluna];
      break;
    }
  }
  return similaridade;
}

// função para calcular 'pesos' e atribuí-los à probabilidade de cada filme
void calcularNovaProbabilidade(int nFilmes, Filme filmes[], Filme filmesSelecionados[])
{

  float similaridade;

  for (int j = 0; j < 3; j++)
  {
    for (int i = 0; i < nFilmes; i++)
    {

      // comparando os gêneros principais
      if (filmesSelecionados[j].genero1.compare(filmes[i].genero1) == 0)
      {
        filmes[i].probabilidade = 1;
      }

      // comparando primário com secundário
      if (filmesSelecionados[j].genero1.compare(filmes[i].genero2) == 0)
      {
        // chamando a função que retorna a similaridade entre os gêneros
        similaridade = consultarMatrizSimilaridade(filmesSelecionados[j].genero1, filmes[i].genero2);
        filmes[i].probabilidade = (filmes[i].probabilidade + similaridade) / 2;
      }

      // comparando os gêneros secundários
      if (filmesSelecionados[j].genero2.compare(filmes[i].genero2) == 0)
      {
        filmes[i].probabilidade = (filmes[i].probabilidade + 0.5) / 2;
      }

      // comparando secundário com primário
      if (filmesSelecionados[j].genero2.compare(filmes[i].genero1) == 0)
      {
        // chamando a função que retorna a similaridade entre os gêneros
        similaridade = consultarMatrizSimilaridade(filmesSelecionados[j].genero2, filmes[i].genero1);
        filmes[i].probabilidade = (filmes[i].probabilidade + similaridade) / 2;
      }
    }
  }
}

// aplica as porcentagens e retorna os filmes sorteados
Filme* sortearNFilmes(int nFilmes, Filme filmes[], int n) // n: numero de filmes a serem sorteados
{
  static Filme escolhidoss[5];
  int c =0;
  // while (c <= n)
  // {
  //   float chance = rand();
  //   int i_random = rand() % nFilmes;
  //   if(chance < filmes[i_random].probabilidade)
  //   {
  //     escolhidoss[c] = filmes[i_random];
  //     c++;
  //   }
  // }
  return escolhidoss;
  
}

int main()
{

  // Definindo região
  setlocale(LC_ALL, "portuguese");

  Filme filmes[100]; // vetor de filmes
  int nFilmes = 0;   // numero de filmes

  // importar filmes
  ifstream r_filmes;                   // variavel de leitura do arquivo
  string fileName = "ListaFilmes.txt"; // nome do arquivo

  r_filmes.open(fileName.c_str(), ifstream::in);

  while (!r_filmes.eof())
  { // lê todas as linhas até a última linha do arquivo
    getline(r_filmes, filmes[nFilmes].nome, '\n');
    r_filmes >> filmes[nFilmes].ano_lancamento;
    r_filmes.ignore();
    getline(r_filmes, filmes[nFilmes].genero1, '\n');
    getline(r_filmes, filmes[nFilmes].genero2, '\n');
    nFilmes++;
  }
  r_filmes.close(); // fechando arquivo de texto

  // Inicio
    welcome();

  Filme filmesSelecionados[3];
  // recebe as opções de preferência do usuário

  mostrarCatalogo(nFilmes, filmes);
  selecionarFilmes(nFilmes, filmes, filmesSelecionados);

  // calcular probabilidade de recomendar filmes
  calcularNovaProbabilidade(nFilmes, filmes, filmesSelecionados);

  // mostrando filmes e a chance deles serem recomendados
  // for (int i = 0; i < nFilmes; i++)
  // {
  //   cout << "Nome do filme: " << filmes[i].nome << endl;
  //   cout << "Chance de recomendá-lo: " << filmes[i].probabilidade << endl
  //        << endl;
  // }

  int n = 5;
  Filme* escolhidos = sortearNFilmes(nFilmes, filmes, n);
  for (int  i = 0; i < n; i++)
  {
    cout << escolhidos[i].nome << endl;
  }
  

  return 0;
}