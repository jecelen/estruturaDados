#include <stdio.h>
#include <assert.h>

int pai(int i){
	if(i==0){
		return i;
	}
	else{
		int result = (i-1)/2;
		return result;
	}
}

int filho_esq(int i){
	return ((2*(i+1))-1);
}

int filho_dir(int i){
	return (2*(i+1));
}

void troca(int *v, int i, int maior){
	int aux = v[i];
	v[i] = v[maior];
	v[maior] = aux;
}

void desce(int n, int *v, int i){
	int esq, dir, maior;

	esq = filho_esq(i);
	dir = filho_dir(i);

	if(esq < n && v[esq] > v[i]){
		maior = esq;
	}
	else{
		maior = i;
	}
	if(dir < n && v[dir] > v[maior]){
		maior = dir;
	}
	if(maior != i){
		troca(v, i, maior);
		desce(n, v, maior);

	}

}

void constroi_max_heap(int n, int *v){
	for(int i = pai(n-1); i>=0; i--){
		desce(n, v, i);
	}

}

void sobe(int v[], int i){
	
	int p = pai(i);

	while(v[p] < v[i]){
		troca(v, i, p);
		i = pai(i);
		p = pai(i);
	}
}

void inserir(int a, int *n, int v[]){
	*n = *n +1;
	v[*n-1] = a;
	sobe(v, *n-1); 
}

int extrai_max(int v[], int *n){
	int max = v[0];
	v[0] = v[*n-1];
	*n = *n-1;
	desce(*n, v, 0);
	return max;
}

void altera_prioridade(int v[], int n, int pos, int valor){
	if(pos<n){
		if(v[pos]>valor){
			v[pos] = valor;
			desce(n, v, pos);
		}
		else{
			v[pos] = valor;
			sobe(v, pos);
		}
	}
}

void heap_sort(int v[],int n){
    int max = n;
    constroi_max_heap(n,v);
    for (int i=0;i<max;i++){
        extrai_max(v,&n);
    }
}

int main(){
	int v[] = {1, 5, 7, 6, 8, 9, 10, 12, 13, 15, 11, 14};
	int n = 12;

	constroi_max_heap(n, v);

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

	inserir(20, &n, v);
	inserir(3, &n, v);
	inserir(8, &n, v);

	assert(v[2] == 15);
	assert(v[0] == 20);
	assert(v[1] == 13);
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

	int max = extrai_max(v, &n);
	max = extrai_max(v, &n);
	max = extrai_max(v, &n);

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

	heap_sort(v, n);

}