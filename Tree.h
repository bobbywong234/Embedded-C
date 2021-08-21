/*
 * Tree.h
 *
 *  Created on: Jul 3, 2021
 *      Author: bobby
 */

#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNodeStructure{
	int serialNum;
	char data;
	int lchildIndex;
	int rchildIndex;
	struct BinaryParentStruct *node;
}TreeNode,*pTreeNode;

typedef struct sequntial_stack_tree {
	int top;
	pTreeNode* treeNodes;
}seqStackT,*pSeqStackT;

typedef struct BinaryParentStruct {
	pTreeNode *childNode;
}BinaryTree, *pBinaryTree;

typedef struct TreeQueuenode{
	 pTreeNode treeNode;
     struct TreeQueuenode *current;
     struct TreeQueuenode *previous;
     struct TreeQueuenode *next;
}tQNode, *pTQNode;

typedef struct TreeNodeLinkedQueue{
	tQNode data;
	pTQNode entranceNode;
	int rear;
	int front;
}tLinkedQueue, *tPlinkedQueue;

tPlinkedQueue initialLinkedQueueTree(tPlinkedQueue pq){
	if(pq == NULL)
		pq = (tLinkedQueue*)malloc(sizeof(tLinkedQueue));

	pTQNode node = (tQNode*)malloc(sizeof(tQNode));
	node->current = NULL;
	node->next = NULL;
	pq->data = *node;
	pq->front = 0;
	pq->rear = 0;
	pq->entranceNode = pq->data.current;
	return pq;
}

void linkedListEnqueueTree(pTreeNode elem, tPlinkedQueue pL){
	pTQNode node = pL->entranceNode;
	if(node == NULL){
		pTQNode new = (tQNode*)malloc(sizeof(tQNode));
		new->treeNode= elem;
		new->next = NULL;
		pL->data = *new;
		pL->data.current = new;
		pL->entranceNode = new;
	}
	else if(node->next == NULL) {
		pTQNode new = (tQNode*)malloc(sizeof(tQNode));
		new->treeNode = elem;
		new->next = NULL;
		pL->entranceNode->next = new;
		pL->entranceNode = pL->entranceNode->next;
		pTQNode buffer = pL->data.current;
		pL->data = *pL->data.current;
		pL->data.current = buffer;
	}
	pL->rear++;

}

