// Copyright 2021 Condrea Tudor-Daniel
#ifndef CIRCULAR_DOUBLY_LINKED_LIST_H_
#define CIRCULAR_DOUBLY_LINKED_LIST_H_

typedef struct dll_node_t dll_node_t;
struct dll_node_t
{
    void* data;
    dll_node_t *prev, *next;
};

typedef struct doubly_linked_list_t doubly_linked_list_t;
struct doubly_linked_list_t
{
    dll_node_t* head;
    int data_size;
    int size;
};

/*
 * Acestea sunt functiile pe care trebuie sa le implementam.
 * Implementarea acestora se va face in LinkedList.c .
 */

doubly_linked_list_t*
dll_create(int data_size);

dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, int n);

void
dll_add_nth_node(doubly_linked_list_t* list, int n, const void* data);

dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, int n);

int
dll_get_size(doubly_linked_list_t* list);

void
dll_free(doubly_linked_list_t** pp_list);

void
dll_print_int_list(doubly_linked_list_t* list);

void
dll_print_string_list(doubly_linked_list_t* list);

void
dll_print_ints_left_circular(dll_node_t* start);

void
dll_print_ints_right_circular(dll_node_t* start);
#endif // __CIRCULAR_DOUBLY_LINKED_LIST_H_
