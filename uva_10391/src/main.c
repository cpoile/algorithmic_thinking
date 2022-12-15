#include <inttypes.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

uint32_t oaat(char *key, uint32_t len, uint32_t bits) {
    uint32_t hash = 0;
    for (uint32_t i = 0; i < len; i++) {
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

bool in_hash_table(word_node *hash_table[], char *find, uint32_t find_len)
{
    uint32_t word_code;
    uint32_t hash = oaat(find, find_len, NUM_BITS);
    word_node *cur = hash_table[hash];
    while (cur)
    {
        if ((strlen(cur->word) == find_len) && (strncmp(find, cur->word, find_len) == 0))
        {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

bool is_compound(word_node *hash_table[], char *word) {
    uint32_t len = strlen(word);
    for (int i = 1; i < len-1; i++) {
        if (in_hash_table(hash_table, word, i) && in_hash_table(hash_table, word[i], len-i)) {
            return true;
        }
    }
    return false;
}

int main()
{
    
}