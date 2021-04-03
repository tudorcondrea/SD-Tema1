#include "planetsFunctionality.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_command(char cmds[10][50])
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
        planet.kills = 0;
        planet.shields = NULL;
        add_planet(sysList, atoi(cmd[2]), atoi(cmd[3]), planet);
    }
    else if (strcmp(cmd[0], "BLH") == 0)
    {
        blackhole(sysList, atoi(cmd[1]));
    }
    else if (strcmp(cmd[0], "UPG") == 0)
    {
        upgrade_shields(sysList, atoi(cmd[1]), atoi(cmd[2]), atoi(cmd[3]));
    }
    else if (strcmp(cmd[0], "EXP") == 0)
    {
        expand(sysList, atoi(cmd[1]), atoi(cmd[2]));
    }
    else if (strcmp(cmd[0], "RMV") == 0)
    {
        remove_shields(sysList, atoi(cmd[1]), atoi(cmd[2]));
    }
    else if (strcmp(cmd[0], "COL") == 0)
    {
        collide(sysList, atoi(cmd[1]), atoi(cmd[2]));
    }
    else if (strcmp(cmd[0], "ROT") == 0)
    {
        rotate_shields(sysList, atoi(cmd[1]), cmd[2][0], atoi(cmd[3]));
    }
    else if (strcmp(cmd[0], "SHW") == 0)
    {
        print_details(sysList, atoi(cmd[1]));
    }
}

void add_planet(doubly_linked_list_t * sysList, int index, int shieldNum, planet_info info)
{
    if (index > sysList->size)
    {
        printf("Planet out of bounds!\n");
        return;
    }
    dll_add_nth_node(sysList, index, &info);
    dll_node_t *planet = dll_get_nth_node(sysList, index);
    ((planet_info*)planet->data)->shields = dll_create(sizeof(int));
    int a = 1, i;
    for (i = 0; i < shieldNum; i++)
        dll_add_nth_node(((planet_info*)planet->data)->shields, i, &a);
    printf("The planet %s has joined the galaxy\n", ((planet_info*)planet->data)->name);
}

void blackhole(doubly_linked_list_t *sysList, int index)
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

void upgrade_shields(doubly_linked_list_t *sysList, int pindex, int sindex, int upgval)
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

void expand(doubly_linked_list_t *sysList, int index, int shval)
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

void remove_shields(doubly_linked_list_t *sysList, int pindex, int sindex)
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

void collide(doubly_linked_list_t *sysList, int p1, int p2)
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
    {
        *(int*)sq1->data -= 1;
    }
    if (*(int*)sq2->data == 0)
    {
        printf("Planet %s has imploded!\n", si2->name);
        blackhole(sysList, p2);
        si1->kills++;
    }
    else
    {
        *(int*)sq2->data -= 1;
    }
}

void rotate_shields(doubly_linked_list_t *sysList, int index, char dir, int units)
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
    int i;
    if (dir == 'c')
        for (i = 0; i < units; i++)
            shields->head = shields->head->next;
    else
        for (i = 0; i < units; i++)
            shields->head = shields->head->prev;
}

void print_details(doubly_linked_list_t *sysList, int index)
{
    if (index >= sysList->size)
    {
        printf("Planet out of bounds!\n");
        return;
    }
    planet_info planetMain = *((planet_info*)dll_get_nth_node(sysList, index)->data), planetPrev, planetNext;
    printf("NAME: %s\nCLOSEST: ", planetMain.name);
    if (sysList->size == 1)
    {
        printf("none\n");
    }
    else if (sysList->size == 2)
    {
        planetNext = *((planet_info*)dll_get_nth_node(sysList, index + 1)->data);
        printf("%s\n", planetNext.name);
    }
    else
    {
        planetNext = *((planet_info*)dll_get_nth_node(sysList, index + 1)->data);
        planetPrev = *((planet_info*)dll_get_nth_node(sysList, index - 1)->data);
        printf("%s and %s\n", planetNext.name, planetPrev.name);
    }
    printf("SHIELDS: ");
    dll_print_ints_right_circular(planetMain.shields->head);
    printf("KILLED: %d\n", planetMain.kills);
}