#include <stdio.h>
#include<stdlib.h>
#include <assert.h>
#include<string.h>
#include<math.h>
#include "k-vizinho.h"


//Parte dos municípios:

//codigo_ibge,nome,latitude,longitude,capital,codigo_uf,siafi_id,ddd,fuso_horario

typedef struct _municipios{
   float x;
   float y;
   char nome[300];
   float codigo;
   int capital;
   int codigo_uf;
   int siafi_id;
   int ddd;
   char fuso[200];

}cidade;

float compara1(const void *a, const void *b){
    return    (*(cidade *)a).x - (*(cidade *)b).x;
}

float compara2(const void *a, const void *b){
	return (*(cidade *)a).y - (*(cidade *)b).y;
}


cidade * aloca_reg(float x, float y, char *nome, float codigo, int capital, int codigo_uf, int siafi_id, int ddd, char *fuso){
    cidade * pitem;
    pitem = malloc(sizeof(cidade));
    pitem->x = x;
    pitem->y = y;
    strcpy(pitem->nome, nome);
    pitem->codigo = codigo;
    pitem->capital = capital;
    pitem->codigo_uf = codigo_uf;
    pitem->siafi_id = siafi_id;
    pitem->ddd = ddd;
    strcpy(pitem->fuso, fuso);
    return pitem;
}


//Parte dos Fast-Food-Restaurants:

//number,address,categories,city,country,latitude,longitude,name,postalCode,province,websites



typedef struct _fastFoodRestaurant{
   float x;
   float y;
   int numeroCSV;
   char address[300];
   char categories[300];
   char city[300];
   char country[300];
   char name[300];
   int postalCode;
   char province[3];
   char websites[10000];
  

}restaurant;

float comparaR1(const void *a, const void *b){
    return    (*(restaurant *)a).x - (*(restaurant *)b).x;
}

float comparaR2(const void *a, const void *b){
    return (*(restaurant *)a).y - (*(restaurant *)b).y;
}

//number,address,categories,city,country,latitude,longitude,name,postalCode,province,websites

restaurant * aloca_reg_rest(float x, float y, int numeroCSV, char *address,  char *categories, char *city, char *country, char *name, int postalCode, char *province, char *websites){

    restaurant * ritem;
    ritem = malloc(sizeof(restaurant));
    ritem->x = x;
    ritem->y = y;
    ritem->numeroCSV = numeroCSV;
    strcpy(ritem->address, address);
    strcpy(ritem->categories, categories);
    strcpy(ritem->city, city);
    strcpy(ritem->country, country);
    strcpy(ritem->name, name);
    ritem->postalCode = postalCode;
    strcpy(ritem->province, province);
    strcpy(ritem->websites, websites);

    return ritem;
}



void  municipios(tarv *arv){
    
    //cidade * p1;
    //tno * pnode;
    abb_construir(arv,compara1, compara2);

    assert(arv->raiz == NULL);

     FILE *arq1;

           arq1 = fopen("cidades.txt", "r");

           if(arq1 == NULL){

                printf("Erro na abertura do arquivo\n");

           }else{      
                       char lixo[200]; //Aqui não
                       int numero_lixo;
                       float x = 0;
                       float y = 0;
                       char nome[300];
                       float codigo;
                       int capital;
                       int codigo_uf;
                       int siafi_id;
                       int ddd;
                       char fuso[200];

              fscanf(arq1, " %[^\n]", lixo  );

             printf("%s \n", lixo);


                while(feof (arq1) == 0){

                    fscanf(arq1, "%f[^,]", &codigo  );

                    fscanf(arq1, " %[^0-9]", nome  );

                    fscanf(arq1, " %f[^,]", &x );

                    fscanf(arq1, " ,%f[^,]", &y );

                    fscanf(arq1, " ,%d[^,]", &capital );

                    fscanf(arq1, " ,%d[^,]", &codigo_uf );

                    fscanf(arq1, " ,%d[^,]", &siafi_id );

                    fscanf(arq1, " ,%d[^,]", &ddd );

                    fscanf(arq1, " %[^\n]", fuso );

                    if(y < 0)
                       y = y * -1;

                    if(x < 0)
                        x = x * -1;

                    abb_inserir(arv, aloca_reg(x, y, nome, codigo, capital, codigo_uf, siafi_id, ddd, fuso ));

                    //printf("%f --%s-- numeero: %f (%f) %d %d %d %d --%s-- \n", codigo, nome, x, y,capital, codigo_uf, siafi_id, ddd, fuso);

               }

        }

   

}


