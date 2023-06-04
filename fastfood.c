#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kdtree.h"
#include <assert.h>

typedef struct _fastFood{
	int codIBGE;
	char adress[200];
	char categ[200];
	char city[100];
	char contry[3];
	float lat;
	float longt;
	char nome[100];
	int postalCode;
	char province[3];
	char site[1000];
}regff;

float compara(const void *a, const void *b, int prof){
	int dimensao = (prof%2);

	if (dimensao==0){
		if ((*(regff*)a).longt < (*(regff*)b).longt){
			return -1;
		}
		else if ((*(regff*)a).longt > (*(regff*)b).longt){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		if ((*(regff*)a).lat < (*(regff*)b).lat){
			return -1;
		}
		else if ((*(regff*)a).lat > (*(regff*)b).lat){
			return 1;
		}
		else{
			return 0;
		}
	}
}

void lerFastFood(regff* preg, arv **parv){
	FILE *ptrarq;

	ptrarq = fopen("Fast_Food_Restaurants_US.csv", "r");
	int result;
	char endereco[200];

	if(ptrarq == NULL){
		printf("Problema ao abrir o arquivo Fast_Food_Restaurants_US");
	}

	else{
		char indice[1000];
		char lixo;
		int i;
		printf("%s\n", indice);
		preg = (regff*) malloc(sizeof(regff)*10000); //total de ff
		result = fscanf(ptrarq, " %[^\n]", indice);
		while((result = fscanf(ptrarq, "%d", &i)) != EOF){
			result = fscanf(ptrarq, "%c", &lixo);
			regff *ff;
			ff = &(preg[i]);

			result = fscanf(ptrarq, "%[^,]", endereco);
			strcpy(ff->adress, endereco);
			printf("%s\n", ff->adress);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%[^,]", &ff->categ);
			printf("%f\n", ff->categ);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%[^,]", &ff->city);
			printf("%f\n", ff->city);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%s", &ff->contry);
			printf("%d\n", ff->contry);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%f", &ff->lat);
			printf("%d\n", ff->lat);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%f", &ff->longt);
			printf("%d\n", ff->longt);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%[^,]", &ff->nome);
			printf("%d\n", ff->nome);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%d", &ff->postalCode);
			printf("%d\n", ff->postalCode);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%s", &ff->province);
			printf("%d\n", ff->province);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, " %[^\n]", ff->site);
			printf("%s\n", ff->site);

			insere(*parv, ff);
			regff* registro = (regff*)((*parv)->r->reg);
            printf("%s", registro->nome);
            i++;
		}

	}

    fclose(ptrarq);

}


void teste_def_sucessor(arv *parv){
	no* p = defineSucessor(parv->r);
	assert(compara(p->reg, parv->r->dir->reg, 1)==0);
	assert(compara(p->reg, parv->r->dir->reg, 0)==0);
}

void teste_def_predecessor(arv *ptr_arv){
	no* p = definePredecessor(ptr_arv->r);
	assert(compara(p->reg, ptr_arv->r->esq->reg, 1)==0);
	assert(compara(p->reg, ptr_arv->r->esq->reg, 0)==0);
}

void teste_destroi(arv **ptr_arv){
	(*ptr_arv)->r = destroi((*ptr_arv)->r);
	assert((*ptr_arv)->r == NULL);
}

void encontraVizinhos(arv *ptr_arv){
	float longff, latff;

	printf("Digite a latitude do município para localizar seu vizinho próximo:\n");
	scanf("%f", &latff);
	printf("Digite a longitude do município para localizar seu vizinho próximo:\n");
	scanf("%f", &longff);

	preg = (regff*) malloc(sizeof(regff));
	preg->longt = longCidade;
	preg->lat = latCidade;

	noBusca = busca(parv, preg);
	no* resultado = defineSucessor(noBusca);

	regff* registro;
	registro = (regff*)(resultado->reg);
	printf("%s\n", registro->nome);

}

void fastFoodControler(){
	regff *preg;
	arv *ptr_arv;
	no* noBusca;
	constroi(&parv);
	preg = NULL;
	//noBusca = parv->r;
	lerFastFood(preg, &ptr_arv);

	encontraVizinhos(ptr_arv);


}
