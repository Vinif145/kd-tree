#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include "k-vizinho.h"



void abb_construir(tarv * parv, float (*compara1)(const void *a, const void *b), float (*compara2)(const void *a, const void *b) ){
    parv->raiz = NULL;
    parv->compara1 = compara1;
    parv->compara2 = compara2;
}

void abb_inserir(tarv * parv, void *pitem){
    tno ** ppno;
    tno * pno;
    ppno = &(parv->raiz);
    pno = *ppno;
    int pos = 1;

    tno * pai = *ppno; //Parte do Pai
  
    while(pno !=NULL){

    	if(pos % 2 == 0){ //y

		    		                    /* 10     20 */
		        if (parv->compara2(pno->item,pitem) < 0){ /* direita*/  //Ver certinho questão do (9,4);
    		        pai = *ppno;
		            ppno = &(pno->dir);
		            pno = *ppno;
		        }else{     
		            pai = *ppno;                         /* esquerda*/
		            ppno = &(pno->esq);
		            pno = *ppno;
		        }

		        //printf("y\n");

        

    	}else { //x

    		//printf("%d\n", parv->compara1(pno->item,pitem));

    		                    /* 10     20 */
	        if (parv->compara1(pno->item,pitem) <  0){ /* direita*/
    		    pai = *ppno;
	            ppno = &(pno->dir);
	            pno = *ppno;
	        }else{ 
	            pai = *ppno;                             /* esquerda*/
	            ppno = &(pno->esq);
	            pno = *ppno;
	        }

	          //printf("x\n");

       

    	}

    	pos = pos +1;
       
    }

    if ((*ppno) == NULL){
        (*ppno) = malloc(sizeof(tno));
        (*ppno)->item = pitem;
        (*ppno)->esq = NULL;
        (*ppno)->dir = NULL;
        (*ppno)->p = pai;
    }
}



/*void percorrer_crescente(tno *primeiroE, int nivel){

    
    //tno pno =  *primeiroE;
   // printf("%d %d\n", ((ponto*)(primeiroE.item))->x, ((ponto*)(primeiroE.item))->y);

    //percorrer_crescente(*(primeiroE.dir));
   // percorrer_crescente(*(primeiroE.dir));
   


	if(primeiroE != NULL ){

		
		printf("%d -- %d (%d)\n", ((ponto*)(primeiroE->item))->x, ((ponto*)(primeiroE->item))->y, nivel);
		if(primeiroE->p != NULL)
		printf("P -> %d -- %d\n " , ((ponto*)(primeiroE->p)->item)->x, ((ponto*)(primeiroE->p)->item)->y); //Caso haja mostra o filho;
		percorrer_crescente(primeiroE->esq, nivel + 1);
		percorrer_crescente(primeiroE->dir, nivel + 1);
	
	}
}*/

  

//Parte das funções de Predecessor e Sucessor

tno* treeMinimum(tno* no) {
    while (no->esq != NULL) {
        no = no->esq;
    }
    return no;
}

tno* treeMaximum(tno* no) {
    while (no->dir != NULL) {
        no = no->dir;
    }
    return no;
}

tno* treeSucessor(tno* no) {
    if (no->dir != NULL) {
        return treeMinimum(no->dir);
    }
    tno* y = no->p;
    while (y != NULL && no == y->dir) {
        no = y;
        y = y->p;
    }
    return y;
}

tno* treePredecessor(tno* no) {
    if (no->esq != NULL) {
        return treeMaximum(no->esq);
    }
    tno* y = no->p;
    while (y != NULL && no == y->esq) {
        no = y;
        y = y->p;
    }
    return y;
}


/* Parte da Busca do Vizinho mais próximo */


/*double distancia(tno* p1, tno* p2, tarv* parv) { //Função de Euclides
    double dx = ((ponto*)p1->item)->x - ((ponto*)p2->item)->x;
    double dy = ((ponto*)p1->item)->y - ((ponto*)p2->item)->y;
    return sqrt(dx * dx + dy * dy);
}*/

double distanciaParcial(tno* p0, tno* p1, tarv* parv) {
		double total = 0;
		
	  
	    int diff = abs( parv->compara1(p0->item, p1->item) );
		total = pow(diff, 2);


	    diff = abs( parv->compara2(p0->item, p1->item) );
		total = total + pow(diff, 2);
				
		return total; 
	
}

