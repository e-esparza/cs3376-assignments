//
//  main.c
//  CLinkedList
//
//  Created by Michael Muggler on 2/18/13.
//  Copyright (c) 2013 Michael Muggler. All rights reserved.
//

#include "main.h"

int main(int argc, const char * argv[])
{
    
    start(list, "ItemA", 2027);
    
    list = add_node(create_dummy(), list);
    
    printf("Started a linked list. First item: %s = %d\n", list->key, list->value);
    printf("--------------------\n");
    
    append(list, "ItemB", 74);
    append(list, "ItemC", 32);
    append(list, "ItemD", 21);
    append(list, "ItemE", 2);
    append(list, "ItemE", 55);
    append(list, "Item*", 42);
    append(list, "ItemF", 54);
    append(list, "ItemG", 86);
    
    printf("--------------------\n");
    
    delete(list, "ItemA");
    delete(list, "ItemD");
    delete(list, "ItemG");
    
    printf("--------------------\n");
    printf("Linked List:\n");
    
    traverse(list, print_node);
    
    printf("--------------------\n");
    printf("Searching for the value of 'ItemB'.\n");
    
    int value;
    bool result = search(list, "ItemB", &value);
    
    printf("Search result: %s\n", (result) ? "Successful" : "Failed");
    printf("The value of ItemB is: %d\n", value);
    
    printf("--------------------\n");
    free_list(list);
    
    printf("List pointer value: %s!\n", (list == NULL) ? "(null)" : "(error)");

    return 0;
}

bool print_node(Node * node, int count) {
    
    printf("(%d) Node(%p) { key: %s, value: %d, next: Node(%p) }\n", count, node, node->key, node->value, node->next);
    
    return false;
    
}
