//
//  vetorDescritor.c
//  Problema
//
//  Created by Vinícius Cantuária on 27/04/2018.
//  Copyright © 2018 Vinícius Cantuária. All rights reserved.
//

#include "vetorDescritor.h"

void normalizaVetor(float *vetor) {
    float minimo = 0.0;
    float maximo = 0.0;
    
    for (int i = 0; i < TAMANHOVETOR; i++) {
        if (*(vetor + i) > maximo) {
            maximo = *(vetor + i);
        }
    }
    
    minimo = maximo;
    for (int i = 0; i < TAMANHOVETOR; i++) {
        if (*(vetor + i) < minimo) {
            minimo = *(vetor + i);
        }
    }
    
    for (int i = 0; i < TAMANHOVETOR; i++) {
        *(vetor + i) = (*(vetor + i) - minimo) / (maximo - minimo);
    }
}

void calculaMediaVetorAsfalto(int a, float *frequenciaMediaAsfalto, float *vetorImagem) {
    if (a == 0) {
        for (int i = 0; i < TAMANHOVETOR; i++) {
            *(frequenciaMediaAsfalto + i) = *(vetorImagem + i);
        }
    } else {
        for (int i = 0; i < TAMANHOVETOR; i++) {
            *(frequenciaMediaAsfalto + i) = (*(frequenciaMediaAsfalto + i) + *(vetorImagem + i)) / 2;
        }
    }
}

void calculaMediaVetorGrama(int a, float *frequenciaMediaGrama, float *vetorImagem) {
    if (a == QUANTIDADETREINAMENTOSTESTES) {
        for (int i = 0; i < TAMANHOVETOR; i++) {
            *(frequenciaMediaGrama + i) = *(vetorImagem + i);
        }
    } else {
        for (int i = 0; i < TAMANHOVETOR; i++) {
            *(frequenciaMediaGrama + i) = (*(frequenciaMediaGrama + i) + *(vetorImagem + i)) / 2;
        }
    }
}
