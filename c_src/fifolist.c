#include <stdio.h>
#include "fifolist.h"


int fifo_list_push(FiFoList * list, FiFoListNode * node) {

	FiFoListNode * head = list->head;
	FiFoListNode * tail = list->tail;	

	//the list is empty
	if (head == NULL) {
		list->head = node;
		list->tail = node;	
		
		node->pre = NULL;
		node->next = NULL;

	} else {
		// the list has one empty
		if (head == tail) {
			list->tail = node;

			list->head->next = node;
			node->pre = list->head;

		} else {

			list->tail->next = node;

			node->pre = list->tail;

			list->tail = node;
		}
	}
	return 0;
}

FiFoListNode *fifo_list_pop(FiFoList * list) {

	FiFoListNode * head = list->head;
	FiFoListNode * tail = list->tail;

	if (tail == NULL) {
		//empty list	

	} else {
		if (head == tail) {
			list->head = NULL;
			list->tail = NULL;
		} else {
			
			list->tail = tail->pre;
			list->tail->next = NULL;
		}	
	}

	return tail;
}



