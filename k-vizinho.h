#ifndef __KVIZNHO__
#define __KVIZNHO__

typedef struct _no{
    void * item;
    struct _no * esq;
    struct _no * dir;
    struct _no * p;
   
}tno;

typedef struct _arv{
    tno * raiz;
    float (*compara1)(const void *a, const void *b);
    float (*compara2)(const void *a, const void *b);
}tarv;

/*typedef struct _pontoCart{  Isso quebra o princípio de ser void * 
   int x;
   int y;

}ponto;*/

void abb_construir(tarv * parv, float (*compara1)(const void *a, const void *b),  float (*compara2)(const void *a, const void *b));
void abb_inserir(tarv * parv, void *pitem);
//void percorrer_crescente(tno *primeiroE, int nivel);

/*tno* treeMinimum(tno* no);
tno* treeMaximum(tno* no);
tno* treeSucessor(tno* no);
tno* treePredecessor(tno* no);*/

tno* nearestNeighbor(tno* root, tno* target, int depth, tarv* parv);

tno* buscaNVizinhos(tno* target, tarv * parv, int n, tno* vetor);

void destruir_arvore(tno *primeiroE);


#endif