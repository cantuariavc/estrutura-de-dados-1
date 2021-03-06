//
//  lista.c
//  Projeto 3
//
//  Created by Vinícius Cantuária on 10/05/2018.
//  Copyright © 2018 Vinícius Cantuária. All rights reserved.
//

#include "lista.h"

No *transfereContatosParaLista(FILE *contatos) {
    No *lista = NULL;
    char nomeCompleto[TAMANHONOMECOMPLETO];
    char telefoneCelular[TAMANHOTELEFONECELULAR];
    char endereco[TAMANHOENDERECO];
    int cep = 0;
    char dataDeNascimento[TAMANHODATADENASCIMENTO];
    int cifrao = 0;
    
    while (1) {
        fgets(nomeCompleto, TAMANHONOMECOMPLETO, contatos);
        fscanf(contatos, "%s", telefoneCelular);
        fgetc(contatos);
        fgets(endereco, TAMANHOENDERECO, contatos);
        fscanf(contatos, "%d", &cep);
        fgetc(contatos);
        fscanf(contatos, "%s", dataDeNascimento);
        fgetc(contatos);
        cifrao = fgetc(contatos);
        
        if (fgetc(contatos) == EOF) {
            break;
        }
        
        lista = insereNo(lista, nomeCompleto, telefoneCelular, endereco, cep, dataDeNascimento);
        lista = ordenaLista(lista);
    }
    
    return lista;
}


No *insereNovoRegistro(No *lista) {
    char nomeCompleto[TAMANHONOMECOMPLETO];
    char telefoneCelular[TAMANHOTELEFONECELULAR];
    char endereco[TAMANHOENDERECO];
    char cep[TAMANHOCEP];
    char dataDeNascimento[TAMANHODATADENASCIMENTO];
    
    do {
        printf("Nome completo: ");
        fgets(nomeCompleto, TAMANHONOMECOMPLETO, stdin);
    } while (!validaCampoVazio(nomeCompleto));
    
    
    do {
        printf("Telefone celular (55555-5555): ");
        scanf("%s", telefoneCelular);
        getchar();
    } while (!validaCelular(telefoneCelular));
    
    do {
        printf("Endereço: ");
        fgets(endereco, TAMANHOENDERECO, stdin);
    } while (!validaCampoVazio(endereco));
        
    do {
        printf("CEP (somente os números): ");
        scanf("%s", cep);
        getchar();
    } while (!validaCEP(cep));
    
    do {
        printf("Data de nascimento (dd/mm/aaaa): ");
        scanf("%s", dataDeNascimento);
        getchar();
    } while (!validaDataDeNascimento(dataDeNascimento));
    
    printf("\n");
    lista = insereNo(lista, nomeCompleto, telefoneCelular, endereco, atoi(cep), dataDeNascimento);
    
    return lista;
}


No *insereNo(No *lista, char nomeCompleto[], char telefoneCelular[], char endereco[], int cep, char dataDeNascimento[]) {
    No *novoNo = criaNo(nomeCompleto, telefoneCelular, endereco, cep, dataDeNascimento, NULL, NULL);
    
    if (lista != NULL) {
        No *aux;
        for (aux = lista; aux->proximo != NULL; aux = aux->proximo);
        
        aux->proximo = novoNo;
        novoNo->anterior = aux;
        
        lista = ordenaLista(lista);
    } else {
        lista = novoNo;
    }
    
    return lista;
}


void imprimeLista(No *lista) {
    printf("Lista");
    printf("\n");
    if (lista != NULL) {
        for (No *aux = lista; aux != NULL; aux = aux->proximo) {
            printf("Nome completo: %s", aux->nomeCompleto);
            printf("\n");
            printf("Telefone celular: %s", aux->telefoneCelular);
            printf("\n");
            printf("Endereço: %s", aux->endereco);
            printf("\n");
            printf("CEP: %d", aux->cep);
            printf("\n");
            printf("Data de nascimento: %s", aux->dataDeNascimento);
            printf("\n\n");
        }
    } else {
        printf("Vazia!");
        printf("\n\n");
    }
}

