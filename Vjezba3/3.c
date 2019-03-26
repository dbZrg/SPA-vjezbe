#include <stdio.h>
#include <stdlib.h>

int main() {
	int N;
	printf("Upisi N:");
	scanf("%d", &N);
	int *arr = (int*)malloc(sizeof(int)*N);
	for (int i = 0, z = N; i < N; i++,z--) {
		*(arr+i) = z;
		printf("%d", *(arr + i));
	}
	int i = 0;
	int koraci = 0;
	while (i < N-1) {
		if (*(arr+i) % 2 == 0) {
			i += *(arr+i) / 2;
			koraci++;
			continue;
		}
		else if (*(arr+i) % 3 == 0) {
			i += *(arr+i) / 3;
			koraci++;
			continue;
		}
		else {
			i++;
			koraci++;
		}
	}
	printf("koraci: %d",koraci);
	getchar();
	getchar();
}