/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                  LISTA 4 - ATIVIDADES PRÁTICAS - EXERCÍCIO 13
                         Strassen’s Matrix Multiplication
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <vector>
#include <iomanip> // setw

using namespace std;

template <class T> void printMatrix(vector<vector<T>>& M);
template <class T> void divideMatrix(
    vector<vector<T>>& M,
    vector<vector<T>>& M00,
    vector<vector<T>>& M01,
    vector<vector<T>>& M10,
    vector<vector<T>>& M11);
template <class T> void uniteMatrix(
    vector<vector<T>>& M,
    vector<vector<T>>& M00,
    vector<vector<T>>& M01,
    vector<vector<T>>& M10,
    vector<vector<T>>& M11);
template <class T> vector<vector<T>> somaMatrix(
    vector<vector<T>>& M1,
    vector<vector<T>>& M2,
    pair<int, int>& count);
template <class T> vector<vector<T>> subtMatrix(
    vector<vector<T>>& M1,
    vector<vector<T>>& M2,
    pair<int, int>& count);
template <class T> void fillzeros(vector<vector<T>>& M, int k);


template <class T>
vector<vector<T>> 
Strassen(vector<vector<T>>& A, vector<vector<T>>& B, pair<int, int>& count) {
    /*  Executa a multiplicação de matrizes usando algoritmo de Strassen
    * As duas matrizes são quadradas e com as dimensões (2^k x 2^k), k inteiro
    * ENTRADAS:
    * Ponteiros p/ Matrizes A e B (2^k x 2^k) c/ elementos de qualquer datatype
    * Par de inteiros 'count' com valores acumulados de operações
    * count.first: produtos e count.second: somas/subtrações
    * SAÍDA:
    * Matriz C (2^k x 2^k) com elementos de qualquer datatype contendo A*B
    */

    // Dimensão das matrizes (lembrando que ambas possuem mesmas dimensões)
    int n = A.size();
    
    // Caso as duas matrizes sejam unitárias (n = 1 ou k = 0), retorna uma 
    // matriz unitária contendo o produto entre os elementos de ambas
    if (n == 1) { 
        // Inicia matriz que será retornada na saída
        vector<vector<T>> C;

        // Cria vetor unitário v com a00 x b00
        vector<T> v = { A[0][0] * B[0][0] };

        // Insere vetor v na matriz C
        C.push_back(v);

        // Apenas um produto
        count.first++;

        return C; 
    }

    /* // Fazendo produto 2x2 na Força Bruta
    // Caso as duas matrizes sejam 2x2 (n = 2 ou k = 1), retorna uma 
    // matriz 2x2 calculada na Força Bruta
    if (n == 2) {
        // Inicia matriz que será retornada na saída e vetor auxiliar v
        vector<vector<T>> C;
        vector<T> v;

        // Primeira linha de C: 
        // c00 = a00*b00 + a01*b10   /   c01 = a00*b01 + a01*b11
        v.push_back({ A[0][0] * B[0][0] + A[0][1] * B[1][0] });
        v.push_back({ A[0][0] * B[0][1] + A[0][1] * B[1][1] });

        // Insere primeira linha na Matriz C e esvazia o vetor v
        C.push_back(v);
        v = {};

        // Segunda linha de C:
        // c10 = a10*b00 + a11*b10   /   c11 = a10*b01 + a11*b11
        v.push_back({ A[1][0] * B[0][0] + A[1][1] * B[1][0] });
        v.push_back({ A[1][0] * B[0][1] + A[1][1] * B[1][1] });

        // Insere segunda linha na Matriz C e esvazia o vetor v
        C.push_back(v);

        // Foram necessárias 8 multiplicações e 4 somas
        count.first = count.first + 8;
        count.second = count.second + 4;

        return C;
    }
    */

    // Caso as matrizes A e B sejam (2x2) ou superior
    // Ou caso sejam (4x4) ou superior quando (2x2) é calculado na força bruta

    // ******* INICIA AS MATRIZES NECESSÁRIAS *******
    
    // Matrizes A e B precisam ser divididas em 4 partes
    vector<vector<int>> A00, A01, A10, A11;
    vector<vector<int>> B00, B01, B10, B11;

    // Matriz de Saída C é criada, bem como suas 4 partes
    vector<vector<int>> C00, C01, C10, C11, C;

    // As sete matrizes que auxiliam os cálculos são criadas
    vector<vector<T>> M1, M2, M3, M4, M5, M6, M7;

    // São criadas 2 matrizes auxiliares para somas e subtrações
    vector<vector<T>> X, Y;

    // ******* DIVIDE MATRIZES 'A' E 'B' EM QUATRO PARTES CADA *******

    divideMatrix(A, A00, A01, A10, A11);
    divideMatrix(B, B00, B01, B10, B11);

    // ******* CALCULA AS MATRIZES M1 A M7 *******

    // M1 = (A00 + A11) * (B00 + B11)
    X = somaMatrix(A00, A11, count);
    Y = somaMatrix(B00, B11, count);
    M1 = Strassen(X, Y, count);

    // M2 = (A10 + A11) * B00
    X = somaMatrix(A10, A11, count);
    M2 = Strassen(X, B00, count);

    // M3 = A00 * (B01 - B11)
    X = subtMatrix(B01, B11, count);
    M3 = Strassen(A00, X, count);

    // M4 = A11 * (B10 - B00)
    X = subtMatrix(B10, B00, count);
    M4 = Strassen(A11, X, count);

    // M5 = (A00 + A01) * B11
    X = somaMatrix(A00, A01, count);
    M5 = Strassen(X, B11, count);

    // M6 = (A10 - A00) * (B00 + B01)
    X = subtMatrix(A10, A00, count);
    Y = somaMatrix(B00, B01, count);
    M6 = Strassen(X, Y, count);

    // M7 = (A01 - A11) * (B10 + B11)
    X = subtMatrix(A01, A11, count);
    Y = somaMatrix(B10, B11, count);
    M7 = Strassen(X, Y, count);

    // ******* CALCULA AS SUBMATRIZES DE C: C00 A C11 *******

    // C00 = M1 + M4 - M5 + M7
    X = somaMatrix(M1, M4, count);
    Y = subtMatrix(M7, M5, count);
    C00 = somaMatrix(X, Y, count);

    // C01 = M3 + M5
    C01 = somaMatrix(M3, M5, count);

    // C10 = M2 + M4
    C10 = somaMatrix(M2, M4, count);

    // C11 = M1 + M3 - M2 + M6
    X = somaMatrix(M1, M3, count);
    Y = subtMatrix(M6, M2, count);
    C11 = somaMatrix(X, Y, count);

    // ******* REUNE SUBMATRIZES DE C: C00 A C11 *******

    uniteMatrix(C, C00, C01, C10, C11);

    return C;
}

