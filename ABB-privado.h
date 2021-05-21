
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "ABB-publico.h"

#define MAX_NOS 100

typedef struct NoABB{
    void *dados;
    struct NoABB *pai;
    struct NoABB *esquerda;
    struct NoABB *direita;
};

typedef struct ABB
{
    int tamInfo;
    pNoABB * NoRaiz;
};



pNoABB* adicionaNo(pNoABB * NoAtual, void * dado, int tamInfo, int * Resultado);
int testaVazia(pABB * arvore);