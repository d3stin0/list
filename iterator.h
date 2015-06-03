#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include "list.h"

#define foreach(content, list, iter)	for(iter = iterator_new(list), content = iterator_get_begin(iter); \
										!iterator_is_end(iter); \
										content = iterator_get_next(iter))

typedef struct iterator
{
	cnct_t* begin;
	cnct_t* end;
	cnct_t* current;
}iterator_t;

iterator_t* iterator_new(list_t* list);

void iterator_free(iterator_t* iterator);

int iterator_is_begin(iterator_t* iterator);

int iterator_is_end(iterator_t* iterator);

void* iterator_get_content(iterator_t* iterator);

void* iterator_get_next(iterator_t* iterator);

void* iterator_get_prev(iterator_t* iterator);

void* iterator_get_begin(iterator_t* iterator);

void* iterator_get_end(iterator_t* iterator);

int iterator_get_index(iterator_t* iterator);

void* iterator_set_content(iterator_t* iterator, void* content);

#endif
