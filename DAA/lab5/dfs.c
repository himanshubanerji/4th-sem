#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
	int n;
	int **arr;
}Graph;

int *visited;

void dfs(Graph *gp, int u) {
	printf("%d ", u);
	visited[u] = 1;

	for(int v=0; v<(gp->n); v++) {
		if((gp->arr[u][v] == 1) && (visited[v] == 0)) {
			dfs(gp, v);
		}
	}
}

int main() {

	Graph *gp = malloc(sizeof(Graph));
	printf("Enter size of matrix: ");
	scanf("%d", &(gp->n));

	int n = gp->n;

	visited = calloc(n, sizeof(int));

	gp->arr = calloc(n, sizeof(int*));

	printf("Enter values\n");
	for(int i=0; i<n; i++) {
		visited[i] = 0;
		gp->arr[i] = calloc(n, sizeof(int));
		for(int j=0; j<n; j++) {
			scanf("%d", &(gp->arr[i][j]));
		}
	}

	printf("------------------------");
	printf("\nDfs for the given graph is: ");
	dfs(gp, 0);
	printf("\n");


	return 0;
}
