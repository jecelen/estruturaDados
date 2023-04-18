#include <stdio.h>
#include <stdlib.h>
#include<assert.h>


typedef struct celula
{
	int chave;
	struct celula *dir;
	struct celula *esq;
}no;

int compara(int a, int b){
	return(a-b);

}

void inserir_no(no** r, int n){
	no *p, *q, *novo;
	novo = (no*) malloc(sizeof(no));
	novo->chave = n;
	novo->esq = NULL;
	novo->dir = NULL;


	p = *r;
	if(p == NULL){
		*r = novo;
	}
	else{
		while(p != NULL){
			q = p;
			if(compara(novo->chave, p->chave) < 0){
				p = p->esq;
			}
			else{
				p = p->dir;
			}
		}
		if(compara(novo->chave, q->chave)< 0){
			q->esq = novo;
			}
		else{
			q->dir = novo;
		}
	}
}

void teste(no *r){

	assert(r->chave == 5);
	assert(r->esq->chave == 3);
	assert(r->dir->dir == NULL);
	assert(r->dir->esq->chave == 7);
	assert(r->esq->esq == NULL);
	assert(r->esq->dir->chave == 4);
}



int main(){
	no *r;
	r = NULL;
	
	inserir_no(&r, 5);
	inserir_no(&r, 8);
	inserir_no(&r, 3);
	inserir_no(&r, 7);
	inserir_no(&r, 4);

	teste(r);
	
}
