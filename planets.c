#include <string.h>
#include <stdio.h>
#include "utils.h"
#include "CircularDoublyLinkedList.h"
#include "planetsFunctionality.h"

int main(void)
{
    doubly_linked_list_t * sysList = dll_create(sizeof(planet_info));
    int cmdCount, argNum;
    char cmd[10][50];
    scanf("%d\n", &cmdCount);
    for (cmdCount; cmdCount > 0; cmdCount--)
    {
        argNum = get_command(cmd);
        exec_command(sysList, cmd);
    }
    return 0;
}
