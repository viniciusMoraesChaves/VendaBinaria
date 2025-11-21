#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "abb.h"
#include <string.h>



int main(){
    setbuf(stdout, NULL);
    Arv *arvoreVendas = criaArvore();
    srand(22);
    while (1)
    {
        int op;
        printf("\nEscolha a Operação desejada: ");
        scanf("%d",&op);
        limpaBuffer();
        switch (op)
        {
        case 1:   
            Venda v = criaVenda(arvoreVendas);
            inserirArvore(arvoreVendas,v);
            printf("\n\t%-3s | %10s | %10s | %10s | %s | %-5s\n","ID","Vendedor","Matricula","Cliente","Data da Transação","Valor");
            imprimirVenda(v);
            break;
        case 2:
            if(!ArvVazia(arvoreVendas)){
                imprimirArvore(arvoreVendas,0);
            }else{
                printf("\nArvore Vazia");
            }
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
                matricula[strcspn(matricula, "\n")] = '\0';

                buscaImprimeMatricula(arvoreVendas->raiz, matricula);

            }
        }break;
        case 4: {
            float valor=0;
            printf("Qual o Valor?");
            scanf("%d", &valor);
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
