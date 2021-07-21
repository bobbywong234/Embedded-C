/*
 * Stack_and_Queue.h
 *
 *  Created on: May 6, 2021
 *      Author: bobby
 */

#ifndef STACK_AND_QUEUE_H_
#define STACK_AND_QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stack_node{
     int elem;
     char cElem;
     struct stack_node *current;
     struct stack_node *previous;
     struct stack_node *next;
}sNode, *pSNode;

typedef struct SeqQueueStructure{
	int* data;
	int rear;
	int front;
	int MaxSize;
	bool overOneLap;
}seqQueue, *pSeqQueue;

typedef struct LinkedQueueStructure{
	sNode data;
	pSNode entranceNode;
	int rear;
	int front;
	int MaxSize;
}linkedQueue, *plinkedQueue;

typedef struct sequntial_stack {
	int top;
	int* data;
	int MaxSize;
}seqStack,*pSeqStack;

typedef struct Linked_stack {
	pSNode top;
	sNode Startnode;
	bool legal;
}LStack, *pLStack;

typedef struct shared_stack {
	int top0;
	int* data0;
	int top1;
	int* data1;
	int MaxSize;
}sharedStack, *pSharedStack;

void initialLinkedQueue(int maxSize,plinkedQueue pq){
	pSNode node = (sNode*)malloc(sizeof(sNode));
	node->current = NULL;
	node->next = NULL;
	pq->data = *node;
	pq->front = 0;
	pq->rear = 0;
	pq->MaxSize = maxSize;
	pq->entranceNode = pq->data.current;
}

void initialSeqQueue(int maxSize,pSeqQueue pq){
	pq->front =0;
	pq->rear =0;
	pq->MaxSize = maxSize;
	pq->data = (int*)malloc(maxSize * sizeof(int));
}

void initialSeqLoopQueue(int maxSize,pSeqQueue pq){
	pq->front = 0;
	pq->rear = maxSize-1;
	pq->MaxSize = maxSize;
	pq->overOneLap = false;
	pq->data = (int*)malloc(maxSize * sizeof(int));
}

void linkedListEnqueue(int elem, plinkedQueue pL){
	if(pL->rear >= pL->MaxSize){
		return;
	}

	pSNode node = pL->entranceNode;
	if(node == NULL){
		pSNode new = (sNode*)malloc(sizeof(sNode));
		new->elem = elem;
		new->next = NULL;
		pL->data = *new;
		pL->data.current = new;
		pL->entranceNode = new;

	}
	else if(node->next == NULL) {
		pSNode new = (sNode*)malloc(sizeof(sNode));
		new->elem = elem;
		new->next = NULL;
		pL->entranceNode->next = new;
		pL->entranceNode = pL->entranceNode->next;
		pSNode buffer = pL->data.current;
		pL->data = *pL->data.current;
		pL->data.current = buffer;
	}
	pL->rear ++;

}

void linkedListEnqueueChar(char elem, plinkedQueue pL){
	if(pL->rear >= pL->MaxSize){
		return;
	}

	pSNode node = pL->entranceNode;
	if(node == NULL){
		pSNode new = (sNode*)malloc(sizeof(sNode));
		new->cElem = elem;
		new->next = NULL;
		pL->data = *new;
		pL->data.current = new;
		pL->entranceNode = new;
	}
	else if(node->next == NULL) {
		pSNode new = (sNode*)malloc(sizeof(sNode));
		new->cElem = elem;
		new->next = NULL;
		pL->entranceNode->next = new;
		pL->entranceNode = pL->entranceNode->next;
		pSNode buffer = pL->data.current;
		pL->data = *pL->data.current;
		pL->data.current = buffer;
	}
	pL->rear++;

}

int linkedListDequeue(plinkedQueue pL){
	if(pL->front == pL->rear){
		return 0;
	}

	pSNode node = pL->data.current;
	int data = node->elem;
	if(node->next == NULL){
		free(pL->data.current);
		pL->data.current = NULL;
		pL->entranceNode = NULL;
		pL->data.elem = 0;
		pL->front=0;
		pL->rear=0;
		pL->data = *pL->data.current;
		return data;
	}
	else{
		free(pL->data.current);
		pL->data.current = node->next;
		pL->data = *pL->data.current;
		pL->data.current = node->next;
		pL->rear --;
		return data;
	}
}

