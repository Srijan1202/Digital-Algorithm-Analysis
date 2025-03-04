#include <stdio.h>
#include <limits.h>

// Function to find the maximum crossing subarray sum
int maxCrossingSum(int arr[], int left, int mid, int right, int *start, int *end) {
    int sum = 0, leftSum = INT_MIN, rightSum = INT_MIN;
    int tempStart = mid, tempEnd = mid + 1;
    
    for (int i = mid; i >= left; i--) {
        sum += arr[i];
        if (sum > leftSum) {
            leftSum = sum;
            tempStart = i;
        }
    }
    
    sum = 0;
    for (int i = mid + 1; i <= right; i++) {
        sum += arr[i];
        if (sum > rightSum) {
            rightSum = sum;
            tempEnd = i;
        }
    }
    
    *start = tempStart;
    *end = tempEnd;
    return leftSum + rightSum;
}

// Function to find the maximum subarray using Divide and Conquer
int maxSubArray(int arr[], int left, int right, int *start, int *end) {
    if (left == right) {
        *start = *end = left;
        return arr[left];
    }
    
    int mid = (left + right) / 2;
    int leftStart, leftEnd, rightStart, rightEnd, crossStart, crossEnd;
    
    int leftMax = maxSubArray(arr, left, mid, &leftStart, &leftEnd);
    int rightMax = maxSubArray(arr, mid + 1, right, &rightStart, &rightEnd);
    int crossMax = maxCrossingSum(arr, left, mid, right, &crossStart, &crossEnd);
    
    if (leftMax >= rightMax && leftMax >= crossMax) {
        *start = leftStart;
        *end = leftEnd;
        return leftMax;
    } else if (rightMax >= leftMax && rightMax >= crossMax) {
        *start = rightStart;
        *end = rightEnd;
        return rightMax;
    } else {
        *start = crossStart;
        *end = crossEnd;
        return crossMax;
    }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int start, end;
    int maxSum = maxSubArray(arr, 0, n - 1, &start, &end);
    
    printf("\nMaximum Subarray Sum: %d\n", maxSum);
    printf("Indices of Maximum Subarray: [%d, %d]\n", start, end);
    printf("Elements of Maximum Subarray: ");
    for (int i = start; i <= end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}
