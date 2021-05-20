/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                  LISTA 4 - ATIVIDADES PRÁTICAS - EXERCÍCIO 14
                                  Quick Hull
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

class Pontos {
    // Classe para armazenar uma lista com pontos no plano
private:
    // Cria um vetor com pares de inteiros
    vector<pair<int, int>> V;
public:
    // Entrada de pontos: recebe coordenadas inteiras (x, y) 
    // e armazena como um par em V
    void set_point(int x, int y) { V.push_back(pair<int, int>(x, y)); }

    // Saída de pontos: devolve o (n+1)-esimo ponto (coordenada x ou y
    int get_x(int n) { return V[n].first; }
    int get_y(int n) { return V[n].second; }

    // Calcula coeficientes da reta entre os pontos [i] e [j]
    int get_a(int i, int j) { return V[j].second - V[i].second; }
    int get_b(int i, int j) { return V[i].first - V[j].first; }
    int get_c(int i, int j) {
        return V[i].first * V[j].second - V[i].second * V[j].first;
    }

    // Informa se o ponto [k] está acima ou abaixo da reta definida por a, b, c
    int get_r(int k, int a, int b, int c) {
        return a * V[k].first + b * V[k].second - c;
    }

    // Retorna a quantidade pontos armazenada
    int size() { return V.size(); }
};

void printPairs(Pontos& P);
int min_index(vector<int>& angles);
int max_index(vector<int>& angles);

int orientation(vector<int>& T) {
    /*  Encontra a orientação da tripla (x1, x2, x3)
    * ENTRADA:
    * Ponteiro para Vetor v com elementos da tripla
    * x1 = {T[0], T[1]} ; x2 = {T[2], T[3]} ; x3 = {T[5], T[5]}
    * SAÍDA:
    * 0 --> (x1, x2, x3) colineares
    * + --> Sentido Horário
    * - --> Sentido AntiHorário
    */

    // Usa a seguinte fórmula para determinar a orientação
    int val = (T[3] - T[1]) * (T[4] - T[2]) - (T[2] - T[0]) * (T[5] - T[3]);

    return val;
}

void execute_quickHull(Pontos& P, 
    int left, int right, 
    vector<bool>& added_to_convexhull,
    int sentido) {
    /*  Encontra recursivamente o próximo elemento da casca convexa 
    * entre 2 pontos já conhecidos da casca
    * ENTRADAS:
    * Ponteiro para Classe de Pontos P com os pontos em ordem crescente
    * Inteiros com pontos esquerdo e direito conhecidos da casca (limites atuais)
    * Ponteiro para vetor de booleanos added_to_convexhull com estado de cada ponto
    * Inteiro sentido com sentido da busca
    * SAÍDA:
    * Vetor added_to_convexhull atualizado com pontos que pertencem à casca
    * + --> Sentido Horário
    * - --> Sentido AntiHorário
    */

    // Determina a quantidade de pontos em P
    int n = P.size();
    
    // Adiciona left e right à casca
    added_to_convexhull[left] = true;
    added_to_convexhull[right] = true;

    // Vetor com os ângulos entre cada ponto e reta entre left e right
    // Vetor com left, right e ponto atual para cálculo da orientação
    vector<int> angles, points;

    // Índices dos pontos com ângulo mínimo e máximo em relação a left-right
    int Pmin, Pmax;

    // Para cada ponto do conjunto P
    for (int i = 0; i < n; i++) {
        // Caso tal ponto já pertença à casca, orientação = 0
        if (added_to_convexhull[i]) { angles.push_back(0); }
        else {
            // Caso contrário, esvazie points e acrescente as coordenadas
            // dos pontos left, right e i (ponto atual do laço)
            points = {};
            points.push_back(P.get_x(left));
            points.push_back(P.get_y(left));
            points.push_back(P.get_x(right));
            points.push_back(P.get_y(right));
            points.push_back(P.get_x(i));
            points.push_back(P.get_y(i));

            // Calcula a orientação da tripla e armazena em angles
            int ori = orientation(points);
            angles.push_back(ori);
        }
    }

    // Caso a busca esteja no sentido superior
    if (sentido == 1) {
        // Encontra o índice do ponto com maior ângulo
        Pmax = max_index(angles);

        // Se tal valor for positivo
        if (angles[Pmax] > 0) {
            // Divida o problema em dois (left-Pmax , Pmax-right) 
            // permanecendo no sentido positivo
            execute_quickHull(P, left, Pmax, added_to_convexhull, 1);
            execute_quickHull(P, Pmax, right, added_to_convexhull, 1);
        }
    }

    // Caso a busca esteja no sentido inferior
    if (sentido == -1) {
        // Encontra o índice do ponto com menor ângulo
        Pmin = min_index(angles);

        // Se tal valor for negativo
        if (angles[Pmin] < 0) {
            // Divida o problema em dois (left-Pmin , Pmin-right) 
            // permanecendo no sentido negativo
            execute_quickHull(P, left, Pmin, added_to_convexhull, -1);
            execute_quickHull(P, Pmin, right, added_to_convexhull, -1);
        }
    }
}