tno* maisPerto(tno* n0, tno* n1, tno* target, tarv* parv) {
	    if (n0 == NULL) 
	    	return n1;

	    if (n1 == NULL) 
	    	return n0;

	    double d1 = distanciaParcial(n0, target, parv);
	    double d2 = distanciaParcial(n1, target, parv);

	    if (d1 < d2)
	        return n0;
	    else
	        return n1;
	}


tno* nearestNeighbor(tno* root, tno* target, int depth, tarv * parv) { //É preciso passar a parv pois usamos o devido método de compara1 compara2 conforme o usuário definir
		
		if (root == NULL) //Raiz
			return NULL; 

		
		tno* caminoNormal = NULL;
		tno* caminhoAlternativo = NULL;

		int profundidade = depth % 2;

		
		if (profundidade == 0) { //X

			//printf("%d\n", parv->compara1(root->item, target->item));

			if (parv->compara1(root->item, target->item) < 0){ 
			//printf("entrou x1\n");
              	

			    caminoNormal = root->dir;
			    caminhoAlternativo = root->esq;

	        }else if (parv->compara1(root->item,target->item) > 0){ 
	           //printf("entrou x2\n"); 
	            caminoNormal = root->esq;
			    caminhoAlternativo = root->dir;
			 }
	        
	    }else {//Y

	    	if (parv->compara2(root->item, target->item) < 0){ 
	    	    //printf("entrou y1\n"); 
                caminoNormal = root->dir;
			    caminhoAlternativo = root->esq;

	        }else if (parv->compara2(root->item,target->item) > 0){  
	        	//printf("entrou y2\n"); 
	           

			    caminoNormal = root->esq;
			    caminhoAlternativo = root->dir;
	        }

	   }

		
		
		tno* temp = nearestNeighbor(caminoNormal, target, depth + 1, parv); //Indo até o fundo da kd-tree
		tno* best = maisPerto(temp,	root, target, parv);

		double radiusSquared = distanciaParcial(target, best, parv); // Calculando a Distancia Parcial com base na formula de Euclides

		double dist;

		if (profundidade == 0) { //X

			dist = parv->compara1(target->item, root->item);

	       
	    }else {//Y

	    	dist = parv->compara2(target->item, root->item);

	   }
		
		
		if (radiusSquared >= dist * dist) { //Notou-se, de acordo comx ou y que a árvore contrária, o caminhoAlternativo pode conter um nó de menor valor
		
			temp = nearestNeighbor(caminhoAlternativo, target, depth + 1, parv);
			best = maisPerto(temp, best, target, parv);

		}

		return best;

		
}

/* Função que retorna N vizinhos mais próximos */

tno* buscaNVizinhos(tno* target, tarv * parv, int n, tno* vetor){ //Dada a longitude e latitude desejada (dentro de um tno), bem como a kd-tree (arvore), segue-se a busca

    tno * pnode = parv->raiz; //Pegando o primeiro elemento da nossa kd-tree

    vetor = (tno *) malloc(n * sizeof(tno)); //Alocação dinâmica para não perder após a chamada da função
   

    tno * kvizinhoClose =  nearestNeighbor(pnode, target, 0, parv); //Método acima construído

    vetor[0].item = kvizinhoClose->item;

    tno * buscarSucessor = kvizinhoClose; //Não está funcionando com vetor, sendo que em tese deveria dar na mesma, eu acho

    tno * buscarPredecessor = kvizinhoClose;


    int i = 1;

    tno * sucessor = NULL;
    tno * predecessor = NULL;

    tno * pont = vetor;

    while(i < n){ 

    	/*printf("Entrou\n");
    	printf("%d  %d \n", i, n);*/

    	if(buscarSucessor != NULL){

    		 sucessor = treeSucessor(buscarSucessor); 
    		 
    		 
        }else{

        	 sucessor = NULL; 
        }

    	if(buscarPredecessor != NULL){

    		predecessor = treePredecessor(buscarPredecessor);

    		
    		
    	}else {

    		 predecessor = NULL;

    	}   


    	if(sucessor == NULL) //Problema de passar o vetor ao invés de kvizinhoClose
    		printf("Problemas\n");

    	vetor[i].item = (maisPerto(sucessor, predecessor, pont , parv))->item;

    	i = i + 1;
         
        buscarSucessor = treeSucessor(sucessor);

        buscarPredecessor = treePredecessor(predecessor);


    	
    }



   return vetor;

}

void destruir_arvore(tno *primeiroE){
        
        if(primeiroE == NULL)
        	return; //VOltar já está nulo

        destruir_arvore(primeiroE->esq);
		destruir_arvore(primeiroE->dir);

		free(primeiroE);
		primeiroE = NULL;

}

