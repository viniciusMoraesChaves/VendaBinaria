#ifndef ABB_H
#define ABB_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

typedef struct data{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct venda{
    int id;
    char cliente[50];
    char vendedor[50];
    char matricula[5];
    Data transacao;
    float valor;
} Venda;

typedef struct noArv{
    Venda info;
    struct noArv *esq, *dir;
} NoArv;

typedef struct Arvore{
    NoArv *raiz;
} Arv;

void limpaBuffer();
int generateId(Arv *arvVendas);
NoArv* buscaArvId(NoArv *no, int n);
NoArv* buscaArvMatricula(NoArv *no, char m[5]);
void buscaImprimeMatricula(NoArv *no, char m[5]);
void buscaImprimeNome(NoArv *no, char m[50]);
Venda criaVenda(Arv *arvVendas);
void vendasAcimaAbaixoValor(NoArv *no, float valor, int op);
int idIsValid(Arv *arvVendas, int id);
int totalVendas(NoArv *no);
float totalFaturamento(NoArv *no);
Arv* criaArvore();
int ArvVazia(Arv *base);
NoArv* auxInsere(NoArv *no, Venda v);
void inserirArvore(Arv *Arvore, Venda v);
NoArv* removeAux(NoArv* noArv, Venda v);
Arv* removeNo(Arv* arvore, Venda v);
void imprimirVenda(Venda v);
void imprimirArvore(Arv *arvore, int ordem);
void imprimirDecrescente(NoArv* Pai);
void imprimirCrescente(NoArv* Pai);

NoArv* buscaArvId(NoArv *no, int n){
    if(no == NULL){
        return NULL;
    }
    if(no->info.id == n){
        return no;
    }
    if(no->info.id > n){
        return buscaArvId(no->esq, n);
    }
    return buscaArvId(no->dir, n);
}

NoArv* buscaArvMatricula(NoArv *no, char m[5]){
    if(no == NULL) return NULL;

    if(strcmp(no->info.matricula, m) == 0){
        return no;
    }

    NoArv* res = buscaArvMatricula(no->esq, m);
    if(res != NULL) return res;

    return buscaArvMatricula(no->dir, m);
}

void buscaImprimeMatricula(NoArv *no, char m[5]){
    if(no != NULL){
        if(strcmp(no->info.matricula, m) == 0){
            printf("\n\t%-3d | %-20s | %02d/%02d/%04d | %-12s | %-5.2f\n",
                no->info.id, no->info.cliente,
                no->info.transacao.dia, no->info.transacao.mes, no->info.transacao.ano,
                no->info.matricula, no->info.valor);
        }
        buscaImprimeMatricula(no->esq, m);
        buscaImprimeMatricula(no->dir, m);
    }
}

void buscaImprimeNome(NoArv *no, char m[50]){
    if(no != NULL){
        if(strcmp(no->info.vendedor, m) == 0){
            printf("\n\t%-3d | %-20s | %02d/%02d/%04d | %-12s | %-5.2f\n",
                no->info.id, no->info.cliente,
                no->info.transacao.dia, no->info.transacao.mes, no->info.transacao.ano,
                no->info.matricula, no->info.valor);
        }
        buscaImprimeNome(no->esq, m);
        buscaImprimeNome(no->dir, m);
    }
}

void limpaBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int generateId(Arv *arvVendas){
    int id;
    do{
        id = 100 + rand() % 900;
    } while(!idIsValid(arvVendas, id));
    return id;
}

int idIsValid(Arv *arvVendas, int id){
    NoArv *v = buscaArvId(arvVendas->raiz, id);
    if(v == NULL){
        return 1;
    }
    return 0;
}

Venda criaVenda(Arv *arvVendas) {
    Venda new_venda;
    new_venda.id = generateId(arvVendas);

    do {
        printf("\nDigite o nome do cliente: ");
        fgets(new_venda.cliente, sizeof(new_venda.cliente), stdin);
        new_venda.cliente[strcspn(new_venda.cliente, "\n")] = '\0';
        if (strlen(new_venda.cliente) == 0) {
            printf("O nome nao pode ser vazio. Tente novamente.\n");
        }
    } while (strlen(new_venda.cliente) == 0);

    int itens_lidos;
    char temMatricula;

    do {
        printf("\nO vendedor ja tem matricula? (S/n): ");
        itens_lidos = scanf("%c", &temMatricula);
        limpaBuffer();
        temMatricula = toupper(temMatricula);
        if (itens_lidos != 1 || (temMatricula != 'S' && temMatricula != 'N')) {
            printf("Opcao invalida. Por favor, digite 'S' para sim ou 'N' para nao.\n");
        }
    } while (itens_lidos != 1 || (temMatricula != 'S' && temMatricula != 'N'));

    if(temMatricula == 'N'){
        do {
            printf("\nDigite o nome do Vendedor: ");
            fgets(new_venda.vendedor, sizeof(new_venda.vendedor), stdin);
            new_venda.vendedor[strcspn(new_venda.vendedor, "\n")] = '\0';
            if (strlen(new_venda.vendedor) == 0) {
                printf("O nome nao pode ser vazio. Tente novamente.\n");
            }
        } while (strlen(new_venda.vendedor) == 0);
        sprintf(new_venda.matricula, "V%03d", generateId(arvVendas));
    } else {
        char matricula[5];
        NoArv *v;
        int found = 0;
        do {
            printf("\nDigite a Matricula do Vendedor: ");
            fgets(matricula, sizeof(matricula), stdin);
            matricula[strcspn(matricula, "\n")] = '\0';

            if (strlen(matricula) == 0) {
                printf("A matricula nao pode ser vazia.\n");
                continue;
            }

            v = buscaArvMatricula(arvVendas->raiz, matricula);
            if(v == NULL){
                printf("A matricula nao existe.\n");
            } else {
                strcpy(new_venda.vendedor, v->info.vendedor);
                strcpy(new_venda.matricula, matricula);
                found = 1;
            }
        } while (!found);
    }

    int flag_data;
    do {
        flag_data = 0;
        printf("\nDigite a data da transacao (DD/MM/AAAA): ");
        itens_lidos = scanf("%d/%d/%d", &new_venda.transacao.dia, &new_venda.transacao.mes, &new_venda.transacao.ano);
        limpaBuffer();
        if(new_venda.transacao.dia > 31 || new_venda.transacao.dia < 1 ||
           new_venda.transacao.mes > 12 || new_venda.transacao.mes < 1 ||
           new_venda.transacao.ano < 1950 || new_venda.transacao.ano > 2025){
            printf("Data invalida.\n");
            flag_data = 1;
        }
        if(itens_lidos != 3) {
            printf("Formato invalido.\n");
            flag_data = 1;
        }
    } while (flag_data);

    do {
        printf("\nDigite o valor da transacao: R$");
        scanf("%f", &new_venda.valor);
        limpaBuffer();
        if(new_venda.valor <= 0){
            printf("\nValor invalido: deve ser positivo.\n");
        }
    } while (new_venda.valor <= 0);

    return new_venda;
}

void vendasAcimaAbaixoValor(NoArv *no, float valor, int op){
    if(no != NULL){
        if(op){
            if(no->info.valor < valor){
                imprimirVenda(no->info);
            }
        } else {
            if(no->info.valor > valor){
                imprimirVenda(no->info);
            }
        }
        vendasAcimaAbaixoValor(no->dir, valor, op);
        vendasAcimaAbaixoValor(no->esq, valor, op);
    }
}

int totalVendas(NoArv *no){
    if(no == NULL) return 0;
    return 1 + totalVendas(no->esq) + totalVendas(no->dir);
}

float totalFaturamento(NoArv *no){
    if(no == NULL) return 0.0;
    return no->info.valor + totalFaturamento(no->esq) + totalFaturamento(no->dir);
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
                else{
                    free(novo);
                    flag=1;
                }
            }
        }
    }
    return no;
}

