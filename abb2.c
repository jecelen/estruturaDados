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
		printf("In %d ", p->chave);
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

	r = remove_no(r, 16);
	r = remove_no(r, 15);
	printf("aqui\n");
	r = remove_no(r, 7);
	printf("aqui2\n");
	r = remove_no(r, 10);
	printf("aqui3\n");
	
	r = remove_no(r, 20);
	r = remove_no(r, 4);

	/*for(int i = 0; i<11; i++){
		inserir_abb(&r, v[i]);
	}

	assert(r->chave == 10);
	assert(r->esq->chave == 7);
	assert(r->dir->chave == 15);
	assert(r->dir->dir->chave == 20);
	assert(r->esq->esq->chave == 5);
	assert(r->esq->dir->chave == 9);
	assert(r->esq->dir->dir == NULL);

	*/
	
	
	in_ordem(r);
	pre_ordem(r);
	pos_ordem(r);

	r = destroi(r);
	if(r == NULL){
	printf("arvore vazia\n");
}
	in_ordem(r);

	return 0;
	
}

/*void remove_no(no **r, int valor){
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

*/
