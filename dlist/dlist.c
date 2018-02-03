//
// Created by xiaozhi on 2018/2/3.
//

#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "dlist.h"

void dlist_init(DList *list, void (*destroy)(void *data))
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->destory = destroy;
    return;
}
void dlist_destory(DList *list)
{
    void *data;
    while (dlist_size(list) > 0)
    {
        if(dlist_remove(list, dlist_tail(list), (void **)&data) == 0 && list->destory != NULL)
        {
            list->destory(data);
        }
    }
    memset(list, 0, sizeof(DList));
    return;
}

int dlist_ins_next(DList *list, DListElmt *element,const void *data)
{
    DListElmt *new_element;
    if(element == NULL && dlist_size(list) != 0)
        return -1;
    if((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL)
        return -1;
    new_element->data = (void *)data;
    if(dlist_size(list) == 0)
    {
        list->head = new_element;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_element;
    }
    else
    {
        new_element->next = element->next;
        new_element->prev = element;
        if(element->next == NULL)
            list->tail = new_element;
        else
            element->next->prev = new_element;
        element->next = new_element;
    }
    list->size++;
    return 0;
}

int dlist_remove(DList *list, DListElmt *element, void **data)
{
    if(element == NULL && dlist_size(list) != 0)
        return -1;
    *data = element->data;
    if(element == list->head)
    {
        list->head = element->next;
        if(list->head == NULL)
            list->tail = NULL;
        else
            element->next->prev = NULL;
    } else
    {
        element->prev->next = element->next;
        if(element->next == NULL)
            list->tail = element->prev;
        else
            element->next->prev = element->prev;
    }
    free(element);
    list->size--;
    return 0;
}
int main()
{
    DList *list = (DList *)malloc(sizeof(DList));
    void *pVoid = &dlist_destory;
    dlist_init(list, pVoid);
    int a = 1;
    dlist_ins_next(list, dlist_head(list), &a);
    int *pVoid1 = (int *)dlist_data(list->head);
    printf("%d\n", *pVoid1);
    void **data;
    dlist_remove(list, dlist_head(list), data);
    if(dlist_data(list->head) == NULL);
        printf("list is empty");
    dlist_destory(list);
}
