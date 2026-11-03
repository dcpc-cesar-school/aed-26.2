// ============================================================
//  07 - Árvore Binária de Busca (ABB): inserir, buscar, remover, percursos
//  Compilar: g++ -std=c++17 -Wall 07_abb.cpp -o abb && ./abb
// ============================================================
#include <iostream>
using namespace std;

struct No {
    int valor;
    No* esq;
    No* dir;
};

No* novoNo(int valor) { return new No{valor, nullptr, nullptr}; }

// Menor à esquerda, maior à direita. Não aceita repetidos.
No* inserir(No* raiz, int valor) {
    if (!raiz) return novoNo(valor);
    if (valor < raiz->valor) raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor) raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

// O(h): um único caminho da raiz até a chave.
No* buscar(No* raiz, int chave) {
    while (raiz && raiz->valor != chave)
        raiz = (chave < raiz->valor) ? raiz->esq : raiz->dir;
    return raiz;
}

No* minimo(No* raiz) {
    while (raiz && raiz->esq) raiz = raiz->esq;
    return raiz;
}

// Três casos: sem filhos, um filho, dois filhos (troca pelo sucessor).
No* remover(No* raiz, int valor) {
    if (!raiz) return nullptr;
    if (valor < raiz->valor) raiz->esq = remover(raiz->esq, valor);
    else if (valor > raiz->valor) raiz->dir = remover(raiz->dir, valor);
    else {
        if (!raiz->esq) { No* d = raiz->dir; delete raiz; return d; }
        if (!raiz->dir) { No* e = raiz->esq; delete raiz; return e; }
        No* suc = minimo(raiz->dir);
        raiz->valor = suc->valor;
        raiz->dir = remover(raiz->dir, suc->valor);
    }
    return raiz;
}

void preOrdem(No* r) { if (r) { cout << r->valor << " "; preOrdem(r->esq); preOrdem(r->dir); } }
void emOrdem(No* r)  { if (r) { emOrdem(r->esq); cout << r->valor << " "; emOrdem(r->dir); } }   // sai ordenado
void posOrdem(No* r) { if (r) { posOrdem(r->esq); posOrdem(r->dir); cout << r->valor << " "; } }
void liberar(No* r)  { if (r) { liberar(r->esq); liberar(r->dir); delete r; } }                 // pós-ordem

int main() {
    No* raiz = nullptr;
    for (int x : {50, 30, 70, 20, 40, 60, 80}) raiz = inserir(raiz, x);
    cout << "Pré-ordem: "; preOrdem(raiz); cout << "\n";
    cout << "Em-ordem:  "; emOrdem(raiz);  cout << "\n";
    cout << "Pós-ordem: "; posOrdem(raiz); cout << "\n";
    cout << "buscar(60): " << (buscar(raiz, 60) ? "achou" : "não achou") << "\n";
    raiz = remover(raiz, 20);  // sem filhos
    raiz = remover(raiz, 30);  // um filho
    raiz = remover(raiz, 50);  // dois filhos (raiz)
    cout << "Após remover 20, 30 e 50 (em-ordem): "; emOrdem(raiz); cout << "\n";
    liberar(raiz);
    return 0;
}
