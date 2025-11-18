#ifndef ABB_H
#define ABB_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct data{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct venda{
    int id;
    char cliente[50];
    char vendedor[50];
    char matricula[5];
    Data transacao;
    float valor;
}Venda;

typedef struct noArv{
    Venda info;
    struct noArv *esq, *dir;
}NoArv;

typedef struct Arvore{
    NoArv *raiz;
}Arv;

int generateRandomInt(){

}

NoArv* buscaArvId(NoArv *no, int n){
    if(no != NULL){
        if(no->info.id > n){
            aux_buscaArv(no->esq,n);
        }else if(no->info.id < n){
            aux_buscaArv(no->dir,n);
        }else{
            return no;
        } 
    }
    return NULL;
}

NoArv* buscaArvMatricula(NoArv *no, char m[5]){
    if(strcmp(no->info.matricula,m) == 0){
        return no;
    }
    if(no->dir !=NULL){
        aux_buscaArvMatricula(no->dir,m);
    }
    if(no->esq != NULL){
        aux_buscaArvMatricula(no->esq,m);
    }
}

void buscaImprimeMatricula(NoArv *no, char m[5]){
    if(strcmp(no->info.matricula,m) == 0){
        printf("\n\t%-3d | %*s | %*s |     %02d/%02d/%04d| %12s| %-5.2f\n",no->info.id,no->info.cliente,no->info.transacao.dia,no->info.transacao.mes,no->info.transacao.ano,no->info.valor);
    }
    if(no->dir !=NULL){
        aux_buscaArvMatricula(no->dir,m);
    }
    if(no->esq != NULL){
        aux_buscaArvMatricula(no->esq,m);
    }
}

void buscaImprimeNome(NoArv *no, char m[50]){
    if(strcmp(no->info.vendedor,m) == 0){
        printf("\n\t%-3d | %*s | %*s |     %02d/%02d/%04d| %12s| %-5.2f\n",no->info.id,no->info.cliente,no->info.transacao.dia,no->info.transacao.mes,no->info.transacao.ano,no->info.valor);
    }
    if(no->dir !=NULL){
        aux_buscaArvNome(no->dir,m);
    }
    if(no->esq != NULL){
        aux_buscaArvNome(no->esq,m);
    }
}

void limpaBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int generateId(arvVendas){
    int id;
    do{
        id = 100 + rand() % 900;
    } while(!idIsValid(arvVendas,id));
    return id;
}

int idIsValid(Arv *arvVendas, int id){
    NoArv *v = buscaArv(arvVendas,id);
    if(v == NULL){
        return 0;
    }
    return 1;
}

Venda criaVenda(Arv *arvVendas) {
    Venda new_venda;

    do {
        printf("\nDigite o nome do cliente: ");
        fgets(new_venda.cliente, sizeof(new_venda.cliente), stdin);
        new_venda.cliente[strcspn(new_venda.cliente, "\n")] = '\0';
        if (strlen(new_venda.cliente) == 0) {
            printf("O nome não pode ser vazio. Tente novamente.\n");
        }
    } while (strlen(new_venda.cliente) == 0);

    int itens_lidos;
    char temMatricula;

    do {
        printf("\nO vendedor já tem matricula? (S/n)");
        itens_lidos = scanf(" %c", &temMatricula);
        limpaBuffer();

        temMatricula = toupper(temMatricula);

        if (itens_lidos != 1 || (temMatricula != 'S' && temMatricula != 'N')) {
            printf("Opção inválida. Por favor, digite 'S' para sim ou 'N' para não.\n");
        }
    } while (itens_lidos != 1 || (temMatricula != 'S' && temMatricula != 'N'));

    if(temMatricula == 'N'){
        do {
            printf("\nDigite o nome do Vendedor: ");
            fgets(new_venda.vendedor, sizeof(new_venda.vendedor), stdin);
            new_venda.vendedor[strcspn(new_venda.vendedor, "\n")] = '\0';
            if (strlen(new_venda.vendedor) == 0) {
                printf("O nome não pode ser vazio. Tente novamente.\n");
            }

        } while (strlen(new_venda.vendedor) == 0);
        new_venda.id = generateId(arvVendas);
    }else{
        char matricula[5];
        int isValidFlag = 0;
        NoArv *v;
        do {
            printf("\nDigite a Matricula do Vendedor: ");
            fgets(matricula, sizeof(matricula), stdin);
            matricula[strcspn(matricula, "\n")] = '\0';
            v = buscaArvMatricula(arvVendas,matricula);
            if(v == NULL){
                printf("A matricula não existe.\n");
            }
            if (strlen(matricula) == 0) {
                printf("A matricula não pode ser vazio. Tente novamente.\n");
            }

        } while ((strlen(new_venda.vendedor) == 0) && (v == NULL));

    }

    int flag_data;
    do {
        flag_data = 0;
        printf("\nDigite a data da transacao do pet (DD/MM/AAAA): ");
        itens_lidos = scanf("%d/%d/%d", &new_venda.transacao.dia, &new_venda.transacao.mes, &new_venda.transacao.ano);
        limpaBuffer();
        if(new_venda.transacao.dia > 31 || new_venda.transacao.dia < 1 || new_venda.transacao.mes > 12 || new_venda.transacao.mes < 1|| new_venda.transacao.ano < 1950 || new_venda.transacao.ano > 2025){
            printf("Formato de data inválido. Tente novamente.\n");
            flag_data = 1;
        }
        if(itens_lidos != 3) {
            printf("Formato de data inválido. Tente novamente.\n");
        }
    } while (itens_lidos != 3 || flag_data);

    int flag_data;
    do {
        flag_data = 0;
        printf("\nDigite o valor da transacao: R$");
        scanf("%f",&new_venda.valor);
        limpaBuffer();
        if(new_venda.valor < 0){
            printf("\nValor invalido: deve ser positivo");
        }

    } while (new_venda.valor <= 0);


    return new_venda;
}

