/* queues.h :   Header for making and manipulating queues
*				By: Kevin MacIntosh
*				Based off code provided by: Michael Galle
*/

#pragma once

struct item { char * msg; int sendid; int recid; int priority; int seqnum; int tbd; char * szKey; }; // structure that holds values for a message queue

typedef struct item Item; // same as item

typedef struct node * link;

struct node { link pNext; Item msgInfo; }; // structure that has a pointer to the next node and an item

typedef struct node Node; // same as node

// Function that creates a queue. Takes in: void. Returns: void.
void initQueue();

// Function that adds a new node to the queue. Takes in: the message, the sender id, the reciever id, the message priority, the sequence number and and value that is not yet used.
void addToQueue(char * msg, int sendid, int recid, int priority, int seqnum, int tbd, char * szKey);

// Function that checks if the queue is empty. Takes in: void. Returns: an integer (0 unless empty).
int isQueueEmpty();

// Function that removes the first node from the queue and returns it and sets the next node to be the head. Takes in: void. Returns: a pointer to a node
node * deQueue();

// Function which prints the message of a node and goes to a new line. Takes in: the Item of a node. Returns: Void.
void visit(Item msgInfo);

// Function which visits each node in a list and prints its message. Takes in: void. Returns: Void.
void travfor();

// Function which prints the message of a list in reverse order. 
// Takes in: any node from the list, an integer for whether or not it is the first call of the function (anything other than 1 means it is not). Returns: Void.
void travback(Node * theNode, int first);