# Algoritmos e Estruturas de Dados — códigos completos

CESAR School · ADS 2026.2 · Prof. David Cunha

Códigos em C++ usados nas aulas de AED, com nomes em português e um `main` de demonstração em cada arquivo.

| Arquivo | Conteúdo | Aula |
|---|---|---|
| `algoritmos/01_array.cpp` | inserir no fim, inserir/remover por posição, alterar por índice e por valor | 01 e 09 |
| `algoritmos/02_pilha.cpp` | pilha com array: empilhar, desempilhar, espiar + verificador de parênteses | 03 e 09 |
| `algoritmos/03_fila_circular.cpp` | fila circular: enfileirar, desenfileirar (base do buffer do Projeto Integrador) | 03 e 09 |
| `algoritmos/04_lista_encadeada.cpp` | lista encadeada: inserir no início/depois/no fim, buscar, alterar, remover | 03 e 09 |
| `algoritmos/05_ordenacao.cpp` | Bubble, Selection, Insertion, Shell, Quick e Merge Sort com contagem de comparações | 07, 08 e 09 |
| `algoritmos/06_busca.cpp` | busca sequencial e binária (iterativa e recursiva) | 06 e 09 |
| `algoritmos/07_abb.cpp` | árvore binária de busca: inserir, buscar, remover e percursos | 04 e 05 |
| `algoritmos/08_espalhamento.cpp` | espalhamento (hash) com sondagem linear e com encadeamento | 06 |

## Como compilar

```bash
cd algoritmos
g++ -std=c++17 -Wall 05_ordenacao.cpp -o ordenacao
./ordenacao
```

Todos os arquivos compilam sem avisos com `g++ -std=c++17 -Wall -Wextra`.