Pontos quickConvexHull(Pontos& P) {
    /*  Implementação do CONVEX HULL via Divide & Conquer
    * Encontra a casca convexa de um conjunto de pontos
    * ENTRADA:
    * Ponteiro para Classe de Pontos P com os pontos em ordem crescente
    * SAÍDA:
    * Objeto da Classe de Pontos convexHull com os pontos da casca convexa
    * em sentido Anti-Horário e começando pelo ponto mais à esquerda
    */

    // Determina a quantidade de pontos em P
    int n = P.size();

    // Inicializa estrutura com a saída
    Pontos convexHull;

    // Deve haver pelo menos 3 pontos, caso contrário retorna vazio
    if (n < 3) return convexHull;

    // Inicializa estrutura auxiliar added_to_convexhull
    // Informa se ponto já pertence à casca convexa ou não
    // Inicialmente, nenhum ponto pertence à casca
    vector<bool> added_to_convexhull;
    for (int i = 0; i < n; i++) {
        added_to_convexhull.push_back(false);
    }

    // O primeiro e o último ponto certamente pertencem à casca convexa
    // Portanto, left = 0 e right = n-1
    // Realiza a busca entre esses limites pelo lado superior E pelo inferior
    execute_quickHull(P, 0, n - 1, added_to_convexhull, 1);
    execute_quickHull(P, 0, n - 1, added_to_convexhull, -1);

    // Transforma added_to_convexhull em um conjunto de pontos
    for (int i = 0; i < n; i++) {
        // Para cda ponto de P, se pertencer à casca, adicione-o em convexHull
        if (added_to_convexhull[i]) { 
            convexHull.set_point(P.get_x(i), P.get_y(i));
        }
    }

    return convexHull;
}

int main() {
    // Cria um objeto P da classe Pontos e acrescenta um conjunto de pontos
    Pontos P;
    P.set_point(0, 2);
    P.set_point(1, 0);
    P.set_point(1, 1);
    P.set_point(1, 8);
    P.set_point(2, 1);
    P.set_point(3, 0);
    P.set_point(3, 3);
    P.set_point(3, 5);
    P.set_point(4, 2);
    P.set_point(5, 4); 
    P.set_point(7, 1);
    P.set_point(7, 7);
    P.set_point(8, 2);

    // Imprime os pontos de P
    cout << "Pairs:" << endl;
    printPairs(P);

    // Calcula a casca convexa e armazena no objeto H da classe Pontos
    // Imprime os pontos do resultado H
    cout << endl << "Convex Hull: " << endl;
    Pontos H = quickConvexHull(P);
    printPairs(H);

    return 0;
}

void printPairs(Pontos& P) {
    /*  Função para Imprimir vetores
    * ENTRADA:
    * Ponteiro para objeto P com pontos
    */

    // Determina a quantidade de pontos em P
    int n = P.size();

    // Itera todos os elementos do objeto P e imprimea cada par
    for (int i = 0; i < n; i++)
        cout << "(" << P.get_x(i) << " , " << P.get_y(i) << ")" << endl;
}

int min_index(vector<int>& v) {
    /*  Função para encontrar o índice do valor mínimo de um vetor
    * ENTRADA:
    * Ponteiro para vetor v com valores
    */

    // Supõe que o menor valor é o primeiro
    int k = 0;

    // Tamanho do vetor v
    int n = v.size();

    // Para cada ponto do vetor (do 2º ao último)
    for (int i = 1; i < n; i++) {
        // Se tal ponto for menor que v[k], atualiza k com seu índice
        if (v[i] < v[k]) { k = i; }
    }

    return k;
}

int max_index(vector<int>& v) {
    /*  Função para encontrar o índice do valor máximo de um vetor
    * ENTRADA:
    * Ponteiro para vetor v com valores
    */

    // Supõe que o maior valor é o primeiro
    int k = 0;

    // Tamanho do vetor v
    int n = v.size();

    // Para cada ponto do vetor (do 2º ao último)
    for (int i = 1; i < n; i++) {
        // Se tal ponto for maior que v[k], atualiza k com seu índice
        if (v[i] > v[k]) { k = i; }
    }

    return k;
}