template <class T>
vector<vector<T>>
StrassenMatrixMultiplication(vector<vector<T>> A, vector<vector<T>> B, pair<int, int>& count) {
    /*  Executa a multiplicação de matrizes usando algoritmo de Strassen
    * As duas matrizes podem ter quaisquer dimensões desde que nA = mB
    * ENTRADAS:
    * Cópia das Matrizes A(nAxmA) e B(nBxmB) c/ elementos de qualquer datatype
    * Ponteiro p/ par de inteiros 'count' com valores acumulados de operações
    * count.first: produtos e count.second: somas/subtrações
    * SAÍDA:
    * Matriz C (nA x mB) com elementos de qualquer datatype contendo A*B
    */

    // Zera os acumuladores de operações
    count.first = 0;
    count.second = 0;

    // Gera as dimensões (n x m) das matrizes A e B
    int nA = A.size();
    int mA = A[0].size();
    int nB = B.size();
    int mB = B[0].size();

    // k é maior dimensão das duas matrizes
    // Transforma k na primeira potência de 2 maior ou igual a ele mesmo
    int k = max(max(nA, mA), max(nB, mB));
    k = (int)ceil(log2(k));
    k = (int)pow(2, k);

    // Expande A e B com zeros até as dimensões (k x k)
    // Assim, ambas ficam com dimensão do tipo (2^j x 2^j), j inteiro
    fillzeros(A, k);
    fillzeros(B, k);

    // PS é o resultado da multiplicação Strassen
    vector<vector<T>> PS = Strassen(A, B, count), P;

    // P contém as dimensões (nA x mB) -> elimina os zeros da expansão
    for (int i = 0; i < nA; i++) {
        vector<T> v;
        for (int j = 0; j < mB; j++) {
            v.push_back(PS[i][j]);
        }
        P.push_back(v);
    }

    // Retorna P
    return P;
}

