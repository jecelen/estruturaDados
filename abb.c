#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct abb
{
	int chave;
	struct abb *dir;
	struct abb *esq;
}no;

void inserir_abb(no **r, int valor){
	no *novo, *p1, *p2;
	novo = (no*) malloc(sizeof(no));
	novo->chave = valor;
	novo->dir = NULL;
	novo ->esq = NULL;

	p1 = *r;
	if(p1 == NULL){
		*r = novo;
		printf("raiz %d\n", novo->chave);
		
	}
	else{
		while(p1!=NULL){
			p2 = p1;
			if(novo->chave > p1->chave){
				p1 = p1->dir;
			}
			else{
				p1=p1->esq;
			}
		}
		if(novo->chave > p2->chave){
			p2->dir = novo;
			printf("dir: %d\n", p2->dir->chave);
		}
		else{
			p2->esq = novo;
			printf("esq: %d\n", p2->esq->chave);
		}
	}
}

void in_ordem(no *r){
	no *p = r;
	if(p!=NULL){
		in_ordem(p->esq);
		printf("%d ", p->chave);
		in_ordem(p->dir);
	}
}

void pre_ordem(no *r){
	no *p = r;
	if(p!=NULL){
		printf("%d ", p->chave);
		pre_ordem(p->esq);
		pre_ordem(p->dir);
	}
}

void pos_ordem(no *r){
	no *p = r;
	if(p!=NULL){
		pos_ordem(p->esq);
		pos_ordem(p->dir);
		printf("%d ", p->chave);
	}
}

void remove_no(no **r, int valor){
	no *p, *pai;
	p = *r;

	while(p != NULL && p->chave != valor){
		pai = p;
		if(p->chave > valor){
			p = p->esq;
		}
		else{
			p = p->dir;
		}
		printf("%d ", p->chave);
	}
	if(p->chave == valor){
		if(p->dir == NULL && p->esq == NULL){
			if(pai->dir->chave == valor){
				pai->dir = NULL;
				free(p);
		}
		else{
			pai->esq = NULL;
			free(p);
		}
	}
}
		else if(p->dir == NULL && p->esq != NULL){
			if(pai->esq->chave == valor){
				pai->esq = p->dir;
			}
			else{
				pai->dir = p->dir;
			}
		free(p);

		}

		else if(p->esq == NULL && p->dir != NULL){
			if(pai->esq->chave == valor){
				pai->esq = p->dir;
			}
			else{
				pai->dir = p->dir;
			}
		free(p);

		}

		else{
			no *aux, *pai2, *suc;
			aux = p->dir;
			suc = aux;
			while(aux != NULL){
				pai2 = suc;
				suc = aux;
				aux = aux->esq;
			}

			aux = suc;
			if(pai->esq->chave == valor){
				pai->esq = suc;
			}
			else{
				pai->dir = suc;
			}
			suc->dir = p->dir;
			suc->esq = p->esq;

			if(pai2->dir->chave==aux->chave){
				pai2->dir=aux->dir;
				}
			else{
				pai2->esq = aux->dir;
			}

			free(p);
			free(aux);


		}
	}

	


int main(){

	no *r; /*raiz*/
	r = NULL;
	int v[11] = {10, 7, 15, 5, 9, 20, 18, 16, 19, 4, 3};

	for(int i = 0; i<11; i++){
		inserir_abb(&r, v[i]);
	}

	assert(r->chave == 10);
	assert(r->esq->chave == 7);
	assert(r->dir->chave == 15);
	assert(r->dir->dir->chave == 20);
	assert(r->esq->esq->chave == 5);
	assert(r->esq->dir->chave == 9);
	assert(r->esq->dir->dir == NULL);

	remove_no(&r, 16);
	remove_no(&r, 7);
	remove_no(&r, 10);
	remove_no(&r, 15);
	remove_no(&r, 20);
	remove_no(&r, 4);
	
	
	in_ordem(r);
	pre_ordem(r);
	pos_ordem(r);

	
	
}
