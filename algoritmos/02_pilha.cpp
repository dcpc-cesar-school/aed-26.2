// ============================================================
//  02 - Pilha com array (último a entrar, primeiro a sair - LIFO)
//  Compilar: g++ -std=c++17 -Wall 02_pilha.cpp -o pilha && ./pilha
// ============================================================
#include <iostream>
#include <string>
using namespace std;

#define TAM 5

int pilha[TAM];
int topo = -1;                           // -1 = pilha vazia

bool vazia() { return topo == -1; }
bool cheia() { return topo == TAM - 1; }

bool empilhar(int x) {
    if (cheia()) return false;
    pilha[++topo] = x;                   // primeiro sobe o topo, depois grava
    return true;
}

int desempilhar() {
    if (vazia()) return -1;
    return pilha[topo--];                // primeiro lê, depois desce o topo
}

int espiar() {                           // olha o topo sem remover
    if (vazia()) return -1;
    return pilha[topo];
}

// Aplicação: verificar se parênteses, colchetes e chaves estão balanceados.
bool balanceado(const string &s) {
    char p[100]; int t = -1;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') p[++t] = c;
        else if (c == ')' || c == ']' || c == '}') {
            if (t == -1) return false;   // fechou sem ter aberto
            char a = p[t--];
            if ((c == ')' && a != '(') || (c == ']' && a != '[') || (c == '}' && a != '{')) return false;
        }
    }
    return t == -1;                      // sobrou algo aberto?
}

int main() {
    empilhar(10); empilhar(20); empilhar(30);
    cout << "Topo após empilhar 10, 20, 30: " << espiar() << " (topo = " << topo << ")\n";
    cout << "desempilhar() = " << desempilhar() << " (topo = " << topo << ")\n";
    cout << "desempilhar() = " << desempilhar() << " (topo = " << topo << ")\n";

    for (string s : {"(a[b]{c})", "(a[b)]", "((a)"})
        cout << s << " -> " << (balanceado(s) ? "balanceado" : "NÃO balanceado") << "\n";
    return 0;
}
