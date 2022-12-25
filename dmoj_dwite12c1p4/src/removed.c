#define MAX_LEN 257

void print_node(char buf[], size_t *pos, node *n) {
    if (n->c) {
        *pos += snprintf(buf + *pos, MAX_LEN - *pos, "%d", n->c);
        return;
    }
    if (n->left) {
        buf[(*pos)++] = '(';
        print_node(buf, pos, n->left);
        buf[(*pos)++] = ' ';
    }
    if (n->right) {
        print_node(buf, pos, n->right);
    }
    buf[(*pos)++] = ')';
}

void print_tree(char buf[], size_t *pos, node *root) {
    print_node(buf, pos, root);
    buf[(*pos)++] = '\0';
}
