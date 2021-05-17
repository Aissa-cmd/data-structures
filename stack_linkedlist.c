#include <stdio.h>
#include <stdlib.h>

// By: Aissa Ouboukioud

typedef struct Node {
	int data;
	struct Node *prev;
} Node;

typedef struct {
	Node *head;
} Stack;

// inirialize the Stack with the data is pointer to the last
// element in the linked list
Stack *init_stack() {
	Stack *new_stack = (Stack *)malloc(sizeof(Stack));
	new_stack->head = NULL;
	return new_stack;
}

// create a new node
Node *_createNode(int data) {
	Node *new_node = (Node *)malloc(sizeof(Node));
	new_node->data = data;
	new_node->prev = NULL;
}

// check weather the Stack is empty or not
// if empty return 1 (true)
// if not return 0 (false)
int isStackEmpty(Stack *root) {
	if(root->head == NULL) {
		return 1;
	} else {
		return 0;
	}
}

// push a element to the top of the Stack
// the head memeber will pointing to the new node
// and the prev memeber in the new node will be 
// pointing to the element that was in the top of the Stack
void push(Stack *root, int data) {
	Node *new_node = _createNode(data);
	if(root->head == NULL) {
		root->head = new_node;
	} else {
		new_node->prev = root->head;
		root->head = new_node;	
	}
}

// pop the element on the top of the Stack and return
// a poiter to that element
// if Stack is empty NULL is retured
int *pop(Stack *root) {
	if(root->head == NULL) {
		return NULL;
	} else {
		Node *node_to_delete = root->head;
		root->head = node_to_delete->prev;
		node_to_delete->prev = NULL;
		return &(node_to_delete->data);
	}
}

// return a pointer to data at the top of the Stack
// if the Stack is empty NULL is returned
int *peek(Stack *root) {
	if(root->head == NULL) {
		return NULL;
	} else {
		return &(root->head->data);
	}	
}

void print(Stack *root) {
	Node *temp = root->head;
	while(temp != NULL) {
		printf(" %d", temp->data);
		temp = temp->prev;
	}
	printf("\n");
}

int main(void) {
	Stack *root = init_stack();
	push(root, 33);
	push(root, 45);
	push(root, 13);
	push(root, 9);
	print(root);
	printf("poping the element on the top of the stack\n");
	int *elemAtTop = pop(root);
	if(elemAtTop == NULL) {
		printf("Stack is Empty\n");
	} else {
		printf("data -> %d\n", *elemAtTop);
	}
	printf("Stack after\n");
	print(root);
	return 0;
}
