/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                  LISTA 4 - ATIVIDADES PRÁTICAS - EXERCÍCIO 04
                           DIVIDE & CONQUER MAXIMUM
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <vector>
#include <math.h> // floor

using namespace std;

template <class T> void printVector(vector<T>& v);

template <class T>
int divcnqMAX(vector<T>& A) {
    /*  Encontra o índice do valor máximo de um arranjo usando a técnica 
    * Divide & Conquer (em caso de empate, retorna o menor índice)
    * ENTRADAS:
    * Ponteiro para Vetor A com elementos de qualquer datatype
    * SAÍDA:
    * Inteiro com o índice do maior elemento do vetor A
    */

    // Tamanho da entrada e sua metade arredondada para baixo
    int n = A.size();
    int n2 = (int)floor(n / 2);

    // Caso o subvetor possua apenas um elemento, retorne sua posição: 0
    // Caso contrário, busque pelo maior elemento
    if (n == 1) { return 0; }
    else {
        // Vetor B contém a primeira metade dos dados
        // Vetor C contém a segunda metade dos dados
        vector<T> B = { A.begin(), A.begin() + n2 };
        vector<T> C = { A.begin() + n2, A.end() };

        // Recursivamente, encontra o índice do valor máximo de
        // cada um das duas metades (B e C)
        // No caso da segunda metade (C), compensar a posição somando n2
        int temp1 = divcnqMAX(B);
        int temp2 = divcnqMAX(C) + n2;

        // Retorna temp1 se A[temp1] maior ou igual a A[temp2]
        // Retorna temp2 se A[temp1] menor que A[temp2]
        // Caso A[temp1] = A[temp2], retorna temp1 < temp2
        if (A[temp1] >= A[temp2]) { return temp1; }
        else { return temp2; }
    }
}

int main() {
    // Cria um vetor de elementos não ordenados (inteiros) 
    vector<int> v = { 12, 30, 64, 25, 12, 22, 35, 22, 11, 64, 10};

    // Imprime o vetor não ordenado
    cout << "Unsorted vector:" << endl;
    printVector(v);

    // Encontra o índice do maior elemento
    int imax = divcnqMAX(v);

    // Imprime a posição (índice + 1) do maior elemento
    cout << endl << "Position (index + 1) of max value (Divide & Conquer): ";
    cout << imax + 1 << endl << endl;

    // Outro exemplo
    vector<int> w = { 30, 22, 25, 12, 64, 35, 22, 11, 64, 10 };

    // Imprime o vetor não ordenado
    cout << "Unsorted vector:" << endl;
    printVector(w);

    // Encontra o índice do maior elemento
    int imax2 = divcnqMAX(w);

    // Imprime a posição (índice + 1) do maior elemento
    cout << endl << "Position (index + 1) of max value (Divide & Conquer): ";
    cout << imax2 + 1 << endl;

    return 0;
}

template <class T>
void printVector(vector<T>& v) {
    /*  Função para Imprimir vetores
    * ENTRADA:
    * Ponteiro para Vetor v com elementos de qualquer datatype
    */

    // Itera todos os elementos do vetor v
    for (T n : v)
        // Imprime cada elemento
        cout << n << " ";
    cout << endl;
}