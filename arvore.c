#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *esq;
    struct no *dir;
}Arv;

int inserir_num(){
    int num;
    printf("Digite o numero que deseja colocar na arvore: \n");
    scanf("%d", &num);
    return num;
}

Arv* inserir(Arv *raiz, int num){
    if (raiz == NULL){
        Arv *aux = malloc(sizeof(Arv));
        aux->valor = num;
        aux->dir = NULL;
        aux->esq = NULL;
        return aux;
    }   
    else{
        if (num < raiz->valor)
            raiz->esq = inserir(raiz->esq, num);
        
        else
            raiz->dir = inserir(raiz->dir, num);
        return raiz;
    }
}

Arv* buscar(Arv *raiz, int num){
    if (raiz){
        if (num == raiz->valor)
            return raiz;
        else if (num < raiz->valor)
            return buscar(raiz->esq, num);
        else    
            return buscar(raiz->dir, num); 
    }
    return NULL;
}

Arv* remover_folha(Arv *raiz, int num){
    if (raiz == NULL){
        printf("Valor nao encontrado.\n");
        return NULL;
    }
    else{
        if (raiz->valor == num){
            if (raiz->esq == NULL && raiz->dir == NULL){
                free(raiz);
                return NULL;
            }
            else{
                if (raiz->esq != NULL && raiz->dir != NULL){
                    Arv *aux = raiz->esq;
                    while (aux->dir != NULL)
                        aux = raiz->dir;
                    raiz->valor = aux->valor;
                    aux->valor = num;
                    raiz->esq = remover_folha(raiz->esq, num);
                    return raiz;
                }
                else{
                    Arv *aux;
                    if (raiz->esq != NULL)
                        aux = raiz->esq;
                    else
                        aux = raiz->dir;
                    free(raiz);
                    return aux;
                }
            }
        }
        else{
            if (num < raiz->valor)
                raiz->esq = remover_folha(raiz->esq, num);
            
            else
                raiz->dir = remover_folha(raiz->dir, num);
            
            return raiz;
        }
    }
}

void imprimir(Arv *raiz){
    if (raiz){
        printf("%d ", raiz->valor);
        imprimir(raiz->esq);
        imprimir(raiz->dir);
    }
}

void imprimir2(Arv *raiz){
    if (raiz){
        imprimir2(raiz->esq);
        printf("%d ", raiz->valor);
        imprimir2(raiz->dir);
    }
}

int main(){
    Arv *remover, *busca, *raiz = NULL;
    int opcao;
    int x;
    int numero;
    while (1){
        printf("1 inserir - 2 imprimir raiz primeiro - 3 imprimir ordenado - 4 busca - 5 remover - 0 sair\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            x = inserir_num();
            raiz = inserir(raiz, x);
            break;
        case 2:
            imprimir(raiz);
            printf("\n");
            break;
        case 3:
            imprimir2(raiz);
            printf("\n");
            break;
        case 4: 
            printf("Digite o numero que voce deseja buscar na arvore: \n");
            scanf("%d", &numero);
            busca = buscar(raiz, numero);
            if (busca)
                printf("Numero encontrado: %d.\n", busca->valor);
            else
                printf("Numero nao existe. \n");
            break;
        case 5:
            printf("Digite a folha que voce deseja remover na arvore: \n");
            scanf("%d", &numero);
            remover = remover_folha(raiz, numero);
            if (remover)
                printf("Folha removida.\n");
            break;
        case 0:
            return 0;
        }
    }

    return 0;
}