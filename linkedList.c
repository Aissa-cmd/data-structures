#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


// By: Aissa Ouboukioud


struct node {
	int data;
	struct node *next;
};

struct node *createNode(int x) {
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	new_node->data = x;
	new_node->next = NULL;
	return new_node;
}

struct node *init_list(int x) {
	struct node *head = createNode(x);
	return head;
}


void print(struct node *head) {
	while(head != NULL) {
		printf(" %d", head->data);
		head = head->next;
	}
	printf("\n");
}

void map(struct node *head, void(*callback)(struct node *, int)) {
	int i = 0;
	while(head != NULL) {
		callback(head, i);
		i++;
		head = head->next;
	}
}

struct node *get(struct node *head, int pos) {
	int i;
	for(i = 0; i < pos && head != NULL; i++) {
		head = head->next;
	}
	if(head == NULL) {
		return NULL;
	}
	return head;
}

struct node *getNode(struct node *head, int pos) {
	int i;
	for(i = 0; i < pos && head->next != NULL; i++) {
		head = head->next;
	}
	return head;
}

struct node *getLastNode(struct node *head) {
	return getNode(head, INT_MAX);
}

void insert(struct node **head, int x, int pos) {
	if(*head == NULL) return;
	if(pos < 0) return;
	struct node *new_node = createNode(x);
	if(pos == 0) {
		new_node->next = *head;
		*head = new_node;
		return;
	} else {
		struct node *before = getNode(*head, pos-1);
		new_node->next = before->next;
		before->next = new_node;
	}
}


void preAppend(struct node **root, int x) {
	insert(root, x, 0);
}

void append(struct node **root, int x) {
	insert(root, x, INT_MAX);
}

void prettyprint(struct node *head, int index) {
	printf("Node #%d, Data: %d\n", index, head->data);
}

struct node *pop(struct node **head, int pos) {
	if(*head == NULL || pos < 0) return NULL;
	struct node *node_to_delete = NULL;
	if(pos == 0) {
		node_to_delete = *head;
		*head = (*head)->next;
	} else {
		struct node *before = getNode(*head, pos-1);
		node_to_delete = before->next;
		before->next = node_to_delete->next;
	}
	return node_to_delete;
}

struct node *popFirst(struct node **head) {
	return pop(head, 0);
}
;

//struct node *popLast(struct node **head) {
//	if(*head == NULL) return;
//	struct node *before = *head;
//	struct node *node_to_delete = NULL;
//        while(before->next->next != NULL) {
//                before = before->next;
//        }
//        node_to_delete = before->next;
//	before->next = NULL;
//	return node_to_delete;
//}

void link(struct node *first, struct node *second) {
	struct node *last_node_in_first = getLastNode(first);
	last_node_in_first->next = second;
}


int sum(struct node *root) {
	int result = 0;
	while(root != NULL) {
		result += root->data;
		root = root->next;
	}
	return result;
}


struct node * find(struct node *root, int target) {
	while(root != NULL) {
		if(root->data == target) {
			return root;
		}
		root = root->next;
	}
	return NULL;
}


int findOneAndDelete(struct node **root, int target) {
	int found = 0;
	if((*root) == NULL) return found;
	else if((*root)->data == target) {
		struct node* node_to_delete = *root;
		*root = (*root)->next;
		free(node_to_delete);
		found = 1;
		return found;
	} else {
		struct node *current = (*root);
		while(current->next != NULL) {
			if(current->next->data == target) {
				struct node* node_to_delete = current->next;
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


void findAllAndDelete(struct node **root, int target) {
	int number = 1;
	while(number) {
		number = findOneAndDelete(root, target);
	}
}


struct node* LinkedListFromArray(int *arr, int arrlen) {
	struct node *head = init_list(arr[0]);
	int i;
	for(i = 1; i < arrlen; i++) {
		append(&head, arr[i]);
	}
	return head;
}


int *ArrayFromLinkedList(struct node *root) {
	int *arr = (int *)malloc(sizeof(int)*10);
	int i;
	for(i = 0; root != NULL; i++, root = root->next) {
		arr[i] = root->data;
	}
	return arr;
}

struct node* reverseLinkedList(struct node *root) {
	struct node *reversed = createNode(root->data);
	root = root->next;
	while(root != NULL) {
		preAppend(&reversed, root->data);
		root = root->next;
	}
	return reversed;
}


void reverse(struct node **root) {
	if (*root == NULL) return;
	struct node *cur, *prev, *next;
	cur = *root;
	prev = NULL;
	while (cur != NULL) {
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*root = prev;
}


struct node* copyLinkedList(struct node *root) {
	struct node *copyll = createNode(root->data);
	root = root->next;
	while(root != NULL) {
		append(&copyll, root->data);
		root = root->next;
	}
	return copyll;
}

void clear(struct node **root) {
	if(*root == NULL) return;
	struct node *next;
	while(*root != NULL) {
		next = (*root)->next;
		free((*root));
		(*root) = next;
	}
}

int main(void) {
	int numbers[4] = {7, 5, 13, 9};
	struct node *head = LinkedListFromArray(numbers, 4);
	map(head, &prettyprint);
	clear(&head);
	printf("[after clearing the list]\n");
	map(head, &prettyprint);
	if(head == NULL) printf("head is null\n");
	return 0;
}
