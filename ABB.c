#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ABB-privado.h"

#define SUCESSO 0
#define ERRO 1

pABB *criarABB(int tamInfo)
{
    pABB *arvore;
    arvore = (pABB *)malloc(sizeof(pABB));
    if (arvore == NULL)
    {
        return arvore;
    } // Caso de erro no malloc

    // Inicializa variaveis
    arvore->tamInfo = tamInfo;
    arvore->quantidadeDados = 0;

    // Prepara a RAIZ
    arvore->NoRaiz = (pNoABB *)malloc(sizeof(pNoABB) + tamInfo);
    arvore->NoRaiz = NULL; // Coloca como NULL inicialmente

    return arvore;
};

// Função PUBLICA
// Adiciona um elemento à arvore
int insereABB(pABB *arvore, void *dado, int (*cmp)(void *, void *))
{
    int Resultado;
    pNoABB *NoAtual;

    // Primeiro passo verifica se a árvore esta vazia
    if (testaVazia(arvore))
    { // Se ela esta vazia, precisamos adicionar o No RAIZ
        NoAtual = adicionaNo(arvore->NoRaiz, dado, arvore->tamInfo, &Resultado);
        NoAtual->pai = NULL;      // No RAIZ não tem PAI
        arvore->NoRaiz = NoAtual; // No RAIZ
        arvore->quantidadeDados++;

        Resultado = SUCESSO;
        return Resultado;
    }
    else // Caso a árvore ja tenha No RAIZ
    {

        // O primeiro No é a RAIZ
        NoAtual = arvore->NoRaiz;

        // NoPAI que mantera as informacoes da arvore para atualizacao
        pNoABB *NoPai;
        NoPai = arvore->NoRaiz;

        int COMPARA;
        COMPARA = cmp(&dado, &arvore->NoRaiz->dados);

        // Verifica se o novo dado é maior que o dado da RAIZ
        // Isso determina se o novo elemento vai para a Direita ou Esquerda
        // Resultado da Comparação (qualquer que seja): 0 = Esquerda, 1 = Direita
        if (COMPARA == 0)
        {
            NoAtual = arvore->NoRaiz->esquerda;
        }
        else if (COMPARA == 1)
        {
            NoAtual = arvore->NoRaiz->direita;
        }
        else if (COMPARA == 2)
        { // Caso seja igual, impede de colocar esse elemento na arvore
            printf("ERRO: Erro ao inserir elemento na arvore: elemento ja existe.\n");
            Resultado = ERRO;
            return Resultado;
        }

        // Agora faz a recorrencia até encontrar um No VAZIO
        while (NoAtual != NULL)
        {

            NoPai = NoAtual;
            COMPARA = cmp(&dado, &NoAtual->dados);

            // Verifica se o novo dado é maior que o dado do NoAtual
            if (COMPARA == 0)
            {
                NoAtual = NoAtual->esquerda;
            }
            else if (COMPARA == 1)
            {
                NoAtual = NoAtual->direita;
            }
            else if (COMPARA == 2)
            {
                printf("ERRO: Erro ao inserir elemento na arvore: elemento ja existe.\n");
                // Resultado = ERRO;
                return Resultado;
            }
        }

        // Depois que encontrou o No VAZIO, adiciona as informacoes
        NoAtual = (pNoABB *)malloc(sizeof(pNoABB) + arvore->tamInfo);     // Faz o malloc
        NoAtual = adicionaNo(NoAtual, dado, arvore->tamInfo, &Resultado); // Coloca as informacoes no NoATUAL
        NoAtual->pai = NoPai;                                             // Atualiza o NoPAI do NoATUAL

        // Atualiza a arvore
        if (COMPARA == 0)
        {
            NoPai->esquerda = NoAtual;
        }
        else
        { // se chegou aqui, não há necessidade de verificar com o 2
            NoPai->direita = NoAtual;
        }
        arvore->quantidadeDados++;

        Resultado = SUCESSO;
        return Resultado;
    }

    // Esse ponto nunca deve ser atingido
    // Resultado = ERRO;
    return Resultado;
}

pNoABB *buscaNo(pABB *arvore, void *item, int (*cmp)(void *, void *))
{
    pNoABB *NoAtual;
    NoAtual = malloc(sizeof(pNoABB) + arvore->tamInfo);
    NoAtual = arvore->NoRaiz;

    int COMPARA;
    COMPARA = cmp(&item, &NoAtual->dados);
    while (NoAtual != NULL)
    {
        printf("[buscaNo] : NóAtual: %d  ", NoAtual->dados);
        if (NoAtual->esquerda != NULL) printf("(<- : %d)", NoAtual->esquerda->dados);
        if (NoAtual->direita != NULL) printf(" (-> : %d)", NoAtual->direita->dados);

        if (COMPARA == 2)
        {
            printf(" Nó encontrado.\n");
            return NoAtual;
        }
        else if (COMPARA == 0)
        {
            printf(" Indo para a esquerda\n");
            NoAtual = NoAtual->esquerda;
        }
        else
        {
            printf(" Indo para a direita\n");
            NoAtual = NoAtual->direita;
        }

        COMPARA = cmp(&item, &NoAtual->dados);
    }
    return NULL;
}



