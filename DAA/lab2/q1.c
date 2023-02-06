#include <stdio.h>

int main() {

	int m,n;
	printf("Input two numbers: ");
	scanf("%d %d", &m, &n);

	int t = (m < n) ? m : n;
	int op_count = 0;
	while(t-->0) {
		op_count++;

		int remainder_m = m%t;
		if(remainder_m == 0) {

			int remainder_n = n%t;
			if(remainder_n == 0) {
				printf("GCD by consecutive integer checking is: %d\n", t);
				break;
			}

		}
	}

	printf("The code has executed %d times\n", op_count);


	return 0;
}