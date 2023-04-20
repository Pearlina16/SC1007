#include <stdio.h>
 
// A utility function that returns
// maximum of two integers
int max(int a, int b) {
    if( a>= b)
        return a;
    if(b>a)
        return b;
 }
 
// Returns the maximum value that
// can be put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n)
{
    int matrix[n+1][W+1];
    for(int i=0; i<=n; i++){
        for(int j=0; j<=W; j+=10){
            if(i==0||j==0)
                matrix[i][j]=0;
            else if(wt[i-1]<=j){
                matrix[i][j] = max(matrix[i-1][j], val[i-1] + matrix[i-1][j-wt[i-1]]);
            }
            else{
                matrix[i][j] = matrix[i-1][j];
            }
        }
    }
    return matrix[n][W];
    // int i, w;
    // int K[n + 1][W + 1];
 
    // // Build table K[][] in bottom up manner

    // for (i = 0; i <= n; i++) {
    //     for (w = 0; w <= W; w+=10) {
    //         if (i == 0 || w == 0)
    //             K[i][w] = 0;
    //         else if (wt[i - 1] <= w)
    //             K[i][w] = max( K[i - 1][w] /*item i notused*/, val[i - 1] + K[i - 1][w - wt[i - 1]]); /*item i used*/
    //         else
    //             K[i][w] = K[i - 1][w];
    //     }
    // }
 
    // return K[n][W];
}
 
// Driver Code
int main()
{
    int profit[] = { 60, 100, 120 };
    int weight[] = { 10, 20, 30 };
    int W = 50;
    int n = sizeof(profit) / sizeof(profit[0]);
    printf("%d", knapSack(W, weight, profit, n));
    return 0;
}