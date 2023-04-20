#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

typedef struct _graph{
    int V;
    int E;
    ListNode **list;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

int BFS (Graph G, int v, int w);

void printGraphList(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);

int main()
{
    Graph g;
    int i,j;
    ListNode *temp;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.list = (ListNode **) malloc(g.V*sizeof(ListNode *));

    for(i=0;i<g.V;i++)
        g.list[i] = NULL;

    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&i,&j)==2)
    {
        i=i-1;

        if(g.list[i]==NULL){
            g.list[i] = (ListNode *)malloc(sizeof(ListNode));
            g.list[i]->vertex = j;
            g.list[i]->next = NULL;
        }
        else{
            temp = (ListNode *)malloc(sizeof(ListNode));
            temp->next = g.list[i];
            temp->vertex = j;
            g.list[i] = temp;
        }
        g.E++;
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    scanf("%*c");
    printf("Enter two vertices for finding their shortest distance:\n");
    scanf("%d %d", &i, &j);

    int d = BFS(g,i,j);
	
    if(d==-1)
        printf("%d and %d are unconnected.\n",i,j);
    else
        printf("The shortest distance is %d\n",d);
    printGraphList(g);
    return 0;
}

void printGraphList(Graph g){
    int i;
    ListNode* temp;

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.list[i];
        while(temp!=NULL){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void enqueue(Queue *qPtr, int item) {
    QueueNode *newNode;
    newNode = malloc( sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = item;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
    if(q.size==0) return 1;
    else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
	while(dequeue(qPtr));
}
int BFS (Graph g, int v, int w){

 // Write your code here
    int temp, num;
    int distance=1, hasVisited=0;
    ListNode *cur;
    int nextI, j;
    int index =1;

    if(v==w)
        return 0;

    Queue q;
    q.head = NULL;
    q.size=0;
    q.tail = NULL;

    Queue visited;
    visited.head=NULL;
    visited.size=0;
    visited.tail=NULL;

    enqueue(&q, v);

    while(!isEmptyQueue(q)){ 
        temp = getFront(q);
        dequeue(&q);
        if(temp==w)
            return distance;

        for(int i=0; i<visited.size; i++){
            vertex = getFront(visited);
            dequeue(&visited);
            enqueue(&visited, vertex);
            if(vertex == temp){
                hasVisited = 1;
                break;
            }
        }


        if(hasVisited==0){
            enqueue(&visited, temp);
            temp = temp-1;
            cur = g.list[temp];
            while(cur!=NULL){
                enqueue(&q, cur->vertex);
                cur = cur->next;
                nextI++;
            }
            j++;

            if(j == index){
                j = 0; //reset flag
                index = nextI;
                nextI = 0;
                distance++;
            }

        }
        if(hasVisited==1)
            hasVisited=0;
    }

    return -1;
}
// int distance, toExpand (temp), vertID, vertIDNext, flag, i, isVisited, tempInt (vertex);
//     vertID (index)= 1;
//     vertIDNext (nextI)= 0;
//     distance = 1;
//     flag (j) = 0;
//     isVisited (hasvisited) =0;

//     ListNode *temp (cur);
//     Queue visited;
//     Queue frontier (q);

//     visited.size = 0;
//     visited.head = NULL;
//     visited.tail = NULL;

//     frontier.size = 0;
//     frontier.head = NULL;
//     frontier.tail = NULL;


    enqueue(&q, v);

    while(!isEmptyQueue(q)){
         temp= getFront(q);
        dequeue(&q);

        if(q == w)
            return distance;
       

        for(int i=0; i<visited.size; i++){
            num = getFront(visited);
            dequeue(&visited);
            enqueue(&visited, num);
            if(num == temp){
                hasVisited = 1;
                break;
            }
        }

        if(hasVisited == 0){
            enqueue(&visited, temp);
            temp = temp-1;
            cur = g.list[temp];
            while(cur!=NULL){
                enqueue(&q, cur->vertex);
                cur = cur->next;
                nextI++;
            }
            j++;

            if(j == index){
                j = 0; 
                index = nextI;
                nextI = 0;
                distance++;
            }

        }

        else if(hasVisited == 1){
            hasVisited = 0;
        }
    }

    //no possible routes found
    return -1;