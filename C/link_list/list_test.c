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
	short data;
}listitem_t;


/*Prototypes*/
void print_list(listitem_t * listhead);

listitem_t* list_init(listitem_t* listhead) {
	listhead=NULL;
	// listhead->next = NULL;
	// list_head++;

	return listhead;

}

listitem_t* add_node(listitem_t* listhead, short data) {
	listitem_t * temp;
	temp=(listitem_t*)malloc(sizeof(listitem_t));
	temp->next = listhead;
	temp->data = data;
	listhead=temp;

	return listhead;
}

/* 1) add to end of list */
listitem_t* add_to_end (listitem_t* listhead, short data) {
	listitem_t* orig_listhead = listhead; // keep the original listhead
	listitem_t * temp;	

	//Iterate through the list to find the last node which points to NULL
	// if temp->next is NULL we know we are end the EOL
	while (listhead != NULL) {
		// printf ("temp_address: %p, temp->next: %p, temp->data %d\n", listhead,listhead->next, listhead->data);

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

/* add element to index */
listitem_t* add_node_index(listitem_t* listhead, short data, int index){
	listitem_t *og_listhead, *prev_node, *next_node, *temp;
	og_listhead = listhead;		//keep track of the original pointer.

	if (index < 0) {
		printf("not a valid index range");
		return og_listhead;
	}

	for (int i=0; i <= index; i++) {
		if (listhead == NULL) {
			printf("index out of range");

			return og_listhead;
		}

		if (i == (index -1)) {
			if (listhead->next != NULL ) {
				prev_node = listhead;		// assign the previous node 
				next_node = listhead->next;
				temp = (listitem_t*)malloc(sizeof(listitem_t));	//create the new node
				prev_node->next = temp;
				temp->data = data;
				temp->next = next_node;			//link the new node to the next node;
				printf ("\n**INSERTED index[%d]: address: %p, ->next: %p, ->data %d\n",index, (void*)temp, (void*)temp->next, temp->data);

			}
		}

		listhead=listhead->next;
	}

	return og_listhead;
}


/* remove element list */
listitem_t* remove_node (listitem_t* listhead, int index ) {
	listitem_t *orig_listhead,*prev_node, *next_node;
	orig_listhead = listhead;		// remember the original LH

	// print_list(listhead);			// print the original list

	if (index < 0){
		return orig_listhead;
	}

	for (int i=0; i <= index; i++) {
		if (listhead == NULL){
			printf("index out of range");
			return orig_listhead;
		}
		if (i == (index -1)) { 			 //we are at the prev node 
			if (listhead->next != NULL) { 	//check if the next node (at index is NULL)?
				prev_node = listhead;			//assign current node to prev
			}
		}
		if (i == index ) {				//we are now at the node to be deleted.
			next_node = listhead->next; // assign the next node to be linked
			printf ("\n**REMOVED index[%d]: address: %p, ->next: %p, ->data %d\n",index, (void*)listhead, (void*)listhead->next, listhead->data);
			listhead->data = 0;
			free(listhead); 			// deallocate the memory 
			prev_node->next = next_node;		//reconnect the prev node with the next node
			
			
		}
		listhead=listhead->next;	//advance to next node
		
	}
	return orig_listhead;

}

/*4) add element to arbitrary index*/
int return_index (listitem_t* listhead, int index) {

	listitem_t *temp;
	temp = listhead;

	if (index < 0) {
		return -2;
	}

	for (int i=0; i <= (index -1); i++) {
		if (temp == NULL) {
			printf("index is out of list range.");
			return -1;
		}
		else if(i == index) {
			printf ("index[%d]: address: %p, ->next: %p, ->data %d\n",i, (void*)temp, (void*)temp->next, temp->data);
		}
		else {
			temp=temp->next;
		}
	}
	return 0;
}

/* Clear the list */
listitem_t* clear_list (listitem_t* listhead) {
	listitem_t *next_node;
	while (listhead != NULL) {
		next_node = listhead->next;  // retain the next address
		listhead->data = 0;
		free(listhead);			// free memory
		listhead = next_node;
	}
	if (listhead == NULL) {
		printf("List successfully deleted\n");
	}
	else {
		printf("List delete error");
	}

		return listhead;
}

/* print the list */
void print_list (listitem_t* listhead) {
	listitem_t * temp;
	temp = listhead;
	printf("\n");

	if (listhead == NULL) {
		printf("Nothing to print. List is empty.\n");
		
	}

	while (temp != NULL) {

		printf ("_address: %p, ->next: %p, ->data %d\n", (void*)temp, (void*)temp->next, temp->data);
		temp = temp->next;
	}
}

int main() {
	listitem_t *listhead;
	listhead = NULL;


	listhead=list_init(listhead);
	listhead=add_node(listhead, 31);
	listhead=add_node(listhead, 44);
	listhead=add_node(listhead, 56);
	listhead=add_node(listhead, 68);
	listhead=add_node(listhead, 79);
	listhead=add_to_end(listhead, 888);
	return_index(listhead, 13);
	print_list(listhead);



	listhead=remove_node(listhead, 3);
	print_list(listhead);
	listhead=add_node_index(listhead,952, 3);
	print_list(listhead);

	listhead=clear_list(listhead);
	print_list(listhead);
	return 0;
}