int main() {
    // Cria matrizes de inteiros
    vector<vector<int>> A = { {1, 2}, {3, 4} };
    vector<vector<int>> B = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16} };
    vector<vector<int>> C = { {1, 2}, {3, 4}, {5, 6}, {7, 8} };
    pair<int, int> count;

    // Imprime as matrizes
    cout << "Matriz A =" << endl;
    printMatrix(A);

    cout << endl << "Matriz B =" << endl;
    printMatrix(B);

    cout << endl << "Matriz C =" << endl;
    printMatrix(C);


    // Multiplica X = A*A
    vector<vector<int>> X = StrassenMatrixMultiplication(A, A, count);

    // Imprime o resultado X = A*A
    cout << endl << "Matriz X = A*A =" << endl;
    printMatrix(X);
    cout << "Count Multiplications = " << count.first << endl;
    cout << "Count Sums/Subtracts. = " << count.second << endl;


    // Multiplica X = B*B
    X = StrassenMatrixMultiplication(B, B, count);

    // Imprime o resultado X = B*B
    cout << endl << "Matriz X = B*B =" << endl;
    printMatrix(X);
    cout << "Count Multiplications = " << count.first << endl;
    cout << "Count Sums/Subtracts. = " << count.second << endl;


    // Multiplica X = B*C
    X = StrassenMatrixMultiplication(B, C, count);

    // Imprime o resultado X = B*C
    cout << endl << "Matriz X = B*C =" << endl;
    printMatrix(X);
    cout << "Count Multiplications = " << count.first << endl;
    cout << "Count Sums/Subtracts. = " << count.second << endl;

    return 0;
}

template <class T>
void printMatrix(vector<vector<T>>& M) {
    /*  Função para Imprimir matrizes (vetor de vetores)
    * ENTRADA:
    * Ponteiro para Matriz M com elementos de qualquer datatype
    */

    // Itera todos os subvetores v da matriz M
    for (vector<T> v : M) {
        // Itera todos os elementos do vetor v
        for (T n : v)
            // Imprime cada elemento
            cout << setw(3) << n << " ";
        cout << endl;
    }
}

template <class T>
void divideMatrix(
    vector<vector<T>>& M,
    vector<vector<T>>& M00,
    vector<vector<T>>& M01,
    vector<vector<T>>& M10,
    vector<vector<T>>& M11) {
    /* Divide uma matriz M (2^k x 2^k), k inteiro, em 4 partes
    * ENTRADAS:
    * Ponteiro para a Matriz M (2^k x 2^k) com entrada
    * Ponteiros para a Matrizes Mij (2^(k-1) x 2^(k-1)) com saídas
    */

    // Dimensão n da Matriz M quadrada e sua metade hn
    int n = M.size();
    int hn = n / 2;

    // Cria vetor auxiliar v
    vector<T> v;

    // Primeira metade das linhas (forma M00 e M01)
    for (int i = 0; i < hn; i++) {
        // M00 recebe a primeira metade da linha atual
        v = vector<int>(M[i].begin(), M[i].begin() + hn);
        M00.push_back(v);

        // M01 recebe a segunda metade da linha atual
        v = vector<int>(M[i].begin() + hn, M[i].end());
        M01.push_back(v);
    }

    // Segunda metade das linhas (forma M10 e M11)
    for (int i = hn; i < n; i++) {
        // M10 recebe a primeira metade da linha atual
        v = vector<int>(M[i].begin(), M[i].begin() + hn);
        M10.push_back(v);

        // M11 recebe a segunda metade da linha atual
        v = vector<int>(M[i].begin() + hn, M[i].end());
        M11.push_back(v);
    }
}

