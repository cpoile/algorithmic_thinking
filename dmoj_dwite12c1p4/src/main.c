#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
    int c;
    node *left, *right;
};

node *new_node() {
    node *n = malloc(sizeof(node));
    n->c = 0;
    n->left = NULL;
    n->right = NULL;
    return n;
}

node *parse_node(char str[], size_t *pos) {
    node *n = new_node();
    if (str[*pos] == '(') {
        (*pos)++;
        n->left = parse_node(str, pos);
        assert(str[(*pos)++] == ' ');
        n->right = parse_node(str, pos);
        assert(str[(*pos)++] == ')');
    } else {
        char buf[3];
        size_t i = 0;
        while (str[*pos] != ')' && str[*pos] != ' ' && str[*pos] != '\0') {
            buf[i++] = str[(*pos)++];
        }
        buf[i] = '\0';
        n->c = atoi(buf);
        char d = str[*pos];
        assert(d == ')' || d == ' ' || d == '\0');
    }
    return n;
}

typedef struct {
    uint8_t r, c, cur_len, max_len;
} ret;

void count(node *root, ret *state) {
    if (root->c) {
        state->c += root->c;
        if (state->cur_len > state->max_len) state->max_len = state->cur_len;
    }
    if (root->left) {
        state->r += 1;
        state->cur_len++;
        count(root->left, state);
        state->r += 1;
    }
    if (root->right) {
        state->r += 1;
        state->cur_len++;
        count(root->right, state);
        state->r += 1;
    }
    state->cur_len--;
}

int main() {
    size_t cap = 257;
    char *buf;
    buf = malloc(sizeof(*buf) * cap);

    while (getline(&buf, &cap, stdin) > 0) {
        size_t pos = 0;
        node *t = parse_node(buf, &pos);

        ret counts = {};
        count(t, &counts);
        uint8_t r = counts.r - counts.max_len;

        printf("%d %d\n", r, counts.c);
    }

    return EXIT_SUCCESS;
}
