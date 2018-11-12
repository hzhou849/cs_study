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

#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

typedef struct listitem_t {
	struct listitem_t *next; // typedef  type isn't know at this point
	short data;
} listitem_t;

int init_node(listitem_t *listhead) {
	// listhead = NULL;
	listhead->next = -1;
	listhead->data = 999;
	printf("listhead: %p; &listhead: %p\n",(void*)listhead, (void*)&listhead->next );
	return 0;
}
int add_node(listitem_t *listhead, listitem_t *temp, short data) {
	listitem_t* temp;
	temp = (listitem_t *)malloc(sizeof (listitem_t)); //allocate memory for node
	temp->data = data;
	temp->next = listhead->next;
	// listhead = temp;
	printf("temp: %p; listhead: %p; value: %d\n", temp, listhead, temp->data);
	return 0;
}

void print_node(listitem_t *temp, short *data){
	*data = temp->data;
	temp->next = temp;
}

int main() {
	short data;
	int element;
	int *element_pt;
	listitem_t listhead, temp;
	listitem_t *p_temp;
	// iniitialize the listhead
	init_node(&listhead);
	printf("listhead: %p\n", listhead);


	add_node(&listhead, &temp, (short)31);
	add_node(&listhead, &temp, (short)42);
	
	// listhead.data = 2331;
	// temp = listhead;
	// while (temp != NULL){
	// 	printf("listitem: current is %p; next is %p; data is %d\n",temp, temp.next, temp.data);  
	// }
	print_node(&temp, &data);
	
	printf("test: %d\n",data);
}