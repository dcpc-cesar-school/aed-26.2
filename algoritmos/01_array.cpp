// ============================================================
//  01 - Array: inserir, remover, alterar e procurar
//  Algoritmos e Estruturas de Dados - CESAR School
//  Compilar: g++ -std=c++17 -Wall 01_array.cpp -o array && ./array
// ============================================================
#include <iostream>
using namespace std;

#define TAM 8   // tamanho máximo do array

void imprimir(int v[], int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) cout << v[i] << " ";
    cout << "]  n = " << n << "\n";
}

// Insere no fim: O(1). n aponta a próxima posição livre.
bool inserirFim(int v[], int &n, int x) {
    if (n == TAM) return false;          // cheio
    v[n] = x;
    n++;
    return true;
}

// Insere na posição pos: O(n). Desloca para a direita começando do FIM.
bool inserir(int v[], int &n, int pos, int x) {
    if (n == TAM || pos < 0 || pos > n) return false;
    for (int i = n; i > pos; i--)
        v[i] = v[i - 1];                 // abre espaço
    v[pos] = x;
    n++;
    return true;
}

// Remove a posição pos: O(n). Desloca para a esquerda começando do buraco.
bool remover(int v[], int &n, int pos) {
    if (pos < 0 || pos >= n) return false;
    for (int i = pos; i < n - 1; i++)
        v[i] = v[i + 1];                 // fecha o buraco
    n--;
    return true;
}

// Alterar sabendo o índice: O(1).
void alterarPorIndice(int v[], int i, int novo) {
    v[i] = novo;
}

// Alterar pelo valor: precisa procurar primeiro, O(n).
bool alterarPorValor(int v[], int n, int antigo, int novo) {
    for (int i = 0; i < n; i++) {
        if (v[i] == antigo) {
            v[i] = novo;
            return true;
        }
    }
    return false;
}

int main() {
    int v[TAM];
    int n = 0;                           // nenhuma posição em uso

    for (int x : {10, 20, 30, 40, 50}) inserirFim(v, n, x);
    cout << "Depois de 5 inserções no fim: "; imprimir(v, n);
    cout << "Primeiro: v[0] = " << v[0] << " | Último: v[n-1] = v[" << n - 1 << "] = " << v[n - 1]
         << " | Próxima livre: v[n] = v[" << n << "]\n";

    inserir(v, n, 2, 25);
    cout << "inserir(v, n, 2, 25):         "; imprimir(v, n);

    remover(v, n, 1);
    cout << "remover(v, n, 1):             "; imprimir(v, n);

    alterarPorIndice(v, 3, 35);
    cout << "v[3] = 35:                    "; imprimir(v, n);

    alterarPorValor(v, n, 50, 55);
    cout << "trocar 50 por 55:             "; imprimir(v, n);
    return 0;
}
