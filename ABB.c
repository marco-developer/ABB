#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ABB-privado.h"

#define SUCESSO 0
#define ERRO 1

pABB * criarABB(int tamInfo)
{
    pABB * arvore;
    arvore = (pABB*) malloc(sizeof(pABB));
    if (arvore == NULL) { 
        printf("Erro ao alocar memoria para arvore!\n");
        exit(1); 
    } // Caso de erro no malloc

    // Inicializa variaveis
    arvore->tamInfo = tamInfo;

    // Prepara a RAIZ
    arvore->NoRaiz = (pNoABB*) malloc(sizeof(pNoABB)+tamInfo);
    arvore->NoRaiz = NULL;  // Coloca como NULL inicialmente
};

// Função PUBLICA
// Adiciona um elemento à arvore
int insereABB(pABB * arvore, void * dado,  int (* cmp)(void *, void *))
{
    int *Resultado;
    *Resultado = ERRO;

    pNoABB* NoAtual;

    // Primeiro passo verifica se a árvore esta vazia
    if (testaVazia(arvore)){  // Se ela esta vazia, precisamos adicionar o No RAIZ
        NoAtual = adicionaNo(arvore->NoRaiz, dado, arvore->tamInfo, Resultado);
        NoAtual->pai = NULL;       // No RAIZ não tem PAI
        arvore->NoRaiz = NoAtual;  // No RAIZ

        *Resultado = SUCESSO;
        return *Resultado;
    } 
    else   // Caso a árvore ja tenha No RAIZ 
    {   

        // O primeiro No é a RAIZ
        NoAtual = arvore->NoRaiz;

        // NoPAI que mantera as informacoes da arvore para atualizacao
        pNoABB* NoPai;
        NoPai = arvore->NoRaiz;

        int COMPARA;
        COMPARA = cmp(&dado,&arvore->NoRaiz->dados);

        // Verifica se o novo dado é maior que o dado da RAIZ
        // Isso determina se o novo elemento vai para a Direita ou Esquerda
        // Resultado da Comparação (qualquer que seja): 0 = Esquerda, 1 = Direita
        if (COMPARA==0){
            NoAtual = arvore->NoRaiz->esquerda;
        } else if (COMPARA == 1) {
            NoAtual = arvore->NoRaiz->direita;
        } else if (COMPARA == 2) { // Caso seja igual, impede de colocar esse elemento na arvore
            printf("ERRO: Erro ao inserir elemento na arvore: elemento ja existe.\n");
            *Resultado = ERRO;
            return *Resultado;
        }

        // Agora faz a recorrencia até encontrar um No VAZIO
        while(NoAtual!=NULL){
            
            NoPai = NoAtual;
            COMPARA = cmp(&dado,&NoAtual->dados);

            // Verifica se o novo dado é maior que o dado do NoAtual
            if (COMPARA==0){
                NoAtual = NoAtual->esquerda;
            } else if (COMPARA == 1) {
                NoAtual = NoAtual->direita;
            } else if (COMPARA ==2) {
                printf("ERRO: Erro ao inserir elemento na arvore: elemento ja existe.\n");
                *Resultado = ERRO;
                return *Resultado;
            }

        }

        // Depois que encontrou o No VAZIO, adiciona as informacoes
        NoAtual = (pNoABB*) malloc(sizeof(pNoABB)+arvore->tamInfo); // Faz o malloc
        NoAtual = adicionaNo(NoAtual, dado, arvore->tamInfo, Resultado);  // Coloca as informacoes no NoATUAL
        NoAtual->pai = NoPai;      // Atualiza o NoPAI do NoATUAL
        
        // Atualiza a arvore
        if (COMPARA == 0){
            NoPai->esquerda = NoAtual;
        } else {  // se chegou aqui, não há necessidade de verificar com o 2
            NoPai->direita = NoAtual;
        }
        
        *Resultado = SUCESSO;
        return *Resultado;
    }

    // Esse ponto nunca deve ser atingido
    *Resultado = ERRO;
    return *Resultado;
}


