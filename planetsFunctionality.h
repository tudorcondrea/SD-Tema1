// Copyright 2021 Condrea Tudor-Daniel
#include "CircularDoublyLinkedList.h"

struct planet_info{
    char name[50];
    int kills;
    doubly_linked_list_t *shields;
};
typedef struct planet_info planet_info;

int get_command(char cmd[10][50]);
void add_planet(doubly_linked_list_t *sysList,
                int index, int shieldNum, planet_info info);
void blackhole(doubly_linked_list_t *sysList,
               int index, int s);
void exec_command(doubly_linked_list_t *sysList,
                  char cmd[10][50]);
void upgrade_shields(doubly_linked_list_t *sysList,
                     int pindex, int sindex, int upgval);
void expand(doubly_linked_list_t *sysList,
            int index, int shval);
void collide(doubly_linked_list_t *sysList,
             int p1, int p2);
void remove_shields(doubly_linked_list_t *sysList,
                    int pindex, int sindex);
void rotate_shields(doubly_linked_list_t *sysList,
                    int index, char dir, int units);
void print_details(doubly_linked_list_t *sysList,
                   int index);
