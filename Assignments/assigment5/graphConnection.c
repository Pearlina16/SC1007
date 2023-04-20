#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

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

typedef struct _stack
{
	int size;
	StackNode *head;
} Stack;

int CC (Graph g);

void printGraphList(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
//////////////////////////////////

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

    int res = CC(g);
    if(res ==1)
        printf("The graph is strongly connected.\n");
    else
        printf("The graph is not strongly connected.\n");

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

void enqueue(Queue *qPtr, int vertex) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = vertex;
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

void push(Stack *sPtr, int vertex)
{
	StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

int isEmptyStack(Stack s)
{
     if(s.size==0) return 1;
     else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
	while(pop(sPtr));
}


int CC (Graph g)
{
 // Write your code here

   
    int visited[g.V];

    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    for(int i = 0 ;i< g.V; i++){
        visited[i] = 0;
    }


    for(int j = 0 ;j< g.V; j++){
        ListNode *temp;
        temp = g.list[j];
        enqueue(&q,j+1);
        visited[j] += 1;

        while(!isEmptyQueue(q)){
            int value = getFront(q);
            dequeue(&q);
            temp = g.list[value-1];
            while(temp != NULL){
                int cur = temp->vertex;
                if(visited[cur-1] < visited[i]){
                    enqueue(&q,cur);
                    visited[cur-1] += 1;
                    }
                temp = temp->next;
            }
        }
        for(k=0; k<g.V; k++){
            if(visited[k] != visited[j]){
                return 0;
            }
        }
    }

    return 1;




}
//    int visited[g.V];
    

//     Stack s;
//     s.size = 0;
//     s.head = NULL;

//     for(int j=0; j<g.V; j++){
//         for (int i = 0; i < g.V; i++) {
//             visited[i] = 0;
//         }
//         push(&s, visited[j]);
//         visited[j] = 1;
//         while (!isEmptyStack(s)) {
//             int cur = peek(s);
//             ListNode *temp = g.list[cur];
//             while (temp != NULL) {
//                 int neighbour = temp->vertex - 1;  //index of vertex
//                 if (!visited[neighbour]) {
//                     visited[neighbour] = 1;
//                     push(&s, neighbour);
//                 }
//                 temp = temp->next;
                
//             }
//             pop(&s);
//         }
//         for (int i = 0; i < g.V; i++) {
//             if (visited[i]!=1) 
//                 return 0;
//         }
      
//     }
//         return 1;
    // check if all vertices were visited
  
    // // reset visited array to false
    // for (int i = 0; i < g.V; i++) {
    //     visited[i] = 0;
    // }

    // // perform depth-first search on first vertex (reverse direction)
    // Stack s2;
    // s2.size = 0;
    // s2.head = NULL;
    // push(&s2, visited[0]);
    // visited[0] = 1;
    // while (!isEmptyStack(s2)) {
    //     int curr = peek(s2);
    //     pop(&s2);
    //     ListNode *temp = g.list[curr];
    //     while (temp != NULL) {
    //         int neighbor = temp->vertex - 1;
    //         if (!visited[neighbor]) {
    //             visited[neighbor] = 1;
    //             push(&s2, neighbor);
    //         }
    //         temp = temp->next;
    //     }
    // }

    // // check if all vertices were visited
    // for (int i = 0; i < g.V; i++) {
    //     if (!visited[i]) {
    //         return 0;
    //     }
    // }

//     return 1;
// }

// int visited[g.V];
//     for (int i = 0; i < g.V; i++) {
//         visited[i] = 0;
//     }

//     Stack s;
//     s.size = 0;
//     s.head = NULL;

//     for(int j=0; j<g.V; j++){
//         push(&s, visited[0]);
//         visited[0] = 1;
//         while (!isEmptyStack(s)) {
//             int curr = peek(s);
//             pop(&s);
//             ListNode *temp = g.list[curr];
//             while (temp != NULL) {
//                 int neighbor = temp->vertex - 1;
//                 if (!visited[neighbor]) {
//                     visited[neighbor] = 1;
//                     push(&s, neighbor);
//                 }
//                 temp = temp->next;
//             }
//         }
//         for (int i = 0; i < g.V; i++) {
//             if (!visited[i]) 
//                 return 0;
//         }
//         break;
//     }
    
//     return 1;
// }


//     int visited[g.V];
//     for (int i = 0; i < g.V; i++) {
//         visited[i] = 0;
//     }

//     Stack s;
//     s.size = 0;
//     s.head = NULL;
//     int found_unvisited = 0; // flag to indicate if unvisited node was found

//     for(int j=0; j<g.V; j++){
//         push(&s, visited[j]);
//         visited[j] = 1;
//         while (!isEmptyStack(s)) {
//             int curr = peek(s);
//             pop(&s);
//             ListNode *temp = g.list[curr];
//             while (temp != NULL) {
//                 int neighbor = temp->vertex - 1;
//                 if (!visited[neighbor]) {
//                     visited[neighbor] = 1;
//                     push(&s, neighbor);
//                 }
//                 temp = temp->next;
//             }
//         }
//         for (int i = 0; i < g.V; i++) {
//             if (!visited[i]) {
//                 found_unvisited = 1; // set flag if unvisited node found
//             }
//         }
//         if (found_unvisited) {
//             return 0; // graph is not strongly connected
//         }
//         break;
//     }
    
//     return 1; // graph is strongly connected
// }

