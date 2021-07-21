/*
 * Output.c
 *
 *  Created on: May 8, 2021
 *      Author: bobby
 */

#include "LinkedList.h"
#include "Stack_and_Queue.h"
#include "String.h"
#include "Tree.h"

bool isAsymmetric(LinkedList input){
	LStack buffer;
	buffer = NewStack(buffer);
	pNode node = input.headNode.pCurrent;
	while(node != NULL){
		push(node->elem,&buffer);
		node = node->pNext;
	}

	bool flag = true;
	node = input.headNode.pCurrent;
	while(node != NULL){
		if(pop(&buffer).elem != node->elem){
			flag = false;
		}
		node = node->pNext;
	}
	return flag;
}

int main(){


	return 0;
}
