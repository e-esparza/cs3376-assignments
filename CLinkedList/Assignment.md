Implementing Linked Lists in The Heap Using C (Using C++ is Not Allowed)

Linked lists are a way to store data dynamically whenever necessary. To implement linked lists, the programmer writes a struct definition that contains variables holding information about something and that has a pointer to a struct of its same type (it has to be a pointer--otherwise, every time an element was created, it would create a new element, infinitely). Each of these individual structs in the list is commonly known as a node or element of the list.
 
In this assignment you will create a linked list in the HEAP and implement algorithms for manipulating it. Each node of the linked list contains a key/value pair and a pointer to the next node, where "key" is a string and "value" is an integer. Your program should have the following functions:

1- create_dummy: Allocate “dummy” node to point to the first real node of the linked list.  

2- add_node: Create a new node, and insert it at front of the list (you need to check for duplicates before creating the new node, duplicates are not allowed). This function takes a key and a value as input.

3- search: Linear search through the list. The function takes the key and returns the value corresponding the key.

4- delete_node: Free a node. Given a key the function removes the node containing that key.

5- free_all: Free nodes while traversing; free the dummy node.