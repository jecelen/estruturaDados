#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef int treg;

typedef struct _node
{
	treg chave;
	struct _node *dir;
	struct _node *esq;
}no;

no* inserir_abb(no *r, no *novo){
    if (r == NULL){
    	return novo;
    }
    if (r->chave > novo->chave){
       r->esq = inserir_abb(r->esq, novo);
    }
    else{
       r->dir = inserir_abb(r->dir, novo);
    }

    return r;
}
no* acha_sucessor(no* suc){
	while(suc->esq != NULL){
		suc = suc->esq;
	}
	return suc;
}
no* remove_no(no *r, int valor){
	no* aux;
	if(r==NULL){
		return NULL;
	}
	else if(valor < r->chave){
		r->esq = remove_no(r->esq, valor);
	}
	else if(valor > r->chave){
		r->dir = remove_no(r->dir, valor);
	}
	else{
		if(r->esq == NULL && r->dir == NULL){
			free(r);
			r = NULL;
			return r;
		}
		else if(r->esq == NULL && r->dir !=NULL){
			aux = r->dir;
			free(r);
			return aux;
			
		}
		else if(r-> esq != NULL && r->dir == NULL){
			aux = r->esq;
			free(r);
			return aux;
		}
		else{
			aux = acha_sucessor(r->dir);
			r->chave = aux->chave;
			r->dir = remove_no(r->dir, aux->chave);
		}
	}
	return r;
}

void in_ordem(no *r){
	no *p = r;
	if(p!=NULL){
		in_ordem(p->esq);
		printf("%d, ", p->chave);
		in_ordem(p->dir);
	}
}

void pre_ordem(no *r){
	no *p = r;
	if(p!=NULL){
		printf("%d, ", p->chave);
		pre_ordem(p->esq);
		pre_ordem(p->dir);
	}
}

void pos_ordem(no *r){
	no *p = r;
	if(p!=NULL){
		pos_ordem(p->esq);
		pos_ordem(p->dir);
		printf("%d, ", p->chave);
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
int main(){

	no *r; /*raiz*/
	r = NULL;
	int v[11] = {10, 7, 15, 5, 9, 20, 18, 16, 19, 4, 3};
	no *novo;

	for(int i=0; i<11;i++){
		novo = (no*) malloc(sizeof(no));
		novo->chave = v[i];
		novo->dir = NULL;
		novo->esq = NULL;
		printf("%d\n", novo->chave);
		r = inserir_abb(r, novo);
		}

	assert(r->chave == 10);
	assert(r->esq->chave == 7);
	assert(r->dir->chave == 15);
	assert(r->dir->dir->chave == 20);
	assert(r->esq->esq->chave == 5);
	assert(r->esq->dir->chave == 9);
	assert(r->esq->dir->dir == NULL);

	printf("árvore original após inserções:\n");
	in_ordem(r);

	r = remove_no(r, 16);
	r = remove_no(r, 15);
	r = remove_no(r, 7);
	r = remove_no(r, 10);
	r = remove_no(r, 20);
	r = remove_no(r, 4);	
	
	printf("\n\nárvore após remoções:\n");
	in_ordem(r);

	printf("\n\npré ordem:\n");
	pre_ordem(r);
	printf("\n\npos pordem:\n");
	pos_ordem(r);

	r = destroi(r);

	if(r == NULL){
	printf("\n\narvore vazia após destruição com pos ordem\n");
	}

	return 0;
	
}
