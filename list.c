#include<stdio.h>
#include<stdlib.h>

#include "iterator.h"

#include "list.h"

list_t* list_new()
{
	list_t* list;

	if((list = malloc(sizeof(list))) == NULL)
	{
		fprintf(stderr,"list.c: list_new(): malloc failed.\n");
		return NULL;
	}

	list->head = list->tail = NULL;

	return list;
}

int	list_add(list_t* list,void* content)
{
	if(!list)
		return FAIL;

	cnct_t* new_cnct;

	if((new_cnct = malloc(sizeof(cnct_t))) == NULL)
	{
		fprintf(stderr,"list.c: list_add(): malloc failed.\n");
		return FAIL;
	}

	new_cnct->content = content;
	new_cnct->next = NULL;
	
	if(list->head == NULL && list->tail == NULL)
	{
		new_cnct->prev = NULL;
		list->head = new_cnct;
	}
	else
	{
		new_cnct->prev = list->tail;
		new_cnct->prev->next = new_cnct;
	}
	
	list->tail = new_cnct;
	
	return OK;
}

void* list_remove(list_t* list, void* content)
{
	if(!list)
		return NULL;

	cnct_t* tmp_cnct;
	void* tmp_content;
	iterator_t* iter;
	
	foreach(tmp_content,list,iter)
	{
		if(tmp_content == content)
		{
			tmp_cnct = iter->current;
			
			if(list->head == list->tail)
				list->head = list->tail = NULL;
			else if(tmp_cnct == list->tail)
			{
				list->tail = tmp_cnct->prev;
				tmp_cnct->prev->next = NULL;
			}
			else
			{
				tmp_cnct->prev->next = tmp_cnct->next;
				tmp_cnct->next->prev = tmp_cnct->prev;
			}

			free(tmp_cnct);
				
			return content;
		}
	}

	return NULL;
}

void* list_remove_by_index(list_t* list, int index)
{
	if(!list || index < 0)
		return NULL;
	
	iterator_t* iter;
	cnct_t* tmp_cnct;
	void* tmp_content;
	int i;

	for(iter = iterator_new(list), i=0; i < index; i++, iterator_get_next(iter));

	if(iterator_is_end(iter))
		return NULL;
	
	tmp_cnct = iter->current;
	tmp_content = tmp_cnct->content;

	if(list->head == list->tail)
		list->head = list->tail = NULL;
	else if(tmp_cnct == list->tail)
	{
		list->tail = tmp_cnct->prev;
		tmp_cnct->prev->next = NULL;
	}
	else
	{
		tmp_cnct->prev->next = tmp_cnct->next;
		tmp_cnct->next->prev = tmp_cnct->prev;
	}

	free(tmp_cnct);

	return tmp_content;
}

void* list_get(list_t* list, int index)
{
	if(!list || index < 0)
		return NULL;

	iterator_t* iter;
	void* tmp_content;
	int i;

	for(iter = iterator_new(list), i=0; i < index; i++, iterator_get_next(iter));
	
	tmp_content = iterator_get_content(iter);
	
	iterator_free(iter);

	return (iterator_is_end(iter)) ? NULL : tmp_content;
}

void* list_set(list_t* list, int index, void* content)
{
	if(!list || index < 0)
		return NULL;

	iterator_t* iter;
	void* tmp_content;
	int i;

	for(iter = iterator_new(list), i=0; i < index; i++, iterator_get_next(iter));
	
	tmp_content = iterator_get_content(iter);
	
	iterator_set_content(iter,content);
	iterator_free(iter);

	return (iterator_is_end(iter)) ? NULL : tmp_content;
}
