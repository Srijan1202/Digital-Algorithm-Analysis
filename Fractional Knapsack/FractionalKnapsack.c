#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store item details
typedef struct {
    char name[20];
    float weight, profit, ratio;
} Item;

// Function to compare items based on profit/weight ratio (for sorting)
int compare(const void *a, const void *b) {
    float r1 = ((Item *)a)->ratio;
    float r2 = ((Item *)b)->ratio;
    return (r2 > r1) - (r2 < r1); // Descending order
}

void fractionalKnapsack(int n, Item items[], float capacity) {
    qsort(items, n, sizeof(Item), compare);

    float totalProfit = 0.0, totalWeight = 0.0;
    printf("\nSelected Items:\n");
    printf("%-10s %-10s %-10s\n", "Item", "Fraction", "Profit");
    
    for (int i = 0; i < n; i++) {
        if (capacity <= 0) break;
        float fraction = (items[i].weight <= capacity) ? 1.0 : capacity / items[i].weight;
        float profitEarned = fraction * items[i].profit;
        printf("%-10s %-10.2f %-10.2f\n", items[i].name, fraction, profitEarned);
        
        totalProfit += profitEarned;
        totalWeight += fraction * items[i].weight;
        capacity -= fraction * items[i].weight;
    }
    printf("\nTotal Profit Earned: %.2f\n", totalProfit);
    printf("Total Weight: %.2f\n", totalWeight);
}

int main() {
    int n;
    float capacity;
    
    printf("Enter number of items: ");
    scanf("%d", &n);
    Item items[n];
    
    printf("Enter knapsack capacity: ");
    scanf("%f", &capacity);
    
    printf("Enter item details (name weight profit):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s %f %f", items[i].name, &items[i].weight, &items[i].profit);
        items[i].ratio = items[i].profit / items[i].weight;
    }
    
    fractionalKnapsack(n, items, capacity);
    return 0;
}

