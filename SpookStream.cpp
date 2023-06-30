#define ESC "\033["
#define BLUE_TXT "34"
#define RED_TXT "31"
#define WHITE_TXT "29"
#define RESET "\033[m"

#include <cstring>
#include <fstream>
#include <iomanip> // tabela
#include <iostream>
#include <locale.h>
//#include <windows.h> // limpar terminal

using namespace std;

// struct com os dados dos filmes
struct Filme
{
  string nome;         // nome do filme
  int ano_lancamento;  // ano de lançamento do filme
  string genero1;      // gênero principal do filme
  string genero2;      // gênero secundário do filme
  float probabilidade; // chance de recomendar o filme ao usuário

  // construtor da classe
  // roda quando um objeto for inicializado
  Filme() {
    probabilidade = 0.0; // define 0 como valor padrão para probabilidade
  };
};

struct indices
{
  string genero; // genero do filme
  int indice;    // indice do filme na matriz de similaridade
};

void mostrarCatalogo(int nFilmes, Filme filmes[])
{
  int cont = 1; // contador para ajudar no ajuste do catálogo em forma de tabela

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
void selecionarFilmes(int nFilmes, Filme filmes[], Filme filmesSelecionados[], int numSelecao)
{
  int opc; // opcao escolhida

  for (int i = 0; i < numSelecao; i++)
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

    if (i < numSelecao - 1)
      cout << "\nEscolha outro filme: ";
  }
}

// função que busca os filmes na matriz e retorna a similaridade
float consultarMatrizSimilaridade(string generoFilmeSelecionado, string generoFilme)
{
  // matriz que contém as similaridades entre os gêneros dos filmes
  // consulte o README
  float matrizSimilaridade[11][11] = {
      {1, 0.8, 0.35, 0.3, 0.6, 0.7, 0.75, 0.4, 0.1, 0.55},
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
  indices generos[11] = {
      {"Ação", 0},
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

  float similaridade; // variável que guarda a similaridade entre os gêneros
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
      // busca o valor da similaridade na matriz
      similaridade = matrizSimilaridade[linha][coluna];
      break;
    }
  }
  return similaridade;
}

// função para calcular 'pesos' e atribuí-los à probabilidade de cada filme
void calcularNovaProbabilidade(int nFilmes, Filme filmes[], Filme filmesSelecionados[], int numSelecao)
{
  float similaridade;

  for (int j = 0; j < numSelecao; j++)
  {
    for (int i = 0; i < nFilmes; i++)
    {
      // gêneros principais iguais
      if (filmesSelecionados[j].genero1.compare(filmes[i].genero1) == 0)
      {
        filmes[i].probabilidade = (filmes[i].probabilidade + 1) / 2; // média aritmética
      }
      // gêneros secundários iguais
      else if (filmesSelecionados[j].genero2.compare(filmes[i].genero2) == 0)
      {
        filmes[i].probabilidade = (filmes[i].probabilidade + 0.5) / 2; // média aritmética
      }
      // gêneros diferentes
      else
      {
        // chamando a função que retorna a similaridade entre os gêneros
        similaridade = consultarMatrizSimilaridade(filmesSelecionados[j].genero1, filmes[i].genero2);

        // fazendo média aritmética das duas similaridades buscadas
        similaridade = (similaridade + consultarMatrizSimilaridade(filmesSelecionados[j].genero2, filmes[i].genero1)) / 2;

        // média aritmética para calcular probabilidade
        filmes[i].probabilidade = (filmes[i].probabilidade + similaridade) / 2;
      }
    }
  }
}

void printarColorido(string txt, char color)
{
    if(color == 'b')
    {
        cout << ESC << ";" << BLUE_TXT << "m" << txt;
    }
     
    else if(color == 'r')
    {
        cout << ESC << ";" << RED_TXT << "m" << txt; 
    }
    
    else if(color == 'w')
    {
        cout << ESC << ";" << WHITE_TXT << "m" << txt;
    }
    cout << RESET;
}

