#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "abb.h"
#include <string.h>




int main(){
    setlocale(LC_ALL, "pt_BR.utf8");


    setbuf(stdout, NULL);
    Arv *arvoreVendas = criaArvore();
    srand(22);
    while (1)
    {
        int op;
        printf("\nEscolha a Operação desejada:\n[1] Adicionar venda \n[2] Imprimir todas as vendas \n[3] Buscar venda (por nome do vendedro ou matrícula) \n[4] Mostrar vendas acima ou abaixo de um certo valor \n[5] Mostrar o número de vendas e o faturamento \n[6] Remover vendas do sistema \n[7] Sair do Sistema \n\n\t>> Sua escolha:");
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
                printf("Deseja buscar as vendas pelo nome do vendedor(0) ou pela matrícula(1)?");
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
            scanf("%f", &valor);
            int b=-1;
            do{
                printf("Deseja buscar as vendas acima do valor(0) ou abaixo(1)?");
                scanf("%d", &b);
                limpaBuffer();
            }while(b!=0 && b!=1);

            vendasAcimaAbaixoValor(arvoreVendas->raiz, valor, b);
        break;
        }
        case 5: {
            int vendas = totalVendas(arvoreVendas->raiz);
            int faturamento = totalFaturamento(arvoreVendas->raiz);

            printf("Foi registrado um total de %d vendas.\n", vendas);
            printf("O faturamento dessas vendas foi de R$%d.\n", faturamento);

            break;
        }
        case 6: {
            printf("Qual venda você gostaria de remover? (Inserir ID da venda)");
            int ID=0;
            scanf("%d", &ID);

            Venda va;
            NoArv *no;
            no = buscaArvId(arvoreVendas->raiz,ID);

            va = no->info;

            arvoreVendas=removeNo(arvoreVendas, va);

            imprimirArvore(arvoreVendas,0);


            break;

        }
        case 7: {
            system("cls");
            printf("Finalizando o sistema... Obrigado por utilizar!\n");
            return 0;
            break;
        }



        default:
            break;
        }
        printf("\n\n");
        system("pause");
        system("cls");
    }


    return 0;
}
