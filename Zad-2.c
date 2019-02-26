#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main(void) {
	int i,j;
	int razlika = 0, N = 0;
	int count = 0;
	
	scanf("%d %d", &N, &razlika);

	int *lista = malloc(N * sizeof(int));
	
	for (i = 0; i < N; i++) {
		scanf("%d", &lista[i]);
	}
	
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (i == j) continue;
			if (lista[i] - lista[j] == razlika) count++;
		}
	}

	printf("\n %d", count);
	free(lista);

	getchar();
	getchar();

}