char linkedListDequeueChar(plinkedQueue pL){
	if(pL->front == pL->rear){
		return 0;
	}

	pSNode node = pL->data.current;
	char data = node->cElem;
	if(node->next == NULL){
		free(pL->data.current);
		pL->data.current = NULL;
		pL->entranceNode = NULL;
		pL->data.elem = 0;
		pL->front=0;
		pL->rear=0;
		pL->data.cElem = 0;
		return data;
	}
	else{
		free(pL->data.current);
		pL->data.current = node->next;
		pL->data = *pL->data.current;
		pL->data.current = node->next;
		pL->rear -- ;
		return data;
	}
}

void SeqEnqueue(int elem,pSeqQueue sq){
	if(sq->rear == sq->MaxSize){
		return;
	}
	else{
		sq->data[sq->rear] = elem;
		if(sq->rear != sq->MaxSize)
		sq->rear++;
	}
}

int SeqDequeue(int elem,pSeqQueue sq){
	int data;
	if(sq->rear == sq->front){
		sq->rear = 0;
		sq->front = 0;
		return 0;
	}
	else{
		data = sq->data[sq->front];
		sq->data[sq->front] = 0;
		if(sq->front != sq->rear)
		sq->front++;
	}
	return data;
}

void SeqLoopEnqueue(int elem, pSeqQueue sq){
	if((sq->rear+1)%sq->MaxSize == sq->front){
		if(sq->overOneLap == false){
			sq->rear = (sq->rear+1)%sq->MaxSize;
			sq->data[sq->rear] = elem;
			sq->overOneLap = true;
		}
		return;
	}
	sq->data[(sq->rear+1)%sq->MaxSize] = elem;
	sq->rear =(sq->rear+1)%sq->MaxSize;
}

void SeqLoopDequeue(pSeqQueue sq){
	if((sq->rear+1)%sq->MaxSize == sq->front && sq->overOneLap == false){
		return;
	}

	if(sq->front == sq->rear && sq->overOneLap == true){
		sq->data[sq->front] = 0;
		sq->overOneLap = false;
		sq->front =(sq->front+1)%sq->MaxSize;
		return;
	}
	sq->data[sq->front % sq->MaxSize] = 0;
	sq->front = (sq->front+1) % sq->MaxSize;
}

pSeqStack newSeqStack(int MaxSize,pSeqStack S){
	S = (seqStack*)malloc(sizeof(seqStack));
	S->MaxSize = MaxSize;
	S->top = 0;
	S->data = (int*)malloc(MaxSize * sizeof(int));
	return S;
}

void newSharedStack(int Maxsize, pSharedStack p){
	p->top0 = -1;
	p->top1 = Maxsize-1;
	p->data1 = (int*)malloc((Maxsize/2+Maxsize%2) * sizeof(int));
	p->data0 = (int*)malloc(Maxsize/2 * sizeof(int));
	p->MaxSize = Maxsize;
}

void pushSharedStack(int elem, pSharedStack p){
	if(p->top1 - p->top0 == 0){
		return;
	}

	if(p->top1 + p->top0 + 2 == p->MaxSize){
		p->data0[++p->top0] = elem;
		return;
	}
	else{
		p->top1 --;
		p->data1[p->top1/2] = elem;
		return;
	}
}

void popSharedStack (pSharedStack p){
	if(p->top1 - p->top0+2 == p->MaxSize){
		return;
	}

	if(p->top1 - p->top0 == 0){
		p->data0[p->top0] =0;
		p->top0--;
		return;
	}
	else{
		p->data1[(p->top1/2)]=0;
		p->top1++;
		return;
	}
}

void seqStackPush(int elem, pSeqStack S){
	if(S->top==S->MaxSize){
		return;
	}
    S->data[S->top] = elem;
    S->top ++;
}

int seqStackPop(pSeqStack S){
	if(S->top== -1){
		return 0;
	}
	S->top --;
	int data = S->data[S->top];
	S->data[S->top] = 0;
    return data;
}

sNode stackRenew(sNode input){
	pSNode buffer = input.current;
	input = *input.current;
	input.current = buffer;
	return input;
}

LStack NewStack(LStack input){
	pSNode new = (sNode*)malloc(sizeof(sNode));
	new->elem = 0;
	new->next = NULL;
	input.Startnode = *new;
	input.Startnode.current = new;
	input.top = new;
    return input;
}

void push(int elem, pLStack L){
	pSNode node = L->Startnode.current;
	while(node != NULL){
		if(node->next == NULL){
			pSNode new = (sNode*)malloc(sizeof(sNode));
			new->elem = elem;
			new->next = NULL;
			node->next = new;
			L->top = new;
			break;
		}
		node = node->next;
	}
	node = L->Startnode.current;
	L->Startnode = *node;
	L->Startnode.current = node;
}

