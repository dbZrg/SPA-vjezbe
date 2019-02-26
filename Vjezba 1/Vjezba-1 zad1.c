#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>

int main(void) {
	int A = 0, B = 0,N = 0;
	int  i, j;
	while (N < 2 || N > 100) {
		printf("Upisite N (2<N<100): ");
		scanf("%d", &N);
	}
	

	srand(time(NULL));
	int *matrica = malloc(N*N * sizeof(int));

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			*(matrica + i * N + j) = rand() % 200 - 100;
			printf("%d ", *(matrica + i * N + j));
		}
	}
	for (i = 0; i < N; i++) {
		A = A + *(matrica + i * N + i);
		B = B + *(matrica + i * N + (N - i - 1));
		printf("\n");
	}
	
	printf("\n %d \n ", A - B);
	if (A - B == 0) printf("Najljepsa");
	else printf("nije naj \n");
	printf("Obj -> %d - %d", A, B);


	free(matrica);
	getchar();
	getchar();
}