// Função PÚBLICA
// Remove elemento da árvore
int removeABB(pABB * arvore, void * item, int (* cmp)(void *, void *))
{
    int *Resultado;
    *Resultado = ERRO;

    int COMPARA;
    int COMPARA_ant;

    // Inicializa o NoATUAL (Temporario)
    pNoABB* NoAtual;
    pNoABB* NoPai;
    NoAtual = malloc(sizeof(pNoABB)+arvore->tamInfo);
    NoPai = malloc(sizeof(pNoABB)+arvore->tamInfo);

    // Primeiro passo verifica se a árvore está vazia 
    if (testaVazia(arvore)){ // Se está vazia, sai e gera erro
        printf("\nERRO: Tentativa de remocao de dado em arvore vazia.\n");
        return *Resultado;
    }

    
    // Percorre os elementos da árvore até encontrar o elemento que deseja-se remover
    // Para percorrer os elementos de forma mais rapida, usa-se da organizacao dos nos da arvore para acelerar o processo
    NoAtual = arvore->NoRaiz;               // Inicializa NoATUAL como NoRAIZ
    NoPai = arvore->NoRaiz;                 // Inicializa NoPAI como NoRAIZ
    COMPARA = cmp(&item,&NoAtual->dados);   // Compara o elemento buscado e o dado armazenado no NoAtual

    if (COMPARA == 2){  // Caso esteja tentando remover o NoRAIZ

        // ?????????

    } else {

        while (COMPARA != 2)  // Enquanto COMPARA não é 2 (==), continua a busca
        {
            NoPai = NoAtual;  // Atualiza o NoPAI

            if (COMPARA == 0){
                NoAtual = NoAtual->esquerda;  // Atualiza o NoATUAL
            } else {
                NoAtual = NoAtual->direita;   // Atualiza o NoATUAL
            }

            COMPARA_ant = COMPARA;
            COMPARA = cmp(&item,&NoAtual->dados);   // Compara o elemento buscado e o dado armazenado no NoAtual

            // Verifica se o NoATUAL está vazio e para o processo
            if (NoAtual == NULL){
                printf("\nERRO: Elemento procurado nao foi encontrado na arvore.\n");
                return *Resultado;
            }
        }
    }

    // Apos encontrar o NoATUAL, que contem a informacao a ser removida, realiza a remocao
    // Caso seja no sem filhos:
    if ((NoAtual->esquerda == NULL) & (NoAtual->direita == NULL)){
        if (COMPARA_ant == 0){
            NoPai->esquerda = NULL;
        } else if (COMPARA_ant == 1) {
            NoPai->direita = NULL;
        }
    } else 
    // Caso seja no com um filho:
    if ((NoAtual->esquerda == NULL) || (NoAtual->direita == NULL)){
        if (NoAtual->esquerda == NULL){
            if (COMPARA_ant == 0){
                NoPai->esquerda = NoAtual->direita;  // Compara_ant define a perna do NoPAI, mas NoATUAL->esquerda == NULL define perna direita do NoATUAL
            } else if (COMPARA_ant == 1){
                NoPai->direita = NoAtual->direita;   // Compara_ant define a perna do NoPAI, mas NoATUAL->esquerda == NULL define perna direita do NoATUAL
            }
        } else {
            if (COMPARA_ant == 0){
                NoPai->esquerda = NoAtual->esquerda;  // Compara_ant define a perna do NoPAI, mas NoATUAL->esquerda == NULL define perna esquerda do NoATUAL
            } else if (COMPARA_ant == 1){
                NoPai->direita = NoAtual->esquerda;   // Compara_ant define a perna do NoPAI, mas NoATUAL->esquerda == NULL define perna esquerda do NoATUAL
            }
        }
    } else {
        
        // Caso seja no com dois filhos:
        pNoABB* NoPROX;
        NoPROX = malloc(sizeof(pNoABB)+arvore->tamInfo);

        // 1. Verificamos se o filho da direita tem filho à esquerda
        // e se esse também não tem filho à esquerda
        NoPROX = NoAtual->direita->esquerda;
        if ( (NoPROX != NULL) & 
              (NoPROX->esquerda == NULL)) {

        } else {

        // 2. Verificamos se o filho da esquerda tem filho à direita
        // e se esse também não tem filho filho à direita
            NoPROX = NoAtual->esquerda->direita;
            if ((NoPROX != NULL) & 
                  (NoPROX->direita == NULL)) {

                  }
        }
    }
}

// Função PÚBLICA
// Destroi a árvore
int destroiABB(pABB * arvore)
{
    printf("Iniciando destruicao. Verfica se arvore esta alocada\n");
    if(!arvore) {

        printf("Arvore nao alocado!\n");
        return ERRO;

    } else {
        printf("Arvore alocada. Partindo para liberacao de nos.\n");
        liberaNo(arvore->NoRaiz);
    }
    free(arvore);
    return SUCESSO;
}

int liberaNo(pNoABB *noArvore)
{
    if(!noArvore) {

        printf("No nao alocado!\n");
        return ERRO;

    } else {
        printf("Analisando no %d\n", noArvore->dados);

        printf("Verificando no a esquerda de %d\n", noArvore->dados);
        if(noArvore->esquerda==NULL) printf("Sem no a esquerda\n\n"); 
        else {
            printf("No a esquerda encontrado!\n\n");
            liberaNo(noArvore->esquerda);
        }

        printf("Verificando no a direita de %d\n", noArvore->dados);
        if(noArvore->direita==NULL) printf("Sem no a direita\n\n");
        else {
            printf("No a direita encontrado!\n\n");
            liberaNo(noArvore->direita);
        }
        
        free(noArvore);
        printf("No liberado com sucesso!\n\n");
    }
    
    return SUCESSO;
}




// Função PRIVADA
// Adiciona um No filho à arvore
pNoABB* adicionaNo(pNoABB * NoAtual, void * dado, int tamInfo, int * Resultado)
{
    *Resultado = ERRO;

    NoAtual = (pNoABB*) malloc(sizeof(pNoABB)+tamInfo);
    if (NoAtual == NULL) { return NoAtual; }  // Em caso de erro

    NoAtual->dados = (void*) malloc(tamInfo);
    NoAtual->dados = dado;
    NoAtual->esquerda = NULL;
    NoAtual->direita = NULL;

    *Resultado = SUCESSO;
    return NoAtual;
}

// Função PRIVADA
// Verifica se a árvore está vazia
int testaVazia(pABB * arvore)
{
    return (arvore->NoRaiz==NULL);
}