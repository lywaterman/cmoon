#ifndef CMOON_FIFOLIST_H
#define CMOON_FIFOLIST_H


typedef struct FiFoListNode {

	void * data;
	struct FiFoListNode * pre;
	struct FiFoListNode * next;

} FiFoListNode;


typedef struct FiFoList {

	FiFoListNode * head;

	FiFoListNode * tail;

} FiFoList;


int fifo_list_push(FiFoList * list, FiFoListNode * node);

FiFoListNode * fifo_list_pop(FiFoList * list);














#endif
