#include <stdio.h>
#include <assert.h>

int pai(int pos){
	if(pos == 0){
		return pos;
	}
	else{
		return (pos-1)/2;
	}
}

int filho_dir(int pos){
	return 2*(pos+1);
}

int filho_esq(int pos){
	return (2*(pos+1))-1;
}

void troca(int *a, int *b){
	int aux = *a;
	*a = *b;
	*b = aux;
}

void desce(int v[], int n, int i){
	int dir, esq, maior;
	dir = filho_dir(i);
	esq = filho_esq(i);

	if(esq<n && v[esq] > v[i]){
		maior = esq;
	}
	else{
		maior = i;
	}
	if(dir<n && v[dir] > v[maior]){
		maior = dir;
	}

	if(maior != i){
		troca(&v[i], &v[maior]);
		desce(v, n, maior);
	}
}


void constroi_max_heap(int v[], int n){
	int i = n;
	for(i = pai(i); i>=0; i--){
		desce(v, n, i);
	}
}

void sobe(int v[], int pos){
	int p = pai(pos);
	while(v[p]<v[pos]){
		troca(&v[pos], &v[p]);
		pos = p;
		p = pai(pos); 
	}

}

void insere_heap(int v[], int *n, int valor){
	*n = *n+1;
	v[*n-1] = valor;
	sobe(v, *n-1);
}

void extrai_max(int v[], int *n, int *max){
	*max = v[0];
	int ultimo = *n-1;
	troca(&v[0], &v[ultimo]);
	desce(v, ultimo, 0);
	*n = *n-1;
	
}

void altera_prioridade(int v[], int n, int pos, int valor){
	if(v[pos]>valor){
		v[pos] = valor;
		desce(v, n, pos);
	}
	else{
		v[pos] = valor;
		sobe(v, pos);
	}
}

void heapsort(int v[], int n){
	constroi_max_heap(v, n);
	int max = n;
	int desc;
	for(int i = 0; i<max; i++){
		extrai_max(v, &n, &desc);
	}
}

int main(){

	int v[] = {1, 5, 7, 6, 8, 9, 10, 12, 13, 15, 11, 14};
	int n = 12;
	int max;

	constroi_max_heap(v, n);

	assert(v[2] == 14);
	assert(v[0] == 15);
	assert(v[1] == 13);
	assert(v[3] == 12);
	assert(v[4] == 11);
	assert(v[5] == 9);
	assert(v[6] == 10);
	assert(v[7] == 1);
	assert(v[8] == 6);
	assert(v[9] == 8);
	assert(v[10] == 5);
	assert(v[11] == 7);

	insere_heap(v, &n, 20);
	insere_heap(v, &n, 3);
	insere_heap(v, &n, 8);
	
	assert(v[0] == 20);
	assert(v[1] == 13);
	assert(v[2] == 15);
	assert(v[3] == 12);
	assert(v[4] == 11);
	assert(v[5] == 14);
	assert(v[6] == 10);
	assert(v[7] == 1);
	assert(v[8] == 6);
	assert(v[9] == 8);
	assert(v[10] == 5);
	assert(v[11] == 7);
	assert(v[12] == 9);
	assert(v[13] == 3);
	assert(v[14] == 8);

	extrai_max(v, &n, &max);
	extrai_max(v, &n, &max);
	extrai_max(v, &n, &max);
	

	assert(v[0] == 13);
	assert(v[1] == 12);
	assert(v[2] == 10);
	assert(v[3] == 8);
	assert(v[4] == 11);
	assert(v[5] == 9);
	assert(v[6] == 3);
	assert(v[7] == 1);
	assert(v[8] == 6);
	assert(v[9] == 8);
	assert(v[10] == 5);
	assert(v[11] == 7);

	altera_prioridade(v, n, 1, 2);
	altera_prioridade(v, n, 4, 100);

	assert(v[0] == 100);
	assert(v[1] == 13);
	assert(v[2] == 10);
	assert(v[3] == 8);
	assert(v[4] == 11);
	assert(v[5] == 9);
	assert(v[6] == 3);
	assert(v[7] == 1);
	assert(v[8] == 6);
	assert(v[9] == 2);
	assert(v[10] == 5);
	assert(v[11] == 7);

	heapsort(v, n);
	printf("%d\n", v[0]);
	printf("%d\n", v[1]);
	printf("%d\n", v[2]);
	printf("%d\n", v[3]);
	printf("%d\n", v[4]);
	printf("%d\n", v[5]);
	printf("%d\n", v[6]);
	printf("%d\n", v[7]);
	printf("%d\n", v[8]);
	printf("%d\n", v[9]);
	printf("%d\n", v[10]);
	printf("%d\n", v[11]);
}