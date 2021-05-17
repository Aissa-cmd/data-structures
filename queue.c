#include <stdio.h>
#include <stdlib.h>

// By: Aissa Ouboukioud

typedef struct Node {
	int data;
	struct Node *next;
} Node;

typedef struct {
	Node *first;
	Node *last;
} Queue;

// create a new element
Node *_createNode(int data) {
	Node *new_node = (Node *)malloc(sizeof(Node));
	new_node->data = data;
	new_node->next = NULL;
}

// initialize a new queue
Queue *init_queue() {
	Queue *new_queue = (Queue *)malloc(sizeof(Queue));
	new_queue->first = NULL;
	new_queue->last = NULL;
	return new_queue;
}

// check if the queue is empty or not
// if empty return 1 (true)
// if not return 0 (false)
int isQueueEmpty(Queue *root) {
	if(root->first == NULL || root->last == NULL) {
		return 1;
	} else {
		return 0;
	}
} 

// add a new elemet to the queue
void enqueue(Queue *root, int data) {
	Node *new_node = _createNode(data);
	if(root->first == NULL) {
		root->first = new_node;
		root->last = new_node;
		return;
	} else {
		root->last->next = new_node;
		root->last = new_node;
	}
}	

// remove the first element in the queue and return a pointer
// to the data of the element
// if the queue is empty the NULL is returned
int *dequeue(Queue *root) {
	if(root->first == NULL) {
		return NULL;
	} else if(root->first->next == NULL) {
		int *data = &(root->first->data);
		root->first = NULL;
		root->last = NULL;
		return data;
	} else {
		int *data = &(root->first->data);
		root->first = root->first->next;
		return data;
	}
}

// return a pointer to the data of the first element
// in the queue if the queue is empty then NULL is returned
int *peek(Queue *root) {
	if(root->first == NULL) {
		return NULL;
	} else {
		return &(root->first->data);
	}
}

void print(Queue *root) {
	Node *current;
	current = root->first;
	while(current != NULL) {
		printf(" %d", current->data);
		current = current->next;
	}
	printf("\n");
}

int main(void) {
	Queue *head = init_queue();
	enqueue(head, 34);
	enqueue(head, 99);
	enqueue(head, 100);
	printf("[the queue]\n");
	print(head);
	dequeue(head);
	dequeue(head);
	if(head->first == NULL) printf("first is NULL\n");
	if(head->last == NULL) printf("last is NULL\n");
	printf("data -> %d\n", head->last->data);
	return 0;
}
