/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                  LISTA 4 - ATIVIDADES PRÁTICAS - EXERCÍCIO 01
                                    MERGE SORT
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <vector>
#include <math.h> // floor

using namespace std;

template <class T> void printVector(vector<T>& v);
template <class T> void mergeVectors(vector<T>& B, vector<T>& C, vector<T>& A);

template <class T>
void mergeSortVector(vector<T>& A) {
    /*  Implementação do MERGE SORT
    * Ordena os elementos de uma série em ordem crescente
    * ENTRADAS:
    * Ponteiro para Vetor A com elementos de qualquer datatype
    */

    // Tamanho da entrada e sua metade arredondada para baixo
    int n = A.size();
    int n2 = (int)floor(n / 2);

    // Caso o vetor A contenha apenas um elemento, não fazer nada
    // Caso possua pelo menos 2 elementos, fazer:
    if (n > 1) {

        // Vetor B contém a primeira metade dos dados
        // Vetor C contém a segunda metade dos dados
        vector<T> B = { A.begin(), A.begin() + n2 };
        vector<T> C = { A.begin() + n2, A.end() };

        // Recursivamente, ordena os elementos das duas metades (B e C)
        mergeSortVector(B);
        mergeSortVector(C);

        // Reune os dados ordenados de B e C de volta para A
        mergeVectors(B, C, A);
    }
}

template <class T> 
void mergeVectors(vector<T>& B, vector<T>& C, vector<T>& A) {
    /*  Mescla dois vetores ordenados em um único vetor ordenado
    * ENTRADAS:
    * Ponteiros para Vetores ordenados B e C com elementos de qualquer datatype
    * Ponteiro para Vetor não ordenado A com elementos de qualquer datatype
    * SAÍDA:
    * Ponteiro para Vetor A contendo mescla ordenada de B e C
    */

    // Contadores de posição (i conta B, j conta C e k conta A)
    unsigned int i = 0, j = 0, k = 0;

    // Percorre os vetores B e C, pára quando um deles chegar no fim
    while (i < B.size() and j < C.size()) {

        // Compara o i-esimo valor de B com o j-ésimo valor de C
        // Atribui o menor deles ao k-ésimo valor de A e incrementa k
        // Incrementa i (se usou valor de B) ou j (se usou valor de C)
        if (B[i] <= C[j]) {
            A[k] = B[i];
            i = i + 1;
        }
        else {
            A[k] = C[j];
            j = j + 1;
        }
        k = k + 1;
    }

    // Caso B tenha chegado ao fim, copie o resto dos elementos de C para A
    // Caso C tenha chegado ao fim, copie o resto dos elementos de B para A
    // Como B e C já estão ordenados, não precisa reordenar o excedente
    if (i == B.size()) { copy(C.begin() + j, C.end(), A.begin() + k); }
    else { copy(B.begin() + i, B.end(), A.begin() + k); }
}


int main() {
    // Cria um vetor de elementos não ordenados (inteiros) 
    vector<int> v = { 30, 64, 25, 12, 22, 35, 22, 11, 10 };

    // Imprime o vetor não ordenado
    cout << "Unsorted vector:" << endl;
    printVector(v);

    // Ordena o vetor usando o MERGE SORT
    mergeSortVector(v);

    // Imprime o vetor ordenado
    cout << endl << "Sorted vector (Merge):" << endl;
    printVector(v);

    cout << endl;

    // Outro exemplo
    vector<char> w = { 'E', 'X', 'A', 'M', 'P', 'L', 'E' };

    // Imprime o vetor não ordenado
    cout << "Unsorted vector:" << endl;
    printVector(w);

    // Ordena o vetor usando o MERGE SORT
    mergeSortVector(w);

    // Imprime o vetor ordenado
    cout << endl << "Sorted vector (Merge):" << endl;
    printVector(w);

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