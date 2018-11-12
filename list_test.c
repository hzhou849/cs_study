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
	struct list_item_t *next;
	short data;
}listitem_t;

void list_init(listitem_t* list_head, listitem_t* temp) {
	list_head=(listitem_t*)malloc(sizeof(listitem_t));
	list_head->data = 999;
	// list_head++;


}

void add_node(listitem_t* listhead, listitem_t* temp) {
	temp=(listitem_t*)malloc(sizeof(listitem_t));
	list_head->next =temp;
	temp->data = 1;
	temp->next = NULL;

	printf("%d %d", list_head->data, temp->data);

}



void main() {
	listitem_t list_head, temp;
	
	list_init(&list_head, &temp);
	// printf("%p, %p", list_head->next, temp->next);
}
