#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>

#define SIZE 6
#define ARR_SIZE 100000

typedef struct s_node s_node;
struct s_node
{
    int snowflake[SIZE];
    s_node *next;
};

bool checkRight(int orig[], int test[], int start)
{
    for (int i = 0; i < SIZE; i++)
    {
        int idx = (start + i) % SIZE;
        if (orig[i] != test[idx])
            return false;
    }
    return true;
}

bool checkLeft(int orig[], int test[], int start)
{
    for (int i = 0; i < SIZE; i++)
    {
        int idx = (start - i + SIZE) % SIZE;
        if (orig[i] != test[idx])
            return false;
    }
    return true;
}

uint64_t hash(int flake[])
{
    uint32_t hash = 0;
    for (int i = 0; i < SIZE; i++)
    {
        hash += flake[i];
    }
    return hash % ARR_SIZE;
}

bool testSnowflake(int flake[], int newFlake[])
{
    // test each starting location
    for (int k = 0; k < SIZE; k++)
    {
        if (checkRight(flake, newFlake, k) || checkLeft(flake, newFlake, k))
        {
            return true;
        }
    }

    return false;
}

bool findSnowflake(s_node *flakes[], int test[])
{
    uint32_t h = hash(test);
    s_node *cur = flakes[h];
    while (cur != NULL)
    {
        if (testSnowflake(cur->snowflake, test))
        {
            return true;
        }
        cur = cur->next;
    }

    // didn't find it, insert it
    s_node *node = malloc(sizeof(s_node));
    for (int i = 0; i < SIZE; i++)
    {
        node->snowflake[i] = test[i];
    }

    node->next = flakes[h];
    flakes[h] = node;

    return false;
}

// store snowflakes, or use static in main
s_node *flakes[ARR_SIZE] = {NULL};

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        int nf[SIZE];
        for (int j = 0; j < SIZE; j++)
        {
            scanf("%d", &nf[j]);
        }

        if (findSnowflake(flakes, nf))
        {
            // printf("Found an identical snowflake ");
            // for (int l = 0; l < SIZE; l++)
            // {
            //     printf("%d ", nf[l]);
            // }
            // printf("\n");
            puts("Twin snowflakes found.");
            return 0;
        }
    }

    puts("No two snowflakes are alike.");
    return 0;
}