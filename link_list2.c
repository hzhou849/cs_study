/* Singly linked list 
 *
 * implement following capabilities:
 *  - Add an element to the end of link list.
 *  - Add and element to an arbitrary index.
 *  - Remove an element at an arbitrary index.
 *  - Find the index of an element in the list.
 *  - Clear the list (remove all elements from it)
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct listitem_t {
	struct listitem_t *next;
	short data;
} listitem_t;

listitem_t *listhead=NULL,  *temp;

void add_node(short data) {
	
	temp = malloc(sizeof(listitem_t));
	temp->data = data;
	temp->next = listhead; 	//temp->next points to old listhead
	listhead = temp; 		// the new node becomes the new listhead
}

void insertion(int index, short data){
	listitem_t *prev_node, *next_node *new_node;

	new_node = malloc(sizeof (listitem_t));
	new_node->data = data;
	new_node->next 

	for (int i =0; i == index; i++ ){
		printf("list item: current is %p; next is %p; data is %d\n", temp, temp->next, temp->data);
		temp = temp->next;	
	}
}

int main() {

	add_node(31);
	add_node(42);
	while (temp != NULL) {
		printf("list item: current is %p; next is %p; data is %d\n", temp, temp->next, temp->data);
		temp = temp->next; //update to next address;
	}
	while (listhead != NULL) {
		printf("listh item: current is %p; next is %p; data is %d\n", listhead, listhead->next, listhead->data);
		listhead= listhead->next; //update to next address;
	}
}