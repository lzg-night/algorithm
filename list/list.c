//
// Created by xiaozhi on 2018/2/2.
//
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#include "list.h"

/*list_init*/
void list_init(List *list, void (*destory)(void *data))
{
    /*Initialize the list.*/
    list->size = 0;
    list->destory = destory;
    list->head = NULL;
    list->tail = NULL;
    return;
}

/*list_destory*/
void list_destory(List *list)
{
    void *data;
    /*Remove each element.*/
    while (list_size(list) > 0)
    {
        if (list_rem_next(list, NULL, (void **)&data) == 0 && list->destory != NULL)
        {
            list->destory(data);
        }
    }
    memset(list, 0, sizeof(data));
    return;
}

/*list_ins_next.*/
int list_ins_next(List *list, ListElmt *element, const void *data)
{
    ListElmt *new_element;
    if((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL)
        return -1;
    new_element->data = (void *)data;
    if(element == NULL)
    {
        if(list_size(list) == 0)
            list->tail = new_element;
        new_element->next = list->head;
        list->head = new_element;
    }
    else
    {
        if(element->next == NULL)
            list->tail = new_element;
        new_element->next = element->next;
        element->next = new_element;
    }
    list->size++;
    return 0;
}

/*list_rem_next.*/
int list_rem_next(List *list, ListElmt *element, void **data)
{
    ListElmt *old_element;
    if(list_size(list) == 0)
        return -1;
    if(element == NULL)
    {
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;
        if(list_size(list) == 1)
            list->tail = NULL;
    }
    else
    {
        if(element->next == NULL)
            return -1;
        *data = element->next->data;
        old_element = element->next;
        element->next = element->next->next;
        if(element->next == NULL)
            list->tail = element;
    }
    free(old_element);
    list->size--;
    return 0;
}

int main()
{
    List *list = (List *) malloc(sizeof(List));
    void *destory = &list_destory;
    list_init(list, destory);
    int i = 9;
    list_ins_next(list, NULL, &i);
    int b = 10;
    list_ins_next(list, NULL, &b);
    for(int i = 1; i < 3; i++)
    {
        int *pInt = (int *) list->head->data;
        printf("%d \n", *pInt);
        list->head = list->head->next;
    }
    void **data;
    list_rem_next(list, list->tail, data);
    int *pInt = (int *) list->tail->data;
    printf("%d \n", *pInt);
}