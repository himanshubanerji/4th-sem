#include <stdio.h>

int main() {

	int m,n,i,j;
	printf("Input two numbers: ");
	scanf("%d %d", &m, &n);

	int MAX_LENGTH = (m>n) ? m : n;
	int primefactor_m[MAX_LENGTH], primefactor_n[MAX_LENGTH];

	int size_m = 0;
	int size_n = 0;

	for(i=2; i<MAX_LENGTH; i++) {
		int remainder_m = m%i;
		int remainder_n = n%i;

		if(remainder_m == 0)
			primefactor_m[size_m++] = i;

		if(remainder_n == 0) 
			primefactor_n[size_n++] = i;
	}

	//applying sieve of eratosthenes
	for(i=0; i<MAX_LENGTH; i++) {
		int element = primefactor_m[i];
		for(j=i+1; j<MAX_LENGTH; j++) {
			if(primefactor_m[j] != 0  && primefactor_m[j]%element == 0)
				primefactor_m[j]  = 0;
		}
	}

	for(i=0; i<MAX_LENGTH; i++) {
		int element = primefactor_n[i];
		for(j=i+1; j<MAX_LENGTH; j++) {
			if(primefactor_n[j] != 0  && primefactor_n[j]%element == 0)
				primefactor_n[j]  = 0;
		}
	}

	int ans[MAX_LENGTH];
	

	return 0;
}