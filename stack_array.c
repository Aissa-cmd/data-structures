#include <stdio.h>
#include <stdlib.h>

// By: Aissa Ouboukioud

typedef struct {
	int num_elems;
	int max_length;
	int *data;
} Stack;

// initialize the Stack with the data is pointer to a block of memeory
// with the size passed as argument to the function
Stack *init_stack(int size) {
	Stack *new_stack = (Stack *)malloc(sizeof(Stack));
	if(new_stack == NULL) return NULL;
	int *data_member = (int *)malloc(sizeof(int) * size);
	if(data_member == NULL) return NULL;
	new_stack->data = data_member;
	new_stack->max_length = size;
	new_stack->num_elems = -1;
}

// check weather the Stack is empty or not
// if empty return 1 (true)
// if not return 0 (false)
int isStackEmpty(Stack *root) {
	if(root->num_elems == -1) {
		return 1;
	} else {
		return 0;
	}
}

// check weather the Stack is full or not
// if full return 1 (true)
// if not return 0 (false)
int isStackFull(Stack *root) {
	if(root->num_elems == (root->max_length-1)) {
		return 1;
	} else {
		return 0;
	}
}

// return a pointer to data at the top of the stack
// if the Stack is empty NULL is returned
int *peek(Stack *root) {
	if(isStackEmpty(root)) {
		return NULL;
	} else {	
		return &((root->data)[root->num_elems]);
	}
}

// push a new element to the top of the stack
// if the push was successful 1 (true) is returned
// if the Stack is full 0 (false) is returned
int push(Stack *root, int value) {
	if(isStackFull(root)) {
		return 0;
	} else {
		(root->data)[++(root->num_elems)] = value;
		return 1;		
	}
}

// pop the element on the top of the Stack and return
// a pointer to that element
// if Stack is empty NULL is retured
int *pop(Stack *root) {
	if(isStackEmpty(root)) {
		return NULL;
	} else {
		int *ptr = &((root->data)[root->num_elems]);
		(root->num_elems)--;
		return ptr;
	}
}

// print the elements in the stack
void print(Stack *root) {
	int i;
	for(i = 0; i <= root->num_elems; i++) {
		printf(" %d", root->data[i]);
	}
	printf("\n");
}

int main(void) {
	Stack *head = init_stack(10);
	push(head, 44);
	push(head, 3);
	push(head, 9);
	print(head);
	printf("%d\n", *peek(head));
	int *num = pop(head);
	printf("pop num -> %d\n", *num);
	printf("[stack after first pop]\n");
	print(head);
	printf("%d\n", head->num_elems);
	int *num1 = pop(head);
	printf("pop num1 -> %d\n", *num1);
	printf("[stack after second pop]\n");
	print(head);
	printf("%d\n", head->num_elems);
	return 0;
}