void inserirArvore(Arv *arvore, Venda v){
    arvore->raiz=auxInsere(arvore->raiz,v);
}

NoArv* removeAux(NoArv* noArv, Venda v){
    if(noArv == NULL){
        return NULL;
    }
    if(noArv->info.id > v.id){
        noArv->esq = removeAux(noArv->esq, v);
    }
    else{
        if(noArv->info.id < v.id){
            noArv->dir = removeAux(noArv->dir, v);
        }
        else
        {
        if((noArv->esq == NULL) && (noArv->dir == NULL)){
            free(noArv);
            return NULL;
        }
        else{
            if(noArv->esq == NULL){
                NoArv *aux = noArv;
                noArv = noArv->dir;
                free(aux);
                return noArv;
            }
            else{
                if(noArv->dir ==NULL){
                    NoArv *aux = noArv;
                    noArv = noArv->esq;
                    free(aux);
                    return noArv;
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
    }
    return noArv;
}

Arv* removeNo(Arv* arvore, Venda v){
    if(arvore != NULL) {
        arvore->raiz = removeAux(arvore->raiz, v);
    }
    return arvore;
}

void imprimirVenda(Venda v){
    printf("\n\t%-3d | %-10s | %-10s | %-10s | %02d/%02d/%04d | %-5.2f\n",
           v.id, v.vendedor, v.matricula, v.cliente,
           v.transacao.dia, v.transacao.mes, v.transacao.ano, v.valor);
}

void imprimirDecrescente(NoArv* Pai){
    if(Pai != NULL){
        imprimirDecrescente(Pai->dir);
        imprimirVenda(Pai->info);
        imprimirDecrescente(Pai->esq);
    }
}

void imprimirCrescente(NoArv* Pai){
    if(Pai == NULL){
        imprimirCrescente(Pai->esq);
        imprimirVenda(Pai->info);
        imprimirCrescente(Pai->dir);
    }
}

void imprimirArvore(Arv *arvore, int ordem){
    printf("\n\t%-3s | %-10s | %-10s | %-10s | %-10s | %-5s\n",
           "ID", "Vendedor", "Matricula", "Cliente", "Data", "Valor");
    if(arvore->raiz != NULL) {
        if(ordem){
            imprimirCrescente(arvore->raiz);
        } else {
            imprimirDecrescente(arvore->raiz);
        }
    }
}

#endif
