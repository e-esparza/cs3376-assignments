//
//  linkedlist.h
//  CLinkedList
//
//  Created by Michael Muggler on 2/18/13.
//  Copyright (c) 2013 Michael Muggler. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    
    const char * key;
    
    int value;
    
    struct Node * next;
    
};

typedef struct Node Node;

/**
 * Starting a Linked List:
 * Node * list;
 * list = node_make("FirstKey", 1, NULL);
 *
 * Shortcut Method:
 * start(list, "FirstKey", 1);
 *
 * Marco start(name, first) will create a linked list variable in the
 * current scope with a first element.
 **/
#define start(list_name, first_key, first_value) Node * list_name; \
                                                 list_name = node_make(first_key, first_value, NULL)

/**
 * Creates a new node in the heap. Provide a key, value and
 * the pointer to the next node. If no next node exists provide NULL.
 *
 * Example:
 * node_make("A Key", 50, NULL);
 *
 * Shortcut:
 * new("A Test Key", 10)
 **/
#define new(key, value) node_make(key, value, NULL)
Node * node_make(const char * key, int value, Node * next);

/**
 * As per spec, create_dummy will call the node_make method and
 * provide an empty string for the key, 0 for the value and NULL
 * for the pointer to the next.
 **/
Node * create_dummy();

/**
 * Will insert a provided node to the beginning of the list. This
 * method will return the memory address to the new beginning of
 * the list.
 *
 * Usage:
 * 1. Provide the pointer to the node and the list.
 *
 * Example:
 * list = add_node(node_make("AnotherKey", 50, NULL), list);
 *
 * Shortcut:
 * append(list, node_make("AnotherKey", 50, NULL));
 **/
#define append(list_name, node_key, node_value) list_name = add_node(new(node_key, node_value), list_name)
Node * add_node(Node * node, Node * list);

/**
 * Linearly traverses the linked list starting at the given node.
 * At each node that is not NULL, this method will call another
 * method to perform some action. The action method should accept
 * a pointer to the node and an integer indicating the depth of
 * the linked list node. The depth of the node starts at 1, despite
 * the item being the 0th in line. The action should return a bool 
 * break indicator. Returning true will stop the traversal.
 *
 * Usage:
 * 1. Call traverse() where list is of type Node * and method is the
 *    name of the method you would like to call.
 * 2. Define a function in the same file with the heading of:
 *    bool method(Node * node, int count)
 *    Where 'method' is the name of the method you provided in traverse().
 *
 * Example:
 * traverse(list, print_node_data);
 * bool print_node_data(Node * node, int count) {
 *    printf("Node(%d): %s\n", count, node->key);
 *    return false;
 * }
 **/

#define traverse(list, method) bool method(Node * node, int count) __attribute__((cdecl)); \
                               _traverse(list, &method);

// DO NOT USE THIS METHOD, INSTEAD USE: traverse(list, method)
void _traverse(Node * list, bool (*action)(Node *, int));

/**
 * Linearly traverses the linked list starting at the given
 * node to look for a key. If the value cannot be found, false
 * will be returned otherwise true. Provide a pointer to store
 * the value corresponding to the key.
 *
 * Example:
 * int value;
 * bool result = search(list, "KeyName", &value);
 **/
bool search(Node * list, const char * search, int * value);
//int search(Node * list, const char * search, bool * success);

/**
 * Linearly traverses the linked list starting at the given
 * node to look for a key to delete. Will free the deleted
 * key from heap memory.
 *
 * Usage:
 * list = delete_node(list, "MyKey");
 *
 * Shortcut:
 * delete(list, "MyKey");
 **/
#define delete(list, key) list = delete_node(list, key)
Node * delete_node(Node * list, const char * key);

/**
 * Recursively removes and will free heap memory for each node
 * starting at the end of the list up to the first item. This
 * method will return NULL. Provide the first node of the list.
 *
 * Usage:
 * list = free_all(list);
 *
 * Shortcut:
 * free_list(list);
 **/
#define free_list(list) list = free_all(list)
Node * free_all(Node * node);