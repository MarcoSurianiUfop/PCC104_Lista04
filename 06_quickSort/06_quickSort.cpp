/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                  LISTA 4 - ATIVIDADES PRÁTICAS - EXERCÍCIO 06
                                    QUICK SORT
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <vector>
#include <math.h> // floor

using namespace std;

template <class T> void printVector(vector<T>& v);
template <class T> int HoarePartition(vector<T>& A, int left, int right);
template <class T> void swapPositions(T& xp, T& yp);

template <class T>
void quickSortVector(vector<T>& A, int left, int right) {
    /*  Implementação do QUICK SORT
    * Ordena os elementos de uma série em ordem crescente
    * ENTRADAS:
    * Ponteiro para Vetor A com elementos de qualquer datatype
    * Inteiros left e right contendo os índices do início e do fim da ordenação
    */

    // Caso haja apenas um elemento (left = right), não faça nada
    // Caso haja pelo menos dois elementos, realizar o que se segue
    if (left < right) {

        // Particiona o vetor A entre os índices left e right
        // Altera o vetor A e retorna um pivô s
        int s = HoarePartition(A, left, right);
        
        // Recursivamente, ordena as porções anterior e posteior ao pivô s
        quickSortVector(A, left, s);
        quickSortVector(A, s + 1, right);
    }
}

template <class T>
int HoarePartition(vector<T>& A, int left, int right) {
    /*  Particiona um subvetor usando o algoritmo de Hoare, 
    * usando primeiro elemento como pivô
    * ENTRADAS:
    * Ponteiro para Vetor A com elementos de qualquer datatype
    * Inteiros left e right contendo os índices do início e do fim da ordenação
    * SAÍDAS:
    * Vetor A particionado
    * Retorna um inteiro contendo o novo pivô
    */

    // Seleciona primeiro elemento como pivô
    int pivot = A[left];

    // Contadores de posição 
    // i conta da esquerda p/ direita, j conta da direita p/ esquerda
    int i = left - 1, j = right + 1;

    // Realiza este laço até que os contadores de posição se encontrem
    while (true) {

        // Encontra o primeiro elemento maior ou igual ao pivô 
        // a partir da posição esquerda atual
        // Ou seja: incrementa i até encontrar A[i] >= pivô
        do { i++; } while (A[i] < pivot);

        // Encontra o último elemento menor ou igual ao pivô 
        // a partir da posição direita atual
        // Ou seja: decrementa j até encontrar A[j] <= pivô
        do { j--; } while (A[j] > pivot);

        // Caso os dois ponteiros se encontrem, retorne j como o novo pivô
        // encerrando o laço e a função de partição
        if (i >= j) { return j; }
            
        // Caso i ainda seja menor que j, troque A[i] com A[j] antes de
        // retornar ao início do laço
        swap(A[i], A[j]);
    }
}


int main() {
    // Cria um vetor de elementos não ordenados (inteiros) 
    vector<int> v = { 30, 64, 25, 12, 22, 35, 22, 11, 10 };
    int n = v.size();

    // Imprime o vetor não ordenado
    cout << "Unsorted vector:" << endl;
    printVector(v);

    // Ordena o vetor usando o QUICK SORT
    quickSortVector(v, 0, n - 1);

    // Imprime o vetor ordenado
    cout << endl << "Sorted vector (Merge):" << endl;
    printVector(v);

    cout << endl;

    // Outro exemplo
    vector<char> w = { 'E', 'X', 'A', 'M', 'P', 'L', 'E' };
    int m = w.size();

    // Imprime o vetor não ordenado
    cout << "Unsorted vector:" << endl;
    printVector(w);

    // Ordena o vetor usando o QUICK SORT
    quickSortVector(w, 0, m - 1);

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

template <class T>
void swapPositions(T& xp, T& yp) {
    /*  Função para Trocar os valores de duas variáveis
    * ENTRADAS:
    * Ponteiros xp, yp para elementos de qualquer datatype
    */

    T temp = xp;    // Guarda o conteúdo apontado por xp em temp
    xp = yp;        // Guarda o conteúdo apontado por yp na pos. apontada por xp
    yp = temp;      // Guarda o conteúdo temp na posição apontada por yp
}