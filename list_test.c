/* Singly linked list 
 * attempting with pointer only. Not the best implementation.
 *
 * implement following capabilities:
 *  - Add an element to the end of link list.
 *  - Add and element to an arbitrary index.
 *  - Remove an element at an arbitrary index.
 *  - Find the index of an element in the list.
 *  - Clear the list (remove all elements from it)
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct list_item_t{
	struct list_item_t* next;
	// short*  prev;
	short data;
}listitem_t;

listitem_t* list_init(listitem_t* listhead) {
	listhead=NULL;
	// listhead->next = NULL;
	// list_head++;

	return listhead;

}

listitem_t* add_node(listitem_t* listhead, listitem_t* temp, short data) {

	temp=(listitem_t*)malloc(sizeof(listitem_t));
	temp->next = listhead;
	temp->data = data;
	listhead=temp;

	return listhead;
}

listitem_t* add_to_end (listitem_t* listhead, listitem_t* temp, short data) {
	listitem_t* orig_listhead = listhead; // keep the original listhead
	

	//Iterate through the list to find the last node which points to NULL
	// if temp->next is NULL we know we are end the EOL
	while (listhead != NULL) {
		printf ("temp_address: %p, temp->next: %p, temp->data %d\n", temp,temp->next, temp->data);

		// if TRUE, this is the node we want to add
		if (listhead->next == NULL) {
			temp = (listitem_t*)malloc (sizeof(listitem_t));

			listhead->next = temp; 	// point to the new node
			temp->data = data;
			temp->next = NULL; 		// make this the last node by pt to NULL

			//set the listhead back to orignal node
			listhead = orig_listhead;
			return listhead;
		}

		// assign the next address to iterate through the list
		listhead = listhead->next;


	}
	listhead = orig_listhead;
	return listhead;
}

void print_list (listitem_t* listhead) {
	listitem_t * temp;
	temp = listhead;
	while (temp != NULL) {
		printf ("temp_address: %p, temp->next: %p, temp->data %d\n", temp,temp->next, temp->data);
		temp = temp->next;
	}
}

void main() {
	listitem_t *listhead, *temp;
	
	listhead=list_init(listhead);
	listhead=add_node(listhead, temp, 31);
	listhead=add_node(listhead, temp, 44);
	listhead=add_node(listhead, temp, 56);
	listhead=add_node(listhead, temp, 68);
	listhead=add_node(listhead, temp, 79);
	// listhead=add_to_end(listhead,temp, 888);


	print_list(listhead);

}
