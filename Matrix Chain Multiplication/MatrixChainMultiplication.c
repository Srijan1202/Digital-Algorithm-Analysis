#include <stdio.h>
#include <limits.h>

// Function to print optimal parenthesization
void printOptimalParenthesis(int i, int j, int n, int bracket[n][n], char *name)
{
    if (i == j)
    {
        printf("%c", (*name)++);
        return;
    }
    
    printf("(");
    printOptimalParenthesis(i, bracket[i][j], n, bracket, name);
    printOptimalParenthesis(bracket[i][j] + 1, j, n, bracket, name);
    printf(")");
}

// Function to compute the minimum number of multiplications using DP
void matrixChainOrder(int p[], int n)
{
    int m[n][n], bracket[n][n];
    
    for (int i = 1; i < n; i++)
        m[i][i] = 0;
    
    for (int L = 2; L < n; L++)
    {
        for (int i = 1; i < n - L + 1; i++)
        {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
            {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    bracket[i][j] = k;
                }
            }
        }
    }
    
    printf("\nOptimal number of multiplications: %d\n", m[1][n - 1]);
    printf("Optimal Parenthesization: ");
    char name = 'A';
    printOptimalParenthesis(1, n - 1, n, bracket, &name);
    printf("\n");
}

int main()
{
    int n;
    printf("Enter number of matrices: ");
    scanf("%d", &n);
    
    int p[n + 1];
    printf("Enter dimensions: ");
    for (int i = 0; i <= n; i++)
        scanf("%d", &p[i]);
    
    matrixChainOrder(p, n + 1);
    return 0;
}
