// Copyright 2021 Condrea Tudor-Daniel
#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "CircularDoublyLinkedList.h"
#include "planetsFunctionality.h"

int main(void)
{
    doubly_linked_list_t *sysList, *shields;
    dll_node_t *q;
    int cmdCount, i;
    char cmd[10][50];

    sysList = dll_create(sizeof(planet_info));
    scanf("%d\n", &cmdCount);
    for (i = cmdCount; i > 0; i--)
    {
        get_command(cmd);
        exec_command(sysList, cmd);
        q = sysList->head;
    }

    int n = sysList->size;
    q = sysList->head;
    for (i = 0; i < n; i++)
    {
        dll_node_t *delNode = q;
        shields = ((planet_info*)q->data)->shields;
        dll_free(&shields);
        q = q->next;
        free(delNode->data);
        free(delNode);
    }
    free(sysList);
    
    return 0;
}
