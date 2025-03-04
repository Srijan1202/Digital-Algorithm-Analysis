#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// Function to check if a number is a power of 2
int isPowerOfTwo(int n) {
    return (n && !(n & (n - 1)));
}

// Function to find the next power of 2
int nextPowerOfTwo(int n) {
    int power = 1;
    while (power < n)
        power *= 2;
    return power;
}

// Function to add leading zeros to make length a power of 2
void padWithZeros(char *num, int newSize) {
    int len = strlen(num);
    if (len < newSize) {
        memmove(num + (newSize - len), num, len + 1);
        memset(num, '0', newSize - len);
    }
}

// Karatsuba multiplication function
long long karatsuba(long long x, long long y) {
    if (x < 10 || y < 10)
        return x * y;
    
    int n = fmax(log10(x) + 1, log10(y) + 1);
    int m = n / 2;
    
    long long high1 = x / pow(10, m);
    long long low1 = x % (long long)pow(10, m);
    long long high2 = y / pow(10, m);
    long long low2 = y % (long long)pow(10, m);
    
    long long z0 = karatsuba(low1, low2);
    long long z1 = karatsuba((low1 + high1), (low2 + high2));
    long long z2 = karatsuba(high1, high2);
    
    return (z2 * pow(10, 2 * m)) + ((z1 - z2 - z0) * pow(10, m)) + z0;
}

int main() {
    char num1[100], num2[100];
    printf("Enter first number: ");
    scanf("%s", num1);
    printf("Enter second number: ");
    scanf("%s", num2);
    
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxLen = fmax(len1, len2);
    
    if (!isPowerOfTwo(maxLen)) {
        int newSize = nextPowerOfTwo(maxLen);
        padWithZeros(num1, newSize);
        padWithZeros(num2, newSize);
        printf("\nNumbers after padding to next power of 2:\n");
        printf("%s\n%s\n", num1, num2);
    } else {
        printf("\nNumbers are already of power of 2 size.\n");
    }
    
    long long x = atoll(num1);
    long long y = atoll(num2);
    long long product = karatsuba(x, y);
    
    printf("\nProduct using Karatsuba Algorithm: %lld\n", product);
    return 0;
}
