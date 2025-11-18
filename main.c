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
        case 3: {
            int a=-1;
            do{
                printf("Deseja buscar as vendas pelo nome do vendedor ou pela matrícula?");
                scanf("%d", &a);
                limpaBuffer();
            }while(a!=0 && a!=1);

            if(a==0) {
                printf("Qual o nome do vendedor?");
                char nome[50];
                fgets(nome,sizeof(nome),stdin);
                nome[strcspn(nome, "\n")] = '\0';

                buscaImprimeNome(arvoreVendas->raiz, nome);

            }
            if(a==1) {
                printf("Qual a matrícula?");
                char matricula[5];
                fgets(matricula,sizeof(matricula),stdin);
                matricula[strcspn(matricula, "\n")] = '\0'

                buscaImprimeMatricula(arvoreVendas->raiz, matricula);

            }
            break;
        }
        case 4: {
            float valor=0;
            printf("Qual o Valor?");
            scanf("%d", valor);
            int b=-1;
            do{
                printf("Deseja buscar as vendas acima do valor(0) ou abaixo(1)?");
                scanf("%d", &b);
                limpaBuffer();
            }while(b!=0 && b!=1);

            vendasAcimaAbaixoValor(arvoreVendas->raiz, valor, b);
        }
        break;


        default:
            break;
        }
    }


    return 0;
}
