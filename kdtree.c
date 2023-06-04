#include <stdio.h>
#include <stdlib.h>
#include "kdtree.h"

void insere(arv *parv, void *preg){
	no *p, *pt_pai;
	no **ptr;
	int prof = 0;
	ptr = &(parv->r);
	p = *ptr;
	pt_pai = NULL;

	while(p!=NULL){
		pt_pai = p;

		if(compara(p->reg, preg, prof) > 0){
			ptr = &(p->esq);
			p = *ptr;
		}

		else{
			ptr = &(p->dir);
			p = *ptr;
		}

		prof+=1;
	}

	if ((*ptr) == NULL){
		(*ptr) = (no*) malloc(sizeof(no));
		(*ptr)->reg = preg;
		(*ptr)->pai = pt_pai;
		(*ptr)->esq = NULL;
		(*ptr)->dir = NULL;
	}
}

void constroi(arv **parv){
    (*parv) = malloc(sizeof(arv));
	(*parv)->r = NULL;
}

no* busca(arv *parv, void *preg){
	no* p = parv->r;
	int prof = 0;
	while (p!=NULL && (compara(p->reg, preg, prof)!=0)){
		if(compara(p->reg, preg, prof) > 0){
			p = p->esq;
			printf("esq\n");
		}
		else{
			p = p->dir;
			printf("dir\n");
		}
		prof++;
	}
	return p;
}

no* defineSucessor(no *ptr){
	if(ptr->dir!=NULL){
		ptr = ptr->dir;
		while(ptr->esq!=NULL){
			ptr = ptr->esq;
		}
		return ptr;
	}
	else{
		no *q;
		q = ptr->pai;
		while(q!=NULL && ptr == q->dir){
			ptr = q;
			q = q->pai;
		}
		return q;
	}
}

no* definePredecessor(no *ptr){
	if(ptr->esq!=NULL){
		ptr = ptr->esq;
		while(ptr->dir!=NULL){
			ptr = ptr->dir;
		}
		return ptr;
	}
	else{
		no *q;
		q = ptr->pai;
		while(q!=NULL && ptr == q->esq){
			ptr = q;
			q = q->pai;
		}
		return q;
	}
}

no* destroi(no *r){
	if(r!=NULL){
		destroi(r->esq);
		destroi(r->dir);
		free(r);
	}
	return NULL;
}


