//
//  linkedlist.c
//  CLinkedList
//
//  Created by Michael Muggler on 2/18/13.
//  Copyright (c) 2013 Michael Muggler. All rights reserved.
//

#include "linkedlist.h"

Node * node_make(const char * key, int value, Node * next)
{
    
    Node * node;
    node = malloc(sizeof(struct Node));
    
    node->key = key;
    node->value = value;
    node->next = next;
    
    return node;
    
}

Node * create_dummy()
{
    
    return node_make("dummy", 0, NULL);
    
}

Node * add_node(Node * node, Node * list)
{
    
    bool found; // indicates if a key of the same name is found.
    int value; // The value of the found key will be stored here but not used in this method.
    
    found = search(list, node->key, &value); // perform a linear search for a node with the same key.
    
    printf("Appending the node '%s' before node '%s'.\n", node->key, list->key);
    printf("  > Duplicate key does %s\n", (found) ? "exist. Will not append." : "NOT exist. Will continue with append.");
    
    // If we found a key of the same name, i.e. a duplicate, we will not add it.
    // Return the address to the list not adding anything.
    if ( found ) return list;
    
    // If we made it here this key is unique. We will append this key to the beginning of the list.
    node->next = list;
    
    // Return the new address of the linked list.
    return node;
    
}

void _traverse(Node * list, bool (*action)(Node *, int))
{
    
    // If the list is empty, nothing exists to search.
    if ( list == NULL ) return;
    
    // If the action is not a valid address in the stack, the we have no point in doing this.
    if ( action == NULL ) return;
    
    // This is the dereferenced pointer to the current node.
    Node * current;
    current = list;
    
    int depth;
    depth = 0;
    
    // If we've reached the last node, its next value would be null.
    // So we don't continue.
    while ( current != NULL ) {

        // call the action if it exists.
        bool stop;
        stop = (*action) (current, ++depth);
        
        // if method wants to stop we should stop.
        if ( stop ) break;
        
        // Set the current node for next go around to the next node in the list.
        current = &((* current->next));
        
    }
    
    return;
    
}

/*
int search(Node * list, const char * search, bool * success)
{
 
    * success = false;
 
    // If the list is empty, nothing exists to search.
    if ( list == NULL ) return -1;
    
    // If we have nothing to search for, then end.
    if ( search == NULL ) return -1;
    
    // This is the dereferenced pointer to the current node.
    Node * current;
    current = list;
    
    // If we've reached the last node, its next value would be null.
    // So we don't continue.
    while ( current != NULL ) {
        
        int cmpresult;
        cmpresult = strcmp(search, current->key);
        
        // The strings are exactly the same in terms of size, position and case.
        if ( cmpresult == 0 ) {
            
            * success = true;
 
            // Provide the caller with the value of the searched item.
            // Return will exit the loop.
            return current->value;
            
        }
        
        // Set the current node for next go around to the next node in the list.
        current = &((* current->next));
        
    }
    
    // End the search, item not found.
    return -1;
    
}
*/


bool search(Node * list, const char * search, int * value)
{
    
    // If the list is empty, nothing exists to search.
    if ( list == NULL ) return false;
    
    // If we have nothing to search for, then end.
    if ( search == NULL ) return false;
    
    // This is the dereferenced pointer to the current node.
    Node * current;
    current = list;
    
    // If we've reached the last node, its next value would be null.
    // So we don't continue.
    while ( current != NULL ) {
        
        int cmpresult;
        cmpresult = strcmp(search, current->key);
        
        // The strings are exactly the same in terms of size, position and case.
        if ( cmpresult == 0 ) {
            
            // Provide the caller with the value of the searched item.
            *value = current->value;
            
            // Exit the loop by return true.
            return true;
            
        }
        
        // Set the current node for next go around to the next node in the list.
        current = &((* current->next));
    
    }
    
    // If we made it here then it doesn't exist.
    *value = -1; // Although we may have a -1 value for a node, this with a return false indicates not found.
    
    // End the search as not found.
    return false;
    
}

Node * delete_node(Node * list, const char * key)
{
    
    // If the list is empty, nothing exists to search.
    if ( list == NULL ) return list;
    
    // If we have nothing to search for, then end.
    if ( key == NULL ) return list;
    
    // This is the dereferenced pointer to the current node.
    Node * current;
    current = list;
    
    // This is the dereferenced pointer to the previous node.
    Node * previous;
    previous = NULL;
    
    // If we've reached the last node, its next value would be null.
    // So we don't continue.
    while ( current != NULL ) {
        
        int cmpresult;
        cmpresult = strcmp(key, current->key);
        
        // The strings are exactly the same in terms of size, position and case.
        // We have found what we are looking for so lets delete it.
        if ( cmpresult == 0 ) {
            
            // Store the memory location of the item to be removed.
            Node * delete;
            delete = current;
            
            printf("Deleting node '%s' at location '%p' from list.\n", delete->key, delete);
            
            // If this is the first node, then set list to the next item.
            if( previous == NULL )
            {
                
                list = current->next;
                printf("  > This node is first in the list! List will now begin at '%p'.\n", list);
                
            }
            else
            {
                
                // Set the previous node's next pointer to point to the current node's next node.
                previous->next = current->next;
                
                printf("  > Setting memory location of %s->next (%p) to %s->next (%p).\n", previous->key, previous, current->key, current);
                
            }
            
            // Lets free the space for the node we deleted from the list.
            printf("  > Freeing memory location: %p\n", delete);
            free(delete);
            
            // Exit the loop by returning the address to the list.
            return list;
            
        }
        
        // Set the previous node to this curren node.
        previous = current;
        
        // Set the current node for next go around to the next node in the list.
        current = &((* current->next));
        
        
    }
    
    // If we haven't returned by now, the key does not exist.
    return list;
    
}

Node * free_all(Node * node)
{
    
    if ( node->next != NULL ) free_all(node->next);
    
    printf("Deleting node '%s' and freeing memory location '%p'.\n", node->key, node);
    
    free(node);
    
    return NULL;
    
}