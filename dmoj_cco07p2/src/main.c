#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#define SIZE 6

typedef struct s_node {
    int snowflake[SIZE];
    s_node *next;
} s_node;

bool checkRight(int orig[SIZE], int test[SIZE], int start)
{
    for (int i = 0; i < SIZE; i++)
    {
        int idx = (start + i) % SIZE;
        if (orig[i] != test[idx])
            return false;
    }
    return true;
}

bool checkLeft(int orig[SIZE], int test[SIZE], int start)
{
    for (int i = 0; i < SIZE; i++)
    {
        int idx = (start - i + SIZE) % SIZE;
        if (orig[i] != test[idx])
            return false;
    }
    return true;
}

// store snowflakes, or use static in main
int flakes[100000][SIZE];

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        int nf[SIZE];
        for (int j = 0; j < SIZE; j++) {
        scanf("%d", &nf[j]);
        }

        // for each existing flake
        for (int j = 0; j < i; j++)
        {
            // test each starting location
            for (int k = 0; k < SIZE; k++)
            {
                if (checkRight(flakes[j], nf, k) || checkLeft(flakes[j], nf, k))
                {
                    printf("Found an identical snowflake ");
                    for (int l = 0; l < SIZE; l++) {
                        printf("%d ", nf[l]);
                    }
                    printf("\n");
                    return 0;
                }
            }
        }

        // track the new snowflake
        for (int j = 0; j < SIZE; j++)
        {
            flakes[i][j] = nf[j];
        }
    }

    puts("No two snowflakes are alike.\n");
}