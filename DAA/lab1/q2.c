#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 5

typedef struct graph {
	int data;
	struct graph *next;

}ListNode;

ListNode* createNode() {
	ListNode *newnode = (ListNode*) malloc(sizeof(ListNode));
	newnode->data = 0;
	newnode->next = NULL;

	return newnode;
}

int main() {
	char str[MAX_LENGTH];
	char GARBAGE_COLLECTOR;
	int n, i;
	printf("Enter the number of vertices: \n");
	scanf("%d", &n);

	ListNode arr[n];
	for(i=0; i<n; i++) {
		printf("Enter the value of vertex number %d: ", i);
		scanf("%d", &(arr[i].data));

		scanf("%c", &GARBAGE_COLLECTOR);

		printf("does vertex %d has any edges? (Input in \"yes\" or \"no\"): ", arr[i].data);
		fgets(str,MAX_LENGTH, stdin);
		if (strcmp(str,"yes") == 0) {
			ListNode *newnode = createNode();
			printf("Enter the value of the vertex: ");
			scanf("%d", &(newnode->data));
			arr[i].next = newnode;

			while(strcmp(str,"no") == 0) {
				printf("does vertex %d has any more edges? ", arr[i].data);
				fgets(str, MAX_LENGTH, stdin);
				if(strcmp(str, "yes") == 0) {
					ListNode *tr = arr[i].next;
					newnode = createNode();
					printf("Enter the value of vertex: ");
					scanf("%d", &(newnode->data));
					while(tr->next) {
						tr = tr->next;
					}
					tr->next = newnode;
				}

			}
		}
	}

	return 0;
}