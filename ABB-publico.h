
#include <stdbool.h>

#define SUCESSO 0
#define ERRO 1

typedef struct ABB pABB;
typedef struct pABB** ppABB;
typedef struct NoABB pNoABB;

pABB* criarABB(int tamInfo);
int insereABB(pABB * arvore, void * dado, int (* cmp)(void *p1, void *p2));
int removeABB(pABB * arvore, void * item, int (* cmp)(void *p1, void *p2));
int destroiABB(pABB * arvore);
int liberaNo(pNoABB *noArvore);
int reiniciaABB(pABB * arvore);

int quantificaABB(pABB * arvore);

int imprimeArvore(pABB * arvore, void (* processa)(void *p));
int percursoEmOrdem(pNoABB *noArvore, void (* processa)(void *p));
int percursoPreOrdem(pNoABB *noArvore, void (* processa)(void *p));
int percursoPosOrdem(pNoABB *noArvore, void (* processa)(void *p));

void mostraArvore(pABB * arvore, int b);
