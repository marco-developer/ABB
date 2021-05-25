#include <stdio.h>
#include <stdlib.h>
#include "ABB-publico.h"

int cmpMaior(void * p1, void * p2)
{
    int *x = p1;
    int *y = p2;

    if (*x > *y) return 1;
    else if (*x < *y) return 0;
    
    return 2;
}

void processa(void *p)
{
    int *item = p;

    
    printf("%d ", *item);
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
    if(!abb)
        printf ("[main] : Erro ao criar arvore!");
    else
        printf("[main] : Arvore criada com sucesso!\n");

    quantificaABB(abb);


    printf("\n[main] : ================================================\n");
    printf("[main] : ======        Inserindo elementos         ======\n");
    printf("[main] : ================================================\n");
    
    for (int i=0; i<13; i++)
    {
        Res = insereABB(abb,p[i],cmpMaior);
        if(Res==0)
            printf("[main] : Elemento %d inserido com sucesso!\n", p[i]);
        else
            printf ("[main] : Erro ao inserir elemento!\n");
        quantificaABB(abb);
    }

    printf("\n[main] : ================================================\n");
    printf("[main] : ======    Removendo elementos em ordem    ======\n");
    printf("[main] : ================================================\n");

    for (int i=0; i<=12; i++)
    {
        printf("\nRemovendo elemento %d\n", p[i]);
        Res = removeABB(abb,p[i],cmpMaior);
        if(Res==0)
            printf("Elemento removido com sucesso!\n");
        else
            printf ("Erro ao remover elemento!\n");
        quantificaABB(abb);
    }
    
    
    printf("\n[main] : ================================================\n");
    printf("[main] : ======        Inserindo elementos         ======\n");
    printf("[main] : ================================================\n");
    
    for (int i=0; i<13; i++)
    {
        Res = insereABB(abb,p[i],cmpMaior);
        if(Res==0)
            printf("[main] : Elemento %d inserido com sucesso!\n", p[i]);
        else
            printf ("[main] : Erro ao inserir elemento!\n");
        quantificaABB(abb);
    }
    
    
    printf("\n[main] : ================================================\n");
    printf("[main] : ======  Removendo elementos ao contrario  ======\n");
    printf("[main] : ================================================\n");

    for (int i=12; i>=0; i--)
    {
        printf("\nRemovendo elemento %d\n", p[i]);
        Res = removeABB(abb,p[i],cmpMaior);
        if(Res==0)
            printf("Elemento removido com sucesso!\n");
        else
            printf ("Erro ao remover elemento!\n");
        quantificaABB(abb);
    }


    printf("\n[main] : ================================================\n");
    printf("[main] : ======        Inserindo elementos         ======\n");
    printf("[main] : ================================================\n");
    
    for (int i=0; i<13; i++)
    {
        Res = insereABB(abb,p[i],cmpMaior);
        if(Res==0)
            printf("[main] : Elemento %d inserido com sucesso!\n", p[i]);
        else
            printf ("[main] : Erro ao inserir elemento!\n");
        quantificaABB(abb);
    }


    printf("\n[main] : ================================================\n");
    printf("[main] : ======    Removendo elementos parcial     ======\n");
    printf("[main] : ================================================\n");

    printf("\n[main] : Removendo elemento %d\n", p[1]);
    Res = removeABB(abb,p[1],cmpMaior);
    if(Res==0)
        printf("[main] : Elemento removido com sucesso!\n");
    else
        printf ("[main] : Erro ao remover elemento!\n");
    quantificaABB(abb);
    
    printf("\n[main] : Removendo elemento %d\n", p[7]);
    Res = removeABB(abb,p[7],cmpMaior);
    if(Res==0)
        printf("[main] : Elemento removido com sucesso!\n");
    else
        printf ("[main] : Erro ao remover elemento!\n");
    quantificaABB(abb);
    
    printf("\n[main] : Removendo elemento %d\n", p[12]);
    Res = removeABB(abb,p[12],cmpMaior);
    if(Res==0)
        printf("[main] : Elemento removido com sucesso!\n");
    else
        printf ("[main] : Erro ao remover elemento!\n");
    quantificaABB(abb);
    
    printf("\n[main] : Removendo elemento %d\n", p[2]);
    Res = removeABB(abb,p[2],cmpMaior);
    if(Res==0)
        printf("[main] : Elemento removido com sucesso!\n");
    else
        printf ("[main] : Erro ao remover elemento!\n");
    quantificaABB(abb);
    
    printf("\n[main] : Removendo elemento %d\n", p[9]);
    Res = removeABB(abb,p[9],cmpMaior);
    if(Res==0)
        printf("[main] : Elemento removido com sucesso!\n");
    else
        printf ("[main] : Erro ao remover elemento!\n");
    quantificaABB(abb);

    
    //quantificaABB(abb);

    // REINICIA ARVORE
    
    printf("\n[main] : ================================================\n");
    printf("[main] : ======          Reinicia arvore           ======\n");
    printf("[main] : ================================================\n");
    
    Res = reiniciaABB(abb);
    if(Res==0)
        printf("Arvore reiniciada com sucesso!\n");
    else
        printf ("Erro ao reiniciar arvore!\n");
    quantificaABB(abb);

    printf("\n[main] : ================================================\n");
    printf("[main] : ======        Inserindo elementos         ======\n");
    printf("[main] : ================================================\n");
    
    for (int i=0; i<13; i++)
    {
        Res = insereABB(abb,p[i],cmpMaior);
        if(Res==0)
            printf("[main] : Elemento %d inserido com sucesso!\n", p[i]);
        else
            printf ("[main] : Erro ao inserir elemento!\n");
        quantificaABB(abb);
    }

    printf("\n[main] : ================================================\n");
    printf("[main] : ======    Imprimindo percurso               ======\n");
    printf("[main] : ================================================\n");

    imprimeArvore(abb, processa);
    

    // DESTROI ARVORE
    printf("\n[main] : ================================================\n");
    printf("[main] : ======         Destruindo arvore          ======\n");
    printf("[main] : ================================================\n");
    
    Res = destroiABB(abb);
    if(Res==0)
        printf("Arvore destruida com sucesso!\n");
    else
        printf ("Erro ao destuir arvore!");
    quantificaABB(abb);
        
}

