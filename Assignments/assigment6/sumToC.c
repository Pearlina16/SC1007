#include <stdio.h>
#include <stdlib.h>

typedef struct _arraynode
{
    int *itemArray;
    int sizeArray;
    struct _arraynode *next;
}ArrayNode;

typedef struct _arraylist{
   int size; //the size of a possible sequence
   ArrayNode *head;
} ArrayList;

typedef struct _listnode
{
    int item;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int sum; //the number of possible sequences
   int size;
   ListNode *head;
} LinkedList;

typedef struct HashSet{
	    int** data;
    int size;
} HashSet;


// You should not change the prototypes of these functions
//////LinkedList///////////////////////////////////////////
int insertNode(LinkedList *ll, int index, int coin);
int removeNode(LinkedList *ll, int index);
ListNode *findNode(LinkedList ll, int index);
void removeAllItems(LinkedList *ll);
///////////////////////////////////////////////////

void sumToC(LinkedList* ll, int C, ArrayList* al);
int main()
{
    int C;
    printf("Enter a number:\n");
    scanf("%d",&C);

    LinkedList ll;
    ll.head = NULL;
    ll.sum = 0;
    ll.size = 0;
    ArrayList al;
    al.head = NULL;
    al.size = 0;

    sumToC(&ll,C,&al);
    ArrayNode* temp;
    int i,j;
    temp = al.head;
    for(i=0;i<al.size;i++){
        for(j=0;j<temp->sizeArray;j++)
            printf(" %d ",temp->itemArray[j]);
        printf("\n");
        temp = temp->next;
    }

    return 0;
}

///////////////////////////////////////////////////////
int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size)
		return 0;

        if (index == 0){
		cur = ll->head;
		ll->head = (ListNode*) malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->sum += value;
		ll->size++;
		return 1;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(*ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->sum += value;
		ll->size++;
		return 1;
	}

	return 0;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index > ll->size)
		return 0;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		ll->sum -= ll->head->item;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 1;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(*ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return 0;

		cur = pre->next;
		ll->sum -= cur->item;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 1;
	}

	return 0;
}

ListNode *findNode(LinkedList ll, int index){

	ListNode *temp;

	if (index < 0 || index >= ll.size)
		return NULL;

	temp = ll.head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
	ll->sum =0;
}
void printarray(LinkedList* ll, ArrayList* al)
{
		ArrayNode* node = (ArrayNode* )malloc(sizeof(ArrayNode));
		node->sizeArray = ll->size;
		node->itemArray = (int*) malloc(sizeof(int) * ll->size);
		node->next = NULL;
		ListNode* temp = ll->head;

		
		for(int j=0; j<ll->size; j++){
			node->itemArray[j] = temp->item;
			temp = temp->next;
		}

		if(al->head==NULL)
			al->head = node;

		else{
			ArrayNode* cur = al->head;
			while(cur->next!=NULL)
				cur=cur->next;
			cur->next = node;
		}
		al->size++;

		return;

}

void sequences(LinkedList* ll, int C, int num, ArrayList* al)
{
	if(C==0){
		printarray(ll, al);
		return;
	}

	for(int i=num; i<=C; ++i){
		insertNode(ll, ll->size, i);
		sequences(ll, C-i, i+1, al );
		removeNode(ll, ll->size-1);
	}

	
}

void sumToC(LinkedList* ll, int C, ArrayList* al)
{
	if(C<1)
		return;

	sequences(ll, C, 1, al);
	
}

// void addSolution(ArrayList *al, LinkedList *ll) {
//     ArrayNode *newNode = (ArrayNode *)malloc(sizeof(ArrayNode));
//     newNode->sizeArray = ll->size;
//     newNode->itemArray = (int *)malloc(newNode->sizeArray * sizeof(int));
//     newNode->next = NULL;

//     ListNode *cur = ll->head;
//     for (int i = 0; i < newNode->sizeArray; ++i) {
//         newNode->itemArray[i] = cur->item;
//         cur = cur->next;
//     }

//     if (al->head == NULL) {
//         al->head = newNode;
//     } else {
//         ArrayNode *temp = al->head;
//         while (temp->next != NULL) {
//             temp = temp->next;
//         }
//         temp->next = newNode;
//     }
//     al->size++;
// }

// void combinations(LinkedList *ll, int C, ArrayList *al, int start) {
//     if (C == 0) {
//         addSolution(al, ll);
//         return;
//     }

//     for (int i = start; i <= C; ++i) {
//         insertNode(ll, ll->size, i);
//         combinations(ll, C - i, al, i + 1);
//         removeNode(ll, ll->size - 1);
//     }
// }

// void sumToC(LinkedList* ll, int C, ArrayList* al) {
//     combinations(ll, C, al, 1);
// }