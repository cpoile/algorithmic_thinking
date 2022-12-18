#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <inttypes.h>
#include <malloc.h>
#endif

#ifdef __APPLE__
#include <stdint.h>
#include <stdlib.h>
#endif

#ifdef __linux__
#include <stdint.h>
#include <stdlib.h>
#endif

char *read_line(int size)
{
    char *str;
    int32_t ch;
    int32_t len = 0;
    str = malloc(size);
    if (str == NULL)
    {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }

    while ((ch = getchar()) != EOF && (ch != '\n'))
    {
        str[len++] = ch;
        if (len == size)
        {
            size *= 2;
            realloc(str, size);
            if (str == NULL)
            {
                fprintf(stderr, "realloc error\n");
                exit(1);
            }
        }
    }
    str[len++] = '\0';
    return str;
}

#define hashsize(n) ((uint32_t)1 << (n))
#define hashmask(n) (hashsize(n) - 1)

uint32_t oaat(char *key, uint32_t len, uint32_t bits)
{
    uint32_t hash = 0;
    uint32_t i;
    for (i = 0; i < len; i++)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash & hashmask(bits);
}

#define NUM_BITS 17

typedef struct word_node
{
    char **word;
    struct word_node *next;
} word_node;

void printNode(word_node *node)
{
    if (!node)
    {
        printf("null\n");
        return;
    }
    uint32_t hash = oaat(*node->word, strlen(*node->word), NUM_BITS);

    printf("%s : %d next? ", *node->word, hash);
    printNode(node->next);
}

void insert(word_node *hash_table[], char **word, uint32_t len)
{
    word_node *node = malloc(sizeof(word_node));
    if (node == NULL)
    {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }

    uint32_t hash = oaat(*word, len, NUM_BITS);
    node->word = word;
    node->next = hash_table[hash];
    hash_table[hash] = node;
}

bool in_hash_table(word_node *hash_table[], char *find, uint32_t find_len)
{
    uint32_t hash = oaat(find, find_len, NUM_BITS);
    word_node *cur = hash_table[hash];

    while (cur)
    {
        if ((strlen(*(cur->word)) == find_len) && (strncmp(find, *(cur->word), find_len) == 0))
        {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

bool is_compound(word_node *hash_table[], char *word)
{
    uint32_t len = strlen(word);
    int i;
    for (i = 1; i < len; i++)
    {
        if (in_hash_table(hash_table, word, i) && in_hash_table(hash_table, &word[i], len - i))
        {
            return true;
        }
    }
    return false;
}

#define NUM_BUCKETS 2 << NUM_BITS

word_node *hash_table[NUM_BUCKETS] = {NULL};

/* assume we'll never have more than NUM_BUCKETS words? */
char *words[NUM_BUCKETS] = {NULL};

int main(void)
{
    int word_num = 0;

    char *word = read_line(16);
    while (*word)
    {
        words[word_num] = word;
        insert(hash_table, &words[word_num], strlen(word));
        word_num++;
        word = read_line(16);
    }

    int i;
    for (i = 0; i < word_num; i++)
    {
        if (is_compound(hash_table, words[i]))
        {
            puts(words[i]);
        }
    }

    return EXIT_SUCCESS;
}