void fast_food(tarv *arv2){

    
    abb_construir(arv2,comparaR1, comparaR2);


     FILE *arq2;

           arq2 = fopen("Fast_Food_Restaurants_US.csv", "r");

           if(arq2 == NULL){

                printf("Erro na abertura do arquivo\n");

           }else{      
                       char cabecalho[200];
                       char descarta;
                       float x;
                       float y;
                       int numeroCSV;
                       char address[300];
                       char categories[300];
                       char city[300];
                       char country[300];
                       char name[300];
                       int postalCode;
                       char province[3];
                       char websites[10000];

               fscanf(arq2, " %[^\n]", cabecalho  );

               printf("%s \n", cabecalho);

    


                while(feof (arq2) == 0){

                    fscanf(arq2, "%d", &numeroCSV   );

                    //printf("%d -> numero\n", numeroCSV);

                     fscanf(arq2, "%c", &descarta);

                    fscanf(arq2, " %[^,]", address );

                    //printf("%s -> address\n", address);

                     fscanf(arq2, "%c", &descarta);

                    fscanf(arq2, " %[^,]", categories );

                    //printf("%s -> categories\n", categories);

                     fscanf(arq2, "%c", &descarta);

                    fscanf(arq2, " %[^,]", city );

                    //printf("%s -> city\n", city);
                    
                     fscanf(arq2, "%c", &descarta);

                    fscanf(arq2, " %[^,]", country );

                    //printf("%s -> country\n", country);

                     fscanf(arq2, "%c", &descarta);

                    fscanf(arq2, " %f", &x );

                    //printf("%f -> lat\n", x);

                     fscanf(arq2, "%c", &descarta);

                    fscanf(arq2, " %f", &y );

                    //printf("%f -> long\n", y);

                     fscanf(arq2, "%c", &descarta);

                    fscanf(arq2, " %[^,]", name );

                    //printf("%s -> name\n", name);

                     fscanf(arq2, "%c", &descarta);

                    fscanf(arq2, " %d", &postalCode );

                    //printf("%d -> postalCode\n", postalCode);

                     fscanf(arq2, "%c", &descarta);

                    fscanf(arq2, " %[^,]", province );

                    //printf("%s -> province\n", province);

                     fscanf(arq2, "%c", &descarta);

                    fscanf(arq2, " %[^\n]", websites );

                    //printf("%s -> websites\n", websites);

                    if(y < 0)
                       y = y * -1;

                    if(x < 0)
                        x = x * -1;

                    abb_inserir(arv2, aloca_reg_rest(x, y, numeroCSV, address, categories, city, country, name, postalCode, province, websites));


                    //printf("%d - %s %s %s %s %s %f %f %s %d %s %s \n", numeroCSV, address, categories, city, country, x, y, name, postalCode, province, websites  );

               }

        }


}


void menu(){

    printf("\nProblema 1 - Cidade mais proxima\n");
    printf("Problema 2 - 5 fast-food mais proximos\n");
    printf("Problema 3 - Retornar N fast-food mais proximos\n");
    printf("0 - Encerrar programa\n");
}

