#include <stdio.h>
#include <stdlib.h>

int main() {
	int N;
	
	printf("Upisi N:");
	scanf("%d", &N);
	
	int *arr = (int*)malloc(sizeof(int)*N);
	int *koraka_do_sad= (int*)malloc(sizeof(int)*N);
	int index2 = 0, index3 = 0, broj_koraka = 9999;
	
	*(koraka_do_sad) = 0;
	for (int i = 1; i < N; i++) {
		if (*(arr + i) % 2 == 0) {  // provjeri jeli djeljiv sa 2
				index2 = *(arr + i)/2;   // ako je nadji mu index tj lokaciju
				broj_koraka = *(koraka_do_sad + index2-1);  // spremi broj koraka 
		}
		if (*(arr + i) % 3 == 0) {  // provjeri jeli djeljiv sa 3
				index3 = *(arr + i) / 2;  // ako je nadji mu index tj lokaciju
				// min od broj koraka za N/2 i broja koraka za N/3
				broj_koraka = (broj_koraka > *(koraka_do_sad + index3-1)) ? *(koraka_do_sad + index3-1) : broj_koraka; 
				
		}
		// min od min broj koraka do sada i broja koraka za jedan pomak unazad
		broj_koraka = (broj_koraka > *(koraka_do_sad + i -1)) ? *(koraka_do_sad + i -1) : broj_koraka;

		//dobijemo min broj koraka od 3 moguca slucaja te dodamo u listu koraka_do_sad
		*(koraka_do_sad + i) = broj_koraka + 1;
	
	}

		//zadnji element liste je rjesenje
		printf("%d ", *(koraka_do_sad + N-1));

	getchar();
	getchar();
	free(arr);
	free(koraka_do_sad);
}