int remocaoNoSemFilhos (pABB * arvore, pNoABB *NoRemover)
{
    pNoABB *NoPai;
    NoPai = malloc(sizeof(pNoABB) + arvore->tamInfo);
    int Resultado = ERRO;

    if (NoRemover == arvore->NoRaiz)
    {
        printf("[removeABB] : Removendo nó raiz sem filhos.\n");
        arvore->NoRaiz = NULL;
        arvore->quantidadeDados--;
        Resultado = SUCESSO;
        return Resultado;
    }

    NoPai = NoRemover->pai;

    if (NoPai->direita == NoRemover)
    {
        NoPai->direita = NULL;
    }
    else
    {
        NoPai->esquerda = NULL;
    }
    arvore->quantidadeDados--;
    Resultado = SUCESSO;
    return Resultado;
}


int remocaoNo1FilhoDireita (pABB * arvore, pNoABB *NoRemover)
{
    pNoABB *NoPai;
    NoPai = malloc(sizeof(pNoABB) + arvore->tamInfo);
    int Resultado = ERRO;

    if (NoRemover == arvore->NoRaiz)
    {
        arvore->NoRaiz = arvore->NoRaiz->direita;
        arvore->quantidadeDados--;
        Resultado = SUCESSO;
        return Resultado;
    }

    NoPai = NoRemover->pai;

    if (NoPai->esquerda == NoRemover)
    {
        NoPai->esquerda = NoRemover->direita;
    }
    else
    {
        NoPai->direita = NoRemover->direita;
    }
    arvore->quantidadeDados--;
    Resultado = SUCESSO;
    return Resultado;
}


int remocaoNo1FilhoEsquerda (pABB * arvore, pNoABB *NoRemover)
{
    pNoABB *NoPai;
    NoPai = malloc(sizeof(pNoABB) + arvore->tamInfo);
    int Resultado = ERRO;

    if (NoRemover == arvore->NoRaiz)
    {
        arvore->NoRaiz = arvore->NoRaiz->esquerda;
        arvore->quantidadeDados--;
        Resultado = SUCESSO;
        return Resultado;
    }

    NoPai = NoRemover->pai;

    if (NoPai->esquerda == NoRemover)
    {
        NoPai->esquerda = NoRemover->esquerda;
    }
    else
    {
        NoPai->direita = NoRemover->esquerda;
    }
    arvore->quantidadeDados--;
    Resultado = SUCESSO;
    return Resultado;
}


int remocaoNo2Filhos(pABB *arvore, pNoABB *NoAtual)
{
    int Resultado = ERRO;
    pNoABB *NoSucessor;
    pNoABB *NoSucessorPai;
    pNoABB *NoRemover;
    NoSucessor = malloc(sizeof(pNoABB) + arvore->tamInfo);
    NoRemover = malloc(sizeof(pNoABB) + arvore->tamInfo);
    NoSucessorPai = malloc(sizeof(pNoABB) + arvore->tamInfo);

    // 1. Procuramos pelo nó sucessor (nó com menor valor dos filhos da direita)
    NoRemover = NoAtual;
    NoSucessor = NoAtual->direita;
    NoSucessorPai = NoAtual;

    // Caso especial onde a subarvore na direita do nó a ser deletado NÃO tem ramo esquerdo
    if (NoSucessor->esquerda == NULL)
    {
        NoRemover->dados = NoSucessor->dados;
        NoRemover->direita = NoSucessor->direita;

        arvore->quantidadeDados--;
        Resultado = SUCESSO;
        return Resultado;
    }

    // Encontra o Nó Sucessor na subarvore da DIREITA do nó a ser deletado
    while (NoSucessor->esquerda != NULL)
    {
        NoSucessorPai = NoSucessor;
        NoSucessor = NoSucessor->esquerda;
    }

    NoRemover->dados = NoSucessor->dados;
    NoSucessorPai->esquerda = NoSucessor->direita;

    arvore->quantidadeDados--;
    Resultado = SUCESSO;
    return Resultado;
}


