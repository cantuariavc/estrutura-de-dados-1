//
//  descritorGLCM.c
//  Problema
//
//  Created by Vinícius Cantuária on 27/04/2018.
//  Copyright © 2018 Vinícius Cantuária. All rights reserved.
//

#include "descritorGLCM.h"

void calculaFrequenciasGLCM(int **matrizDecimal, int **noroeste, int **norte, int **nordeste, int **oeste, int **leste, int **sudoeste, int **sul, int **sudeste) {
    *(*(noroeste + (*(*(matrizDecimal + 1) + 1))) + (*(*(matrizDecimal + 0) + 0))) += 1;
    *(*(norte + (*(*(matrizDecimal + 1) + 1))) + (*(*(matrizDecimal + 0) + 1))) += 1;
    *(*(nordeste + (*(*(matrizDecimal + 1) + 1))) + (*(*(matrizDecimal + 0) + 2))) += 1;
    *(*(oeste + (*(*(matrizDecimal + 1) + 1))) + (*(*(matrizDecimal + 1) + 0))) += 1;
    *(*(leste + (*(*(matrizDecimal + 1) + 1))) + (*(*(matrizDecimal + 1) + 2))) += 1;
    *(*(sudoeste + (*(*(matrizDecimal + 1) + 1))) + (*(*(matrizDecimal + 2) + 0))) += 1;
    *(*(sul + (*(*(matrizDecimal + 1) + 1))) + (*(*(matrizDecimal + 2) + 1))) += 1;
    *(*(sudeste + (*(*(matrizDecimal + 1) + 1))) + (*(*(matrizDecimal + 2) + 2))) += 1;
}

float calculaContraste(int **matriz) {
    int somaValores = 0;
    float contraste = 0.0;
    
    for (int i = 0; i < TAMANHOMATRIZGLCM; i++) {
        for (int j = 0; j < TAMANHOMATRIZGLCM; j++) {
            somaValores += *(*(matriz + i) + j);
        }
    }
    
    for (int i = 0; i < TAMANHOMATRIZGLCM; i++) {
        for (int j = 0; j < TAMANHOMATRIZGLCM; j++) {
            contraste += pow((i - j), 2) * ((float) *(*(matriz + i) + j) / somaValores);
        }
    }
    
    return contraste;
}

float calculaEnergia(int **matriz) {
    int somaValores = 0;
    float energia = 0.0;

    for (int i = 0; i < TAMANHOMATRIZGLCM; i++) {
        for (int j = 0; j < TAMANHOMATRIZGLCM; j++) {
            somaValores += *(*(matriz + i) + j);
        }
    }
    
    for (int i = 0; i < TAMANHOMATRIZGLCM; i++) {
        for (int j = 0; j < TAMANHOMATRIZGLCM; j++) {
            energia += pow(((float) *(*(matriz + i) + j) / somaValores), 2);
        }
    }
    
    return energia;
}

float calculaHomogeneidade(int **matriz) {
    int somaValores = 0;
    float homogeneidade = 0.0;
    
    for (int i = 0; i < TAMANHOMATRIZGLCM; i++) {
        for (int j = 0; j < TAMANHOMATRIZGLCM; j++) {
            somaValores += *(*(matriz + i) + j);
        }
    }
    
    for (int i = 0; i < TAMANHOMATRIZGLCM; i++) {
        for (int j = 0; j < TAMANHOMATRIZGLCM; j++) {
            homogeneidade += ((float) *(*(matriz + i) + j) / somaValores) / (1 + abs(i - j));
        }
    }
    
    return homogeneidade;
}
