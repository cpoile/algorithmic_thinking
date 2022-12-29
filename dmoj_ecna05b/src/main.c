#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define MAX_NAME_SIZE 21
typedef struct person person;

typedef struct person_array {
    int cap, pos;
    person *array[];
} person_array;

struct person {
    char name[MAX_NAME_SIZE];
    person_array *children;
};

person *new_person(char *name)
{
    person *p = calloc(1, sizeof(person));
    if (p == NULL) {
        fprintf(stderr, "error allocating person\n");
        return NULL;
    }
    strcpy(p->name, name);
    assert(p->children == NULL);

    return p;
}

person_array *append(person_array *arr, person *p)
{
    if (!arr) {
        arr = (person_array *) calloc(1, sizeof(person_array));
    }
    if (arr->pos >= arr->cap) {
        int cap;
        int pos = arr->pos;
        if (arr->cap == 0) {
            cap = 8;
        } else {
            cap = arr->cap * 2;
        }
        arr = (person_array *) realloc(arr, sizeof(person_array) + sizeof(person *) * cap);
        if (arr == NULL) {
            fprintf(stderr, "error reallocating arr\n");
            return NULL;
        }
        arr->cap = cap;
        arr->pos = pos;
    }
    arr->array[arr->pos] = p;
    arr->pos++;
    return arr;
}

void add_child(person *parent, person *child)
{
    parent->children = append(parent->children, child);
}

person *find(person_array *arr, char *name)
{
    if (!arr) {
        return NULL;
    }
    for (int i = 0; i < arr->pos; i++) {
        if (strcmp(arr->array[i]->name, name) == 0) {
            return arr->array[i];
        }
    }
    return NULL;
}

person *find_or_create(person_array **arr, char *name)
{
    person *found = find(*arr, name);
    if (!found) {
        found = new_person(name);
        *arr = append(*arr, found);
    }
    return found;
}

void print(person_array *arr)
{
    for (int i = 0; i < arr->pos; i++) {
        uint32_t num_children = 0;
        if (arr->array[i]->children) {
            num_children = arr->array[i]->children->pos;
        }
        printf("%s, c: %d ; ", arr->array[i]->name, num_children);
    }
    printf("\n");
}

typedef struct result {
    char *name;
    int num_descedents;
} result;

void count(person *p, uint32_t generation, result *res)
{
    int num_children = 0;
    if (p->children) {
        num_children = p->children->pos;
    }

    if (generation == 1) {
        res->num_descedents += num_children;
        return;
    }

    for (int i = 0; i < num_children; i++) {
        count(p->children->array[i], generation - 1, res);
    }
}

int comp_res(const void *a, const void *b)
{
    result arg1 = *(const result *) a;
    result arg2 = *(const result *) b;

    if (arg1.num_descedents == arg2.num_descedents) {
        return strcmp(arg1.name, arg2.name);
    }
    return arg2.num_descedents - arg1.num_descedents; // poss underflow? but not for this exercise.
}

int main(void)
{
    //freopen("in1.txt", "r", stdin);

    uint32_t cases;
    scanf("%d", &cases);

    for (uint32_t i = 0; i < cases; i++) {
        person_array *all_people = NULL;

        uint32_t lines, target_depth;
        scanf("%d %d", &lines, &target_depth);

        for (uint32_t j = 0; j < lines; j++) {
            char name[MAX_NAME_SIZE] = {0};
            uint32_t children;
            scanf("%s %d", name, &children);

            person *parent = find_or_create(&all_people, name);

            for (uint32_t k = 0; k < children; k++) {
                char child_name[MAX_NAME_SIZE] = {0};
                scanf("%s", child_name);
                person *child = find_or_create(&all_people, child_name);
                add_child(parent, child);
            }
        }

        // Now count the number of generations (target_depth)
        int len = all_people->pos;
        result results[len];

        for (int j = 0; j < len; j++) {
            results[j].name = all_people->array[j]->name;
            results[j].num_descedents = 0;
            count(all_people->array[j], target_depth, &results[j]);
        }

        qsort(results, len, sizeof(result), comp_res);

        printf("Tree %d:\n", i + 1);

        int last_num = results[0].num_descedents;
        int count = 3;
        int pos = 0;
        while (count > 0 && pos < len && results[pos].num_descedents > 0) {
            printf("%s %d\n", results[pos].name, results[pos].num_descedents);
            pos++;
            if (results[pos].num_descedents != last_num) {
                count--;
                last_num = results[pos].num_descedents;
            }
        }

        if (i + 1 < cases) {
            printf("\n");
        }
    }

    return EXIT_SUCCESS;
}
