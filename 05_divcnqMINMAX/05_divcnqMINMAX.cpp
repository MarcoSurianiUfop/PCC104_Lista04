/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                  LISTA 4 - ATIVIDADES PRÁTICAS - EXERCÍCIO 05
                           DIVIDE & CONQUER MIN MAX
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <vector>
#include <math.h> // floor

using namespace std;

template <class T> void printVector(vector<T>& v);

template <class T>
pair<T, T> divcnqMINMAX(vector<T>& A) {
    /*  Encontra os valores mínimo e máximo de um arranjo usando 
    * a técnica Divide & Conquer
    * ENTRADAS:
    * Ponteiro para Vetor A com elementos de qualquer datatype
    * SAÍDA:
    * Par com elementos de qualquer datatype contendo valores mínimo e máximo
    */

    // Tamanho da entrada e sua metade arredondada para baixo
    int n = A.size();
    int n2 = (int)floor(n / 2);

    // Caso subvetor contenha apenas 1 elemento, os valores mínimo e máximo
    // são iguais ao único elemento do vetor. Retorna par com dois A[0]
    if (n == 1) { return { A[0], A[0] }; }
    else if (n == 2) { 
        // Caso haja dois elementos, retorne {A[0], A[1]} se A[0] <= A[1]
        // ou {A[1], A[0]} se A[0] > A[1]
        if (A[0] <= A[1]) { return { A[0], A[1] }; }
        else { return { A[1], A[0] }; }
    }
    else {
        // Caso haja 3 ou mais elementos, realizar os passos a seguir

        // Vetor B contém a primeira metade dos dados
        // Vetor C contém a segunda metade dos dados
        vector<T> B = { A.begin(), A.begin() + n2 };
        vector<T> C = { A.begin() + n2, A.end() };

        // Recursivamente, encontra o par com os valores mínimo e máximo 
        // de cada uma das duas metades (B e C)
        pair<T, T> pair1 = divcnqMINMAX(B);
        pair<T, T> pair2 = divcnqMINMAX(C);

        // Caso o mínimo do par2 seja menor, atualize o par1 com tal valor
        // Caso o máximo do par2 seja maior, atualize o par1 com tal valor
        if (pair2.first < pair1.first) { pair1.first = pair2.first; }
        if (pair2.second > pair1.second) { pair1.second = pair2.second; }

        // Retorne o par1
        return pair1;
    }
}

int main() {
    // Cria um vetor de elementos não ordenados (inteiros) 
    vector<int> v = { 12, 30, 64, 25, 12, 22, 35, 22, 11, 64, 10 };

    // Imprime o vetor não ordenado
    cout << "Unsorted vector:" << endl;
    printVector(v);

    // Encontra o par com os valores mínimo e máximo 
    pair<int, int> minmax1 = divcnqMINMAX(v);

    // Imprime os valores mínimo e máximo 
    cout << endl;
    cout << "Min: " << minmax1.first;
    cout << " Max: " << minmax1.second << endl << endl;

    // Outro exemplo
    vector<int> w = { 30, 10, 25, 12, 64, 35, 22, 11, 64, 22 };

    // Imprime o vetor não ordenado
    cout << "Unsorted vector:" << endl;
    printVector(w);

    // Encontra o par com os valores mínimo e máximo 
    pair<int, int> minmax2 = divcnqMINMAX(w);

    // Imprime os valores mínimo e máximo 
    cout << endl;
    cout << "Min: " << minmax2.first;
    cout << " Max: " << minmax2.second << endl << endl;

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