#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kdtree.h"
#include <assert.h>

typedef struct _reg{
	int codIBGE;
	char nome[100];
	int codUF;
	char uf[3];
	int capital;
	float lat;
	float longt;
	char regiao[20];
	int codSiafi;
	int ddd;
	char fuso[33];
}reg;

float compara(const void *a, const void *b, int prof){
	int dimensao = (prof%2);

	if (dimensao==0){
		if ((*(reg*)a).longt < (*(reg*)b).longt){
			return -1;
		}
		else if ((*(reg*)a).longt > (*(reg*)b).longt){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		if ((*(reg*)a).lat < (*(reg*)b).lat){
			return -1;
		}
		else if ((*(reg*)a).lat > (*(reg*)b).lat){
			return 1;
		}
		else{
			return 0;
		}
	}
}

void ler_cidades(reg* preg, arv **parv){
	FILE *ptrarq; 
	//no* raiz = (*parv)->r;
	
	ptrarq = fopen("municipios.csv", "r");
	int result;
	char nome[100];

	if(ptrarq == NULL){
		printf("Problema ao abrir o arquivo municipios");
	}

	else{
		char indice[1000];
		char lixo;	
		int i = 0;	
		printf("%s\n", indice);
		preg = (reg*) malloc(sizeof(reg)); //total de cidades
		result = fscanf(ptrarq, " %[^\n]", indice);
		while((result = fscanf(ptrarq, "%d", &preg->codIBGE)) != EOF){
			result = fscanf(ptrarq, "%c", &lixo);
			reg *cidade = preg;
			printf("%d\n", cidade->codIBGE);
			printf("%c\n", lixo);

			result = fscanf(ptrarq, "%[^,]", nome);
			strcpy(cidade->nome, nome);
			printf("%s\n", cidade->nome);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%f", &cidade->lat);
			printf("%f\n", cidade->lat);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%f", &cidade->longt);
			printf("%f\n", cidade->longt);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%d", &cidade->capital);
			printf("%d\n", cidade->capital);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%d", &cidade->codUF);
			printf("%d\n", cidade->codUF);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%d", &cidade->codSiafi);
			printf("%d\n", cidade->codSiafi);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, "%d", &cidade->ddd);
			printf("%d\n", cidade->ddd);

			result = fscanf(ptrarq, "%c", &lixo);
			result = fscanf(ptrarq, " %[^\n]", cidade->fuso);
			printf("%s\n", cidade->fuso);

			insere(*parv, cidade);

			
		}

	}

    fclose(ptrarq);
    free(preg);

}

arv* teste_constroi(){
	
	arv* ptr;

	ptr = constroi(ptr);
	printf("aqui\n");
		

	assert(ptr->r == NULL); /*teste inicialização da árvore*/
	return ptr;
}

/*void teste_inserir(arv **parv, reg *preg, int n){
	no* raiz = (*parv)->r;
	reg* cidade;
	int i;
	for(i = 0; i < n; i++){
		cidade = &(preg[i]);
		insere(*parv, cidade);
		printf("i =%d\n", i);
	}


	/*reg *preg, *preg1, *preg2, *preg3;
	

	preg = (reg*) malloc(sizeof(reg));
	preg->lat = -12.9551;
	preg->longt = -60.8947;
	strcpy(preg->nome, "Corumbiara");
	assert(strcmp(preg->nome, "Corumbiara") == 0);
	insere(*parv, preg);
	assert(compara((*parv)->r->reg, preg, 0) == 0); 

	
	preg1 = (reg*) malloc(sizeof(reg));
	preg1->lat = -26.9155;
	preg1->longt = -49.0709;
	strcpy(preg1->nome, "Blumenau");
	insere((*parv), preg1);

	preg2 = (reg*) malloc(sizeof(reg));
	preg2->lat = -24.2868;
	preg2->longt = -53.8404;
	strcpy(preg2->nome, "Palotina");
	insere(*parv, preg2);

	preg3 = (reg*) malloc(sizeof(reg));
	preg3->lat = -4.88161;
	preg3->longt = -64.3953;
	strcpy(preg3->nome, "Canutama");
	insere(*parv, preg3);

	assert(raiz->esq->esq == NULL);
	assert(raiz->dir->esq == NULL);
	assert(compara(raiz->reg, preg, 0) == 0);
	assert(compara(raiz->dir->reg, preg2, 1) == -1);*/


void teste_def_sucessor(arv *parv){
	/*teste função defineSucessor*/
	no* p = defineSucessor(parv, parv->r);
	assert(compara(p->reg, parv->r->dir->reg, 1)==0);
	assert(compara(p->reg, parv->r->dir->reg, 0)==0);
}

void teste_def_predecessor(arv *parv){
	/*teste função definePredecessor*/
	no* p = definePredecessor(parv, parv->r);
	assert(compara(p->reg, parv->r->esq->reg, 1)==0);
	assert(compara(p->reg, parv->r->esq->reg, 0)==0);
}

void teste_destroi(arv **parv){
	(*parv)->r = destroi((*parv)->r);
	assert((*parv)->r == NULL);
}

int main(){
	reg *preg;
	no *noBusca;
	arv *parv;
	parv = teste_constroi();
	printf("aquiii\n");
	
	ler_cidades(preg, &parv);
	
	/*registro = (reg*)(parv->r->reg);
	preg = (reg*)(parv->r->esq->reg);

	printf("%d\n",registro->codIBGE);
	printf("%d\n",preg->codIBGE);*/
	float longCidade, latCidade;

	printf("Digite o código do IBGE da cidade para localizar seu vizinho próximo:\n");
	scanf("%f", &latCidade);
	scanf("%f", &longCidade);

	preg = (reg*) malloc(sizeof(reg));	
	preg->longt = longCidade;
	preg->lat = latCidade;

	noBusca = busca(parv, preg);
	//no* resultado = defineSucessor(parv, noBusca);

	/*reg* registro;
	registro = (reg*)(resultado->reg);
	printf("%s\n", registro->nome);


}*/
}
