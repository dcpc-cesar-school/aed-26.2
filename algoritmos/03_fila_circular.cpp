// ============================================================
//  03 - Fila circular com array (primeiro a entrar, primeiro a sair - FIFO)
//  É o buffer limitado do monitor do Projeto Integrador.
//  Compilar: g++ -std=c++17 -Wall 03_fila_circular.cpp -o fila && ./fila
// ============================================================
#include <iostream>
using namespace std;

#define TAM 5

int fila[TAM];
int ini = 0, fim = 0, qtd = 0;           // ini: quem sai | fim: onde entra

bool vazia() { return qtd == 0; }
bool cheia() { return qtd == TAM; }

bool enfileirar(int x) {
    if (cheia()) return false;
    fila[fim] = x;
    fim = (fim + 1) % TAM;               // dá a volta
    qtd++;
    return true;
}

int desenfileirar() {
    if (vazia()) return -1;
    int x = fila[ini];
    ini = (ini + 1) % TAM;
    qtd--;
    return x;
}

void mostrar() {
    cout << "fila: ";
    for (int k = 0, i = ini; k < qtd; k++, i = (i + 1) % TAM) cout << fila[i] << " ";
    cout << " (ini = " << ini << ", fim = " << fim << ", qtd = " << qtd << ")\n";
}

int main() {
    enfileirar(10); enfileirar(20); enfileirar(30); mostrar();
    cout << "desenfileirar() = " << desenfileirar() << "\n"; mostrar();
    enfileirar(40); enfileirar(50); mostrar();    // fim volta para 0
    enfileirar(60); mostrar();                    // reaproveita a casa 0: cheia
    cout << "enfileirar(70) com a fila cheia: " << (enfileirar(70) ? "ok" : "recusado") << "\n";
    while (!vazia()) cout << "sai " << desenfileirar() << "\n";
    return 0;
}
