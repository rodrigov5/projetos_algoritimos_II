/*
    Alunos: GABRIEL DA SILVA PEREIRA Matricula 202204940044
            RODRIGO RODRIGUES VELOSO Matricula 202104940044 
*/


#include <iostream>

using namespace std;

struct Node {
    int chave;
    Node* esquerda;
    Node* direita;
    int altura;
};

int obtemAltura(Node* node) {
    if (node == nullptr)
        return 0;

    return node->altura;
}

int fatorDeBalanceamento(Node* node) {
    if (node == nullptr)
        return 0;
    
    return obtemAltura(node->esquerda) - obtemAltura(node->direita);
}

void attAltura(Node* node) {
    node->altura = max(obtemAltura(node->esquerda), obtemAltura(node->direita)) + 1;
}

Node* rotacionaDireita(Node* y) {
    Node* x = y->esquerda;
    Node* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    attAltura(y);
    attAltura(x);

    return x;
}

Node* rotacionaEsquerda(Node* x) {
    Node* y = x->direita;
    Node* T2 = x->esquerda;

    x->esquerda = x;
    y->direita = T2;

    attAltura(x);
    attAltura(y);

    return y;
}

Node* balanceamento(Node* node) {
    attAltura(node);
    int balanco = fatorDeBalanceamento(node);

    if(balanco > 1 && fatorDeBalanceamento(node->esquerda) >= 0)
        return rotacionaDireita(node);

    if (balanco < -1 && fatorDeBalanceamento(node->direita) <= 0)
        return rotacionaEsquerda(node);

    if (balanco > 1 && fatorDeBalanceamento(node->esquerda) < 0) {
        node->esquerda = rotacionaEsquerda(node->esquerda);
        return rotacionaDireita(node);
    }

    if (balanco < 1 && fatorDeBalanceamento(node->direita) > 0) {
        node->direita = rotacionaDireita(node->direita);
        return rotacionaEsquerda(node);
    }

    return node;
}

Node* insere(Node* node, int chave) {
    if (node == nullptr) {
        Node* novoNode = new Node();
        novoNode->chave = chave;
        novoNode->esquerda = novoNode->direita = nullptr;
        novoNode->altura = 1;
        return novoNode;
    }

    if (chave < node->chave) 
        node->esquerda = insere(node->esquerda, chave);
    else if (chave > node->chave)
        node->direita = insere(node->direita, chave);

    
    return balanceamento(node);   
}

Node* minimoNode(Node* node) {
    Node* atual = node;
    while (atual->esquerda != nullptr)
        atual = atual->esquerda;

    return atual;
}

Node* remove(Node* raiz, int chave) {
    if (raiz == nullptr)
        return raiz;

    if (chave < raiz->chave)
        raiz->esquerda = remove(raiz->esquerda, chave);
    else if (chave > raiz->chave)
        raiz->direita = remove(raiz->direita, chave);
    else {
        if (raiz->esquerda == nullptr) {
            Node* temp = raiz->direita;
            delete raiz;
            return temp;
        } else if (raiz->esquerda == nullptr) {
            Node* temp = raiz->esquerda;
            delete raiz;
            return temp;
        }

        Node* temp = minimoNode(raiz->direita);
        raiz->chave = temp->chave;
        raiz->direita = remove(raiz->direita, temp->chave);
    }
}

Node* procura(Node* raiz, int chave) {
    if (raiz == nullptr || raiz->chave == chave)
        return raiz;

    if (chave < raiz->chave)
        return procura(raiz->esquerda, chave);
    return procura(raiz->direita, chave);
}

void mostraEmOrdem(Node* raiz) {
    if (raiz == nullptr)
        return;
    
    mostraEmOrdem(raiz->esquerda);
    cout << raiz->chave << " ";
    mostraEmOrdem(raiz->direita);
}

int main() {
    Node* raiz = nullptr;

    raiz = insere(raiz, 10);
    raiz = insere(raiz, 20);
    raiz = insere(raiz, 30);
    raiz = insere(raiz, 25);
    raiz = insere(raiz, 5);
    raiz = insere(raiz, 15);

    cout << "Arvore em ordem: ";
    mostraEmOrdem(raiz);
    cout << endl;

    raiz = remove(raiz, 20);
    cout << "Árvore AVL após remover 20: ";
    mostraEmOrdem(raiz);
    cout << endl;

    Node* resultado = procura(raiz, 25);
    if (resultado != nullptr)
        cout << "Elemento 25 encontrado na árvore!" << endl;
    else
        cout << "Elemento 25 não encontrado na árvore." << endl;

    return 0;
}