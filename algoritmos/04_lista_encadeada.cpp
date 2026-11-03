// ============================================================
//  04 - Lista encadeada simples
//  Compilar: g++ -std=c++17 -Wall 04_lista_encadeada.cpp -o lista && ./lista
// ============================================================
#include <iostream>
using namespace std;

struct No {
    int dado;
    No* prox;
};

// O(1): o novo nó vira o início.
No* inserirNoInicio(No* inicio, int x) {
    No* novo = new No;
    novo->dado = x;
    novo->prox = inicio;
    return novo;
}

// O(1) com o nó anterior em mãos. A ORDEM das duas ligações importa.
void inserirDepois(No* ant, int x) {
    No* novo = new No;
    novo->dado = x;
    novo->prox = ant->prox;              // 1º: segura o resto da lista
    ant->prox = novo;                    // 2º: religa o anterior
}

// O(n) para chegar ao fim.
No* inserirNoFim(No* inicio, int x) {
    No* novo = new No{x, nullptr};
    if (!inicio) return novo;
    No* p = inicio;
    while (p->prox) p = p->prox;
    p->prox = novo;
    return inicio;
}

// O(n): percorre até achar.
No* buscar(No* inicio, int x) {
    for (No* p = inicio; p; p = p->prox)
        if (p->dado == x) return p;
    return nullptr;
}

// Alterar = buscar + trocar o dado.
bool alterar(No* inicio, int antigo, int novo) {
    No* p = buscar(inicio, antigo);
    if (!p) return false;
    p->dado = novo;
    return true;
}

// Percorre com dois ponteiros (ant e atual), pula o nó e libera a memória.
No* remover(No* inicio, int x) {
    No* ant = nullptr;
    No* atual = inicio;
    while (atual && atual->dado != x) {
        ant = atual;
        atual = atual->prox;
    }
    if (!atual) return inicio;           // não achou
    if (!ant) inicio = atual->prox;      // era o 1º nó
    else ant->prox = atual->prox;        // pula o nó
    delete atual;
    return inicio;
}

void imprimir(No* inicio) {
    for (No* p = inicio; p; p = p->prox) cout << p->dado << " -> ";
    cout << "NULL\n";
}

void liberar(No* inicio) {
    while (inicio) { No* p = inicio; inicio = inicio->prox; delete p; }
}

int main() {
    No* inicio = nullptr;
    inicio = inserirNoInicio(inicio, 40);
    inicio = inserirNoInicio(inicio, 20);
    inicio = inserirNoInicio(inicio, 10);
    imprimir(inicio);                                  // 10 -> 20 -> 40

    inserirDepois(buscar(inicio, 20), 30);  imprimir(inicio);   // 10 -> 20 -> 30 -> 40
    inicio = inserirNoFim(inicio, 50);      imprimir(inicio);
    alterar(inicio, 50, 55);                imprimir(inicio);
    inicio = remover(inicio, 30);           imprimir(inicio);
    inicio = remover(inicio, 10);           imprimir(inicio);   // remove o 1º
    liberar(inicio);
    return 0;
}
