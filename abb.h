#ifndef ABB_H
#define ABB_H
typedef struct venda; Venda;
typedef struct noArv{
    Venda info;
    struct noArv *esq, *dir;
}NoArv;

typedef struct Arvore{
    NoArv *raiz;
}Arv;

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

NoArv * auxInsere(NoArv *no, int num){
    int flag;
    NoArv *Pai;
    NoArv *novo = (NoArv*)malloc(sizeof(NoArv));
    novo->info = num;
    novo->esq =NULL;
    novo->dir=NULL;
    if(no==NULL){

        return novo;
    }
    else{

        Pai = no;
        flag=0;
        while (flag==0){
            if(Pai->info<num){
                if(Pai->dir==NULL){
                    Pai->dir = novo;
                    flag=1;
                }
                else{
                    Pai=Pai->dir;
                }
            }
            else{
                if(Pai->info>num){
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

void inserirArvore(Arv *Arvore, int num){
    Arvore->raiz=auxInsere(Arvore->raiz,num);
}
NoArv * removeAux(NoArv* noArv, int n){
    if(noArv->info== NULL){
        return NULL;
    }
    if(noArv->info.id > n){
        removeAux(noArv->esq, n);
    }
    else{
        if(noArv->info.id < n){
            removeAux(noArv->dir, n);
        }
        if((noArv->esq == NULL) && (noArv->dir == NULL){
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
                    aux->info = n;
                    noArv->esq = removeAux(noArv->esq, n);
                }
            }
        }
    }
    return noArv;
}

Arv * removeNo(Arv* arvore, int n){
    NoArv *aux = arvore->raiz;
    if(aux->info == n && aux->dir == NULL && aux->esq == NULL){
        free(aux);
        free(arvore);
        return NULL;
    }
    else{
        arvore->raiz = removeAux(arvore->raiz, n);
    }
}
#endif // ABB_H
