
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
        Node* u;
        while (k->pai->cor == RED) {
            if (k->pai == k->pai->pai->direita) {
                u = k->pai->pai->esquerda;
                if (u->cor == RED) {
                    u->cor = BLACK;
                    k->pai->cor = BLACK;
                    k->pai->pai->cor = RED;
                    k = k->pai->pai;
                } else {
                    if (k == k->pai->esquerda) {
                        k = k->pai;
                        rotacaoDireita(k);
                    }
                    k->pai->cor = BLACK;
                    k->pai->pai->cor = RED;
                    rotacaoEsquerda(k->pai->pai);
                }
            } else {
                u = k->pai->pai->direita;
                if (u->cor == RED) {
                    u->cor = BLACK;
                    k->pai->cor = BLACK;
                    k->pai->pai->cor = RED;
                    k = k->pai->pai;
                } else {
                    if (k == k->pai->direita) {
                        k = k->pai;
                        rotacaoEsquerda(k);
                    }
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
        inserirFixup(k);
    }

    Node* minimo(Node* node) {
        while (node->esquerda != TNULL) {
            node = node->esquerda;
        }
        return node;
    }

    void transpor(Node* u, Node* v) {
        if (u->pai == nullptr) {
            raiz = v;
        } else if (u == u->pai->esquerda) {
            u->pai->esquerda = v;
        } else {
            u->pai->direita = v;
        }
        v->pai = u->pai;
    }

    void removerFixup(Node* x) {
        Node* w;
        while (x != raiz && x->cor == BLACK) {
            if (x == x->pai->esquerda) {
                w = x->pai->direita;
                if (w->cor == RED) {
                    w->cor = BLACK;
                    x->pai->cor = RED;
                    rotacaoEsquerda(x->pai);
                    w = x->pai->direita;
                }
                if (w->esquerda->cor == BLACK && w->direita->cor == BLACK) {
                    w->cor = RED;
                    x = x->pai;
                } else {
                    if (w->direita->cor == BLACK) {
                        w->esquerda->cor = BLACK;
                        w->cor = RED;
                        rotacaoDireita(w);
                        w = x->pai->direita;
                    }
                    w->cor = x->pai->cor;
                    x->pai->cor = BLACK;
                    w->direita->cor = BLACK;
                    rotacaoEsquerda(x->pai);
                    x = raiz;
                }
            } else {
                w = x->pai->esquerda;
                if (w->cor == RED) {
                    w->cor = BLACK;
                    x->pai->cor = RED;
                    rotacaoDireita(x->pai);
                    w = x->pai->esquerda;
                }
                if (w->direita->cor == BLACK && w->esquerda->cor == BLACK) {
                    w->cor = RED;
                    x = x->pai;
                } else {
                    if (w->esquerda->cor == BLACK) {
                        w->direita->cor = BLACK;
                        w->cor = RED;
                        rotacaoEsquerda(w);
                        w = x->pai->esquerda;
                    }
                    w->cor = x->pai->cor;
                    x->pai->cor = BLACK;
                    w->esquerda->cor = BLACK;
                    rotacaoDireita(x->pai);
                    x = raiz;
                }
            }
        }
        x->cor = BLACK;
    }

    void remover(Node* z) {
        Node* y = z;
        Node* x;
        Cor yOriginalColor = y->cor;
        if (z->esquerda == TNULL) {
            x = z->direita;
            transpor(z, z->direita);
        } else if (z->direita == TNULL) {
            x = z->esquerda;
            transpor(z, z->esquerda);
        } else {
            y = minimo(z->direita);
            yOriginalColor = y->cor;
            x = y->direita;
            if (y->pai == z) {
                x->pai = y;
            } else {
                transpor(y, y->direita);
                y->direita = z->direita;
                y->direita->pai = y;
            }
            transpor(z, y);
            y->esquerda = z->esquerda;
            y->esquerda->pai = y;
            y->cor = z->cor;
        }
        if (yOriginalColor == BLACK) {
            removerFixup(x);
        }
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
        if (raiz == TNULL) {
            return;
        }

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

    void remover(int chave) {
        Node* node = procura(raiz, chave);
        if (node != TNULL) {
            remover(node);
        }
    }

    void mostrar() {
        mostraEmOrdem(raiz);
        cout << endl;
    }

    bool procurar(int chave) {
        Node* result = procura(raiz, chave);
        return result != TNULL;
    }
};

int main() {
    ArvoreRubroNegra arvore;

    arvore.inserir(10);
    arvore.inserir(20);
    arvore.inserir(30);
    arvore.inserir(25);
    arvore.inserir(5);
    arvore.inserir(15);

    cout << "Árvore em ordem: ";
    arvore.mostrar();

    arvore.remover(20);
    cout << "Árvore após remover 20: ";
    arvore.mostrar();

    if (arvore.procurar(25)) {
        cout << "Elemento 25 encontrado na árvore!" << endl;
    } else {
        cout << "Elemento 25 não encontrado na árvore." << endl;
    }

    return 0;
}