void pushChar(char elem, pLStack L){
	pSNode node = L->Startnode.current;
	while(node != NULL){
		if(node->next == NULL){
			pSNode new = (sNode*)malloc(sizeof(sNode));
			new->cElem = elem;
			new->next = NULL;
			node->next = new;
			L->top = new;
			break;
		}
		node = node->next;
	}
	node = L->Startnode.current;
	L->Startnode = *node;
	L->Startnode.current = node;
}

sNode pop (pLStack S){
	pSNode node = S->Startnode.current;
	sNode result;
	if(node->next !=NULL)
	{if(node->next->next == NULL){
		result = *node->next;
		node->next = NULL;
		S->Startnode.current = node;
		S->Startnode = *S->Startnode.current;
		S->Startnode.current = node;
		free(node->next);
		S->top = NULL;
		return result;
	}}

	while(node->next != NULL){
		if(node->next->next == NULL){
			result = *node->next;
			free(node->next);
			node->next = NULL;
			S->top = node;
		}
		else
		 node = node->next;
	}
	return result;
}

bool expressionBracketMatch(char* expression){
	LStack temp;
	temp = NewStack(temp);
	bool flag = true;
	int length = strlen(expression);
	for(int i=0;i<length;i++){
		if(expression[i] == '{'
			|| expression[i] == '['
			|| expression[i] == '('
		){
			pushChar(expression[i], &temp);
		}

		if(expression[i] == '}'
			|| expression[i] == ']'
			|| expression[i] == ')'
		){
			switch(temp.top->cElem){
		     	case '{':
		     		if(expression[i] == '}'){
		     			flag = true;
		     			pop(&temp);
		     		}
		     		else{
		     			flag=false;
		     			break;
		     		}
				break;
		     	case '(':
		     		if(expression[i] == ')'){
		     		    flag = true;
		     		    pop(&temp);
		     		}
		     		else{
		     			flag = false;
		     			break;
		     		}
		     	break;

		     	case '[':
		     		if(expression[i] == ']'){
		     		     flag = true;
		     		     pop(&temp);
		     		}
		     		else{
		     			 flag=false;
		     		     break;
		     	    }
		     	break;
		    }
		}

		if(flag == false){
			break;
		}
	}
	return flag;
}

LStack schduleTrain (pLStack l){
	LStack out;LStack exchange;
	out = NewStack(out);
	exchange = NewStack(exchange);
	while(l->Startnode.next !=NULL){
		char train = pop(l).cElem;
		if(train == 'H'){
			pushChar(train,&exchange);
		}
		else{
			while(exchange.top !=NULL && exchange.top->cElem == 'H'){
				pushChar(pop(&exchange).cElem,&out);
			}
			pushChar(train,&exchange);
		}
	}

	while(exchange.top !=NULL){
		pushChar(pop(&exchange).cElem,&out);
	}
	return out;


}

int functionCalculation (int n,int x){
	if(n == 0){
		return 1;
	}

	if(n == 1){
		return 2*x;
	}

	int result = 0;
	if(n>1){
		seqStack sq;
		newSeqStack(n,&sq);
		for(int i=0;i<n;i++){
			if(i == 0){
				seqStackPush(1,&sq);
			}

			if(i == 1){
				seqStackPush(2*x,&sq);
			}


			if(i > 1){
				int firstF=seqStackPop(&sq);
				int secondF=seqStackPop(&sq);
			    result = 2*x*firstF-2*(n-1)*secondF;
				if(i < n-1)
				{secondF = firstF;
				seqStackPush(secondF,&sq);
				seqStackPush(result,&sq);}
			}
		}
	}
	return result;
}

pSNode onBoarding(plinkedQueue pq){
	pSNode ship = (sNode*)malloc(10*sizeof(sNode));
	int carN=0;
	int shipSlot=0;
	bool isTrcukEntred = false;
	int rear =0;
	while(pq->rear != 0){
		char automobile = linkedListDequeueChar(pq);
		if(automobile == 'C'){
			ship[shipSlot].cElem = automobile;
			shipSlot++;
			carN++;
			isTrcukEntred = false;
		}
		else if(automobile == 'T'
				&&
				((carN+1)%4 == 0||(carN+1)/4 <1) &&
				!isTrcukEntred){
			ship[shipSlot].cElem = automobile;
			shipSlot++;
			if((carN+1)/4 > 1)
			isTrcukEntred = true;
		}
		else{
			linkedListEnqueueChar(automobile,pq);
			rear ++;
			if(rear == pq->rear){
				carN =0;
				isTrcukEntred=false;
			}
		}
	}

	return ship;
}
#endif /* STACK_AND_QUEUE_H_ */
