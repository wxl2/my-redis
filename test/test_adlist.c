#include "base/adlist.h"
#include <stdio.h>
#include <stdlib.h>

void *int_dup(void *ptr){
	int *i = (int*)malloc(sizeof(int));
	int *j = (int*)ptr;
	*i = *j;
	return i;
}

void int_free(void *ptr){
	free(ptr);
}

int int_match(void *ptr, void *key){
	int *i = (int*)ptr;
	int *j = (int*)key;

	if(*i == *j) return 0;
	else if(*i > *j) return 1;
	else return 1;
}

int main()
{
	list *list_ = listCreate();

	listSetDupMethod(list_,int_dup);
	listSetFreeMethod(list_,int_free);
	listSetMatchMethod(list_,int_match);
	
	for(int i = 0;i < 6;i++){
		int *p = (int*)malloc(sizeof(int));
		*p = i;
		list_ = listAddNodeHead(list_,p);
	}

	printf("list size %lu\n",listLength(list_));
	printf("list head %d\n",*(int *)listFirst(list_)->value);
	printf("list tail %d\n",*(int *)listLast(list_)->value);

	listIter* iter = listGetIterator(list_,AL_START_HEAD);
	while(1)
	{
		listNode * node = listNext(iter);
		if(node == NULL) break;
		printf("current node %d\n",*(int*)listNodeValue(node));
	}

	listRelease(list_);
	return 0;
}
