//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////

typedef struct _btnode{
int item;
struct _btnode *left;
struct _btnode *right;
} BTNode;

///////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value);
void printBSTInOrder(BTNode *node);
int isBST(BTNode *node, int min, int max);
BTNode *removeBSTNode(BTNode *node, int value);
BTNode *findMin(BTNode *p);

///////////////////////////////////////////////////////////////////////

int main(){
	int i=0;

	BTNode *root=NULL;

	//question 1
	do{
		printf("input a value you want to insert(-1 to quit):");

		scanf("%d",&i);
		if (i!=-1)
			insertBSTNode(&root,i);
	}while(i!=-1);

	//question 2
	printf("\n");
	printBSTInOrder(root);

	//question 3
	if ( isBST(root,-1000000, 1000000)==1)
		printf("It is a BST!\n");
	else
		printf("It is not a BST!\n");

	//question 4
	do{
		printf("\ninput a value you want to remove(-1 to quit):");
		scanf("%d",&i);
		if (i!=-1)
		{
			root=removeBSTNode(root,i);
			printBSTInOrder(root);
		}
	}while(i!=-1);


	return 0;
}

//////////////////////////////////////////////////////////////////////

void insertBSTNode(BTNode **node, int value)
{
	// write your code here
    if(*node==NULL){
        *node = malloc(sizeof(BTNode));
        (*node)->item = value;
        (*node)->left = NULL;
        (*node)->right = NULL;
    }
    else{
        if(value<(*node)->item){
            insertBSTNode(&((*node)->left), value);
        }
        else{
            insertBSTNode(&((*node)->right), value);
        }
    }

//use node pointer 

    // BTNode *temp = *node;

    // if(temp == NULL){
    //     temp = malloc(sizeof(BTNode));
    //     temp->item = value;
    //     temp->left = NULL;
    //     temp->right = NULL;
    //     return;
    // }

    // else if(temp->item>value){
    //     insertBSTNode(&temp->left, value);
    // }
    // else{
    //     insertBSTNode(&temp->right,value);
    // }
    // *node=temp;

    }



//////////////////////////////////////////////////////////////////////

void printBSTInOrder(BTNode *node)
{
	// write your code here

        if(node!=NULL){
        printBSTInOrder(node->left);
        printf("%d ", node->item);
        printBSTInOrder(node->right);
    }
        
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int isBST(BTNode *node, int min, int max) // the item stored in node has to be smaller than max and larger than min
{
	// write your code here

    if(node==NULL)
    return 1 ;

    if(node->item<min || node->item > max){
        return 0;
    }

    return isBST(node->left, min, node->item -1) && isBST(node->right, node->item +1 , max);
    
}
   


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *removeBSTNode(BTNode *node, int value)
{
	// write your code here
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BTNode *findMin(BTNode *p)
{
	// write your code here
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////