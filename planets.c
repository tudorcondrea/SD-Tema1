#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "CircularDoublyLinkedList.h"
#include "planetsFunctionality.h"

int main(void)
{
    doubly_linked_list_t * sysList = dll_create(sizeof(planet_info));
    int cmdCount, i;
    char cmd[10][50];
    scanf("%d\n", &cmdCount);
    for (i = cmdCount; i > 0; i--)
    {
        get_command(cmd);
        exec_command(sysList, cmd);
    }
    int n = sysList->size;
    dll_node_t *q = sysList->head;
    for (i = 0; i < n; i++)
    {
        dll_node_t *delNode = q;
        dll_free(&((planet_info*)q->data)->shields);
        q = q->next;
        free(delNode->data);
        free(delNode);
    }
    free(sysList);
    return 0;
}
