#include <stdio.h>
#include <stdlib.h>


// By: Aissa Ouboukioud


typedef struct Node {
	int data;
	struct Node *next;
	struct Node *prev;
} Node;

typedef struct {
	Node *first;
	Node *last;
} dblist;

// print the linked list in right order (first -> last)
void print(Node *root) {
	while(root != NULL) {
		printf(" %d", root->data);
		root = root->next;
	}
	printf("\n");
}

// print the linked list in the reverse order (last -> first)
void reversePrint(Node *root) {
	while(root != NULL) {
		printf(" %d", root->data);
		root = root->prev;
	}
	printf("\n");
}

void prettyPrint(Node *root, int index) {
	printf("Node #%d, Data: %d\n", index, root->data);
}

// initialize a new double linked list
dblist *init_dblist() {
	dblist *new_dblist = (dblist *)malloc(sizeof(dblist));
	new_dblist->first = NULL;
	new_dblist->last = NULL;
	return new_dblist;
}

// create a node
Node *createNode(int data) {
	Node *new_node = (Node *)malloc(sizeof(Node));
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

// get a node in the giving position (used in the _insert function)
Node *_get(Node *root, int pos) {
	int i;
	for(i = 0; i < pos && root != NULL; i++) {
		root = root->next;
	}
	return root;
}

// insert a node in a postion if position is out of range
// then the function simply exits without doing anything
void _insert(Node **root, int data, int pos) {
	Node *new_node = createNode(data);
	Node *before = _get(*root, pos-1);
	if(before == NULL) return;
	new_node->next = before->next;
	new_node->prev = before;
	before->next->prev = new_node;
	before->next = new_node;
}

// append a node to the end of the double linked list
// and update the last property to point to the newly
// created node
void append(dblist *root, int data) {
	Node *new_node = createNode(data);
	new_node->prev = root->last;
	if(root->last != NULL) {
		root->last->next = new_node;
		new_node->prev = root->last;
	} else {
		root->first = new_node;
	}
	root->last = new_node;
}

// inserting a new node in giving position
void insert(dblist *root, int data, int pos) {
	if(pos < 0 ) return;
	else if(pos == 0) {
		append(root, data);
	} else {
		_insert(&(root->first), data, pos);
	}
}

// append a node to the head of the double linked list
// and update the fist property to point to the newly
// created node
void preAppend(dblist *root, int data) {
	Node *new_node = createNode(data);
	new_node->next = root->first;
	if(root->first != NULL) {
		root->first->prev = new_node;
		new_node->next = root->first;
	} else {
		root->last = new_node;
	}
	root->first = new_node;
};

// deleting the first node in the double linked list
// and returning it
Node *popFirst(dblist *root) {
	Node *node_to_delete = root->first;
	root->first = node_to_delete->next;
	root->first->prev = NULL;
	node_to_delete->next = NULL;
	node_to_delete->prev = NULL;
}

// pop and element in the giving position and return it
Node *pop(dblist *root, int pos) {
	Node *node_to_delete = NULL;
	if(root->first == NULL || root->last == NULL || pos < 0) return node_to_delete;
	if(pos == 0) return popFirst(root);
	else {
		Node *before = _get(root->first, pos-1);
		if(before == NULL) {
			return node_to_delete;
		} else {
			node_to_delete = before->next;
			before->next = node_to_delete->next;
			node_to_delete->next->prev = before;
			node_to_delete->next = NULL;
			node_to_delete->prev = NULL;
			return node_to_delete;
		}
	}
}

// deleting the last node in the double linked list
// and returning it
Node *popLast(dblist *root) {
	Node *node_to_delete = root->last;
	root->last = node_to_delete->prev;
	root->last->next = NULL;
	node_to_delete->next = NULL;
	node_to_delete->prev = NULL;
}

// removing a node from the double linked list
// and free it memory
void removeByIndex(dblist *root, int pos) {
	Node *node_to_delete = pop(root, pos);
	free(node_to_delete);
}

// this function removes the first occurence of the value in
// the double link list traversing the list starting from
// the first node to the last node
int _findFirstAndDelete(Node **root, int target) {
	int found = 0;
	if((*root) == NULL) return found;
	else if((*root)->data == target) {
		Node *node_to_delete = *root;
		*root = (*root)->next;
		(*root)->prev = NULL;
		free(node_to_delete);
		found = 1;
		return found;
	} else {
		Node *current = (*root);
		while(current->next != NULL) {
			if(current->next->data == target) {
				Node *node_to_delete = current->next;
				node_to_delete->next->prev = current;
				current->next = node_to_delete->next;
				free(node_to_delete);
				found = 1;
				return found;
			}
			current = current->next;
		}
	}
	return found;
}

// this function removes the last occurence of the value in
// the double linked list traversing the list starting from
// the last node to the first node
void _findLastAndDelete(Node **root, int target) {
	if((*root) == NULL) return;
	else if((*root)->data == target) {
		Node *node_to_delete = *root;
		*root = (*root)->prev;
		(*root)->next = NULL;
		free(node_to_delete);
		return;
	} else {
		Node *current = (*root);
		while(current->prev != NULL) {
			if(current->prev->data == target) {
				Node *node_to_delete = current->prev;
				node_to_delete->prev->next = current;
				current->prev = node_to_delete->prev;
				free(node_to_delete);
				return;
			}
		}
	}
}

// remove the first node that has the data equal to the target
void removeFirstByValue(dblist *root, int target) {
	_findFirstAndDelete(&(root->first), target);
}

// remove the last node that has the data equal to the target
void removeLastByValue(dblist *root, int target) {
	_findLastAndDelete(&(root->last), target);
}

// remove all the nodes that have the data equal to the target 
void removeAllByValue(dblist *root, int target) {
	int number = 1;
	while(number) {
		number = _findFirstAndDelete(&(root->first), target);
	}
}

void map(Node *root, void(*callback)(Node *, int)) {
	int i = 0;
	while(root != NULL) {
		callback(root, i);
		i++;
		root = root->next;
	}
}

// create a double linked list from an array
dblist *doubleLinkedListFromArray(int *arr, int arrlen) {
	dblist *root = init_dblist();
	int i;
	for(i = 0; i < arrlen; i++) {
		append(root, arr[i]);
	}
	return root;
}

void _clear(Node **root) {
	if(*root == NULL) return;
	Node *next;
	while(*root != NULL) {
		next = (*root)->next;
		free((*root));
		(*root) = next;
	}
}

// clear the double linked list
void clear(dblist *root) {
	_current(root->first);
}

int main(void) {
	int numbers[5] = {4, 7, 13, 7, 9};
	dblist *head = doubleLinkedListFromArray(numbers, 5);
	printf("[Linked List]\n");
	map(head->first, &prettyPrint);
	printf("[Reverse Linkded List]\n");
	reversePrint(head->last);
	removeAllByValue(head, 7);
	printf("\n[Delete All 7]\n\n");
	printf("[Linked List]\n");
	map(head->first, &prettyPrint);
	printf("[Reverse Linkded List]\n");
	reversePrint(head->last);
	return 0;
}
