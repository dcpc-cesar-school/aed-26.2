// ============================================================
//  05 - Métodos de ordenação (com contagem de comparações)
//  Bubble, Selection, Insertion, Shell, Quick e Merge Sort
//  Compilar: g++ -std=c++17 -Wall 05_ordenacao.cpp -o ordenacao && ./ordenacao
// ============================================================
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

long long comparacoes = 0;

void trocar(int &a, int &b) { int t = a; a = b; b = t; }

// Bubble Sort: troca vizinhos fora de ordem. O(n²); O(n) se já ordenado (flag trocou).
void bubbleSort(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool trocou = false;
        for (int j = 0; j < n - 1 - i; j++) {
            comparacoes++;
            if (v[j] > v[j + 1]) { trocar(v[j], v[j + 1]); trocou = true; }
        }
        if (!trocou) break;              // já ordenado
    }
}

// Selection Sort: escolhe o menor e coloca na posição i. O(n²) sempre.
void selectionSort(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j] < v[menor]) menor = j;
        }
        if (menor != i) trocar(v[i], v[menor]);
    }
}

// Insertion Sort: encaixa cada chave na parte já ordenada. O(n²); O(n) se quase ordenado.
void ordenarPorInsercao(int v[], int n) {
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;
        while (j >= 0 && (comparacoes++, v[j] > chave)) {
            v[j + 1] = v[j];             // desliza
            j--;
        }
        v[j + 1] = chave;                // encaixa
    }
}

// Shell Sort: Insertion com saltos (gap) que diminuem até 1.
void shellSort(int v[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int chave = v[i];
            int j = i;
            while (j >= gap && (comparacoes++, v[j - gap] > chave)) {
                v[j] = v[j - gap];
                j -= gap;
            }
            v[j] = chave;
        }
    }
}

// Quick Sort: pivô (último elemento); menores à esquerda, maiores à direita. O(n log n) médio.
int particionar(int v[], int ini, int fim) {
    int pivo = v[fim];
    int i = ini - 1;
    for (int j = ini; j < fim; j++) {
        comparacoes++;
        if (v[j] <= pivo) { i++; trocar(v[i], v[j]); }
    }
    trocar(v[i + 1], v[fim]);
    return i + 1;
}
void quickSort(int v[], int ini, int fim) {
    if (ini < fim) {
        int p = particionar(v, ini, fim);
        quickSort(v, ini, p - 1);
        quickSort(v, p + 1, fim);
    }
}

// Merge Sort: divide ao meio e intercala as metades ordenadas. O(n log n) sempre.
void intercalar(int v[], int ini, int meio, int fim) {
    int n1 = meio - ini + 1, n2 = fim - meio;
    int* esq = new int[n1];
    int* dir = new int[n2];
    for (int i = 0; i < n1; i++) esq[i] = v[ini + i];
    for (int j = 0; j < n2; j++) dir[j] = v[meio + 1 + j];
    int i = 0, j = 0, k = ini;
    while (i < n1 && j < n2) {
        comparacoes++;
        if (esq[i] <= dir[j]) v[k++] = esq[i++];
        else v[k++] = dir[j++];
    }
    while (i < n1) v[k++] = esq[i++];
    while (j < n2) v[k++] = dir[j++];
    delete[] esq; delete[] dir;
}
void mergeSort(int v[], int ini, int fim) {
    if (ini < fim) {
        int meio = (ini + fim) / 2;
        mergeSort(v, ini, meio);
        mergeSort(v, meio + 1, fim);
        intercalar(v, ini, meio, fim);
    }
}

// ---------- utilitários ----------
void imprimir(int v[], int n) { cout << "[ "; for (int i = 0; i < n; i++) cout << v[i] << " "; cout << "]\n"; }
void copiar(int o[], int d[], int n) { for (int i = 0; i < n; i++) d[i] = o[i]; }
bool ordenado(int v[], int n) { for (int i = 1; i < n; i++) if (v[i - 1] > v[i]) return false; return true; }

int main() {
    int ex[] = {40, 20, 50, 10, 30};
    int a[5]; copiar(ex, a, 5);
    comparacoes = 0; ordenarPorInsercao(a, 5);
    cout << "Insertion em [40, 20, 50, 10, 30]: "; imprimir(a, 5);
    cout << "comparações: " << comparacoes << "\n\n";

    const int N = 1000;
    int base[N], v[N];
    srand(42);
    for (int i = 0; i < N; i++) base[i] = rand() % 10000;

    const char* nomes[] = {"Bubble", "Selection", "Insertion", "Shell", "Quick", "Merge"};
    cout << "n = " << N << " valores aleatórios\n";
    for (int m = 0; m < 6; m++) {
        copiar(base, v, N); comparacoes = 0;
        switch (m) {
            case 0: bubbleSort(v, N); break;
            case 1: selectionSort(v, N); break;
            case 2: ordenarPorInsercao(v, N); break;
            case 3: shellSort(v, N); break;
            case 4: quickSort(v, 0, N - 1); break;
            case 5: mergeSort(v, 0, N - 1); break;
        }
        cout << "  " << nomes[m] << ": " << comparacoes << " comparações"
             << (ordenado(v, N) ? "  (ok)" : "  (ERRO)") << "\n";
    }
    return 0;
}
