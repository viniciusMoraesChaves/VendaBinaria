#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "abb.h"



int main(){
    // Para garantir a unicidade das Matrículas deve-se criar uma árvore binária de busca (ABB) ou um Vetor Ordenado para armazenar as matrículas já utilizadas.
    // A insersão de uma nova venda deve verificar se a matrícula do vendedor já existe na estrutura escolhida.
    // Isso ocorrerá dessa forma:
    // 1. Pergunta se o vendedor já está cadastrado.
    // 2. Se sim, Pergunta a matrícula. Pergunta a metricula e verifica na estrutura se já existe.
    // 3. Se não, Gera uma nova matrícula única e armazena nas estruturas.

    // Vetor Ordenado
    // Pros: Simples de implementar, fácil de entender.
    // Cons: Inserção e remoção podem ser lentas (O(n)).

    // Árvore Binária de Busca (ABB)
    // Pros: Inserção, remoção e busca eficientes (O(log n) em média
    // Cons: Mais complexa de implementar, requer mais memória.

    Arv *arvoreVendas = criaArvore();
    while (1)
    {
        int op;
        printf("Escolha a Operação desejada: ");
        scanf("%d",&op);
        limpaBuffer();
        switch (op)
        {
        case 1:
            Venda v = criaVenda(arvoreVendas);
            inserirArvore(arvoreVendas,v);
            imprimirVenda(v);
            break;
        case 2:
            imprimirArvore(arvoreVendas,0);
            break;
        default:
            break;
        }
    }
    

    return 0;
}
