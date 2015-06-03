#include<stdio.h>
#include<stdlib.h>

#include "list.h"

#include "iterator.h"

iterator_t* iterator_new(list_t* list)
{
	iterator_t* iterator;

	if((iterator = malloc(sizeof(iterator_t*))) == NULL)
	{
		fprintf(stderr,"iterator.c: iterator_new(): malloc failed.\n");
		return NULL;
	}

	iterator->begin = iterator->current = list->head;
	iterator->end = list->tail;

	return iterator;
}

void iterator_free(iterator_t* iterator)
{
	if(iterator)
		free(iterator);
}

int iterator_is_begin(iterator_t* iterator)
{
	return (iterator->begin == iterator->current) ? TRUE: FALSE;
}

int iterator_is_end(iterator_t* iterator)
{
	return (iterator->current == NULL) ? TRUE: FALSE; 
}

void* iterator_get_content(iterator_t* iterator)
{
	if(!iterator)
		return NULL;
	
	if(!iterator->current)
		return NULL;

	return iterator->current->content;
}

void* iterator_get_next(iterator_t* iterator)
{
	if(!iterator)
		return NULL;
	
	if(!iterator->current)
		return NULL;
		
	iterator->current = iterator->current->next;

	return (iterator->current) ? iterator->current->content : NULL;
}

void* iterator_get_prev(iterator_t* iterator)
{
	if(!iterator)
		return NULL;
	
	if(!iterator->current)
		return NULL;

	iterator->current = iterator->current->prev;

	return (iterator->current) ? iterator->current->content : NULL;
}

void* iterator_get_begin(iterator_t* iterator)
{
	if(!iterator)
		return NULL;

	iterator->current = iterator->begin;

	return (iterator->current) ? iterator->current->content : NULL;
}

void* iterator_get_end(iterator_t* iterator)
{
	if(!iterator)
		return NULL;

	iterator->current = iterator->end;

	return (iterator->current) ? iterator->current->content : NULL;
}

int iterator_get_index(iterator_t* iterator)
{
	int index = 0;

	if(!iterator)
		return -1;

	cnct_t* tmp_cnct;

	for (tmp_cnct = 0; tmp_cnct ; tmp_cnct = tmp_cnct->next, index++)
		if(tmp_cnct == iterator->current)
			return index;
	
	return -1;
}

void* iterator_set_content(iterator_t* iterator, void* content)
{
	if(!iterator)
		return NULL;

	if(!iterator->current)
		return NULL;

	void* tmp_content = iterator->current->content;
	iterator->current->content = content;

	return tmp_content;
}
