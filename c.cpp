#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ofstream file;
    char f_name[50] = "ListaFilmes.txt";

    file.open(f_name, ofstream::out);

    

    return 0;
}
