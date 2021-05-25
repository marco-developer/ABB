# ABB - Arvore Binária de Busca  

Para utilizar, acrescente #include "ABB-publico.h" ao seu código.

Este TDA acompanha um código de exemplo de uso (main.c). Para compilar, execute o comando make e, em seguida, ./main.  

# Funções públicas  

pABB* criarABB(int tamInfo);  
int insereABB(pABB * arvore, void * dado, int (* cmp)(void * p1, void * p2));  
int removeABB(pABB * arvore, void * item, int (* cmp)(void * p1, void * p2));  
int destroiABB(pABB * arvore);  
int liberaNo(pNoABB * noArvore);  
int reiniciaABB(pABB * arvore);  

int quantificaABB(pABB * arvore);  

int imprimeArvore(pABB * arvore, void (* processa)(void * p));  
int percursoEmOrdem(pNoABB * noArvore, void (* processa)(void * p));  
int percursoPreOrdem(pNoABB * noArvore, void (* processa)(void * p));  
int percursoPosOrdem(pNoABB * noArvore, void (* processa)(void * p));  

# Funções privadas

pNoABB* adicionaNo(pNoABB * NoAtual, void * dado, int tamInfo, int * Resultado);  
int testaVazia(pABB * arvore);  
