#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int cmpfunc(const void * a, const void * b) {
	return (*(int*)a - *(int*)b);
}


int main(void) {
	int i,j;
	int razlika = 0, N = 0;
	int count = 0;
	
	scanf("%d %d", &N, &razlika);

	int *lista = malloc(N * sizeof(int));
	
	for (i = 0; i < N; i++) {
		scanf("%d", &lista[i]);
	}
	
	/*for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (i == j) continue;
			if (lista[i] - lista[j] == razlika) count++;
		}
	}*/
	int *broj=NULL;
	int broj_trazim;
	qsort(lista, N, sizeof(int), cmpfunc);
	for (i = 0; i < N; i++) {
		broj_trazim = *(lista + i) - razlika;
		broj=bsearch(&broj_trazim, lista, N, sizeof(int), cmpfunc);
		if (broj!=NULL)count++;
	}

	printf("\n %d", count);
	free(lista);

	getchar();
	getchar();

}