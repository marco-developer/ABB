#include <stdio.h>
#include <stdlib.h>
#include "ABB-publico.h"

int* cmpMaior(int * p1, int * p2)
{
    int COMPARA;
    if (*p1 > *p2){
        COMPARA = 1;
    } else if (*p1 < *p2) {
        COMPARA = 0;
    } else if (*p1 = *p2){
        COMPARA = 2;
    }
    return COMPARA;
}

int main(int argc, char **argv)
{
    int p[20];
    int Res;

    // Inicializa os elementos do vetor
    p[0] = 9;       //0x9
    p[1] = 4;       //0x4
    p[2] = 12;      //0xc
    p[3] = 10;      //0xa
    p[4] = 6;       //0x6
    p[5] = 2;       //0x2
    p[6] = 16;      //0x10
    p[7] = 7;       //0x7
    p[8] = 11;      //0xb
    p[9] = 13;      //0xd
    p[10] = 18;     //0x12
    p[11] = 14;     //0xe
    p[12] = 8;      //0x8

    pABB * abb;

    abb = criarABB(sizeof(int));


    // ADICIONA ELEMENTOS À ÀRVORE
    for (int i=0; i<13; i++){

        Res = insereABB(abb,p[i],cmpMaior);

    }

    


    // REMOVE ELEMENTOS
    Res = removeABB(abb,p[4],cmpMaior);


    Res = destroiABB(abb);
    Res = destroiABB(abb);

}