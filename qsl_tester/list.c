#include <stdio.h>
#include <stdlib.h>

typedef struct listitem_t {
	struct listitem_td *next;
	short data;
}listitem_t;

// initialize structs
listitem_t *listhead;

void list_init() {
	listhead = NULL;

	// return listhead;
}

void add_node(short data) {
	listitem_t *temp;
	temp = (listitem_t*)malloc(sizeof(listitem_t));
	temp->next = listhead;	//assign the temp->next to the old listhead.
	temp->data = data;
	listhead = temp; 	//assign the new node to be the LH
	
}

void print_list() {
	listitem_t *reader;
	reader = listhead;
	while (reader != NULL) {
		printf("address: %p, next_address: %p, data: %d\n", reader, reader->next, reader->data);
		reader=reader->next;
	}
}

int main() {
	list_init();
	add_node(31);
	add_node(45);
	print_list();
}
