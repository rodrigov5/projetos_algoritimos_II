/*
    Alunos: GABRIEL DA SILVA PEREIRA Matricula 202204940044.
            RODRIGO RODRIGUES VELOSO Matricula 202104940044.
*/

#include <iostream>
using namespace std;

enum Cor { RED, BLACK };

struct Node {
    int chave;
    Node* esquerda;
    Node* direita;
    Node* pai;
    Cor cor;
};

class ArvoreRubroNegra {
private:
    Node* raiz;
    Node* TNULL;

    void rotacaoEsquerda(Node* x) {
        cout << "Executando rotação à esquerda no nó com chave " << x->chave << endl;
        Node* y = x->direita;
        x->direita = y->esquerda;
        if (y->esquerda != TNULL) {
            y->esquerda->pai = x;
        }
        y->pai = x->pai;
        if (x->pai == nullptr) {
            raiz = y;
        } else if (x == x->pai->esquerda) {
            x->pai->esquerda = y;
        } else {
            x->pai->direita = y;
        }
        y->esquerda = x;
        x->pai = y;
    }

    void rotacaoDireita(Node* x) {
        cout << "Executando rotação à direita no nó com chave " << x->chave << endl;
        Node* y = x->esquerda;
        x->esquerda = y->direita;
        if (y->direita != TNULL) {
            y->direita->pai = x;
        }
        y->pai = x->pai;
        if (x->pai == nullptr) {
            raiz = y;
        } else if (x == x->pai->direita) {
            x->pai->direita = y;
        } else {
            x->pai->esquerda = y;
        }
        y->direita = x;
        x->pai = y;
    }

    void balanceamentoInsercao(Node* k) {
        cout << "Balanceando após inserção do nó com chave " << k->chave << endl;
        Node* u;
        while (k->pai->cor == RED) {
            if (k->pai == k->pai->pai->direita) {
                u = k->pai->pai->esquerda;
                if (u->cor == RED) {
                    cout << "Caso 1: Tio é vermelho." << endl;
                    u->cor = BLACK;
                    k->pai->cor = BLACK;
                    k->pai->pai->cor = RED;
                    k = k->pai->pai;
                } else {
                    if (k == k->pai->esquerda) {
                        cout << "Caso 2: Nó é filho esquerdo." << endl;
                        k = k->pai;
                        rotacaoDireita(k);
                    }
                    cout << "Caso 3: Rotação à esquerda no avô." << endl;
                    k->pai->cor = BLACK;
                    k->pai->pai->cor = RED;
                    rotacaoEsquerda(k->pai->pai);
                }
            } else {
                u = k->pai->pai->direita;
                if (u->cor == RED) {
                    cout << "Caso 1: Tio é vermelho." << endl;
                    u->cor = BLACK;
                    k->pai->cor = BLACK;
                    k->pai->pai->cor = RED;
                    k = k->pai->pai;
                } else {
                    if (k == k->pai->direita) {
                        cout << "Caso 2: Nó é filho direito." << endl;
                        k = k->pai;
                        rotacaoEsquerda(k);
                    }
                    cout << "Caso 3: Rotação à direita no avô." << endl;
                    k->pai->cor = BLACK;
                    k->pai->pai->cor = RED;
                    rotacaoDireita(k->pai->pai);
                }
            }
            if (k == raiz) break;
        }
        raiz->cor = BLACK;
    }

    void inserirFixup(Node* k) {
        balanceamentoInsercao(k);
    }

    void inserir(Node* k) {
        cout << "Inserindo no com chave " << k->chave << endl;
        Node* y = nullptr;
        Node* x = raiz;
        while (x != TNULL) {
            y = x;
            if (k->chave < x->chave) {
                x = x->esquerda;
            } else {
                x = x->direita;
            }
        }
        k->pai = y;
        if (y == nullptr) {
            raiz = k;
        } else if (k->chave < y->chave) {
            y->esquerda = k;
        } else {
            y->direita = k;
        }
        k->esquerda = TNULL;
        k->direita = TNULL;
        k->cor = RED;
        cout << "No com chave " << k->chave << " inserido. Ajustando a arvore..." << endl;
        inserirFixup(k);
        cout << "Inserção do no com chave " << k->chave << " conclida!" << endl;
    }

    Node* procura(Node* raiz, int chave) {
        if (raiz == TNULL || raiz->chave == chave) {
            return raiz;
        }
        if (chave < raiz->chave) {
            return procura(raiz->esquerda, chave);
        }
        return procura(raiz->direita, chave);
    }

    void mostraEmOrdem(Node* raiz) {
        if (raiz == TNULL) return;
        mostraEmOrdem(raiz->esquerda);
        cout << raiz->chave << " ";
        mostraEmOrdem(raiz->direita);
    }

public:
    ArvoreRubroNegra() {
        TNULL = new Node;
        TNULL->cor = BLACK;
        TNULL->chave = 0;
        TNULL->esquerda = nullptr;
        TNULL->direita = nullptr;
        raiz = TNULL;
    }

    void inserir(int chave) {
        Node* node = new Node;
        node->chave = chave;
        node->pai = nullptr;
        node->cor = RED;
        node->esquerda = TNULL;
        node->direita = TNULL;
        inserir(node);
    }

    void mostrar() {
        mostraEmOrdem(raiz);
        cout << endl;
    }
};

int main() {
    ArvoreRubroNegra arvore;

    cout << "Inserindo elementos na arvore..." << endl;
    arvore.inserir(10);
    arvore.inserir(20);
    arvore.inserir(30);
    arvore.inserir(25);
    arvore.inserir(5);
    arvore.inserir(15);

    cout << "arvore em ordem: ";
    arvore.mostrar();

    return 0;
}
