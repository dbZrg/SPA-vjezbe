#include <stdio.h>

int max_suma(int *arr, int N, int razmak)
{
	int max_do_sad[18];

	max_do_sad[N - 1] = arr[N - 1];

	for (int i = N - 2; i >= 0; i--) {
		//dodaj if umjesto ? i nadji indexe brojeva koji su izabrani
		if (i + razmak + 1 >= N)
			max_do_sad[i] = ((arr[i] > max_do_sad[i + 1]) ? arr[i] : max_do_sad[i + 1]);
		else
			max_do_sad[i] = (((arr[i] + max_do_sad[i + razmak + 1])>max_do_sad[i + 1]) ? (arr[i] + max_do_sad[i + razmak + 1]) : max_do_sad[i + 1]);
	}

	return max_do_sad[0];
}

int main()
{
	int N = 18, razmak = 4;
	int arr[] = { 9, 2, 3, 5, 7, 6, 5, 8, 8, 7, 2, 3, 1, 3, 4, 1, 5, 6 };
	printf("%d", max_suma(arr, N, razmak));
	getchar();
	getchar();
	return 0;
}