void NearestCidade(tarv *arv, float x, float y){

        int TrueX =0;
        int TrueY =0;


        if(y < 0){

          TrueX = 1;

          y = y * -1;
        }

        if(x < 0){

          TrueY = 1;

          x = x * -1;
        }

        

        tno * buscar;

        buscar = malloc(sizeof(tno));
        buscar->item = NULL;
        buscar->esq = NULL;
        buscar->dir = NULL;
        buscar->p = NULL;

        buscar->item = aloca_reg(x,y,"Qualquer um",5200050,0,52,1050,62,"America/Sao_Paulo");

        tno * maisProximo = NULL;

        maisProximo = nearestNeighbor(arv->raiz, buscar, 0, arv); 

        //float x, float y, char *nome, float codigo, int capital, int codigo_uf, int siafi_id, int ddd, char *fuso

        //Código IBGE, Nome do Município, Código UF, UF Estado, Capital, Latitude, Longitude, Região, Código Siafi, DDD e Fuso Horário

        if(TrueY==1)
            (((cidade*)maisProximo->item)->x) = (((cidade*)maisProximo->item)->x) *-1;

        if(TrueX==1)
            (((cidade*)maisProximo->item)->y) = (((cidade*)maisProximo->item)->y) *-1;

        printf("%f %s %d %d %.4f %.4f %d %d %s\n", (((cidade*)maisProximo->item)->codigo), (((cidade*)maisProximo->item)->nome), (((cidade*)maisProximo->item)->codigo_uf),
        (((cidade*)maisProximo->item)->capital), (((cidade*)maisProximo->item)->x), (((cidade*)maisProximo->item)->y), 
        (((cidade*)maisProximo->item)->siafi_id), (((cidade*)maisProximo->item)->ddd), (((cidade*)maisProximo->item)->fuso)  );




}



void buscaNClose(tarv *arv2, int n, float x, float y){


        if(y < 0){

          y = y * -1;
        }

        if(x < 0){

          x = x * -1;
        }


        tno * buscar2 = NULL;

        buscar2 = malloc(sizeof(tno));
        buscar2->item = NULL;
        buscar2->esq = NULL;
        buscar2->dir = NULL;
        buscar2->p = NULL;

        buscar2->item = aloca_reg_rest(x, y, 0, "any", "noop", "br", "Brazil", "ñao tem", 8, "LA", "lalalala.com");

         tno * vetorNvizinhosClose2 = NULL; 

         vetorNvizinhosClose2 = buscaNVizinhos(buscar2, arv2, n, vetorNvizinhosClose2);




         //address,categories,city,country,latitude,longitude,name,postalCode,province

         for(int i = 0; i < n; i++ ){

            (((restaurant*)vetorNvizinhosClose2[i].item)->y) = (((restaurant*)vetorNvizinhosClose2[i].item)->y) * -1;

             printf( "%d - %s %s %s %s %f %f %s %d %s %s\n\n", i+1 ,(((restaurant*)vetorNvizinhosClose2[i].item)->address), 
                (((restaurant*)vetorNvizinhosClose2[i].item)->categories), (((restaurant*)vetorNvizinhosClose2[i].item)->city), 
                (((restaurant*)vetorNvizinhosClose2[i].item)->country), (((restaurant*)vetorNvizinhosClose2[i].item)->x), 
                (((restaurant*)vetorNvizinhosClose2[i].item)->y), (((restaurant*)vetorNvizinhosClose2[i].item)->name), 
                (((restaurant*)vetorNvizinhosClose2[i].item)->postalCode), (((restaurant*)vetorNvizinhosClose2[i].item)->province), 
                (((restaurant*)vetorNvizinhosClose2[i].item)->websites) );
         }
}



int main(){

    tarv arv;

    tarv arv2;

	municipios(&arv);
    fast_food(&arv2);

    int op;

    menu();

    scanf(" %d", &op);

    do{

        if(op == 1){

            float x,y;

            printf("Digite a latitude: ");
            scanf(" %f", &x);
            printf("Digite a longitude: ");
             scanf(" %f", &y);

            printf("\n");

            NearestCidade(&arv, x, y);




        } else if (op == 2){

            float x,y;

            printf("Digite a latitude: ");
            scanf(" %f", &x);
            printf("Digite a longitude: ");
             scanf(" %f", &y);

            printf("\n");

            buscaNClose(&arv2, 5,x,y);




        }else if(op == 3){

            int qtd;

            float x,y;


            printf("Digite a latitude: ");
             scanf(" %f", &x);
            printf("Digite a longitude: ");
             scanf(" %f", &y);

            printf("Digite a quantidade de vizinhos próximos requeridos: ");
             scanf(" %d", &qtd);

            
            printf("\n");
            buscaNClose(&arv2, qtd,x,y);



        }else {

           printf("Desculpe, a opcao digitade foge do escopo\n");
        }

        menu();

        scanf(" %d", &op);


    }while(op != 0);

    destruir_arvore(arv.raiz);
    destruir_arvore(arv2.raiz);

	return 0;
}
