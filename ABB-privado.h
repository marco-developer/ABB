#include "ABB-publico.h"

typedef struct NoABB{
    void *dados;
    struct NoABB *pai;
    struct NoABB *esquerda;
    struct NoABB *direita;
}NoABB;

typedef struct ABB
{
    int tamInfo;
    int quantidadeDados;
    pNoABB * NoRaiz;
}ABB;

pNoABB* adicionaNo(pNoABB * NoAtual, void * dado, int tamInfo, int * Resultado);
int testaVazia(pABB * arvore);