void imprimeNoPorNome(No *lista) {
    int haNome = 0;

    if (lista != NULL) {
        char nomeCompleto[101];
        
        printf("Nome para pesquisa: ");
        fgets(nomeCompleto, TAMANHONOMECOMPLETO, stdin);
        nomeCompleto[(strlen(nomeCompleto) - 1)] = '\0';
        printf("\n");
        
        for (No *aux = lista; aux != NULL; aux = aux->proximo) {
            if (verificaNome(aux->nomeCompleto, nomeCompleto)) {
                printf("Nome completo: %s", aux->nomeCompleto);
                printf("\n");
                printf("Telefone celular: %s", aux->telefoneCelular);
                printf("\n");
                printf("Endereço: %s", aux->endereco);
                printf("\n");
                printf("CEP: %d", aux->cep);
                printf("\n");
                printf("Data de nascimento: %s", aux->dataDeNascimento);
                printf("\n\n");
                
                haNome++;
            }
        }
        
        if (haNome == 0) {
            printf("Nada encontrado!");
            printf("\n\n");
        }
    } else {
        printf("Lista Vazia!");
        printf("\n\n");
    }
}


No *excluiNosPorNome(No *lista) {
    int haNome = 0;
    
    if (lista != NULL) {
        char nomeCompleto[101];
        
        printf("Nome para exclusão: ");
        fgets(nomeCompleto, TAMANHONOMECOMPLETO, stdin);
        nomeCompleto[(strlen(nomeCompleto) - 1)] = '\0';
        printf("\n");
        
        for (No *aux = lista; aux != NULL; aux = aux->proximo) {
            if (verificaNome(aux->nomeCompleto, nomeCompleto)) {
                if (aux->proximo != NULL) {
                    aux->proximo->anterior = aux->anterior;
                }
                
                if (aux->anterior != NULL) {
                    aux->anterior->proximo = aux->proximo;
                    No *aux2 = aux->anterior;
                    free(aux);
                    aux = aux2;
                } else {
                    lista = aux->proximo;
                    free(aux);
                    aux = lista;
                }
                
                if (lista == NULL) {
                    haNome++;
                    break;
                }
                
                haNome++;
            }
        }
        
        if (haNome == 1) {
            printf("Exclusão ocorrída com sucesso!");
        } else if (haNome > 1) {
            printf("Exclusões ocorrídas com sucesso!");
        } else {
            printf("Nada encontrado!");
        }
    } else {
        printf("Lista Vazia!");
    }
    printf("\n\n");
    
    return lista;
}


No *ordenaLista(No *lista) {
    int tamanhoDaLista = 0;
    No *aux = lista;
    
    while (aux != NULL) {
        tamanhoDaLista++;
        aux = aux->proximo;
    }
    
    No *ptr1 = lista;
    No *ptr2 = lista;
    No *temp = NULL;
    int i = 0;
    int j = 0;

    for (i = 0; i < tamanhoDaLista; i++) {
        temp = (No *) calloc(1, sizeof(No));
        
        strcpy(temp->nomeCompleto, ptr1->nomeCompleto);
        strcpy(temp->telefoneCelular, ptr1->telefoneCelular);
        strcpy(temp->endereco, ptr1->endereco);
        temp->cep = ptr1->cep;
        strcpy(temp->dataDeNascimento, ptr1->dataDeNascimento);
        
        for (j = 0; j < i; j++)
            ptr2 = ptr2->proximo;
        for (j = i; j > 0 && strcmp(ptr2->anterior->nomeCompleto, temp->nomeCompleto) > 0; j--) {
            strcpy(ptr2->nomeCompleto, ptr2->anterior->nomeCompleto);
            strcpy(ptr2->telefoneCelular, ptr2->anterior->telefoneCelular);
            strcpy(ptr2->endereco, ptr2->anterior->endereco);
            ptr2->cep = ptr2->anterior->cep;
            strcpy(ptr2->dataDeNascimento, ptr2->anterior->dataDeNascimento);
            
            ptr2 = ptr2->anterior;
        }
        memcpy(ptr2->nomeCompleto, temp->nomeCompleto, sizeof(temp->nomeCompleto));
        memcpy(ptr2->telefoneCelular, temp->telefoneCelular, sizeof(temp->telefoneCelular));
        memcpy(ptr2->endereco, temp->endereco, sizeof(temp->endereco));
        ptr2->cep = temp->cep;
        memcpy(ptr2->dataDeNascimento, temp->dataDeNascimento, sizeof(temp->dataDeNascimento));
        
        ptr2 = lista;
        ptr1 = ptr1->proximo;
        
        free(temp);
    }

    return lista;
}
