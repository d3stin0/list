#ifndef _LIST_H_
#define _LIST_H_

#ifndef OK
#define OK 1
#endif

#ifndef FAIL
#define FAIL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef struct cnct cnct_t;

typedef struct cnct
{
	cnct_t* next;
	cnct_t* prev;
	void* content;
}cnct_t;

typedef struct list
{
	cnct_t* head;
	cnct_t* tail;
}list_t;

list_t* list_new();

int list_add(list_t* list, void* content);

void* list_remove(list_t* list, void* content);

void* list_remove_by_index(list_t* list, int index);

void* list_get(list_t* list, int index);

void* list_set(list_t* list, int index, void* content);

#endif
