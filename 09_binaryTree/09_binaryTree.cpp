/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
             LISTA 4 - ATIVIDADES PRÁTICAS - EXERCÍCIOS 09, 10 E 12
                               BINARY SEARCH TREE
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <vector>
#include <iomanip> // setw

using namespace std;

class classBST {
    // Classe para armazenar a árvore de busca binária
private:
    // Valor do nó
    int value;

    // Ponteiros para nós filhos da esquerda e da direita
    classBST* left = nullptr;
    classBST* right = nullptr;

    // Indica se nó atual é a raiz da ávore bb
    bool root = false;

public:
    // Construtor da Classe
    // Inicializa seu valor 'value'
    classBST(int k) { value = k; }

    // Elege nó atual como raiz
    void set_root() { root = true; }

    // Altera o valor do nó
    void set_value(int k) { value = k; }

    // Retorna o valor do nó
    int get_value() { return value; }

    // Método de inserção de elementos
    // ENTRADA: inteiro k a ser inserido
    // SAÍDA: objeto atualizado com o novo valor
    void insert(int k) {
        // Caso k seja menor que o valor deste nó, insira na subárvore esquerda
        if (k <= value) {
            // Caso o nó esquerdo esteja vazio, ocupe-o com um novo nó com valor k
            if (left == nullptr) { left = new classBST(k); }
            // Caso contrário, insira k recursivamente na subárvore esquerda
            else { left->insert(k); }
        }
        // Caso k seja maior que o valor deste nó, insira na subárvore direita
        else {
            // Caso o nó direito esteja vazio, ocupe-o com um novo nó com valor k
            if (right == nullptr) { right = new classBST(k); }
            // Caso contrário, insira k recursivamente na subárvore direita
            else { right->insert(k); }
        }
    }

    // Encontra o valor mínimo da árvore
    int search_min() {
        // Se o nó esquerdo estiver vazio, encontrou o mínimo -> retorne-o
        if (left == nullptr) { return value; }
        // Caso contrário, retorne recursivamente o mínimo da sub-árvore esquerda
        else { return left->search_min(); }
    }

    // Encontra o valor máximo da árvore
    int search_max() {
        // Se o nó direito estiver vazio, encontrou o máximo -> retorne-o
        if (right == nullptr) { return value; }
        // Caso contrário, retorne recursivamente o mínimo da sub - árvore direita
        else { return right->search_max(); }
    }

    // Procura o elemento de valor k na árvore, imprime o caminho
    void print_search(int k) {
        // Se valor do presente nó é o valor buscado k, imprima "raiz" e retorne
        if (k == value) { cout << "root" << endl; return; }
        // Caso contrário, se o valor buscado é menor que o valor do nó atual
        else if (k <= value) {
            // Caso não haja mais nó à esquerda, imprima "Não encontrado" e retorne
            if (left == nullptr) { cout << "NOT FOUND" << endl; return; }
            // Caso haja nó à esquerda, imprima "esquerda" e busque recursivamente na sub-árvore esquerda
            else { cout << " left -> "; left->print_search(k); }
        }
        // Caso contrário, se o valor buscado é maior ou igual ao valor do nó atual
        else {
            // Caso não haja mais nó à direita, imprima "Não encontrado" e retorne
            if (right == nullptr) { cout << "NOT FOUND" << endl; return; }
            // Caso haja nó à direita, imprima "direita" e busque recursivamente na sub-árvore direita
            else { cout << "right -> "; right->print_search(k); }
        }
    }

    // Implementa um algoritmo recursivo que encontra o tamanho de uma arvore binária
    int height() {
        /* Computa recursivamente o tamanho (a altura) de uma arvore binária
        * ENTRADA:
        * A árvore desta classe.
        * SAÍDA:
        * A altura de tal árvore (-1 se árvore vazia).
        */

        // Caso o nó atual não possua filhos, retorna -1
        if (left == nullptr and right == nullptr) { return -1; }
        else {
            // Caso o nó atual não tenha filho à esquerda, a altura esquerda é 0
            // Caso contrário, calcule a altura da árvore esquerda
            int h1 = (left == nullptr) ? 0 : left->height();

            // Caso o nó atual não tenha filho à direita, a altura direita é 0
            // Caso contrário, calcule a altura da árvore direita
            int h2 = (right == nullptr) ? 0 : right->height();

            // Retorne 0 maior entre as duas alturas, mais 1
            int hmax = (h1 >= h2) ? h1 + 1 : h2 + 1;
            return hmax;
        }
    }

    // x
    void preordertransversal() {
        /* x
        * ENTRADA:
        * A árvore desta classe.
        * SAÍDA:
        * Imprime o caminhamento.
        */

        // x
        cout << setw(3) << value << " , ";

        // x
        if (left != nullptr) { left->preordertransversal();  }

        // x
        if (right != nullptr) { right->preordertransversal(); }
    }

    // x
    void inordertransversal() {
        /* x
        * ENTRADA:
        * A árvore desta classe.
        * SAÍDA:
        * Imprime o caminhamento.
        */

        // x
        if (left != nullptr) { left->inordertransversal(); }

        // x
        cout << setw(3) << value << " , ";

        // x
        if (right != nullptr) { right->inordertransversal(); }
    }

    // x
    void postordertransversal() {
        /* x
        * ENTRADA:
        * A árvore desta classe.
        * SAÍDA:
        * Imprime o caminhamento.
        */

        // x
        if (left != nullptr) { left->postordertransversal(); }

        // x
        if (right != nullptr) { right->postordertransversal(); }

        // x
        cout << setw(3) << value << " , ";
    }
};

int main() {
    // Cria uma árvore BB e construa com valor = 10, e torne o primeiro nó raiz
    classBST bst(10);
    bst.set_root();

    // Insira os elementos 0, 15, 5, -10, -5, 25 e 20 na árvore
    vector<int> v = { 0, 15, 5, -10, -5, 25, 20 };
    for (int k : v) { bst.insert(k); }

    // Busca e imprime os valores mínimo e máximo da árvore
    int val = bst.search_min();
    cout << "Minimo = " << setw(3) << val << endl;

    val = bst.search_max();
    cout << "Maximo = " << setw(3) << val << endl;

    // Busca e imprime a altura da árvore
    val = bst.height();
    cout << "Altura = " << setw(3) << val << endl << endl;

    // Busca e imprime o caminho de cada elemento da árvore
    // Tenta buscar elemento que não pertence à árvore
    vector<int> w = { 10, 0, 15, 5, -10, -5, 25, 20, 30 };
    for (int k : w) {
        cout << setw(3) << k << ": ";
        bst.print_search(k);
    }

    // Caminhamento preorder
    cout << endl << "Preorder Transversal: " << endl;
    bst.preordertransversal();

    // Caminhamento inorder
    cout << endl << "Inorder Transversal: " << endl;
    bst.inordertransversal();

    // Caminhamento postorder
    cout << endl << "Postorder Transversal: " << endl;
    bst.postordertransversal();

    cout << endl;

    return 0;
}