// program to implement Tower Of Hanoi by recursion
// additional exercise lab 2 q2

#include <stdio.h>

int op_count;

void towerOfHanoi (int n, char from_rod, char to_rod, char aux_rod) {

	if(n == 0) return;

	towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
	op_count++;
	printf("Move disc %d from rod %c to rod %c \n", n, from_rod, to_rod);
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);

}


int main() {

	int n; 
	printf("Enter the number of disc: ");
	scanf("%d", &n);

	towerOfHanoi(n, 'A', 'C', 'B');
	printf("The value of op_count is %d\n", op_count);

	return 0;
}