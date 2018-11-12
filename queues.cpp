/* queues.cpp : Source for making and manipulating queues
*				By: Kevin MacIntosh
*				Based off code provided by: Michael Galle
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "queues.h"

// create pointers to the head and tail of the queue and initialize them
static Node * pHead = (Node *)malloc(sizeof(Node));
static Node * pTail = (Node *)malloc(sizeof(Node));

// Function that creates a queue. Takes in: void. Returns: void.
void initQueue(){
	pHead = pTail = NULL; // set the head and tail pointers to point at null
}


// Function that adds a new node to the queue. Takes in: the message, the sender id, the reciever id, the message priority, the sequence number and and value that is not yet used.
void addToQueue(char * msg, int sendid, int recid, int priority, int seqnum, int tbd, char * szKey){

	// create a pointer for the new node
	link pnode;
	pnode = (link)malloc(sizeof(Node));

	// check if this is the first node in the queue, if yes make it the head, if not add it to the end
	if (pHead == NULL) {
		pHead = pnode; // make the new node the head
	}
	else {
		pTail->pNext = pnode; // add new node to the end
	}

	// make the new node the tail
	pnode->pNext = NULL;
	pTail = pnode;
	// allocate memory for the message
	pnode->msgInfo.msg = (char *)malloc(sizeof(char) * 140);
	
	// put information into the node
	memcpy(pnode->msgInfo.msg, msg, strlen(msg) + 1);
	pnode->msgInfo.sendid = sendid;
	pnode->msgInfo.recid = recid;
	pnode->msgInfo.priority = priority;
	pnode->msgInfo.seqnum = seqnum;
	pnode->msgInfo.tbd = tbd;
	memcpy(pnode->msgInfo.szKey, szKey, strlen(szKey));
}

// Function that checks if the queue is empty. Takes in: void. Returns: an integer (0 unless empty).
int isQueueEmpty(){
	return(pHead == NULL); // check if the pointer for the head node points to anything
}

// Function that removes the first node from the queue and returns it and sets the next node to be the head. Takes in: void. Returns: a pointer to a node
node * deQueue(){

	Node * pTemp; // create a pointer to temporarily hold the pointer to the node that is to be removed

	// if the queue is empty, return nothing
	if (pHead == NULL)
		return(NULL);
	pTemp = pHead; // assign the head pointer to the temp pointer
	pHead = pHead->pNext; // set the head pointer to point to the next node
	return(pTemp); // return the desired node
}

// Function which prints the message of a node and goes to a new line. Takes in: the Item of a node. Returns: Void.
void visit(Item msgInfo) {

	// Print the message of the node and go to a new line
	printf("%s\n", msgInfo.msg);
}

// Function which visits each node in a list and prints its message. Takes in: void. Returns: Void.
void travfor() {

	// declare a new node
	Node * pt; 

	// Until the end of the list, visit each node and print the message
	for (pt = pHead; pt != NULL; pt = pt->pNext) {
		visit(pt->msgInfo);
	}
}

// Function which prints the message of a list in reverse order. 
// Takes in: any node from the list, an integer for whether or not it is the first call of the function (anything other than 1 means it is not). Returns: Void.
void travback(Node * theNode, int first) {

	// check if this is the first call of the function, if so start at the head. Also check if the last node has been reached, in which case print the message and exit the current call
	if (first == 1)
		theNode = pHead;
	else if (!theNode->pNext) {
		visit(theNode->msgInfo);
		return;
	}

	// call the function again, using the next node in the list
	travback(theNode->pNext, 0);

	//call the function which prints the message of the current node
	visit(theNode->msgInfo);

}