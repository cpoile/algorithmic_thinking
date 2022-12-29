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


// a flexible array (not working yet)
typedef struct person_array {
    int cap, pos;
    person *array[];
} person_array;

person_array append(person_array arr, person *p) {
    if (arr.pos >= arr.cap) {
        if (arr.cap == 0) {
            arr.cap = 8;
        } else {
            arr.cap *= 2;
        }
        arr.array = realloc(arr.array, sizeof(person *) * arr.cap);
        if (arr.array == NULL) {
            fprintf(stderr, "error reallocating arr.array\n");
            return (person_array) {0};
        }
    }
    arr.array[arr.pos++] = p;
    return arr;
}

person *find_or_create(person_array *arr, char *name) {
    person *found = find(arr, name);
    if (!found) {
        found = calloc(1, sizeof(person));
        strlcpy(found->name, name, MAX_NAME_SIZE);
        *arr = append(*arr, found);
    }
    return found;
}
