
#include <stdbool.h>

#define SUCESSO 0
#define ERRO 1

typedef struct ABB pABB;
typedef struct pABB** ppABB;
typedef struct NoABB pNoABB;

struct pABB* criarABB(int tamInfo);
int insereABB(pABB * arvore, void * dado, int (* cmp)(void *p1, void *p2));
int removeABB(pABB * arvore, void * item, int (* cmp)(void *p1, void *p2));
int destroiABB(pABB * arvore);