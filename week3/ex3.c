#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct node {
	struct node* next;
	int data;
	bool isEnd;
};

struct LinkedList {
	struct node* firstNode;
	bool isEmpty;
};

void print_list(struct LinkedList* list) {
	if (list->isEmpty) {
		return;
	}
	struct node cur = *(list->firstNode);
	while (!cur.isEnd) {
		printf("%d ", cur.data);
		cur = *(cur.next);
	}
	printf("%d\n", cur.data);
}

void insert_node(int data, int index, struct LinkedList* list) {
	if (list->isEmpty) {
		if (index != 0) {
			printf("There is no element with such an index\n");
			return;	
		}
		list->isEmpty = false;
		list->firstNode = malloc(sizeof(struct node));
		list->firstNode->data = data;
		list->firstNode->isEnd = true;
		return;
	}
	if (index < 0) {
		printf("There is no element with such an index\n");
		return;
	}
	if (index == 0) {
		struct node* newNode = malloc(sizeof(struct node));
		newNode->next = list->firstNode;
		newNode->data = data;
		newNode->isEnd = false;
		list->firstNode = newNode;
		return;
	}
	struct node* cur = list->firstNode;
	int i = 0;
	while (!cur->isEnd && i != index-1) {
		cur = cur->next;
		i++;
	}
	if (i != index-1) {
		printf("There is no element with such an index\n");
		return;
	}
	struct node* newNode = malloc(sizeof(struct node));
	newNode->data = data;
	if (cur->isEnd) {
		cur->isEnd = false;
		newNode->isEnd = true;
	} else {
		newNode->isEnd = false;
		newNode->next = cur->next;
	}
	cur->next = newNode;
}

void delete_node(int indexNode, struct LinkedList* list) {
	if (list->isEmpty) {
		printf("There is no element with such an index\n");
		return;
	}
	struct node* cur = list->firstNode;
	struct node* pre = list->firstNode;
	int i = 0;
	while (!cur->isEnd && i != indexNode) {
		i++;
		pre = cur;
		cur = cur->next;
	}
	if (i != indexNode) {
		printf("There is no element with such an index\n");
		return;
	}
	if (cur == list->firstNode) {
		list->firstNode = cur->next;
		if (cur->isEnd) {
			list->isEmpty = true;
		}
	} else {
		pre->next = cur->next;
	}
	free(cur);
}

int main() {
	int cur_com;
	struct LinkedList list;
	list.isEmpty = true;
	while (true) {
		printf("Enter command (1 - print linked list, 2 - insert element to linked list, 3 - delete element from linked list, 0 - exit):\n");
		scanf("%d", &cur_com);
		if (cur_com == 1) {
			print_list(&list);
			continue;
		}
		if (cur_com == 2) {
			printf("Enter index of element that before the new element:\n");
			int index;
			scanf("%d", &index);
			printf("Enter integer element:\n");
			int data;
			scanf("%d", &data);
			insert_node(data, index, &list);
			continue;
		}
		if (cur_com == 3) {
			printf("Enter index of element that will be deleted:\n");
			int index;
			scanf("%d", &index);
			delete_node(index, &list);
			continue;
		}
		if (cur_com == 0) {
			return 0;
		}
		printf("Unaccessable command. Please enter correct command\n");
	}
	return 0;
}
