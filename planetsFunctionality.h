#include "CircularDoublyLinkedList.h"

struct planet_info{
    char name[50];
    int kills;
    doubly_linked_list_t *shields;
};
typedef struct planet_info planet_info;

int get_command(char cmd[10][50]);
void add_planet(doubly_linked_list_t *sysList, unsigned int index, unsigned int shieldNum, planet_info info);
void blackhole(doubly_linked_list_t *sysList, unsigned int index);
void exec_command(doubly_linked_list_t *sysList, char cmd[10][50]);
void upgrade_shields(doubly_linked_list_t *sysList, unsigned int pindex, unsigned int sindex, unsigned int upgval);
void expand(doubly_linked_list_t *sysList, unsigned int index, unsigned int shval);
void remove_shields(doubly_linked_list_t *sysList, unsigned int pindex, unsigned int sindex);
void rotate_shields(doubly_linked_list_t *sysList, unsigned int index, char dir, unsigned int units);