// ============================================================
//  06 - Busca sequencial x busca binária
//  Compilar: g++ -std=c++17 -Wall 06_busca.cpp -o busca && ./busca
// ============================================================
#include <iostream>
using namespace std;

// Busca sequencial: O(n). Funciona com ou sem ordem.
int buscaSeq(int v[], int n, int chave, int &comp) {
    comp = 0;
    for (int i = 0; i < n; i++) {
        comp++;
        if (v[i] == chave) return i;
    }
    return -1;
}

// Busca binária iterativa: O(log n). EXIGE array ordenado.
int buscaBinaria(int v[], int n, int chave, int &comp) {
    comp = 0;
    int ini = 0, fim = n - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comp++;
        if (v[meio] == chave) return meio;
        if (v[meio] < chave) ini = meio + 1;     // descarta a metade esquerda
        else fim = meio - 1;                     // descarta a metade direita
    }
    return -1;
}

// Busca binária recursiva (mesma ideia).
int buscaBinariaRec(int v[], int ini, int fim, int chave) {
    if (ini > fim) return -1;
    int meio = (ini + fim) / 2;
    if (v[meio] == chave) return meio;
    if (v[meio] < chave) return buscaBinariaRec(v, meio + 1, fim, chave);
    return buscaBinariaRec(v, ini, meio - 1, chave);
}

int main() {
    int desordenado[] = {27, 9, 42, 3, 36, 15, 45, 21, 6, 39, 12, 30, 33, 18, 24};
    int ordenado[]    = {3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45};
    int n = 15, c;

    int p = buscaSeq(desordenado, n, 33, c);
    cout << "Sequencial (sem ordem): 33 na posição " << p << " com " << c << " comparações\n";
    p = buscaBinaria(ordenado, n, 33, c);
    cout << "Binária (ordenado):     33 na posição " << p << " com " << c << " comparações\n";
    cout << "Binária recursiva:      33 na posição " << buscaBinariaRec(ordenado, 0, n - 1, 33) << "\n";
    p = buscaBinaria(ordenado, n, 34, c);
    cout << "Binária procurando 34:  " << p << " (não existe) com " << c << " comparações\n";
    return 0;
}
