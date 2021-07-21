/*
 * Linked_List.h
 *
 *  Created on: May 8, 2021
 *      Author: bobby
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LinkedListNode {
    int elem;
    int freq;
    struct LinkedListNode *pNext;
    struct LinkedListNode *pCurrent;
    struct LinkedListNode *pPrevious;
}Node,*pNode;

typedef struct headList_static{
	Node headNode;
}LinkedList, *pLinkedList;

Node pointerRenew(Node input){
	pNode buffer = input.pCurrent;
	input = *input.pCurrent;
	input.pCurrent = buffer;
	return input;
}

pNode newStaticLinkedList(unsigned int slot){
	pNode list = (Node*)malloc(slot*sizeof(Node));
	for(int i=0;i<sizeof(list)-1;i++){
		if(list[i].pCurrent == NULL){
			list[i].pCurrent = &list[i];
			if(i != 0){
			   list[i-1].pNext = &list[i];
			}
		}
	}
	return list;
}

bool StaticLinkedListAdd(pNode staticL,int elem){
	bool flag = false;
	for(int i =0; i<sizeof(staticL)-1;i++){
		if(staticL[i].freq == -1){
			staticL[i].elem = elem;
			staticL[i].freq = 0;
			flag = true;
			return flag;
		}
	}
	return flag;
}

pNode findNode(unsigned int position, pNode L){
	if(position -1 ==0){
		if(L->pNext == NULL){
			return L;
		}
		return L->pNext;
	}else{
		if(L->pNext == NULL){
			return L;
		}
		position --;
		pNode next = findNode(position,L->pNext);
		return next;
	}
}

void DeleteNode(unsigned int position, pNode L){
	pNode node = findNode(position,L);
	if(node->pNext !=NULL){
		node->pPrevious->pNext = node->pNext;
	    node->pNext->pPrevious = node->pPrevious;
	}
	else{
		node->pPrevious->pNext =NULL;
	}
}

void InsertNode(unsigned int position, pNode L,int elem){
	pNode offsetedNode = findNode(position,L);

	pNode node = (Node*)malloc(sizeof(Node));
	node->elem = elem;
	node->freq = 0;
	node->pNext = offsetedNode;
	node->pPrevious = offsetedNode->pPrevious;

	offsetedNode->pPrevious->pNext = node;
	offsetedNode->pPrevious = node;
}

pNode New (Node n){
	pNode p = (Node*)malloc(sizeof(Node));
	n.pPrevious = NULL;
	n.pNext = NULL;
	n.freq = -1;
	n.elem = 0;
	p = &n;
	n.pCurrent = p;
	return p;
}

void addwithouthead(int elem, pLinkedList list){
	if(list->headNode.freq == -1){
				pNode node = (Node*)malloc(sizeof(Node));
				node->elem = elem;
				node->pCurrent = node;
				node->pNext = NULL;
				node->freq = 0;
				list->headNode.pCurrent = node;
				list->headNode= pointerRenew(list->headNode);
			}
			else
			{
				pNode pointer = list->headNode.pCurrent;
				while(pointer != NULL){
					if(pointer->pNext == NULL){
						pNode node = (Node*)malloc(sizeof(Node));
						node->elem = elem;
						node->pNext = NULL;
						node->pCurrent = node;
						node->freq = 0;
						pointer->pNext = node;
						pointer = pointer->pNext;
					}
					pointer = pointer->pNext;

				}
				list->headNode = pointerRenew(list->headNode);
			}
}

LinkedList addwithHead_single_direction(int elem, LinkedList list){
		if(list.headNode.pNext == NULL){
			pNode node = (Node*)malloc(sizeof(Node));
			node->elem = elem;
			node->pCurrent = node;
			node->pNext = NULL;
			list.headNode.pCurrent->pNext = node;
		}
		else
		{
			pNode pointer = list.headNode.pCurrent;
			while(pointer->pNext != NULL){
				pointer = pointer->pNext;
				if(pointer->pNext == NULL){
					pNode node = (Node*)malloc(sizeof(Node));
					node->elem = elem;
					node->pNext = pointer->pNext;
					node->pCurrent = node;
					pointer->pNext = node;
					pointer = pointer->pNext;
				}

			}
		}
		list.headNode = pointerRenew(list.headNode);
	return list;
}

LinkedList addwithHead_signle_loop(int elem,LinkedList list){
    pNode node=list.headNode.pCurrent;
    if(node->pNext == list.headNode.pCurrent){
    	pNode new = (Node*)malloc(sizeof(Node));
    	new->elem = elem;
    	new->pCurrent = new;
    	new->pNext = list.headNode.pCurrent;
    	node->pNext = new;
    }
    else
    {
    	while(node->pNext != list.headNode.pCurrent){
    		node = node->pNext;
    		if(node->pNext == list.headNode.pCurrent){
    			pNode new = (Node*)malloc(sizeof(Node));
    			new->elem = elem;
    			new->pCurrent = new;
    			new->pNext = list.headNode.pCurrent;
    			node->pNext = new;
        		node = node->pNext;
    		}
        }
    }
    list.headNode = pointerRenew(list.headNode);
    return list;
}

LinkedList addwithHead_double_loop(int elem,LinkedList list){
	Node L = list.headNode;

	if(L.pNext == L.pCurrent){
		pNode node = (Node*)malloc(sizeof(Node));
		node->elem = elem;
		node->pPrevious = list.headNode.pCurrent;
		node->pCurrent = node;
		node->pNext = list.headNode.pCurrent;
	    L.pNext = node;
	    list.headNode = L;
	}
	else
	{
		while(L.pNext != list.headNode.pCurrent){
			L = *L.pNext;
			if(L.pNext == list.headNode.pCurrent){
				pNode node = (Node*)malloc(sizeof(Node));
				node->elem = elem;
				node->pPrevious = L.pCurrent;
				node->pNext = L.pNext;
				node->pCurrent = node;
				L.pNext = node;
				L = *L.pNext;
			}
		}
		L.pCurrent->pPrevious->pNext = L.pCurrent;
		list.headNode.pPrevious = L.pCurrent;
		list.headNode.pCurrent = L.pCurrent->pNext;
	}
	return list;
}

LinkedList addwithHead_double_directional(int elem,LinkedList L){
	pNode node = L.headNode.pCurrent;
	while(node != NULL){
		//node = node->pNext;
		if(node->pNext == NULL){
			pNode new = (Node*)malloc(sizeof(Node));
		    new->elem=elem;
		    new->freq=0;
		    new->pNext = NULL;
		    new->pCurrent = new;
		    new->pPrevious = node;
		    node->pNext = new;
		    node = node->pNext;
		}
		node = node->pNext;
	}
	L.headNode = pointerRenew(L.headNode);
	return L;

}

LinkedList newHead_double_loop(LinkedList list){
	 pNode node = (Node*)malloc(sizeof(Node));
	 node->elem = 0;
	 node->pNext = node;
	 node->pPrevious = node;
	 node->pCurrent = node;
     list.headNode.pCurrent = node;
     list.headNode.pNext = node;
     list.headNode.pPrevious = node;
     return list;
}

LinkedList newHead_single_loop(LinkedList list){
	 pNode node = (Node*)malloc(sizeof(Node));
     node->elem = 0;
	 node->pNext = node;
	 node->pCurrent = node;
     list.headNode.pCurrent = node;
     list.headNode.pNext = node;
     return list;
}

LinkedList newHead_double(LinkedList list){
	pNode node = (Node*)malloc(sizeof(Node));
	node->elem = 0;
	node->freq = -1;
	node->pCurrent = node;
	node->pNext= NULL;
	node->pPrevious = NULL;
	list.headNode.pCurrent = node;
	return list;
}

void clearLinkListNode (int elem,pNode L){
	if(L->elem == elem){
		pNode temp = L;
		L = L->pNext;
		free(temp);
	}
	else if(L->pNext != NULL){
	   clearLinkListNode(elem,L->pNext);
	}
}

LinkedList clearLinkList (int elem,LinkedList L){
	pNode node = L.headNode.pCurrent;

	while(node->pNext !=NULL){
		if(node->pNext->elem == elem){
			pNode temp = node->pNext->pNext;
			free(node->pNext);
			node->pNext = temp;
		}
		if(node->pNext->elem != elem){
			node = node->pNext;
		}
	}

	L.headNode = pointerRenew(L.headNode);
	return L;

}

void reverse_single_direction_print(pNode L){
	if(L!=NULL){
		reverse_single_direction_print(L->pNext);
	    printf("%i\n",L->elem);
	}
}

LinkedList reverse_signle_directional(LinkedList L){
	pNode s; pNode e;
	e=L.headNode.pCurrent;
	while(L.headNode.pCurrent->pNext !=NULL){
		s=L.headNode.pCurrent->pNext;
		L.headNode.pCurrent->pNext = L.headNode.pCurrent->pNext->pNext;
		s->pNext = e;
		e=s;
	}
	L.headNode = *s;
	return L;
}

LinkedList sortAscending(LinkedList L){
	pNode s; pNode e;
	e= L.headNode.pCurrent;
	while(e->pNext != NULL){
		pNode buffer;
		s= L.headNode.pCurrent;
		while(s->pNext!=NULL){
			if(s->pNext->elem <= e->pNext->elem){
				buffer = s;
			}
			s = s->pNext;
		}
		pNode new = (Node*)malloc(sizeof(Node));
		new->elem = buffer->pNext->elem;
		new->pCurrent = new;
		new->pNext = e->pNext;
		new->freq = 0;
		e->pNext = new;
		pNode temp = buffer->pNext;
		buffer->pNext = buffer->pNext->pNext;
		free(temp);

		e = e->pNext;
	}
	L.headNode = pointerRenew(L.headNode);

	return L;
}

LinkedList free_space_by_ascending(LinkedList L){
	pNode headNode = L.headNode.pCurrent;
	while(headNode->pNext != NULL){
		pNode buffer = L.headNode.pCurrent;
		pNode node = L.headNode.pCurrent;
		while(buffer->pNext != NULL){
			if(node->pNext->elem >= buffer->pNext->elem){
				node = buffer;
			}

			buffer = buffer->pNext;
		}
		printf("%i\n",node->pNext->elem);
		pNode freedSpace = node->pNext;
		node->pNext = node->pNext->pNext;
		free(freedSpace);

	}
	L.headNode = pointerRenew(L.headNode);
	return L;

}

LinkedList remove_min_single_directional(LinkedList L){
	pNode pointer = L.headNode.pCurrent;
	pNode cursor = L.headNode.pCurrent;
	while(pointer->pNext != NULL){
		if(pointer->pNext->elem <= cursor->pNext->elem){
			cursor = pointer;
		}
		pointer = pointer->pNext;
	}
	pNode buffer = cursor->pNext->pNext;
	free(cursor->pNext);
	cursor->pNext = buffer;
	L.headNode = pointerRenew(L.headNode);
	return L;
}

pLinkedList evenodd_signle_directional(LinkedList A){
	pNode node = A.headNode.pCurrent;
	int num;
	LinkedList B;
	B.headNode = *New(B.headNode);
	pNode B_buffer = B.headNode.pCurrent;
	while(node->pNext != NULL){
		num = node->pNext->elem;
		if(num%2 == 0){
			B_buffer->pNext =node->pNext;
			node->pNext = node->pNext->pNext;
			B_buffer->pNext->pNext = NULL;
			B_buffer = B_buffer->pNext;
		}
		node = node->pNext;
	}
	B.headNode = pointerRenew(B.headNode);
	pLinkedList two_list = (LinkedList*)malloc(2*sizeof(LinkedList));
	two_list[0] = A;
	two_list[1] = B;
	return two_list;
}

pLinkedList ab_signle_directional(LinkedList L){
	pNode node = L.headNode.pCurrent;
	LinkedList aL;
	aL.headNode = *New(aL.headNode);
	pNode node_a = aL.headNode.pCurrent;
	while(node != NULL){
		node_a->pNext = node->pNext;
		node->pNext = node->pNext->pNext;
		node_a->pNext->pNext = NULL;
		node = node->pNext;
		node_a = node_a->pNext;
	}
	aL.headNode = pointerRenew(aL.headNode);
	L.headNode = pointerRenew(L.headNode);

	pLinkedList two_list = (LinkedList*)malloc(2*sizeof(LinkedList));
	two_list[0] = aL;
	two_list[1] = L;
	return two_list;
}

LinkedList single_directional_distinc(LinkedList L){
	pNode node = L.headNode.pCurrent->pNext;
	while(node->pNext != NULL){
		while(node->elem == node->pNext->elem){
			pNode buffer = node->pNext->pNext;
			free(node->pNext);
			node->pNext = buffer;
		}
		node = node->pNext;
	}
	L.headNode = pointerRenew(L.headNode);
	return L;
}

LinkedList signle_directional_merge_ascend(LinkedList aL, LinkedList bL){
	pNode aNode = aL.headNode.pCurrent;
	pNode bNode = bL.headNode.pCurrent;
	while(aNode->pNext !=NULL){
		while(bNode->pNext !=NULL){
			if(aNode->pNext->elem < bNode->pNext->elem){
				pNode temp = (Node*)malloc(sizeof(Node));
				temp->elem = aNode->pNext->elem;
				temp->pNext = bNode->pNext;
				bNode->pNext = temp;
				break;
			}
			bNode = bNode->pNext;
		}
	    aNode = aNode->pNext;
	}
	bL.headNode = pointerRenew(bL.headNode);
	return bL;

}

LinkedList signle_directional_find_common_item(LinkedList aL, LinkedList bL){
	    pNode aNode = aL.headNode.pCurrent;
		pNode bNode = bL.headNode.pCurrent;
		pNode aBuffer = NULL;
		pNode bBuffer = NULL;
		LinkedList cL;
		cL.headNode = *New(cL.headNode);
		while(aNode->pNext !=NULL && bNode->pNext != NULL){
			if(bNode->pNext == aNode->pNext && cL.headNode.pCurrent->pNext == NULL){
				cL.headNode.pCurrent->pNext = bNode->pNext;
			}

			if(bNode->pNext == NULL){
				bBuffer = bNode;
				break;
			}
			if(aNode->pNext == NULL ){
				aBuffer = aNode;
				break;
			}
			aNode = aNode->pNext;
			bNode = bNode->pNext;
		}

		if(bBuffer == NULL){
			pNode temp = cL.headNode.pCurrent;
			while(temp->pNext!=NULL){
				if(temp->pNext == bBuffer){
					pNode DeletedNode = temp->pNext->pNext;
					temp->pNext->pNext =NULL;
					free(DeletedNode);
				}
				temp=temp->pNext;
			}
		}

		if(aBuffer == NULL){
			pNode temp = cL.headNode.pCurrent;
			while(temp->pNext!=NULL){
				if(temp->pNext == aBuffer){
					pNode DeletedNode = temp->pNext->pNext;
					temp->pNext->pNext = NULL;
					free(DeletedNode);
				}
				temp=temp->pNext;
			}
		}

		cL.headNode = pointerRenew(cL.headNode);

		return cL;

}

bool single_directional_issublist(LinkedList majorL, LinkedList subL){
	bool flag = true;
	pNode node = subL.headNode.pCurrent;
	while(node->pNext != NULL && flag){
		pNode buffer = majorL.headNode.pCurrent;
		while(buffer->pNext != NULL){
			if(node->pNext->elem == buffer->pNext->elem){
				flag = true;
				break;
			}
			else{
				flag = false;
			}
			buffer = buffer->pNext;
		}
		node = node->pNext;
	}
	return flag;
}

LinkedList single_directional_loop_merge(LinkedList h1, LinkedList h2){
	pNode node_h1 = h1.headNode.pCurrent;
	while(node_h1->pNext != h1.headNode.pCurrent){
		node_h1 = node_h1->pNext;
		if(node_h1->pNext == h1.headNode.pCurrent){
			node_h1->pNext = h2.headNode.pCurrent->pNext;
			while(node_h1->pNext != h2.headNode.pCurrent){
				node_h1 = node_h1->pNext;
				if(node_h1->pNext == h2.headNode.pCurrent){
					node_h1->pNext = h1.headNode.pCurrent;
					break;
				}
			}
		}
	 }
	h1.headNode = pointerRenew(h1.headNode);
	return h1;
}

LinkedList single_directinoal_loop_free_assending(LinkedList L){
	pNode node = L.headNode.pCurrent;

	while(node->pNext != L.headNode.pCurrent){
		pNode buffer =L.headNode.pCurrent;
		pNode temp = L.headNode.pCurrent;
		while(buffer->pNext != L.headNode.pCurrent){
			if(buffer->pNext->elem <= temp->pNext->elem){
				temp = buffer;
			}
			buffer = buffer->pNext;
		}
		printf("%i\n",temp->pNext->elem);
		pNode freeNode = temp->pNext;
		temp->pNext = temp->pNext->pNext;
		free(freeNode);
	}

	L.headNode = pointerRenew(L.headNode);
	return L;
}

LinkedList double_directional_locate(int elem,LinkedList L){
	pNode node = L.headNode.pCurrent;
	while(node->pNext !=NULL){
		if(node->pNext->elem == elem){
			node->pNext->freq ++;
			pNode renew = node->pNext;
			pNode buffer = node;
			while(buffer != L.headNode.pCurrent){
				if(buffer->freq > node->pNext->freq){
					node->pNext = node->pNext->pNext;
					renew->pNext = buffer->pNext;
					buffer->pNext = renew;
					break;
				}
				else if(buffer->pPrevious == L.headNode.pCurrent){
					node->pNext = node->pNext->pNext;
					renew->pNext = L.headNode.pCurrent->pNext;
					L.headNode.pCurrent->pNext = renew;
				}
				buffer = buffer->pPrevious;
			}
			break;
		}
		node = node->pNext;
	}
	L.headNode = pointerRenew(L.headNode);
	return L;
}

LinkedList single_directional_merge(LinkedList main,LinkedList sub){
	pNode node = main.headNode.pCurrent;
	while(node->pNext != NULL){
		node = node->pNext;
		if(node->pNext == NULL){
			node->pNext = sub.headNode.pNext;
			break;
		}
	}
	main.headNode = pointerRenew(main.headNode);
	return main;
}

#endif /* LINKEDLIST_H_ */
