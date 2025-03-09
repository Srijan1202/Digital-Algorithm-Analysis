#include <stdio.h>
#include <string.h>

// Define struct for Item
typedef struct {
    char name[20];
    int weight;
    int profit;
} Item;

// 0/1 Knapsack using Dynamic Programming
void nap(int n, Item items[], int cap) {
    int dp[n + 1][cap + 1];

    // Build DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= cap; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;  // Base case
            } 
            else if (items[i - 1].weight <= w) {
                dp[i][w] = (items[i - 1].profit + dp[i - 1][w - items[i - 1].weight] > dp[i - 1][w]) ?
                           (items[i - 1].profit + dp[i - 1][w - items[i - 1].weight]) : dp[i - 1][w];
            } 
            else {
                dp[i][w] = dp[i - 1][w];  // Exclude item
            }
        }
    }

    // Print maximum profit
    printf("Maximum Profit: %d\n", dp[n][cap]);

    // Find selected items
    int w = cap;
    printf("Selected Items: ");
    for (int i = n; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {  // If item is included
            printf("%s ", items[i - 1].name);
            w -= items[i - 1].weight;
        }
    }
    printf("\n");
}

// Main function
int main() {
    int n, cap;

    // Input number of items
    printf("Enter the number of items: ");
    scanf("%d", &n);

    Item items[n]; // Array of struct

    // Input knapsack capacity
    printf("Enter the capacity: ");
    scanf("%d", &cap);

    // Input item details
    printf("Enter item details (name weight profit):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", items[i].name, &items[i].weight, &items[i].profit);
    }

    // Call knapsack function
    nap(n, items, cap);

    return 0;
}