pTreeNode linkedListDequeueTree(tPlinkedQueue pL){
	if(pL->front == pL->rear){
		return NULL;
	}

	pTQNode node = pL->data.current;
	pTreeNode data = node->treeNode;
	if(node->next == NULL){
		free(pL->data.current);
		pL->data.current = NULL;
		pL->entranceNode = NULL;
		pL->data.treeNode = NULL;
		pL->front=0;
		pL->rear=0;
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

void seqStackPushTree(pTreeNode elem, pSeqStackT S){
    S->top ++;
    S->treeNodes = (pTreeNode*)realloc(S->treeNodes,S->top*sizeof(pTreeNode));
    S->treeNodes[S->top-1] = elem;
}

pTreeNode seqStackPopTree(pSeqStackT S){
	if(S->top== -1){
		return NULL;
	}
	S->top --;
	pTreeNode node = S->treeNodes[S->top];
	S->treeNodes[S->top] = NULL;
    return node;
}

pSeqStackT newSeqStackTree(pSeqStackT S){
	S = (seqStackT*)malloc(sizeof(seqStackT));
	S->top = 0;
	S->treeNodes = (pTreeNode*)malloc(1 * sizeof(pTreeNode));
	return S;
}

pSeqStackT MergeSeqStackTree(pSeqStackT before, pSeqStackT after){
	int len = before->top;
	for(int i=0;i<len;i++){
		seqStackPushTree(seqStackPopTree(before),after);
	}
	free(before);
	return after;
}

pTreeNode newNode(char data,int num){
	pTreeNode node = (TreeNode*)malloc(sizeof(TreeNode));
	node->data = data;
	node->serialNum = num;
	node->node = (BinaryTree*)malloc(sizeof(BinaryTree));
	node->node->childNode = (pTreeNode*)malloc(2*sizeof(pTreeNode));
	node->node->childNode[0] = NULL;
	node->node->childNode[1] = NULL;
	node->lchildIndex = 0;
	node->rchildIndex = 0;
	return node;
}

void SearchandInsert(pTreeNode root,char data,int* path,int pathLen){
	if(path[pathLen]%2 == 0){
		if(root->node->childNode[0] != NULL && pathLen==0){
			root->node->childNode[0]->data = data;
		}

		if(root->node->childNode[0] == NULL && pathLen==0){
			root->node->childNode[0] = newNode(data,path[pathLen]);
		}

		if(root->node->childNode[0] != NULL && pathLen!=0)
        {
			pathLen--;
			path = (int*)realloc(path,pathLen*sizeof(int));
			SearchandInsert(root->node->childNode[0],data,path,pathLen);
		}
	}
	else{
		if(root->node->childNode[1] != NULL && pathLen==0){
			root->node->childNode[1]->data = data;
		}

		if(root->node->childNode[1] == NULL && pathLen==0){
			root->node->childNode = (pTreeNode*)realloc(root->node->childNode,2*sizeof(pTreeNode));
			root->node->childNode[1] = newNode(data,path[pathLen]);
		}

		if(root->node->childNode[1] != NULL && pathLen!=0)
		{
		    pathLen--;
			path = (int*)realloc(path,pathLen*sizeof(int));
			SearchandInsert(root->node->childNode[1],data,path,pathLen);
		}
	}
}

void BTreeAppend (pTreeNode root,char data,int serialNum){
	int* path = (int*)malloc(sizeof(int));
	int num = serialNum,index=-1;
	while(num/2!=0){
		path[++index] = num;
		num = num/2;
		if(num/2 !=0)
			path = (int*)realloc(path,(index+1)*sizeof(int));
	}
	SearchandInsert(root,data,path,index);
}

int GetPublicParentSerial(int i, int j){
	int iParent = i/2;
	int jParent = j/2;
	if(iParent == jParent){
		return iParent;
	}
	else{
		return GetPublicParentSerial(iParent,jParent);
	}
}

TreeNode BinaryTreeFindNode(pTreeNode root,int* path,int pathLen){
	TreeNode output;
	for(int i=0;i<2;i++){
		if(root->node->childNode[i]->serialNum==path[pathLen]){
			if(pathLen == 0)
				return *root->node->childNode[i];

			path = (int*)realloc(path,(pathLen-1)*sizeof(int));
			output=BinaryTreeFindNode(root->node->childNode[i],path,pathLen-1);
		}
	}
	return output;
}

TreeNode GetPublicParent(pTreeNode parent,int i, int j){
	int publicSerialNum = GetPublicParentSerial(i,j);
	if(publicSerialNum == 1)
		return *parent;
	else{
		int* path = (int*)malloc(sizeof(int));
		int index = 0;
		while (publicSerialNum!=1){
			path = (int*)realloc(path,(index+1)*sizeof(int));
			path[index] = publicSerialNum;
			publicSerialNum = publicSerialNum/2;
			index++;
		}
		return BinaryTreeFindNode(parent,path,index-1);

	}
}


pSeqStackT LevelOrder (pTreeNode root,tPlinkedQueue queue,int* level){
	if(queue == NULL){
		queue = initialLinkedQueueTree(queue);
		linkedListEnqueueTree(root,queue);
		return LevelOrder(root, queue, level);
	}
	else{
		pSeqStackT levelNodes = (seqStackT*)malloc(sizeof(seqStackT));
		levelNodes = newSeqStackTree(levelNodes);
		int len = queue->rear;
		for(int i=0; i<len;i++){
			pTreeNode treeNode = linkedListDequeueTree(queue);
			seqStackPushTree(treeNode,levelNodes);
			if(treeNode->node->childNode[0]!=NULL)
			linkedListEnqueueTree(treeNode->node->childNode[0],queue);
			if(treeNode->node->childNode[1]!=NULL)
			linkedListEnqueueTree(treeNode->node->childNode[1],queue);
		}

		level[0] += 1;

		if(queue->rear == 0)
		 return levelNodes;


		pSeqStackT recessiveLevel = LevelOrder(root, queue, level);
		levelNodes = MergeSeqStackTree(levelNodes,recessiveLevel);

		return levelNodes;
	}
}

int TwoBranchNodeNumber (pTreeNode root,tPlinkedQueue queue,int number){
	if(queue == NULL){
		queue = initialLinkedQueueTree(queue);
		linkedListEnqueueTree(root,queue);
		number = 0;
		return TwoBranchNodeNumber(root, queue, number);
	}
	else{
		int len = queue->rear;
		int twoBranch =0;
		for(int i=0; i<len;i++){
			pTreeNode treeNode = linkedListDequeueTree(queue);
			if(treeNode->node->childNode[0]!=NULL){
				linkedListEnqueueTree(treeNode->node->childNode[0],queue);
				twoBranch ++;
			}
			if(treeNode->node->childNode[1]!=NULL){
				linkedListEnqueueTree(treeNode->node->childNode[1],queue);
				twoBranch ++;
			}
			number += twoBranch/2;
			twoBranch =0;
		}

		if(queue->rear == 0)
		 return number;

		return TwoBranchNodeNumber(root, queue, number);


	}
}

pTreeNode* PreOrder(pTreeNode root,pSeqStackT buffer,pTreeNode* branch,int* currentIndex,int len){
	if(buffer==NULL){
		//branch = (pTreeNode*)malloc(sizeof(pTreeNode));
		buffer = newSeqStackTree(buffer);
		if(currentIndex == NULL)
		{
			currentIndex = (int*)malloc(sizeof(int));
			currentIndex[0] = 1;
		}
		seqStackPushTree(root, buffer);
	}

	if(root != NULL){
		if(root->node->childNode[0] == NULL)
			root->lchildIndex = 1;
		if(root->node->childNode[1] == NULL)
			root->rchildIndex = 1;
		currentIndex[0]++;
		branch = (pTreeNode*)realloc(branch,currentIndex[0]*sizeof(pTreeNode));
		branch[currentIndex[0]-1] = root;
		if(currentIndex[0] == len)
			return branch;
		 seqStackPushTree(root->node->childNode[0], buffer);
		 root = root->node->childNode[0];
		 branch = PreOrder(root,buffer,branch,currentIndex,len);
	}
	else{
		pTreeNode treeNode = seqStackPopTree(buffer);
		if(buffer->top == 0)
			return branch;
		treeNode = seqStackPopTree(buffer);
		seqStackPushTree(treeNode->node->childNode[1], buffer);
		root = treeNode->node->childNode[1];
		branch = PreOrder(root,buffer,branch,currentIndex,len);

	}
	return branch;
}

pTreeNode* IndexedPreOrder (pSeqStackT buffer,pTreeNode* branch,int currentIndex,int len){
	pTreeNode node = buffer->treeNodes[buffer->top-1];
	if(node != NULL){
		branch = (pTreeNode*)realloc(branch,(currentIndex+2)*sizeof(pTreeNode));
		branch[++currentIndex] = node;

		if(node->lchildIndex != 1){
			if(node->node->childNode[0]->lchildIndex == 1){
			   branch = (pTreeNode*)realloc(branch,(currentIndex+2)*sizeof(pTreeNode));
			   pTreeNode temp = seqStackPopTree(buffer);
			   branch[++currentIndex] = temp->node->childNode[0];
			   if(node->rchildIndex != 1)
			       seqStackPushTree(node->node->childNode[1], buffer);
			   else{
				   if(buffer->top == 0 || currentIndex == len)
				   		return branch;
				   seqStackPushTree(seqStackPopTree(buffer)->node->childNode[1], buffer);
			   }
			}
			else
				seqStackPushTree(node->node->childNode[0], buffer);
		}else{
			seqStackPushTree(node->node->childNode[1], buffer);
		}

		if(buffer->top == 0 || currentIndex == len)
			return branch;
		branch = IndexedPreOrder(buffer,branch,currentIndex,len);
	}
	else{
		seqStackPopTree(buffer);
		seqStackPopTree(buffer);
		seqStackPushTree(seqStackPopTree(buffer)->node->childNode[1], buffer);

		branch = IndexedPreOrder(buffer,branch,currentIndex,len);
	}
	return branch;
}

pTreeNode* InOrder (pTreeNode root,pSeqStackT buffer,pTreeNode* branch,int* currentIndex,int len){
	   if(buffer==NULL){
			//branch = (pTreeNode*)malloc(sizeof(pTreeNode));
			buffer = newSeqStackTree(buffer);
			if(currentIndex == NULL)
			{
				currentIndex = (int*)malloc(sizeof(int));
				currentIndex[0] = 1;
			}
			seqStackPushTree(root, buffer);
		}


	    if(root != NULL){
			if(currentIndex[0] == len)
				return branch;

			 seqStackPushTree(root->node->childNode[0], buffer);
			 branch = InOrder(root->node->childNode[0],buffer,branch,currentIndex,len);
		}
		else{
			pTreeNode treeNode = seqStackPopTree(buffer);
			if(buffer->top == 0)
				return branch;
			treeNode = seqStackPopTree(buffer);
			if(treeNode->node->childNode[0] == NULL)
				treeNode->lchildIndex = 1;
			if(treeNode->node->childNode[1] == NULL)
				treeNode->rchildIndex = 1;
			currentIndex[0]++;
			branch = (pTreeNode*)realloc(branch,(currentIndex[0])*sizeof(pTreeNode));
			branch[currentIndex[0]-1] = treeNode;
			seqStackPushTree(treeNode->node->childNode[1], buffer);

			branch = InOrder(treeNode->node->childNode[1],buffer,branch,currentIndex,len);

		}
		return branch;
}

pTreeNode* IndexedInOrder (pSeqStackT buffer, pTreeNode* branch,int currentIndex, int len){
	if(buffer->top == 0 || currentIndex == len)
		return branch;

	pTreeNode node = buffer->treeNodes[buffer->top-1];
	if(node !=NULL){
		if(node->lchildIndex != 1){
			if(node->node->childNode[0]->lchildIndex == 1){
				pTreeNode treeNode = seqStackPopTree(buffer);
				branch = (pTreeNode*)realloc(branch,(currentIndex+2)*sizeof(pTreeNode));
				branch[++currentIndex] = treeNode->node->childNode[0];
				branch = (pTreeNode*)realloc(branch,(currentIndex+2)*sizeof(pTreeNode));
				branch[++currentIndex] = treeNode;
				if(treeNode->node->childNode[0]->rchildIndex != 1)
					seqStackPushTree(treeNode->node->childNode[0]->node->childNode[1], buffer);
				else{
					if(treeNode->rchildIndex !=1){
					    seqStackPushTree(treeNode->node->childNode[1], buffer);
					}
					else{
						if(buffer->top == 0 || currentIndex == len)
							return branch;
						 treeNode = seqStackPopTree(buffer);
						 branch = (pTreeNode*)realloc(branch,(currentIndex+2)*sizeof(pTreeNode));
						 branch[++currentIndex] = treeNode;
						 seqStackPushTree(treeNode->node->childNode[1], buffer);
					}
				}
			}else
				seqStackPushTree(node->node->childNode[0], buffer);
		}else
			seqStackPushTree(node->node->childNode[0], buffer);

		branch = IndexedInOrder(buffer,branch,currentIndex,len);

	}else{
		seqStackPopTree(buffer);
		pTreeNode treeNode = seqStackPopTree(buffer);
		branch = (pTreeNode*)realloc(branch,(currentIndex+2)*sizeof(pTreeNode));
		branch[++currentIndex] = treeNode;
		if(treeNode->rchildIndex != 1)
			seqStackPushTree(treeNode->node->childNode[1], buffer);
		else{
			if(buffer->top == 0 || currentIndex == len)
					return branch;

			treeNode = seqStackPopTree(buffer);
			branch = (pTreeNode*)realloc(branch,(currentIndex+2)*sizeof(pTreeNode));
			branch[++currentIndex] = treeNode;
			seqStackPushTree(treeNode->node->childNode[1], buffer);
		}

		branch = IndexedInOrder(buffer,branch,currentIndex,len);
	}

	return branch;
}

pTreeNode* PostOrder (pTreeNode root,pSeqStackT buffer, pTreeNode* branch, int* size, int len){
	if(buffer == NULL){
		buffer = newSeqStackTree(buffer);
		seqStackPushTree(root,buffer);
	}
	if(branch == NULL){
		if(size == NULL)
		{size = (int*)malloc(sizeof(int));
		size[0] = 1;}
		branch = (pTreeNode*)malloc(sizeof(pTreeNode));
	}

	if(root!=NULL){
		if(root->node->childNode[0] != NULL)
		    seqStackPushTree(root->node->childNode[0],buffer);
		else
			root->lchildIndex = 1;

		branch = PostOrder(root->node->childNode[0],buffer,branch,size,len);

		if(root->node->childNode[1] != NULL)
		    seqStackPushTree(root->node->childNode[1],buffer);
		else
			root->rchildIndex = 1;

		branch = PostOrder(root->node->childNode[1],buffer,branch,size,len);

		if(buffer->top == 0)
			return branch;

		int temp = size[0];

		temp++;
		branch = (pTreeNode*)realloc(branch,temp*sizeof(pTreeNode));
		branch[temp-1] = seqStackPopTree(buffer);
		size[0] = temp;

		if(temp >= len)
		return branch;
	}

    return branch;
}

pTreeNode* IndexedPostOrder (pTreeNode root,pSeqStackT buffer, pTreeNode* branch, int* size, int len){
	if(buffer == NULL){
		buffer = newSeqStackTree(buffer);
		seqStackPushTree(root,buffer);
	}
	if(branch == NULL){
		size = (int*)malloc(sizeof(int));
		size[0] = 1;
		branch = (pTreeNode*)malloc(sizeof(pTreeNode));
	}

	if(root!=NULL){
			if(root->lchildIndex == 1){
				 seqStackPushTree(root->node->childNode[1],buffer);
                 branch = IndexedPostOrder(root->node->childNode[1],buffer,branch,size,len);
			}
			else{
				 seqStackPushTree(root->node->childNode[0],buffer);
				 branch = IndexedPostOrder(root->node->childNode[0],buffer,branch,size,len);
			}

			if(root->rchildIndex == 1){
                pTreeNode tempNode = seqStackPopTree(buffer);
                if(tempNode != NULL){
                	 seqStackPushTree(tempNode,buffer);
                	 branch = IndexedPostOrder(tempNode->node->childNode[1],buffer,branch,size,len);
                }
			}
			else{
				seqStackPushTree(root->node->childNode[1],buffer);
				branch = IndexedPostOrder(root->node->childNode[1],buffer,branch,size,len);
			}

			if(buffer->top == 0)
				return branch;


			int temp = size[0];

			temp++;
			branch = (pTreeNode*)realloc(branch,temp*sizeof(pTreeNode));
			branch[temp-1] = seqStackPopTree(buffer);

			size[0] = temp;
			if(temp >= len)
			return branch;
		}

	return branch;
}


pTreeNode* Tranverse(pTreeNode root,int len,int tranverseMode){
	pSeqStackT buffer;
	buffer = newSeqStackTree(buffer);
	seqStackPushTree(root,buffer);
	if(buffer->treeNodes[buffer->top-1]->node->childNode == NULL){
		return NULL;
	}

	pTreeNode* result = (pTreeNode*)malloc(sizeof(pTreeNode));
	switch (tranverseMode){
	case 1:
		result =PreOrder(root,NULL,NULL,NULL,len);
		break;
	case 2:
		result =InOrder(root,NULL,NULL,NULL,len);
		break;
	case 3:
		result =PostOrder(root,NULL,NULL,NULL,len);
		break;
	case 4:
		result = IndexedPreOrder(buffer,result,0,len);
		break;
	case 5:
		result = IndexedInOrder(buffer,result,0,len);
		break;
	case 6:{
		result = IndexedPostOrder(root,NULL,NULL,NULL,len);
		break;
	   }
	}
	buffer = (pSeqStackT)realloc(buffer,0);
	buffer = NULL;
	return result;
}

pTreeNode BTreeBuilding(pTreeNode preOrder,pTreeNode inOrder, int totalLen){
	if(preOrder[1].node == NULL && inOrder[1].node == NULL)
		return NULL;

	TreeNode treeNode;
	pTreeNode root;
	pTreeNode result;
	pSeqStackT buffer = newSeqStackTree(buffer);

	int len =1; int lenlDivided = 0;int lenCompare = 0;int lenrDivided = 0;bool isRoot = false;
	while(treeNode.node != NULL && len <= totalLen){
		treeNode = preOrder[len];
		TreeNode treeNodeCompare;
		while(treeNode.serialNum != treeNodeCompare.serialNum){
			lenlDivided ++;
			treeNodeCompare = inOrder[lenlDivided];
			if(treeNode.serialNum == treeNodeCompare.serialNum){
				if(lenCompare - lenlDivided - 1 == 0){
					pTreeNode temp;
					if(buffer->top != 1)
						temp = seqStackPopTree(buffer);
					else{
						temp = buffer->treeNodes[buffer->top-1];
					}

					if(inOrder[lenCompare+1].serialNum != buffer->treeNodes[buffer->top-1]->serialNum){
						root->data = treeNode.data;
						root->serialNum = treeNode.serialNum;
						root->node = (BinaryTree*)malloc(sizeof(BinaryTree));
						root->node->childNode = (pTreeNode*)malloc(2*sizeof(pTreeNode));
						root->node->childNode[0] = NULL;
						root->node->childNode[1] = NULL;
				     	lenlDivided = lenCompare;
				    	lenrDivided = lenCompare;
				    	if(inOrder[lenCompare].serialNum != buffer->treeNodes[buffer->top-1]->serialNum){
				    		root = temp->node->childNode[1] = (TreeNode*)malloc(sizeof(TreeNode));

				    	}
				    	else{
				    		root = seqStackPopTree(buffer)->node->childNode[1]=(TreeNode*)malloc(sizeof(TreeNode));
				    	}
					}
					else{
						lenCompare ++;
						len--;
					}
				}
				else{
					if(!isRoot){
						root = newNode(treeNode.data,treeNode.serialNum);
						result=root;
						isRoot=true;

					}
					else{
						root->data = treeNode.data;
						root->serialNum = treeNode.serialNum;

						if(len+1>totalLen){
							break;
						}

						root->node = (BinaryTree*)malloc(sizeof(BinaryTree));
						root->node->childNode = (pTreeNode*)malloc(2*sizeof(pTreeNode));
						root->node->childNode[0] = NULL;
						root->node->childNode[1] = NULL;
					}

					seqStackPushTree(root,buffer);
					lenCompare = lenlDivided;
					lenlDivided = lenrDivided;
					if(preOrder[len+1].serialNum != inOrder[lenCompare+1].serialNum){
						if(inOrder[lenCompare+1].serialNum != preOrder[lenrDivided].serialNum)
					     	root = root->node->childNode[0] = (TreeNode*)malloc(sizeof(TreeNode));
						else{
							seqStackPopTree(buffer);
							root = seqStackPopTree(buffer)->node->childNode[1]=(TreeNode*)malloc(sizeof(TreeNode));
						}
					}
					else{
						root = root->node->childNode[1] = (TreeNode*)malloc(sizeof(TreeNode));
						lenCompare+=lenlDivided;
					}

				}
			}

		}
		len++;
	}
	return result;
}

bool isCompleteBTree (pTreeNode root,tPlinkedQueue queue, int level){
	if(queue == NULL){
			queue = initialLinkedQueueTree(queue);
			linkedListEnqueueTree(root,queue);
			return isCompleteBTree(root, queue, 1);
		}
		else{
			int len = queue->rear;
			int previousLevelnodes = len;
			level +=1;
			for(int i=0; i<len;i++){
				pTreeNode treeNode = linkedListDequeueTree(queue);
				if(treeNode->node->childNode[0]!=NULL)
				linkedListEnqueueTree(treeNode->node->childNode[0],queue);
				if(treeNode->node->childNode[1]!=NULL)
				linkedListEnqueueTree(treeNode->node->childNode[1],queue);
			}


			bool isComplete;
			if(queue->rear == 0){
			    int nodes = 1;
				for(int i= 1;i<level-1;i++)
				    nodes *= 2;

				isComplete = previousLevelnodes<nodes?true:false;
				return isComplete;
			}

			isComplete = isCompleteBTree(NULL, queue, level);

			return isComplete;
		}
}


void TreeSwap (pTreeNode root){
	if(root!=NULL){
		pTreeNode temp = root->node->childNode[0];
		root->node->childNode[0] = root->node->childNode[1];
		root->node->childNode[1] = temp;
		TreeSwap(root->node->childNode[0]);
		TreeSwap(root->node->childNode[1]);
	}
	else{
		return;
	}
}

pSeqStackT Ancestor(pTreeNode root,pSeqStackT lineage, char elem, tPlinkedQueue queue){
	if(root == NULL)
		return NULL;

	lineage = newSeqStackTree(lineage);
	queue = initialLinkedQueueTree(queue);
	pSeqStackT result = newSeqStackTree(result);
	seqStackPushTree(root,result);
	seqStackPushTree(root,lineage);
	pTreeNode node = root->node->childNode[0];

	while(node!=NULL){
		seqStackPushTree(node,lineage);
		pTreeNode temp = node->node->childNode[0];
		if(temp == NULL){
		   node = node->node->childNode[1];
		   while(node == NULL){
			   node = seqStackPopTree(lineage);
			   if(node->data == elem){
				   node = NULL;
				   break;
			   }
			   else if(result->top!=1)
				   seqStackPopTree(result);


			   if(lineage->top !=0)
				   node = seqStackPopTree(lineage)->node->childNode[1];
		   }
		}else{
			if(node->data == elem){
				node = NULL;
				break;
			}

			seqStackPushTree(node,result);
			node = node->node->childNode[0];

		}
	}
	return result;
}

int ClearTree (pTreeNode root,int len,char elem){
	pTreeNode* trees = PostOrder(root,NULL,NULL,NULL,len);

	int deletedNode = 0;
	for(int i=1;i<=len;i++){
		if(trees[i]->data == elem){
			int* size = (int*)malloc(sizeof(int));
			size[0] = 1;
		    pTreeNode* buffer = PostOrder(trees[i],NULL,NULL,size,len);
		    for(int x=1;x<size[0];x++){
		    	pTreeNode temp = buffer[x];
		    	if(x!= size[0]-1)
		    	{
		    	    buffer[x] = NULL;
		    	    free(temp);
		    	    deletedNode ++;
		    	}
		    	else{
		    		buffer[x]->node->childNode[0] =NULL;
		    		buffer[x]->node->childNode[1] =NULL;
		    	}
		    }
		    free(buffer);
		}
	}
	free(trees);
	return deletedNode;
}

pSeqStackT* PublicAncestor (pTreeNode root, pSeqStackT* trace, short* branched,char elemA,char elemB){
	if(trace == NULL){
		trace = (pSeqStackT*)malloc(2*sizeof(pSeqStackT));
		trace[0] = newSeqStackTree(trace[0]);
		trace[1] = newSeqStackTree(trace[1]);
		seqStackPushTree(root,trace[0]);
		seqStackPushTree(root,trace[1]);
		branched = (short*)malloc(sizeof(short));
		branched[0] =0;
	}

	if(root!=NULL){
		if(root->node->childNode[0] != NULL){
			if(branched[0] == 0)
     			seqStackPushTree(root->node->childNode[0],trace[0]);

			if(branched[0] < 2)
	     		seqStackPushTree(root->node->childNode[0],trace[1]);
		}

		trace = PublicAncestor(root->node->childNode[0],trace,branched,elemA,elemB);

		if(root->node->childNode[1] != NULL){
			if(branched[0] == 0)
	    		seqStackPushTree(root->node->childNode[1],trace[0]);

			if(branched[0] < 2)
	     		seqStackPushTree(root->node->childNode[1],trace[1]);
		}

		trace = PublicAncestor(root->node->childNode[1],trace,branched,elemA,elemB);

		if(branched[0] == 1){
			if(trace[branched[0]]->top != 0)
			if(seqStackPopTree(trace[branched[0]])->data == elemB){
				branched[0] = 2;
				return trace;
			}
		}

		if(branched[0] == 0){
			seqStackPopTree(trace[1]);
		    if(seqStackPopTree(trace[branched[0]])->data == elemA){
		      	branched[0] = 1;
	         }
		}
	}

    return trace;
}


pTreeNode CommonAncester (pTreeNode root,char elemA, char elemB){
	pSeqStackT* trace = PublicAncestor(root,NULL,NULL,elemA,elemB);
	pTreeNode result = NULL;

	while(trace[0]->top > trace[1]->top){
		seqStackPopTree(trace[0]);
	}

	while(trace[0]->top < trace[1]->top){
		seqStackPopTree(trace[1]);
	}

	while(trace[0]->top!=0 && trace[1]->top!=0){
		pTreeNode temp =seqStackPopTree(trace[0]);
		if(temp->serialNum == seqStackPopTree(trace[1])->serialNum){
			result = temp;
			break;
		}
	}
	return result;
}

int WidestLevel(pTreeNode root,tPlinkedQueue queue,int nodesInLevel, int level,int result){
	if(queue == NULL){
			queue = initialLinkedQueueTree(queue);
			linkedListEnqueueTree(root,queue);
			nodesInLevel = 1;
			level = 1;
			result = 1;
			return WidestLevel(root, queue, nodesInLevel,level,result);
		}
		else{
			level++;

			int len = queue->rear;
			int temp = 0;
			for(int i=0; i<len;i++){
				pTreeNode treeNode = linkedListDequeueTree(queue);
				if(treeNode->node->childNode[0]!=NULL){
					linkedListEnqueueTree(treeNode->node->childNode[0],queue);
					temp++;
				}

				if(treeNode->node->childNode[1]!=NULL){
					linkedListEnqueueTree(treeNode->node->childNode[1],queue);
					temp++;
				}
			}

			if(temp>nodesInLevel){
				nodesInLevel = temp;
				result = level;
			}

			if(queue->rear == 0)
			 return result;

			return WidestLevel(root, queue, nodesInLevel,level,result);
		}
}

pTreeNode* PreOrdertoPostOrder(pTreeNode* preOrder, int prestart, int preend,int poststart,int postend,pTreeNode* postOrder){
	if(postOrder == NULL){
		postOrder = (pTreeNode*)malloc((postend+1)*sizeof(pTreeNode));
		prestart = 1;
		poststart = 1;
	}

    if(preend < prestart)
    	return postOrder;
    else{
    	postOrder[postend] = preOrder[prestart];
    	int slice = (preend - prestart)/2;
    	postOrder = PreOrdertoPostOrder(preOrder,prestart+1,prestart+slice,poststart,poststart+slice-1,postOrder);
    	postOrder = PreOrdertoPostOrder(preOrder,prestart+slice+1,preend,poststart+slice,postend-1,postOrder);
    	return postOrder;
    }
}

pTreeNode* PreOrdertoForest(pTreeNode root,pTreeNode* forest,pSeqStackT buffer,int* rootIndex){
	if(forest==NULL){
		rootIndex = (int*)malloc(sizeof(int));
		rootIndex[0]=1;
		forest = (pTreeNode*)malloc(rootIndex[0]*sizeof(pTreeNode));
		buffer = newSeqStackTree(buffer);
	}

	if(root != NULL){
		forest[rootIndex[0]-1] = newNode(root->data,root->serialNum);
		pTreeNode newTreeNode = forest[rootIndex[0]-1];
		tPlinkedQueue queue = initialLinkedQueueTree(queue);
		linkedListEnqueueTree(root,queue);
		int len = queue->rear;
		pTreeNode temp = newTreeNode;
		while(queue!=0){
			for(int i = 0; i<len;i++){
			   pTreeNode treeNode = linkedListDequeueTree(queue);
			   if(treeNode->node->childNode[0]!=NULL){
				   linkedListEnqueueTree(treeNode->node->childNode[0],queue);
				   if(i == 0)
				       temp->node->childNode[0]=newNode(treeNode->node->childNode[0]->data,treeNode->node->childNode[0]->serialNum);
				   else{
					   temp->node->childNode[1]=newNode(treeNode->node->childNode[0]->data,treeNode->node->childNode[0]->serialNum);
					   temp = temp->node->childNode[1];
				   }
			   }
			   if(treeNode->node->childNode[1]!=NULL)
				  linkedListEnqueueTree(treeNode->node->childNode[1],queue);
			}
			len = queue->rear;

		}
		forest = (pTreeNode*)realloc(forest,(++rootIndex[0])*sizeof(pTreeNode));
		forest = PreOrdertoForest(root->node->childNode[1],forest, buffer, rootIndex);
	}
	else{
		forest = (pTreeNode*)realloc(forest,(++rootIndex[0])*sizeof(pTreeNode));
		forest[rootIndex[0]] = root;
		return forest;
	}

	return forest;
}

void ForestPostOrder(pTreeNode* forest){
	    int len = 0;
	    pSeqStackT buffer = newSeqStackTree(buffer);
		while(forest[len]!=NULL){
			int* size = (int*)malloc(sizeof(int));
			size[0]=1;
			pTreeNode* postOrder = PostOrder(forest[len],NULL,NULL,size,0);
			seqStackPushTree(forest[len],buffer);
			for (int i=1;i<size[0]-1;i++){
				printf("%i,",postOrder[i]->serialNum);
			}
			len++;
			free(size);
		}

		while(buffer->top!=0){
			if(buffer->top==1)
				printf("%i",seqStackPopTree(buffer)->serialNum);
			else
			    printf("%i,",seqStackPopTree(buffer)->serialNum);
		}
}

void ForestPreOrder(pTreeNode* forest){
	    int len = 0;
		while(forest[len]!=NULL){
			int* size = (int*)malloc(sizeof(int));
			size[0]=1;
			pTreeNode* postOrder = PreOrder(forest[len],NULL,NULL,size,0);
			for (int i=1;i<size[0];i++){
				if(forest[len+1]==NULL&&i==size[0]-1)
				    printf("%i",postOrder[i]->serialNum);
				else
					printf("%i,",postOrder[i]->serialNum);
			}
			len++;
			free(size);
		}
}

void ForestInOrder(pTreeNode* forest){
	    int len = 0;
		while(forest[len]!=NULL){
			int* size = (int*)malloc(sizeof(int));
			size[0]=1;
			pTreeNode* postOrder = InOrder(forest[len],NULL,NULL,size,0);
			for (int i=1;i<size[0];i++){
				if(forest[len+1]==NULL&&i==size[0]-1)
				    printf("%i",postOrder[i]->serialNum);
				else
					printf("%i,",postOrder[i]->serialNum);
			}
			len++;
			free(size);
		}
}

#endif /* TREE_H_ */