template <class T>
void uniteMatrix(
    vector<vector<T>>& M,
    vector<vector<T>>& M00,
    vector<vector<T>>& M01,
    vector<vector<T>>& M10,
    vector<vector<T>>& M11) {
    /* Reune 4 matrizes Mij (2^k x 2^k), k inteiro, em 1 só
    * ENTRADAS:
    * Ponteiros para a Matrizes Mij (2^(k-1) x 2^(k-1)) com entradas
    * Ponteiro para a Matriz M (2^k x 2^k) com saída
    */

    // Dimensão n da Matriz M quadrada 
    int n = M00.size();

    // Cria vetor auxiliar v
    vector<T> v;

    // Para cada linha da matriz reunida 
    for (int i = 0; i < 2 * n; i++) {
        // Esvazia o vetor v
        v = {};

        // Colunas da esquerda M00 e M10
        for (int j = 0; j < n; j++) {
            // Se metade de cima, pega de M00; se metade de baixo, pega M10
            if (i < n) { v.push_back(M00[i][j]); }
            else { v.push_back(M10[i - n][j]); }
        }

        // Colunas da direita M01 e M11
        for (int j = 0; j < n; j++) {
            // Se metade de cima, pega de M01; se metade de baixo, pega M11
            if (i < n) { v.push_back(M01[i][j]); }
            else { v.push_back(M11[i - n][j]); }
        }

        // Acrescenta linha à saída
        M.push_back(v);
    }
}

template <class T>
vector<vector<T>> somaMatrix(
    vector<vector<T>>& M1,
    vector<vector<T>>& M2,
    pair<int, int>& count) {
    /* Soma 2 matrizes M1 e M2 (2^k x 2^k), k inteiro
    * ENTRADAS:
    * Ponteiros para a Matrizes Mij (2^k x 2^k) 
    * SAÍDA
    * Matriz C (2^k x 2^k) com c(ij) = m1(ij) + m2(ij)
    */

    // Dimensão n da Matriz M quadrada 
    int n = M1.size();

    // Cria matriz de saída e vetor auxiliar v
    vector<vector<T>> C;
    vector<T> v;

    // Percorre cada linha
    for (int i = 0; i < n; i++) {
        // Esvazia o vetor v
        v = {};

        // Percorre cada coluna
        for (int j = 0; j < n; j++) {
            // Executa a soma e incrementa contador de soma
            v.push_back(M1[i][j] + M2[i][j]);
            count.second++;
        }

        // Insere linha na saída
        C.push_back(v);
    }

    return C;
}

template <class T>
vector<vector<T>> subtMatrix(
    vector<vector<T>>& M1,
    vector<vector<T>>& M2,
    pair<int, int>& count) {
    /* Subtrai 2 matrizes M1 e M2 (2^k x 2^k), k inteiro
    * ENTRADAS:
    * Ponteiros para a Matrizes Mij (2^k x 2^k)
    * SAÍDA
    * Matriz C (2^k x 2^k) com c(ij) = m1(ij) - m2(ij)
    */

    // Dimensão n da Matriz M quadrada 
    int n = M1.size();

    // Cria matriz de saída e vetor auxiliar v
    vector<vector<T>> C;
    vector<T> v;

    // Percorre cada linha
    for (int i = 0; i < n; i++) {
        // Esvazia o vetor v
        v = {};

        // Percorre cada coluna
        for (int j = 0; j < n; j++) {
            // Executa a subtração e incrementa contador de soma
            v.push_back(M1[i][j] - M2[i][j]);
            count.second++;
        }

        // Insere linha na saída
        C.push_back(v);
    }

    return C;
}

template <class T> void fillzeros(vector<vector<T>>& M, int k) {
    /* Insere zeros em uma matriz (n x m) até se tornar (k x k)
    * ENTRADAS:
    * Ponteiro para a Matriz M (n x m)
    * Inteiro k com novas dimensões
    * SAÍDA
    * Matriz M atualizada (k x k)
    */

    // Dimensões 'n' e 'm' atuais
    int n = M.size();
    int m = M[0].size();

    // Insere k-m zeros em cada uma das n linhas
    // Para cada uma das n linhas
    for (int i = 0; i < n; i++)
        // Para cada um dos k-m elementos extra
        for (int j = m; j < k; j++)
            M[i].push_back(0);

    // Insere k zeros em cada uma das k-n linhas extra
    // Para cada uma das k-n linhas extra
    for (int i = n; i < k; i++) {
        vector<T> v;
        // Para cada uma das k colunas
        for (int j = 0; j < k; j++)
            v.push_back(0);
        // Insere a linha extra em M
        M.push_back(v);
    }
}