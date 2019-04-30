#include <stdio.h>


int max_suma(int *arr, int d) {
	int max_trenutni = 0, max_totalni = 0, poc = 0, kraj = 0, temp = 0;

	for (int i = 0; i < d; i++) {
		max_trenutni += arr[i];
		
		if (max_trenutni < 0) {
			max_trenutni = 0;
			temp = i + 1;
		}
		else if (max_trenutni > max_totalni) {
			max_totalni = max_trenutni;
			poc = temp;
			kraj = i;
		}
	}
	printf("od i=%d do i=%d", poc, kraj);
	return max_totalni;
}


int main() {
	int arr[5]= { 2,3,-10,3,8 };

	printf("   MAX: %d", max_suma(arr, 5));
	getchar();
	getchar();
}