int main()
{
  // Definindo região
  setlocale(LC_ALL, "portuguese");

  Filme filmes[100]; // vetor de filmes
  int nFilmes = 0;   // numero de filmes


  printarColorido("               ____                            ", 'w'); printarColorido("                                                         ", 'w'); cout << endl;
  printarColorido("           ___|    |___                        ", 'w'); printarColorido("                                                         ", 'w'); cout << endl;
  printarColorido("         _|            |_                      ", 'w'); printarColorido("        _____                           _                ", 'w'); cout << endl;
  //Sleep(600);
  printarColorido("       _|                |_                    ", 'w'); printarColorido("       / ____|                         | |               ", 'w'); cout << endl;
  printarColorido("     _|       ____        _|__                 ", 'w'); printarColorido("      | (___    _ __     ___     ___   | | __            ", 'w'); cout << endl;
  printarColorido("    |       _| ___|     _| ___|                ", 'w'); printarColorido("       \\___ \\  | '_ \\   / _ \\   / _ \\  | |/ /       ", 'w'); cout << endl;
  //Sleep(600);
  printarColorido("    |      |  |        |  |                    ", 'w'); printarColorido("       ____) | | |_) | | (_) | | (_) | |   <             ", 'w'); cout << endl;
  printarColorido("   _|      |_ |___     |_ |___                 ", 'w'); printarColorido("      |_____/  | .__/   \\___/   \\___/  |_|\\_\\        ", 'w'); cout << endl;
  printarColorido("  |          |____|      |____|                ", 'w'); printarColorido("               | |                                       ", 'w'); cout << endl;
  //Sleep(600);
  printarColorido("  |                            |               ", 'w'); printarColorido("               |_|                                       ", 'w'); cout << endl;
  printarColorido("  |                            |               ", 'w'); printarColorido("   _____   _                                             ", 'r'); cout << endl;
  printarColorido("  |                            |               ", 'w'); printarColorido("  / ____| | |                                            ", 'r'); cout << endl;
  //Sleep(600);
  printarColorido("  |                            |               ", 'w'); printarColorido(" | (___   | |_   _ __    ___    __ _   _ __ ___          ", 'r'); cout << endl;
  printarColorido("  |   __      __        __     |               ", 'w'); printarColorido("  \\___ \\  | __| | '__|  / _ \\  / _` | | '_ ` _ \\     ", 'r'); cout << endl;
  printarColorido("  |  |  |    |  |      |  |    |               ", 'w'); printarColorido("  ____) | | |_  | |    |  __/ | (_| | | | | | | |        ", 'r'); cout << endl;
  //Sleep(600);
  printarColorido("  |__|   |__|    |____|    |__|                ", 'w'); printarColorido(" |_____/   \\__| |_|     \\___|  \\__,_| |_| |_| |_|     ", 'r'); cout << endl;
  //Sleep(600);
  cout << endl;
  system("pause");

  ifstream r_filmes;                   // variavel de leitura do arquivo
  string fileName = "ListaFilmes.txt"; // nome do arquivo

  r_filmes.open(fileName.c_str(), ifstream::in);

  // lê todas as linhas do arquivo
  while (!r_filmes.eof())
  {
    getline(r_filmes, filmes[nFilmes].nome, '\n');
    r_filmes >> filmes[nFilmes].ano_lancamento;
    r_filmes.ignore();
    getline(r_filmes, filmes[nFilmes].genero1, '\n');
    getline(r_filmes, filmes[nFilmes].genero2, '\n');
    nFilmes++;
    cout << filmes[nFilmes].nome;
  }
  r_filmes.close(); // fechando arquivo de texto
  
  system("cls");

  cout << "************************* Seja bem-vindo(a) ao SpookStream! *************************\n" << endl;
  cout << "Para sua melhor experiência selecione o número correspondente ao seu filme favorito:\n " << endl;

  Filme filmesSelecionados[3]; //opções de preferência do usuário

  // chamando função que mostra catálogo inicial
  mostrarCatalogo(nFilmes, filmes);

  // função para que o usuário selecione um dos filmes do catálogo
  selecionarFilmes(nFilmes, filmes, filmesSelecionados, 3);

  // calcular probabilidade de recomendar filmes
  calcularNovaProbabilidade(nFilmes, filmes, filmesSelecionados, 3);

  // limpar tela
  system("cls");
  
  // perguntar se gostaria de assistir um filme
  string opcao;
  cout << "Gostaria de assistir algum filme? ([S] [N]):" << endl;
  cin.ignore();
  getline(cin, opcao);
  cout << endl;

  bool continuar = false; // condicao do loop

  // se escolheu continuar, definir condicao para o loop rodar
  if (opcao == "S" || opcao == "s" || opcao == "Sim" || opcao == "sim" || opcao == "SIM")
  {
    continuar = true;
  }

  // loop enquanto o usuario escolher continuar assistindo filmes
  while (continuar == true)
  {
    Filme recomendacoes[6]; // filmes que serão recomendados
    float maior; // variável para comparar com os filmes de maior probabilidade
    int indice; // indice do filme com maior probabilidade
                // usado para "eliminar" um filme da comparação

    // recuperando filmes com maior probabilidade
    for (int i = 0; i < 6; i ++) 
    {
      maior = 0.0; // resetando o valor da variável para comparar novamente
      for (int j = 0; j < nFilmes; j ++) 
      {
        if (filmes[j].probabilidade > maior && filmes[j].probabilidade < 1) {
          recomendacoes[i] = filmes[j];
          maior = filmes[j].probabilidade;
          indice = j;
        }
      }
      filmes[indice].probabilidade = 1; // "eliminando" probabilidade para continuar comparação
    }

    // apresentar catalogo
    cout << "Filmes recomendados:" << endl;
    mostrarCatalogo(6, recomendacoes);

    // selecionar um dos filmes
    selecionarFilmes(nFilmes, filmes, filmesSelecionados, 1);

    cout << "Assistindo " << filmesSelecionados[0].nome << endl ;
    cout << endl;

    system("pause");
    system("cls");

    // perguntar se gostaria de assistir novamente
    string opcao;
    cout << "Gostaria de assistir mais algum filme? ([S] [N]): " << endl;
    cin.ignore();
    getline(cin, opcao);
    cout << endl;

    if (opcao == "S" || opcao == "s" || opcao == "Sim" || opcao == "sim" || opcao == "SIM")
    {
      continuar = true;
      calcularNovaProbabilidade(nFilmes, filmes, filmesSelecionados, 1);
    } else {
      continuar = false;
    }
  }

  cout << "\nPrograma finalizado." << endl;

  return 0;
}