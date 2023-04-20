#include<stdio.h>
#include <stdlib.h>

int* city_population (int N, int* population, int** road, int Q, int** cities) ;

int main() {
    int N;
    scanf("%d", &N);
    int i_population;
    int *population = (int *)malloc(sizeof(int)*(N));
    for(i_population = 0; i_population < N; i_population++)
    	scanf("%d", &population[i_population]);
    int i_road, j_road;
    int **road = (int **)malloc((N-1)*sizeof(int *));
    for(i_road = 0; i_road < N-1; i_road++)
    {
    	road[i_road] = (int *)malloc((2)*sizeof(int));
    }
    for(i_road = 0; i_road < N-1; i_road++)
    {
    	for(j_road = 0; j_road < 2; j_road++)
    	{
    		scanf("%d", &road[i_road][j_road]);
    	}
    }
    int Q;
    scanf("%d", &Q);
    int i_cities, j_cities;
    int **cities = (int **)malloc((Q)*sizeof(int *));
    for(i_cities = 0; i_cities < Q; i_cities++)
    {
    	cities[i_cities] = (int *)malloc((3)*sizeof(int));
    }
    for(i_cities = 0; i_cities < Q; i_cities++)
    {
    	for(j_cities = 0; j_cities < 3; j_cities++)
    	{
    		scanf("%d", &cities[i_cities][j_cities]);
    	}
    }

    int* out_ = city_population(N, population, road, Q, cities);
    printf("%d", out_[0]);
    int i_out_;
    for(i_out_ = 1; i_out_ < Q; i_out_++)
    	printf("\n%d", out_[i_out_]);
}

typedef struct listnode {
    int p;
    int vertex;
    struct listnode *next;
} ListNode;

void add(ListNode **adjList, int _new, int v, int population) {
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->vertex = v;
    newNode->p = population;
    newNode->next = adjList[_new];
    adjList[_new] = newNode;
}


int** buildTable(int N, ListNode** adj_list, int MAX) {
    int power = MAX;
    int** table = (int**)malloc(N * sizeof(int*));
    for (int a = 0; a < N; a++) {
        table[a] = (int*)malloc((power) * sizeof(int));
        for (int b = 0; b < power; b++) {
            table[a][b] = -1;
        }
    }
    DFS(0, -1, adj_list, table);

    for (int i = 1; i <= power; i++) {
        for (int j = 0; i < N; i++) {
            if (table[j][i - 1] != -1) {
                table[j][i] = table[table[j][i - 1]][i - 1];
            }
        }
    }
    return table;
}

void DFS(int node, int head, ListNode** adj_list, int** table) {
    table[node][0] = head;
    ListNode* cur = adj_list[node];
    while (cur != NULL)
    {
        if (cur->vertex != head) {
            DFS(cur->vertex, node, adj_list, table);
        }
        cur = cur->next;
    }

}

int count_cities(ListNode **adjList, int start_node, int target_node, int maxP, int *visited, int *count) {
    
    visited[start_node] = 1;

    if (start_node == target_node) {
        return 1;
    }

    ListNode *num = adjList[start_node];
    while (num) {
        if (!visited[num->vertex]) {
            if (count_cities(adjList, num->vertex, target_node, maxP, visited, count)) {
                 if (num->p <= maxP) {
                    (*count)++;
                }
                return 1;
            }
        }
        num = num->next;
    }

    return 0;
}

int *city_population(int N, int *population, int **road, int Q, int **cities) {

    int MAX = 0;
    for (int this = N; this > 1; this >>= 1) {
        MAX++;
    }

    ListNode **adjList = (ListNode **)calloc(N, sizeof(ListNode *));
    for (int i = 0; i < N - 1; i++) {
        int city = road[i][0] - 1;
        int city1 = road[i][1] - 1;
        add(adjList, city, city1, population[city1]);
        add(adjList, city1, city, population[city]);
    }

    int** table = buildTable(N, adjList, MAX);
  
    int *final = (int *)malloc(Q * sizeof(int));
    for (int i = 0; i < Q; i++) {
        int city = cities[i][0] - 1;
        int city1 = cities[i][1] - 1;
        int max_population = cities[i][2];

        // visited array for dfs size N
        int *visited = (int *)calloc(N, sizeof(int));
        // counter for dfs
        int count = 0;
        // check for start node if it is less than max_population
        if (population[city] <= max_population)
        {
            count++;
        }
        // then check from the neighbour nodes of start to target
        dfs_path(adjList, city, city1, max_population, visited, &count);
        final[i] = count;
        free(visited);
    }

    // Free the adjacency list memory
    for (int i = 0; i < N; i++) {
        ListNode *temp = adjList[i];
        while (temp) {
            ListNode *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(adjList);
    return final;
}
