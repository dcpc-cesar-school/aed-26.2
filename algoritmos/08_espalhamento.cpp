// ============================================================
//  08 - Busca por espalhamento (hash)
//  a) sondagem linear   b) encadeamento (lista em cada posição)
//  Compilar: g++ -std=c++17 -Wall 08_espalhamento.cpp -o hash && ./hash
// ============================================================
#include <iostream>
using namespace std;

#define TAM 10
#define VAZIO -1
#define REMOVIDO -2

int h(int chave) { return chave % TAM; }        // função de espalhamento

// ---------- a) Sondagem linear ----------
int tabela[TAM];

void inicializar() { for (int i = 0; i < TAM; i++) tabela[i] = VAZIO; }

bool inserirSondagem(int chave) {
    int pos = h(chave);
    for (int k = 0; k < TAM; k++) {
        int i = (pos + k) % TAM;                 // colisão? tenta a próxima
        if (tabela[i] == VAZIO || tabela[i] == REMOVIDO) { tabela[i] = chave; return true; }
    }
    return false;                                // tabela cheia
}

int buscarSondagem(int chave) {
    int pos = h(chave);
    for (int k = 0; k < TAM; k++) {
        int i = (pos + k) % TAM;
        if (tabela[i] == VAZIO) return -1;       // casa nunca usada: não existe
        if (tabela[i] == chave) return i;
    }
    return -1;
}

void removerSondagem(int chave) {
    int i = buscarSondagem(chave);
    if (i != -1) tabela[i] = REMOVIDO;           // marca, para não quebrar buscas
}

// ---------- b) Encadeamento ----------
struct No { int chave; No* prox; };
No* baldes[TAM];

void inserirEncadeado(int chave) {
    int i = h(chave);
    baldes[i] = new No{chave, baldes[i]};        // insere no início da lista
}

bool buscarEncadeado(int chave) {
    for (No* p = baldes[h(chave)]; p; p = p->prox)
        if (p->chave == chave) return true;
    return false;
}

int main() {
    inicializar();
    for (int x : {15, 25, 35, 7, 42}) inserirSondagem(x);   // 15, 25 e 35 colidem na casa 5
    cout << "Sondagem linear: ";
    for (int i = 0; i < TAM; i++) cout << "[" << i << "]=" << tabela[i] << " ";
    cout << "\nbuscar(35) -> posição " << buscarSondagem(35) << "\n";
    removerSondagem(25);
    cout << "após remover 25, buscar(35) -> posição " << buscarSondagem(35) << "\n\n";

    for (int i = 0; i < TAM; i++) baldes[i] = nullptr;
    for (int x : {12, 22, 32, 5, 17}) inserirEncadeado(x);
    cout << "Encadeamento:\n";
    for (int i = 0; i < TAM; i++) if (baldes[i]) {
        cout << "  [" << i << "] ";
        for (No* p = baldes[i]; p; p = p->prox) cout << p->chave << " -> ";
        cout << "NULL\n";
    }
    cout << "buscar(22): " << (buscarEncadeado(22) ? "achou" : "não achou") << "\n";
    for (int i = 0; i < TAM; i++) while (baldes[i]) { No* p = baldes[i]; baldes[i] = p->prox; delete p; }
    return 0;
}
