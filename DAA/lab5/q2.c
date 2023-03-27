#include<stdio.h>
#include<stdlib.h>

int **adj;
int n;
int *visited;


void dfs(int vertex) {
    visited[vertex] = 1;
    printf("DFS of the entered graph is\n");
    printf("%d\t", vertex);

    for (int i = 0 ; i<n; i++){
        if (adj[vertex][i] == 1 && visited[i] == 0){
            dfs (i);
        }
    }
}


 
int main(){

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    adj = calloc (n, sizeof (int *));
    for (int i =0 ; i<n; i++){
        adj[i] = calloc(n, sizeof (int));
    }

    visited = calloc (n, sizeof(int));
    for (int i = 0; i<n; i++){
        visited[i] = 0;
    }

    printf("\nEnter values of adjacency matrix \n");

    for (int i = 0; i<n; i++){
        for (int j = 0 ; j<n; j++){
            scanf("%d", &adj[i][j]);
        }
    }

    dfs(0);

    for (int i =0 ; i<n ;i++){
        if (visited[i] ==0){
            dfs(i);
        }
    }

    return 0;
}