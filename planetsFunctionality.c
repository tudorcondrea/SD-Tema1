#include "planetsFunctionality.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getCommand(char cmds[10][50])
{
    char cmdLine[101];
    int n = 0;
    fgets(cmdLine, 100, stdin);
    cmdLine[strlen(cmdLine) - 1] = '\0';
    char * tok = strtok(cmdLine, " ");
    while (tok != NULL)
    {
        strcpy(cmds[n], tok);
        n++;
        tok = strtok(NULL, " ");
    }
    return n;
}

void exec_command(doubly_linked_list_t *sysList, char cmd[10][50])
{
    planet_info planet;
    if (strcmp(cmd[0], "ADD") == 0)
    {
        strcpy(planet.name, cmd[1]);
        printf("aici");
        planet.kills = 0;
        planet.shields = NULL;
        add_planet(sysList, atoi(cmd[2]), atoi(cmd[3]), planet);
    }
    else if (strcmp(cmd[0], "BLH") == 0)
    {
        blackhole(sysList, atoi(cmd[1]));
    }
}

void add_planet(doubly_linked_list_t * sysList, unsigned int index, unsigned int shieldNum, planet_info info)
{
    if (index > sysList->size)
    {
        printf("Planet out of bounds!\n");
        return;
    }
    dll_add_nth_node(sysList, index, &info);
    dll_node_t *planet = dll_get_nth_node(sysList, index);
    ((planet_info*)planet->data)->shields = dll_create(sizeof(int));
    int a = 1;
    for (int i = 0; i < shieldNum; i++)
        dll_add_nth_node(((planet_info*)planet->data)->shields, i, &a);
    printf("The planet %s has joined the galaxy\n", ((planet_info*)planet->data)->name);
}

void blackhole(doubly_linked_list_t *sysList, unsigned int index)
{
    if (index >= sysList->size)
    {
        printf("Planet out of bounds!\n");
        return;
    }
    dll_node_t *planet = dll_remove_nth_node(sysList, index);
    printf("The planet %s has been eaten by the Vortex\n", ((planet_info*)planet->data)->name);
    dll_free(&((planet_info*)planet->data)->shields);
    free(planet->data);
    free(planet);
}

void upgrade_shields(doubly_linked_list_t *sysList, unsigned int pindex, unsigned int sindex, unsigned int upgval)
{
    if (pindex >= sysList->size)
    {
        printf("Planet out of bounds!\n");
        return;
    }
    dll_node_t *q = dll_get_nth_node(sysList, pindex);
    doubly_linked_list_t *shields = ((planet_info*)q->data)->shields;
    if (sindex >= shields->size)
    {
        printf("Shield out of bounds!\n");
        return;
    }
    q = dll_get_nth_node(shields, sindex);
    *(int*)q->data += upgval;
}

void expand(doubly_linked_list_t *sysList, unsigned int index, unsigned int shval)
{
    if (index >= sysList->size)
    {
        printf("Planet out of bounds!\n");
        return;
    }
    dll_node_t *q = dll_get_nth_node(sysList, index);
    doubly_linked_list_t *shields = ((planet_info*)q->data)->shields;
    dll_add_nth_node(shields, shields->size, &shval);
}

void remove_shields(doubly_linked_list_t *sysList, unsigned int pindex, unsigned int sindex)
{
    if (pindex >= sysList->size)
    {
        printf("Planet out of bounds!\n");
        return;
    }
    dll_node_t *q = dll_get_nth_node(sysList, pindex);
    doubly_linked_list_t *shields = ((planet_info*)q->data)->shields;
    if (sindex >= shields->size)
    {
        printf("Shield out of bounds!\n");
        return;
    }
    q = dll_remove_nth_node(shields, sindex);
    free(q->data);
    free(q);
}

void collide(doubly_linked_list_t *sysList, unsigned int p1, unsigned int p2)
{
    if (p1 >= sysList->size || p2 > sysList->size)
    {
        printf("Planet out of bounds!\n");
        return;
    }
    dll_node_t *q = dll_get_nth_node(sysList, p1);
    planet_info *si1 = (planet_info*)q->data;
    planet_info *si2 = (planet_info*)q->next->data;
    dll_node_t *sq1 = dll_get_nth_node(si1->shields, si1->shields->size / 4);
    dll_node_t *sq2 = dll_get_nth_node(si2->shields, (si2->shields->size / 4) * 3);
    if (*(int*)sq1->data == 0)
    {
        printf("Planet %s has imploded!\n", si1->name);
        blackhole(sysList, p1);
        si2->kills++;
    }
    else
        *(int*)sq1->data--;
    if (*(int*)sq2->data == 0)
    {
        printf("Planet %s has imploded!\n", si2->name);
        blackhole(sysList, p2);
        si1->kills++;
    }
    else
        *(int*)sq2->data--;
}

void rotate_shields(doubly_linked_list_t *sysList, unsigned int index, char dir, unsigned int units)
{
    if (index >= sysList->size)
    {
        printf("Planet out of bounds!\n");
        return;
    }
    if (dir != 'c' && dir != 't')
    {
        printf("Not a valid direction!\n");
        return;
    }
    dll_node_t *q = dll_get_nth_node(sysList, index);
    doubly_linked_list_t *shields = ((planet_info*)q->data)->shields;
    if (dir == 'c')
        for (int i = 0; i < units; i++)
            shields->head = shields->head->next;
    else
        for (int i = 0; i < units; i++)
            shields->head = shields->head->prev;
}

void print_details(doubly_linked_list_t *sysList, unsigned int index)
{
    if (index >= sysList->size)
    {
        printf("Planet out of bounds!\n");
        return;
    }
    planet_info planet = *((planet_info*)dll_get_nth_node(sysList, index)->data);
    printf("NAME: %s\n");
}