// Função PÚBLICA
// Remove elemento da árvore
int removeABB(pABB *arvore, void *item, int (*cmp)(void *, void *))
{
    int Resultado;
    Resultado = ERRO;

    // Inicializa o NoATUAL (Temporario)
    pNoABB *NoRemover;
    NoRemover = malloc(sizeof(pNoABB) + arvore->tamInfo);

    // Primeiro passo verifica se a árvore está vazia
    if (testaVazia(arvore))
    { // Se está vazia, sai e gera erro
        printf("\n[removeABB] ERRO: Tentativa de remocao de dado em arvore vazia.\n");
        return Resultado;
    }

    // Encontra o nó a ser removido da árvore
    NoRemover = buscaNo(arvore, item, cmp);
    
    // Se o nó for nulo, é por quê ele não existe na árvore
    if (NoRemover == NULL)
    {
        printf("\n[removeABB] ERRO: Elemento procurado nao foi encontrado na arvore.\n");
        return Resultado;
    }

    // Caso 1: NoRemover não tem filhos
    if (NoRemover->direita == NULL & NoRemover->esquerda == NULL)
    {
        printf("[removeABB] : removendo sem filhos.\n");
        Resultado = remocaoNoSemFilhos (arvore, NoRemover);
        return Resultado;
    }

    // Caso 2a: NoRemover tem 1 filho na ESQUERDA
    else if (NoRemover->direita == NULL)
    {
        printf("[removeABB] : Removendo no com 1 filho na esquerda.\n");
        Resultado = remocaoNo1FilhoEsquerda (arvore, NoRemover);
        return Resultado;
    }
    // Caso 2b: NoRemover tem 1 filho na DIREITA
    else if (NoRemover->esquerda == NULL)
    {
        printf("[removeABB] : removendo no com 1 filho na direita.\n");
        Resultado = remocaoNo1FilhoDireita (arvore, NoRemover);
        return Resultado;
    }
    // Caso 3: NoRemover tem 2 filhos
    else
    {
        printf("[removeABB] : Removendo no com 2 filhos.\n");
        Resultado = remocaoNo2Filhos(arvore, NoRemover);
        return Resultado;
    }
}


// Função PÚBLICA
// Destroi a árvore
int destroiABB(pABB *arvore)
{
    printf("Iniciando destruicao. Verfica se arvore esta alocada.\n");
    if (!arvore)
    {
        printf("Arvore nao alocada!\n");
        return ERRO;
    }
    /*else if ((arvore->NoRaiz->esquerda == NULL) || (arvore->NoRaiz->direita == NULL))
    {
        
    }*/
    else
    {
        if ((arvore->NoRaiz->esquerda == NULL) || (arvore->NoRaiz->direita == NULL))
        {
            printf("Árvore sem nós filhos. ");
        }
        else
        {
            printf("Arvore alocada. Iniciando liberacao de nos.\n");
            liberaNo(arvore->NoRaiz);
            printf("Todos os nos liberados. ");
        }
    }
    printf(" Liberando arvore.\n");
    free(arvore);
    return SUCESSO;
}

int liberaNo(pNoABB *noArvore)
{
    void *tmp;

    if (!noArvore)
    {

        printf("No nao alocado!\n");
        return ERRO;
    }
    else
    {
        tmp = noArvore->dados;

        printf("Analisando no %d\n", tmp);

        printf("Verificando no a esquerda de %d\n", tmp);
        if (noArvore->esquerda == NULL)
            printf("Sem no a esquerda\n");
        else
        {
            printf("No a esquerda encontrado!\n\n");
            liberaNo(noArvore->esquerda);
            noArvore->esquerda = NULL;
        }

        printf("Verificando no a direita de %d\n", tmp);
        if (noArvore->direita == NULL)
            printf("Sem no a direita\n");
        else
        {
            printf("No a direita encontrado!\n\n");
            liberaNo(noArvore->direita);
            noArvore->direita = NULL;
        }

        if ((noArvore->direita == NULL)&(noArvore->esquerda == NULL)){
            if (noArvore->dados != NULL){
                noArvore->pai = NULL;
                free(noArvore->pai);
                noArvore->dados = NULL;
                free(noArvore->dados);
                noArvore = NULL; 
                free(noArvore);
                printf("No %d liberado com sucesso!\n\n", tmp);
            }
        }
    }

    return SUCESSO;
}

// Função PRIVADA
// Adiciona um No filho à arvore
pNoABB *adicionaNo(pNoABB *NoAtual, void *dado, int tamInfo, int *Resultado)
{
    NoAtual = (pNoABB *)malloc(sizeof(pNoABB) + tamInfo);
    if (NoAtual == NULL)
    {
        *Resultado = ERRO;
        exit(1);
    }
    else
    {
        NoAtual->dados = (void *)malloc(tamInfo);
        NoAtual->dados = dado;
        NoAtual->esquerda = NULL;
        NoAtual->direita = NULL;

        *Resultado = SUCESSO;
    }
    return NoAtual;
}

// Função PRIVADA
// Verifica se a árvore está vazia
int testaVazia(pABB *arvore)
{
    return (arvore->NoRaiz == NULL);
}

int reiniciaABB(pABB *arvore)
{
    // Verifica se a ABB já não está vazia //WIP
    if (testaVazia(arvore))
    {
        printf("A arvore já está vazia\n");
        return SUCESSO;
    }
    if (!arvore)
    {
        printf("Arvore nao alocada!\n");
        return ERRO;
    }

    liberaNo(arvore->NoRaiz);
    printf("[reiniciaABB] : Todos os nós liberados. ");
    arvore->quantidadeDados = 0;
    return SUCESSO;
}

int quantificaABB(pABB *arvore)
{
    if (!arvore)
    {
        printf("Arvore nao alocada!\n");
        return ERRO;
    }
    printf("[Existem %d elementos na árvore.]\n", arvore->quantidadeDados);
    return SUCESSO;
}
