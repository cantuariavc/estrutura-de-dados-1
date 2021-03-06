//
//  arvore.c
//  Projeto 5
//
//  Created by Vinícius Cantuária on 12/06/2018.
//  Copyright © 2018 Vinícius Cantuária. All rights reserved.
//

#include "arvore.h"

#define espaco 5
int nivel = 0;

No *loadTreeFromFile(char nomeDoArquivo[]) {
    FILE *arquivo = abreArquivo(nomeDoArquivo);
    if (!arquivo) {
        return NULL;
    }

    No *raiz = NULL;
    int valor = 0;

    while (fscanf(arquivo, "%d", &valor) != EOF) {
        insereNo(&raiz, valor);
    }

    return raiz;
}
// int rec[1000006];
// void showTree(No* raiz,int profundidade) {
//     int i;
//
//     if (raiz==NULL) {
//         return;
//     }
//
//     printf("\t");
//     for(i=0; i<profundidade; i++) {
//         if (i==profundidade-1)
//             printf("%s\u2014\u2014\u2014",rec[profundidade-1]?"\u0371":"\u221F");
//         else
//             printf("%s   ",rec[i]?"\u23B8":"  ");
//     }
//
//     printf("%d\n",raiz->valor);
//     rec[profundidade]=1;
//     showTree(raiz->esquerda,profundidade+1);
//     rec[profundidade]=0;
//     showTree(raiz->direita,profundidade+1);
// }





void showTreeHoriz(No *raiz, int profundidade, char *caminho, int direita)
{
    if (raiz== NULL)
        return;

    profundidade++;

    showTreeHoriz(raiz->direita, profundidade, caminho, 1);

    caminho[profundidade-2] = 0;

    if(direita)
        caminho[profundidade-2] = 1;

    if(raiz->esquerda)
        caminho[profundidade-1] = 1;

    printf("\n");

    for(int i=0; i<profundidade-1; i++)
    {
      if(i == profundidade-2)
          printf("+");
      else if(caminho[i])
          printf("|");
      else
          printf(" ");

      for(int j=1; j<espaco; j++)
      if(i < profundidade-2)
          printf(" ");
      else
          printf("-");
    }

    printf("%d\n", raiz->valor);

    for(int i=0; i<profundidade; i++)
    {
      if(caminho[i])
          printf("|");
      else
          printf(" ");

      for(int j=1; j<espaco; j++)
          printf(" ");
    }

    showTreeHoriz(raiz->esquerda, profundidade, caminho, 0);
}

void showTree(No *raiz)
{
    char caminho[255] = {};

    showTreeHoriz(raiz, 0, caminho, 0);
}









int isFull(No *raiz) {
    if (!raiz) {
        return 1;
    } else if (!raiz->esquerda && !raiz->direita) {
        return 1;
    } else if (raiz->esquerda && raiz->direita) {
        return (isFull(raiz->esquerda) && isFull(raiz->direita));
    }

    return 0;
}

int searchValue(No *raiz, int valor) {
    int encontrado = 0;

    if (raiz) {
        if (raiz->valor == valor) {
            printf("Nível do nó: %d\n", nivel);
            nivel = 0;

            return 1;
        } else if (valor < raiz->valor && raiz->esquerda != NULL) {
            nivel++;
            encontrado = searchValue(raiz->esquerda, valor);
        } else if (valor > raiz->valor && raiz->direita != NULL) {
            nivel++;
            encontrado = searchValue(raiz->direita, valor);
        } else {
            printf("Valor não encontrado!\n\n");
        }

        if (encontrado) {
            printf("Valor do pai: %d\n", raiz->valor);
            if (raiz->esquerda != NULL && valor == raiz->esquerda->valor && raiz->direita != NULL) {
                printf("Valor do irmão a direita: %d\n", raiz->direita->valor);
            } else if (raiz->direita != NULL && valor == raiz->direita->valor && raiz->esquerda != NULL) {
                printf("Valor do irmão a esquerda: %d\n", raiz->esquerda->valor);
            } else {
                printf("Não possue irmão.\n");
            }

            return 0;
        }
    }

    return encontrado;
}

int getHeight(No *raiz) {
    if (!raiz) {
        return -1;
    } else {
        int esquerda = getHeight(raiz->esquerda);
        int direita = getHeight(raiz->direita);

        if (esquerda > direita) {
            return esquerda + 1;
        } else {
            return direita + 1;
        }
    }
}

void removeValue(No **raiz, int valor) {
    if (!(*raiz)) {
        printf("Este valor não existe na árvore!");

        return;
    }

    if (valor < (*raiz)->valor) {
        removeValue(&(*raiz)->esquerda, valor);
    } else {
        if (valor > (*raiz)->valor) {
            removeValue(&(*raiz)->direita, valor);
        } else {
            No *pAux = *raiz;
            if (!(*raiz)->esquerda && !(*raiz)->direita) {
                free(pAux);
                (*raiz) = NULL;
            } else {
                if ((*raiz)->esquerda == NULL) {
                    (*raiz) = (*raiz)->direita;
                    pAux->direita = NULL;
                    free(pAux);
                    pAux = NULL;
                } else {
                    if (!(*raiz)->direita) {
                        (*raiz) = (*raiz)->esquerda;
                        pAux->esquerda = NULL;
                        free(pAux);
                        pAux = NULL;
                    } else {
                        pAux = MaiorDireita(&(*raiz)->esquerda);
                        pAux->esquerda = (*raiz)->esquerda;
                        pAux->direita = (*raiz)->direita;
                        (*raiz)->esquerda = (*raiz)->direita = NULL;
                        free((*raiz));
                        *raiz = pAux;
                        pAux = NULL;
                    }
                }
            }
        }
    }
}

