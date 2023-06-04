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
		preg = (reg*) malloc(sizeof(reg)*5570); //total de cidades
		result = fscanf(ptrarq, " %[^\n]", indice);
		while((result = fscanf(ptrarq, "%d", &preg[i].codIBGE)) != EOF){
			result = fscanf(ptrarq, "%c", &lixo);
			reg *cidade;
			cidade = &(preg[i]);
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
			reg* registro = (reg*)((*parv)->r->reg);
            printf("%s", registro->nome);
            i++;
		}

	}

    fclose(ptrarq);

}

/*arv* teste_constroi(){

	arv* ptr;
	ptr = NULL;
	ptr = constroi(ptr);
	printf("aqui\n");


	assert(ptr->r == NULL); teste inicialização da árvore
	return ptr;
}*/


void teste_def_sucessor(arv *parv){
	/*teste função defineSucessor*/
	no* p = defineSucessor(parv->r);
	assert(compara(p->reg, parv->r->dir->reg, 1)==0);
	assert(compara(p->reg, parv->r->dir->reg, 0)==0);
}

void teste_def_predecessor(arv *parv){
	/*teste função definePredecessor*/
	no* p = definePredecessor(parv->r);
	assert(compara(p->reg, parv->r->esq->reg, 1)==0);
	assert(compara(p->reg, parv->r->esq->reg, 0)==0);
}

void teste_destroi(arv **parv){
	(*parv)->r = destroi((*parv)->r);
	assert((*parv)->r == NULL);
}

void cidadesControler(){
	reg *preg;
	arv *parv;
	preg = NULL;
	constroi(&parv);
	no* noBusca;
	noBusca = parv->r;
	ler_cidades(preg, &parv);

	float longCidade, latCidade;

	printf("Digite a latitude do município para localizar seu vizinho próximo:\n");
	scanf("%f", &latCidade);
	printf("Digite a longitude do município para localizar seu vizinho próximo:\n");
	scanf("%f", &longCidade);

	preg = (reg*) malloc(sizeof(reg));
	preg->longt = longCidade;
	preg->lat = latCidade;

	noBusca = busca(parv, preg);
	no* resultado = defineSucessor(noBusca);

	reg* registro;
	registro = (reg*)(resultado->reg);
	printf("%s\n", registro->nome);


}
