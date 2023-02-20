// program for matrix multiplication

#include <stdio.h>
#include <stdlib.h>


int main() {
	int n1, m1;
	int i, j,k;

	printf("enter number of rows and column for matrix 1: ");
	scanf("%d %d", &n1, &m1);

	int arr1[n1][m1];

	printf("enter the values of matrix 1\n");
	for(i=0; i<n1; i++)
		for(j=0; j<m1; j++)
			scanf("%d", &arr1[i][j]);


	int n2, m2;
	printf("enter number of rows and column for matrix 2: ");
	scanf("%d %d", &n2, &m2);

	int arr2[n2][m2];

	printf("enter the values of matrix 2\n");
	for(i=0; i<n2; i++)
		for(j=0; j<m2; j++)
			scanf("%d", &arr2[i][j]);


	if(m1 != n2) {
		printf("Matrix Multiplication not allowed\n");
		exit(EXIT_FAILURE);
	}

	int ans[n1][m2];

	for(i=0; i<n1; i++) {
		for(j=0; j<m2; j++) {

			ans[i][j] = 0;

			for(k=0; k<n2; k++) {
				ans[i][j] += arr1[i][k] * arr2[k][j];
			}
		}
	}

	int row = sizeof(ans) / sizeof(ans[0]);
	int column = sizeof(ans[0]) / sizeof(ans[0][0]);

	printf("\nResultant Matrix: \n");

	for(i=0; i<row; i++) {
		for(j=0; j<column; j++) {
			printf("%d ", ans[i][j]);
		}
		printf("\n");
	}



	return 0;
}