Arv* criaArvore(){
    Arv *aux;
    aux=(Arv*)malloc(sizeof(Arv));
    aux->raiz = NULL;
    return aux;
}

int ArvVazia(Arv *base){
    if(base->raiz==NULL){
        return 1;
    }
    return 0;
}

NoArv * auxInsere(NoArv *no, Venda v){
    int flag;
    NoArv *Pai;
    NoArv *novo = (NoArv*)malloc(sizeof(NoArv));
    novo->info = v;
    novo->esq =NULL;
    novo->dir=NULL;
    if(no==NULL){

        return novo;
    }
    else{

        Pai = no;
        flag=0;
        while (flag==0){
            if(Pai->info.id<v.id){
                if(Pai->dir==NULL){
                    Pai->dir = novo;
                    flag=1;
                }
                else{
                    Pai=Pai->dir;
                }
            }
            else{
                if(Pai->info.id>v.id){
                    if(Pai->esq==NULL){
                        Pai->esq=novo;
                        flag=1;
                    }
                    else{
                        Pai=Pai->esq;
                    }
                }
            }
        }
    }
    return no;
}

void inserirArvore(Arv *Arvore, Venda v){
    Arvore->raiz=auxInsere(Arvore->raiz,v);
}

NoArv* removeAux(NoArv* noArv, Venda v){
    if(noArv == NULL){
        return NULL;
    }
    if(noArv->info.id > v.id){
        removeAux(noArv->esq, v);
    }
    else{
        if(noArv->info.id < v.id){
            removeAux(noArv->dir, v);
        }
        if((noArv->esq == NULL) && (noArv->dir == NULL)){
            free(noArv);
        }
        else{
            if(noArv->esq == NULL){
                NoArv *aux = noArv;
                noArv = noArv->dir;
                free(aux);
            }
            else{
                if(noArv->dir ==NULL){
                    NoArv *aux = noArv;
                    noArv = noArv->esq;
                    free(aux);
                }
                else{
                    NoArv *aux = noArv->esq;
                    while(aux->dir != NULL){
                        aux = aux->dir;
                    }
                    noArv->info = aux->info;
                    aux->info = v;
                    noArv->esq = removeAux(noArv->esq, v);
                }
            }
        }
    }
    return noArv;
}

Arv * removeNo(Arv* arvore, Venda v){
    NoArv *aux = arvore->raiz;
    if(aux->info.id == v.id && aux->dir == NULL && aux->esq == NULL){
        free(aux);
        free(arvore);
        return NULL;
    }
    else{
        arvore->raiz = removeAux(arvore->raiz, v);
    }
}

void liberarNo(NoArv* no){
    if(no!=NULL){
        liberarNo(no->esq);
        liberarNo(no->dir);
        free(no);
    }
}

void imprimirVenda(Venda v){
    printf("\n\t%-3d | %*s | %*s | %*s |     %02d/%02d/%04d| %12s| %-5.2f\n",v.id,v.vendedor,v.matricula,v.cliente,v.transacao.dia,v.transacao.mes,v.transacao.ano,v.valor);
}

void imprimirDecrescente(NoArv* Pai)
{
    if(Pai->dir!=NULL)
    {
        imprimirDecrescente(Pai->dir);
    }
    imprimirVenda(Pai->info);
    if(Pai->esq!=NULL)
    {
        imprimirDecrescente(Pai->esq);
    }
}

void imprimirCrescente(NoArv* Pai){
    if(Pai->esq!=NULL){
        imprimirCrescente(Pai->esq);
    }
    imprimirVenda(Pai->info);
    if(Pai->dir!=NULL){
        imprimirCrescente(Pai->dir);
    }
}

void imprimirArvore(Arv *arvore, int ordem){
    printf("\n\t%-3d | %*s | %*s | %*s |     %02d/%02d/%04d| %12s| %-5.2f\n","ID","Vendedor","Matricula","Cliente","Data da Transação","Valor");
    if(ordem){
        imprimirCrescente(arvore->raiz);
    }
    else{
        imprimirDecrescente(arvore->raiz);
    }
}

#endif // ABB_H
