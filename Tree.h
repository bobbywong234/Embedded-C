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
	int MaxSize;
}seqStackT,*pSeqStackT;

typedef struct BinaryParentStruct {
	pTreeNode *childNode;
}BinaryTree, *pBinaryTree;

void seqStackPushTree(pTreeNode elem, pSeqStackT S){
	if(S->top==S->MaxSize){
		return;
	}
    S->treeNodes[S->top] = elem;
    S->top ++;
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

pSeqStackT newSeqStackTree(int MaxSize,pSeqStackT S){
	S = (seqStackT*)malloc(sizeof(seqStackT));
	S->MaxSize = MaxSize;
	S->top = 0;
	S->treeNodes = (pTreeNode*)malloc(MaxSize * sizeof(pTreeNode));
	return S;
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

pTreeNode PreOrder(pSeqStackT buffer,pTreeNode branch,int currentIndex,int len){
	pTreeNode node = buffer->treeNodes[buffer->top-1];
	if(node != NULL){
		branch = (TreeNode*)realloc(branch,(currentIndex+2)*sizeof(TreeNode));
		if(node->node->childNode[0] == NULL)
			node->lchildIndex = 1;
		else if(node->node->childNode[1] == NULL)
			node->rchildIndex = 1;
		branch[++currentIndex] = *node;
		if(currentIndex == len)
			return branch;
		seqStackPushTree(node->node->childNode[0], buffer);
		 branch = PreOrder(buffer,branch,currentIndex,len);
	}
	else{
		pTreeNode treeNode = seqStackPopTree(buffer);
		if(buffer->top == 0)
			return branch;
		treeNode = seqStackPopTree(buffer);
		seqStackPushTree(treeNode->node->childNode[1], buffer);
		branch = PreOrder(buffer,branch,currentIndex,len);

	}
	return branch;
}

pTreeNode IndexedPreOrder (pSeqStackT buffer,pTreeNode branch,int currentIndex,int len){
	pTreeNode node = buffer->treeNodes[buffer->top-1];
	if(node->lchildIndex ==1){
		branch = (TreeNode*)realloc(branch,(currentIndex+2)*sizeof(TreeNode));
		pTreeNode treeNode = seqStackPopTree(buffer);
		branch[++currentIndex] = *treeNode;
		if(buffer->top == 0 || currentIndex == len)
			return branch;
		treeNode = seqStackPopTree(buffer);
		seqStackPushTree(treeNode->node->childNode[1], buffer);
		branch = PreOrder(buffer,branch,currentIndex,len);
	}else{
		branch = (TreeNode*)realloc(branch,(currentIndex+2)*sizeof(TreeNode));
		branch[++currentIndex] = *node;
		if(currentIndex == len)
			return branch;
		seqStackPushTree(node->node->childNode[0], buffer);
		branch = PreOrder(buffer,branch,currentIndex,len);
	}
	return branch;
}

pTreeNode InOrder (pSeqStackT buffer, pTreeNode branch,int currentIndex, int len){
	pTreeNode node = buffer->treeNodes[buffer->top-1];
		if(node != NULL){
			if(currentIndex == len)
				return branch;

			 if(node->node->childNode[0] == NULL)
				 node->lchildIndex = 1;
			 seqStackPushTree(node->node->childNode[0], buffer);
			 branch = InOrder(buffer,branch,currentIndex,len);
		}
		else{
			branch = (TreeNode*)realloc(branch,(currentIndex+2)*sizeof(TreeNode));
			pTreeNode treeNode = seqStackPopTree(buffer);
			if(buffer->top == 0)
				return branch;
			treeNode = seqStackPopTree(buffer);
			if(treeNode->lchildIndex != 1 && treeNode->node->childNode[1] == NULL)
				treeNode->rchildIndex = 1;
			branch[++currentIndex] = *treeNode;
			seqStackPushTree(treeNode->node->childNode[1], buffer);

			branch = InOrder(buffer,branch,currentIndex,len);

		}
		return branch;
}

pTreeNode IndexedInOrder (pSeqStackT buffer, pTreeNode branch,int currentIndex, int len){

	pTreeNode node = buffer->treeNodes[buffer->top-1];
	if(node == NULL)
	 return branch;

	if(node->lchildIndex == 1){
		pTreeNode treeNode = seqStackPopTree(buffer);
		branch = (TreeNode*)realloc(branch,(currentIndex+2)*sizeof(TreeNode));
		branch[++currentIndex]=*treeNode;
		if(currentIndex == len)
		  return branch;

		if(buffer->top != 0){
			treeNode = seqStackPopTree(buffer);
	        branch = (TreeNode*)realloc(branch,(currentIndex+2)*sizeof(TreeNode));
	    	branch[++currentIndex]=*treeNode;
	    	if(currentIndex == len)
	    	  return branch;
		}

		while(treeNode->rchildIndex == 1){
			treeNode = seqStackPopTree(buffer);
		    branch = (TreeNode*)realloc(branch,(currentIndex+2)*sizeof(TreeNode));
			branch[++currentIndex]=*treeNode;
			if(currentIndex == len)
				return branch;
		}

		seqStackPushTree(treeNode->node->childNode[1], buffer);
		branch = IndexedInOrder(buffer,branch,currentIndex,len);
	}
	else{
		seqStackPushTree(node->node->childNode[0], buffer);
		branch = IndexedInOrder(buffer,branch,currentIndex,len);
	}

	return branch;
}

pTreeNode PostOrder (pSeqStackT buffer, pTreeNode branch,int currentIndex, int len){
	pTreeNode node = buffer->treeNodes[buffer->top-1];
		if(node != NULL){
			 if(node->node->childNode[0] == NULL)
				 node->lchildIndex = 1;
			 seqStackPushTree(node->node->childNode[0], buffer);
			 branch = PostOrder(buffer,branch,currentIndex,len);
		}
		else{
			branch = (TreeNode*)realloc(branch,(currentIndex+2)*sizeof(TreeNode));
			seqStackPopTree(buffer);

			branch[++currentIndex] = *seqStackPopTree(buffer);
			if(currentIndex == len)
				return branch;

		    if(buffer->treeNodes[buffer->top-1]->node->childNode[1]!= NULL){
		    	while(branch[currentIndex].serialNum == buffer->treeNodes[buffer->top-1]->node->childNode[1]->serialNum){
		    			branch = (TreeNode*)realloc(branch,(currentIndex+2)*sizeof(TreeNode));
		    			branch[++currentIndex] = *seqStackPopTree(buffer);
		    			if(currentIndex == len)
		    				return branch;
		    	}
		    	seqStackPushTree(buffer->treeNodes[buffer->top-1]->node->childNode[1], buffer);
		    }
		    else{
		    	if(buffer->treeNodes[buffer->top-1]->lchildIndex!=1)
		    	 buffer->treeNodes[buffer->top-1]->rchildIndex = 1;

		    	branch = (TreeNode*)realloc(branch,(currentIndex+2)*sizeof(TreeNode));
		    	branch[++currentIndex] = *seqStackPopTree(buffer);
		    	if(buffer->top == 0 || currentIndex == len)
		    		return branch;

		    	while(branch[currentIndex].serialNum == buffer->treeNodes[buffer->top-1]->node->childNode[1]->serialNum){
		    		branch = (TreeNode*)realloc(branch,(currentIndex+2)*sizeof(TreeNode));
		    		branch[++currentIndex] = *seqStackPopTree(buffer);
		    		if(buffer->top == 0 || currentIndex == len)
		    		  return branch;
		    	}
		    	seqStackPushTree(buffer->treeNodes[buffer->top-1]->node->childNode[1], buffer);
		    }

			branch = PostOrder(buffer,branch,currentIndex,len);
		}
		return branch;
}

pTreeNode IndexedPostOrder (pSeqStackT buffer, pTreeNode branch,int* currentIndex, int len){
	pTreeNode node = buffer->treeNodes[buffer->top-1];
	if(node->lchildIndex == 1){
		int temp = currentIndex[0];
		branch = (TreeNode*)realloc(branch,(temp+2)*sizeof(TreeNode));
		branch[++temp] = *seqStackPopTree(buffer);
		currentIndex[0] = temp;
		return branch;
	}
	seqStackPushTree(node->node->childNode[0], buffer);
	branch = IndexedPostOrder(buffer,branch,currentIndex,len);

	if(currentIndex[0] == len)
	   return branch;

	if(buffer->top == 0)
		return branch;

	if(buffer->treeNodes[buffer->top-1]->rchildIndex ==1){
		int temp = currentIndex[0];
		branch = (TreeNode*)realloc(branch,(temp+2)*sizeof(TreeNode));
		branch[++temp] = *seqStackPopTree(buffer);
		currentIndex[0] = temp;
		return branch;
	}

	if(branch[currentIndex[0]].serialNum == buffer->treeNodes[buffer->top-1]->node->childNode[1]->serialNum)
		return branch;


	while(buffer->top != 0){
			if(buffer->treeNodes[buffer->top-1]->rchildIndex != 1){
				if(branch[currentIndex[0]].serialNum == buffer->treeNodes[buffer->top-1]->node->childNode[1]->serialNum){
				    int temp = currentIndex[0];
				    branch = (TreeNode*)realloc(branch,(temp+2)*sizeof(TreeNode));
			    	branch[++temp] = *seqStackPopTree(buffer);
			    	currentIndex[0] = temp;
			    	if(currentIndex[0] == len)
			    		   return branch;

			    	while(branch[currentIndex[0]].serialNum == buffer->treeNodes[buffer->top-1]->node->childNode[1]->serialNum){
			    		 int temp = currentIndex[0];
			    		 branch = (TreeNode*)realloc(branch,(temp+2)*sizeof(TreeNode));
			    		 branch[++temp] = *seqStackPopTree(buffer);
			    		 currentIndex[0] = temp;
			    		 if(buffer->top == 0 || currentIndex[0] == len)
			    			 return branch;
			    	}
			    	seqStackPushTree(buffer->treeNodes[buffer->top-1]->node->childNode[1], buffer);
			    	branch = IndexedPostOrder(buffer,branch,currentIndex,len);
			    }
			    else{
			    	seqStackPushTree(buffer->treeNodes[buffer->top-1]->node->childNode[1], buffer);
			     	branch = IndexedPostOrder(buffer,branch,currentIndex,len);
			    }
		    }
			else{
				branch = IndexedPostOrder(buffer,branch,currentIndex,len);
	    	}
	}

	return branch;
}


pTreeNode Tranverse(pTreeNode root,int len,int tranverseMode){
	pSeqStackT buffer;
	buffer = newSeqStackTree(len,buffer);
	seqStackPushTree(root,buffer);
	if(buffer->treeNodes[buffer->top-1]->node->childNode == NULL){
		return buffer->treeNodes[buffer->top];
	}

	pTreeNode result = (TreeNode*)malloc(sizeof(TreeNode));
	switch (tranverseMode){
	case 1:
		result =PreOrder(buffer,result,0,len);
		break;
	case 2:
		result =InOrder(buffer,result,0,len);
		break;
	case 3:
		result =PostOrder(buffer,result,0,len);
		break;
	case 4:
		result = IndexedPreOrder(buffer,result,0,len);
		break;
	case 5:
		result = IndexedInOrder(buffer,result,0,len);
		break;
	case 6:{
		int* pIndex = (int*)malloc(sizeof(int));
		pIndex[0] = 0;
		result = IndexedPostOrder(buffer,result,pIndex,len);
		break;
	   }
	}
	buffer = (pSeqStackT)realloc(buffer,0);
	buffer = NULL;
	return result;
}

#endif /* TREE_H_ */