No *MaiorDireita(No **no) {
    if ((*no)->direita) {
        return MaiorDireita(&(*no)->direita);
    } else {
        No *aux = *no;
        if ((*no)->esquerda) {
            *no = (*no)->esquerda;
        } else {
            *no = NULL;
        }

        return aux;
    }
}

No *MenorEsquerda(No **no) {
    if ((*no)->esquerda) {
        return MenorEsquerda(&(*no)->esquerda);
    } else {
        No *aux = *no;
        if ((*no)->direita) {
            *no = (*no)->direita;
        } else {
            *no = NULL;
        }

        return aux;
    }
}

void printInOrder(No *raiz) {
    if (raiz) {
        printInOrder(raiz->esquerda);
        printf("%d\t", raiz->valor);
        printInOrder(raiz->direita);
    }
}

void printPreOrder(No *raiz) {
    if (raiz) {
        printf("%d\t", raiz->valor);
        printPreOrder(raiz->esquerda);
        printPreOrder(raiz->direita);
    }
}

void printPostOrder(No *raiz) {
    if (raiz) {
        printPostOrder(raiz->esquerda);
        printPostOrder(raiz->direita);
        printf("%d\t", raiz->valor);
    }
}

void balanceTree(No *raiz) {

    No *novaRota = NULL;


    switch(checkIfTreeIsBalanced(raiz)) {
        case 0:
            printf("Balanceando Arvore");
            novaRota = balanceNode(raiz);
            if(novaRota != raiz) {
                raiz = novaRota;
            }
            break;
        case 1:
            printf("Arvore já esta Balanceada");
            break;
        case 2:
            printf("Arvore Vazia");
            break;
    }
}

int checkIfTreeIsBalanced(No *raiz) {
    int value;

    if (raiz == NULL) {
        return 2;
    }
    value = abs(getHeight(raiz->esquerda) - getHeight(raiz->direita)) <= 1;
    if(checkIfTreeIsBalanced(raiz->esquerda) == 0 && checkIfTreeIsBalanced(raiz->direita) == 0) {
        value = 0;
    }

    return value;
}

int calculateBalanceFactor(No *raiz) {
    int balanceFactor = 0;

    if(raiz->esquerda) {
        balanceFactor += getHeight(raiz->esquerda);
    }
    if(raiz->direita) {
        balanceFactor -= getHeight(raiz->direita);
    }

    return balanceFactor;
}

No *balanceNode(No *raiz) {
    No *novaRota = NULL;

    if(raiz->esquerda) {
        raiz->esquerda  = balanceNode(raiz->esquerda);
    }

    if(raiz->direita) {
        raiz->direita = balanceNode(raiz->direita);
    }

    int balanceFactor = calculateBalanceFactor(raiz);

    if(balanceFactor >= 2) {
        if(calculateBalanceFactor(raiz->esquerda) <= -1) {
            novaRota = rotateLeftRight(raiz);
        } else {
            novaRota = rotateLeftLeft(raiz);
        }
    } else if(balanceFactor <= -2) {
        if(calculateBalanceFactor(raiz->direita) >= 1) {
            novaRota = rotateRightLeft(raiz);
        } else {
            novaRota = rotateRightRight(raiz);
        }
    } else {
        novaRota = raiz;
    }

    return novaRota;
}

No *rotateLeftLeft(No *raiz) {
    No *aux1 = raiz;
    No *aux2 = aux1->esquerda;

    aux1->esquerda = aux2->direita;
    aux2->direita = aux1;

    return aux2;
}

No *rotateLeftRight(No *raiz) {
    No *aux1 = raiz;
    No *aux2 = aux1->esquerda;
    No *aux3 = aux2->direita;

    aux1->esquerda = aux3->direita;
    aux2->direita = aux3->esquerda;
    aux3->esquerda = aux2;
    aux3->direita = aux1;

    return aux3;
}

No *rotateRightLeft(No *raiz) {
    No *aux1 = raiz;
    No *aux2 = aux1->direita;
    No *aux3 = aux2->esquerda;

    aux1->direita = aux3->esquerda;
    aux2->esquerda = aux3->direita;
    aux3->direita = aux2;
    aux3->esquerda = aux1;

    return aux3;
}

No *rotateRightRight(No *raiz) {
    No *aux1 = raiz;
    No *aux2 = aux1->direita;

    aux1->direita = aux2->esquerda;
    aux2->esquerda = aux1;

    return aux2;
}
