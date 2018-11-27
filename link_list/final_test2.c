#include <stdio.h>
#include <stdlib.h>

typedef struct l_node {
    struct l_node *next;
    short value;
} l_node;

typedef struct LinkedList {
    struct l_node *head;
} LinkedList;

void listhead_init(LinkedList * list) {
   list->head= NULL;
}

void add_node(LinkedList *list, short value) {
    l_node *newNode = (l_node*)malloc(sizeof(l_node));
    newNode->next = 0;
    newNode->value = value;

    if (list->head == 0) {
        list->head = newNode;
    }
    else {
        l_node *lastNode = list->head;
        while (lastNode->next != 0) {
            lastNode = lastNode->next; //dereference "its" current iteration's next address
        }
        lastNode->next = newNode; 
    }
}

void dump_list(LinkedList *list) {
    l_node *temp = list->head;
    while (temp != 0) {
        printf("current: %p, ->next: %p, ->value: %d\n", temp, temp->next, temp->value);
        temp=temp->next;
    }
}
int main() {
    LinkedList list;
    // list.head=0;
    listhead_init(&list);
    add_node(&list, 31);
    add_node(&list, 45);
    add_node(&list, 57);
    dump_list(&list);

}