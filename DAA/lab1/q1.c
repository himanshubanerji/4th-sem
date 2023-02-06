#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	int data;
	struct node* lchild;
	struct node* rchild;
}Node;

void CreateBST(Node *head) {
	Node *newnode = (Node*) malloc(sizeof(Node));
	newnode->lchild = NULL;
	newnode->rchild = NULL;
	printf("Enter next element of tree or enter -1 to exit: ");
	scanf("%d", &(newnode->data));

	if(newnode->data == -1) {
		printf("Creation of Binary Search Tree complete...\n");
		printf("exiting...\n");
		printf("----------------------\n");
		return;
	}

	else {
		Node *tr = head;
		Node *pre = head;
		while(tr) {
			pre = tr;
			if (newnode->data < tr->data) tr = tr->lchild;

			// else if doesn't cause error but just writing if does since 
			// after the first if successfully executes value of tr becomes NULL
			// then with just `if` the compiler check the second if as well
			// tr->data is nothing since tr was already updated to NULL
			// thus Segmentation Fault(core dump) error is shown
			// with `else if` after successfull execution of the first `if` the second condition
			// is not executed therefore no error
			else if (newnode->data > tr->data) tr = tr->rchild;

		}

		if (newnode->data < pre->data) pre->lchild = newnode;
		if (newnode->data > pre->data) pre->rchild = newnode;

	}

	CreateBST(head);

}

void checkKey(Node *head) {
	bool present = false;
	int key = 0;
	printf("Enter the value of key: ");
	scanf("%d", &key);

	while(present == false && head) {
		if(key == head->data) {
			printf("Key found\n");
			present = true;
		}
		else if(key < head->data) head = head->lchild;
		else head = head->rchild;
	}

	if (!present)
		printf("Key not found\n");

	printf("----------------------\n");

}

void displayInorder(Node *head) {
	if(head) {
		displayInorder(head->lchild);
		printf("%d ", head->data);
		displayInorder(head->rchild);
	}

}

void displayPreorder(Node *head) {
	if(head) {
		printf("%d ", head->data);
		displayPreorder(head->lchild);
		displayPreorder(head->rchild);
	}

}

void displayPostorder(Node *head) {
	if(head) {
		displayPostorder(head->lchild);
		displayPostorder(head->rchild);
		printf("%d ", head->data);
	}

}

void DisplayTree(Node *head) {

	printf("Inorder: ");
	displayInorder(head);
	printf("\n");

	printf("Preorder: ");
	displayPreorder(head);
	printf("\n");

	printf("Postorder: ");
	displayPostorder(head);
	printf("\n");
	printf("----------------------\n");

}

int main()
{
	Node *head = (Node*) malloc(sizeof(Node));
	printf("Enter the root of the tree: ");
	scanf("%d", &(head->data));
	head->lchild = NULL;
	head->rchild = NULL;

	CreateBST(head);
	checkKey(head);
	DisplayTree(head);

	return 0;
}